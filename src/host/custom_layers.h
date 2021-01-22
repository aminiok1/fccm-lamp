#ifndef CUSTOM_LAYERS_H
#define CUSTOM_LAYERS_H

#include "defines.h"

int custom_layers_top(volatile dtype *data_in, dtype *data_out);
void global_average_pool(volatile dtype *data_in, dtype* data_out);
void dense(dtype *data_in, dtype* data_out);
void sigmoid(dtype *data_in, dtype* data_out);

#endif

