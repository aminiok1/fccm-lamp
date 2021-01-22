/*
 * Copyright 2019 Xilinx Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <sys/time.h>

/* header file OpenCV for image processing */
#include <opencv2/opencv.hpp>

/* header file for Vitis AI advanced API */
#include <dnndk/dnndk.h>

/* header file for Caffe input images APIs */
#include "dputils.h"

using namespace std;
using namespace cv;

/* 7.71 GOP MAdds for Lamp */
#define LAMP_WORKLOAD (7.71f)
/* DPU Kernel name for Lamp */
#define KRENEL_LAMP "lamp_0"
/* Input Node for Kernel Lamp */
#define INPUT_NODE      "conv1"
/* Output Node for Kernel Lamp */
#define OUTPUT_NODE     "fc1000"

const string baseImagePath = "../dataset/image500_640_480/";


struct timeval timer;
struct timeval start_timer;

unsigned long TimerRead(){
   gettimeofday(&timer, NULL);
   //return (timer.tv_sec - start_timer.tv_sec) * 1000 + (timer.tv_usec - start_timer.tv_usec) / 1000 ;
   return (timer.tv_usec - start_timer.tv_usec) ;
}

void TimerOn(){
   gettimeofday(&start_timer, NULL);
}


/**
 * @brief put image names to a vector
 *
 * @param path - path of the image direcotry
 * @param images - the vector of image name
 *
 * @return none
 */
void ListImages(string const &path, vector<string> &images) {
    images.clear();
    struct dirent *entry;

    /*Check if path is a valid directory path. */
    struct stat s;
    lstat(path.c_str(), &s);
    if (!S_ISDIR(s.st_mode)) {
        fprintf(stderr, "Error: %s is not a valid directory!\n", path.c_str());
        exit(1);
    }

    DIR *dir = opendir(path.c_str());
    if (dir == nullptr) {
        fprintf(stderr, "Error: Open %s path failed.\n", path.c_str());
        exit(1);
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG || entry->d_type == DT_UNKNOWN) {
            string name = entry->d_name;
            string ext = name.substr(name.find_last_of(".") + 1);
            if ((ext == "JPEG") || (ext == "jpeg") || (ext == "JPG") ||
                (ext == "jpg") || (ext == "PNG") || (ext == "png")) {
                images.push_back(name);
            }
        }
    }

    closedir(dir);
    sort(images.begin(), images.end());
}

/**
 * @brief load kinds from file to a vector
 *
 * @param path - path of the kinds file
 * @param kinds - the vector of kinds string
 *
 * @return none
 */
void LoadWords(string const &path, vector<string> &kinds) {
    kinds.clear();
    fstream fkinds(path);
    if (fkinds.fail()) {
        fprintf(stderr, "Error : Open %s failed.\n", path.c_str());
        exit(1);
    }
    string kind;
    while (getline(fkinds, kind)) {
        kinds.push_back(kind);
    }

    fkinds.close();
}

/**
 * @brief Get top k results according to its probability
 *
 * @param d - pointer to input data
 * @param size - size of input data
 * @param k - calculation result
 * @param vkinds - vector of kinds
 *
 * @return none
 */
void TopK(const float *d, int size, int k, vector<string> &vkinds) {
    assert(d && size > 0 && k > 0);
    priority_queue<pair<float, int>> q;

    for (auto i = 0; i < size; ++i) {
        q.push(pair<float, int>(d[i], i));
    }

    for (auto i = 0; i < k; ++i) {
        pair<float, int> ki = q.top();
        printf("top[%d] prob = %-8f  name = %s\n", i, d[ki.second],
        vkinds[ki.second].c_str());
        q.pop();
    }
}

/**
 * @brief Run DPU Task for Lamp
 *
 * @param taskResnet50 - pointer to Lamp Task
 *
 * @return none
 */
void runResnet50(DPUTask *taskResnet50) {
    assert(taskResnet50);

    /* Mean value for Lamp specified in Caffe prototxt */
    vector<string> kinds, images;
    unsigned long start_t,end_t;
    /* Load all image names.*/
    ListImages(baseImagePath, images);
    if (images.size() == 0) {
        cerr << "\nError: No images existing under " << baseImagePath << endl;
        return;
    }

    /* Load all kinds words.*/
    LoadWords(baseImagePath + "words.txt", kinds);
    if (kinds.size() == 0) {
        cerr << "\nError: No words exist in file words.txt." << endl;
        return;
    }

    /* Get the output Tensor for Resnet50 Task  */
    int8_t *outAddr = (int8_t *)dpuGetOutputTensorAddress(taskResnet50, OUTPUT_NODE);
    /* Get size of the output Tensor for Resnet50 Task  */
    int size = dpuGetOutputTensorSize(taskResnet50, OUTPUT_NODE);
    /* Get channel count of the output Tensor for Lamp Task  */
    int channel = dpuGetOutputTensorChannel(taskResnet50, OUTPUT_NODE);
    /* Get scale of the output Tensor for Resnet50 Task  */
    float out_scale = dpuGetOutputTensorScale(taskResnet50, OUTPUT_NODE);
    float *softmax = new float[size];
    
    TimerOn();
	
    for (auto &imageName : images) {
        cout << "\nLoad image : " << imageName << endl;
        /* Load image and Set image into DPU Task for Lamp */
        Mat image = imread(baseImagePath + imageName);
        dpuSetInputImage2(taskResnet50, INPUT_NODE, image);

        /* Launch RetNet50 Task */
        cout << "\nRun DPU Task for Lamp ..." << endl;

        start_t = TimerRead();
        dpuRunTask(taskResnet50);
		end_t = TimerRead();
		printf("elapsed time = %lu - %lu = %lu\n", end_t, start_t, end_t-start_t);
		
        /* Get DPU execution time (in us) of DPU Task */
        long long timeProf = dpuGetTaskProfile(taskResnet50);
        cout << "  DPU Task Execution time: " << (timeProf * 1.0f) << "us\n";
        float prof = (LAMP_WORKLOAD / timeProf) * 1000000.0f;
        cout << "  DPU Task Performance: " << prof << "GOPS\n";

        /* Calculate softmax on DPU and display TOP-5 classification results */
        dpuRunSoftmax(outAddr, softmax, channel, size/channel, out_scale);
        TopK(softmax, channel, 5, kinds);

        /* Display the impage */
        //cv::imshow("Classification of Lamp", image);
        //cv::waitKey(1);
    }

    delete[] softmax;
}

/**
 * @brief Entry for runing Lamp neural network
 *
 * @note Vitis AI advanced APIs prefixed with "dpu" are used to easily program &
 *       deploy Lamp on DPU platform.
 *
 */
int main(void) {
    /* DPU Kernel/Task for running Lamp */
    DPUKernel *kernelResnet50;
    DPUTask *taskResnet50;

    /* Attach to DPU driver and prepare for running */
    dpuOpen();

    /* Load DPU Kernel for Lamp */
    kernelResnet50 = dpuLoadKernel(KRENEL_LAMP);

    /* Create DPU Task for Lamp */
    taskResnet50 = dpuCreateTask(kernelResnet50, 0);

    /* Run Lamp Task */
    runResnet50(taskResnet50);

    /* Destroy DPU Task & free resources */
    dpuDestroyTask(taskResnet50);

    /* Destroy DPU Kernel & free resources */
    dpuDestroyKernel(kernelResnet50);

    /* Dettach from DPU driver & free resources */
    dpuClose();

    return 0;
}

// Fixed point implementation of layers on ARM
/*
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "custom_layers.h"
#include "weights.h"


struct timeval timer;
struct timeval start_timer;

unsigned long TimerRead(){
   gettimeofday(&timer, NULL);
   //return (timer.tv_sec - start_timer.tv_sec) * 1000 + (timer.tv_usec - start_timer.tv_usec) / 1000 ;
   return (timer.tv_usec - start_timer.tv_usec) ;
}

void TimerOn(){
   gettimeofday(&start_timer, NULL);
}


int main()
{
	dtype data_in[WINDOW_SIZE*OUTPUT_SIZE];
	dtype data_out[OUTPUT_SIZE];
	unsigned long start_t,end_t;


	for (int i = 0; i < WINDOW_SIZE*OUTPUT_SIZE; i++)
		data_in[i] = i % 20;
	TimerOn();
	for (int i = 0; i < 10; i++)
	{
		start_t = TimerRead();
		custom_layers_top(data_in, data_out);
		end_t = TimerRead();

		printf("elapsed time = %lu - %lu = %lu\n", end_t, start_t, end_t-start_t);
    }

	return 0;
}
int custom_layers_top(volatile dtype *data_in, dtype *data_out)
{
	dtype gap_out[GAP_SHAPE];
	dtype dense_out[OUTPUT_SIZE];

	global_average_pool(data_in, gap_out);
	dense(gap_out, dense_out);
	sigmoid(dense_out, data_out);

	return 0;
}


void global_average_pool(volatile dtype *data_in, dtype* data_out)
{
	dtype buffer[WINDOW_SIZE];
	dtype sum = 0;
	int i;

	 for (i = 0; i < GAP_SHAPE; i++)
	{
		memcpy(buffer, (const dtype*)(data_in + (i*WINDOW_SIZE)), WINDOW_SIZE*sizeof(dtype));

		sum = 0;
		for (int j = 0; j < WINDOW_SIZE; j++)
			sum += buffer[j];
			//fix16_add(sum, buffer[j]);
		data_out[i] = sum / dtype(WINDOW_SIZE);
		//data_out[i] = fix16_div(sum, WINDOW_SIZE);

	}

}

void dense(dtype *data_in, dtype* data_out)
{
	static dtype acc, mul;
	int i, j;

	for (i = 0; i < OUTPUT_SIZE; i++)
	{
		acc = 0;
		for (j = 0; j < GAP_SHAPE; j++)
		{
			mul = data_in[j] * WEIGHTS[j][i];
			//mul = fix16_mul(data_in[j], WEIGHTS[j][i]);
			acc += mul;
			//acc = fix16_add(mul, acc);
		}

		acc += BIAS[i];
		//acc = fix16_add(acc, BIAS[i]);
		data_out[i] = acc;
	}

}

void sigmoid(dtype *data_in, dtype* data_out)
{
	int i, j;
	dtype tmp, result[OUTPUT_SIZE];

	for (i = 0 ; i < OUTPUT_SIZE; i++)
	{
		tmp = data_in[i];

		if (tmp >= dtype(0) && tmp < dtype(3.4))
			result[i] = ((((dtype(0.75)) * tmp) / (dtype(1) + (tmp / dtype(2)))) + dtype(1)) ;

		else if (tmp >= dtype(3.4) && tmp < dtype(6))
			result[i] = (dtype(1.935409070603099) + (dtype(0.0458812946797165) * ((tmp / dtype(2)) - dtype(1.7))));

		else if (tmp > dtype(6))
			result[i] = dtype(1.99505475368673);

		else if (tmp <= dtype(0) && tmp > dtype(-3.4))
			result[i] = (dtype(-1) * ((dtype(-1.5/2) * tmp) / (dtype(1) + ((dtype(-1) * tmp)  / dtype(2)))) + dtype(1));

		else if (tmp <= dtype(-3.4) && tmp > dtype(-6))
			result[i] = (dtype(1) - (dtype(0.935409070603099) + (dtype(0.0458812946797165) * (((dtype(-1)*tmp) / dtype(2)) - dtype(1.7)))));

		else if (tmp <= dtype(-6))
			result[i] = dtype(0.00494524631327) ;

		result[i] = result[i] / dtype(2);
		//result[i] = fix16_div(result[i], 2);

	}

	memcpy(data_out, (const dtype*)result, OUTPUT_SIZE*sizeof(dtype));
}

*/