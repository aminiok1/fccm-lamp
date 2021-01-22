// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XCUSTOM_LAYERS_CUSTOM_LAYERS_H
#define XCUSTOM_LAYERS_CUSTOM_LAYERS_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xcustom_layers_custom_layers_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XCustom_layers_custom_layers_Config;
#endif

typedef struct {
    u32 Control_BaseAddress;
    u32 IsReady;
} XCustom_layers_custom_layers;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XCustom_layers_custom_layers_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XCustom_layers_custom_layers_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XCustom_layers_custom_layers_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XCustom_layers_custom_layers_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XCustom_layers_custom_layers_Initialize(XCustom_layers_custom_layers *InstancePtr, u16 DeviceId);
XCustom_layers_custom_layers_Config* XCustom_layers_custom_layers_LookupConfig(u16 DeviceId);
int XCustom_layers_custom_layers_CfgInitialize(XCustom_layers_custom_layers *InstancePtr, XCustom_layers_custom_layers_Config *ConfigPtr);
#else
int XCustom_layers_custom_layers_Initialize(XCustom_layers_custom_layers *InstancePtr, const char* InstanceName);
int XCustom_layers_custom_layers_Release(XCustom_layers_custom_layers *InstancePtr);
#endif

void XCustom_layers_custom_layers_Start(XCustom_layers_custom_layers *InstancePtr);
u32 XCustom_layers_custom_layers_IsDone(XCustom_layers_custom_layers *InstancePtr);
u32 XCustom_layers_custom_layers_IsIdle(XCustom_layers_custom_layers *InstancePtr);
u32 XCustom_layers_custom_layers_IsReady(XCustom_layers_custom_layers *InstancePtr);
void XCustom_layers_custom_layers_EnableAutoRestart(XCustom_layers_custom_layers *InstancePtr);
void XCustom_layers_custom_layers_DisableAutoRestart(XCustom_layers_custom_layers *InstancePtr);
u32 XCustom_layers_custom_layers_Get_return(XCustom_layers_custom_layers *InstancePtr);

void XCustom_layers_custom_layers_Set_in_r(XCustom_layers_custom_layers *InstancePtr, u64 Data);
u64 XCustom_layers_custom_layers_Get_in_r(XCustom_layers_custom_layers *InstancePtr);
void XCustom_layers_custom_layers_Set_out_r(XCustom_layers_custom_layers *InstancePtr, u64 Data);
u64 XCustom_layers_custom_layers_Get_out_r(XCustom_layers_custom_layers *InstancePtr);

void XCustom_layers_custom_layers_InterruptGlobalEnable(XCustom_layers_custom_layers *InstancePtr);
void XCustom_layers_custom_layers_InterruptGlobalDisable(XCustom_layers_custom_layers *InstancePtr);
void XCustom_layers_custom_layers_InterruptEnable(XCustom_layers_custom_layers *InstancePtr, u32 Mask);
void XCustom_layers_custom_layers_InterruptDisable(XCustom_layers_custom_layers *InstancePtr, u32 Mask);
void XCustom_layers_custom_layers_InterruptClear(XCustom_layers_custom_layers *InstancePtr, u32 Mask);
u32 XCustom_layers_custom_layers_InterruptGetEnabled(XCustom_layers_custom_layers *InstancePtr);
u32 XCustom_layers_custom_layers_InterruptGetStatus(XCustom_layers_custom_layers *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
