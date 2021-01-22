// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xcustom_layers_custom_layers.h"

extern XCustom_layers_custom_layers_Config XCustom_layers_custom_layers_ConfigTable[];

XCustom_layers_custom_layers_Config *XCustom_layers_custom_layers_LookupConfig(u16 DeviceId) {
	XCustom_layers_custom_layers_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XCUSTOM_LAYERS_CUSTOM_LAYERS_NUM_INSTANCES; Index++) {
		if (XCustom_layers_custom_layers_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XCustom_layers_custom_layers_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XCustom_layers_custom_layers_Initialize(XCustom_layers_custom_layers *InstancePtr, u16 DeviceId) {
	XCustom_layers_custom_layers_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XCustom_layers_custom_layers_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XCustom_layers_custom_layers_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

