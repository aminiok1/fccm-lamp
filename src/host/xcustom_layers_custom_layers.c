// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xcustom_layers_custom_layers.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XCustom_layers_custom_layers_CfgInitialize(XCustom_layers_custom_layers *InstancePtr, XCustom_layers_custom_layers_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XCustom_layers_custom_layers_Start(XCustom_layers_custom_layers *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_AP_CTRL) & 0x80;
    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XCustom_layers_custom_layers_IsDone(XCustom_layers_custom_layers *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XCustom_layers_custom_layers_IsIdle(XCustom_layers_custom_layers *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XCustom_layers_custom_layers_IsReady(XCustom_layers_custom_layers *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XCustom_layers_custom_layers_EnableAutoRestart(XCustom_layers_custom_layers *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XCustom_layers_custom_layers_DisableAutoRestart(XCustom_layers_custom_layers *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_AP_CTRL, 0);
}

u32 XCustom_layers_custom_layers_Get_return(XCustom_layers_custom_layers *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_AP_RETURN);
    return Data;
}
void XCustom_layers_custom_layers_Set_in_r(XCustom_layers_custom_layers *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_IN_R_DATA, (u32)(Data));
    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_IN_R_DATA + 4, (u32)(Data >> 32));
}

u64 XCustom_layers_custom_layers_Get_in_r(XCustom_layers_custom_layers *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_IN_R_DATA);
    Data += (u64)XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_IN_R_DATA + 4) << 32;
    return Data;
}

void XCustom_layers_custom_layers_Set_out_r(XCustom_layers_custom_layers *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_OUT_R_DATA, (u32)(Data));
    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_OUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XCustom_layers_custom_layers_Get_out_r(XCustom_layers_custom_layers *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_OUT_R_DATA);
    Data += (u64)XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_OUT_R_DATA + 4) << 32;
    return Data;
}

void XCustom_layers_custom_layers_InterruptGlobalEnable(XCustom_layers_custom_layers *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_GIE, 1);
}

void XCustom_layers_custom_layers_InterruptGlobalDisable(XCustom_layers_custom_layers *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_GIE, 0);
}

void XCustom_layers_custom_layers_InterruptEnable(XCustom_layers_custom_layers *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_IER);
    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_IER, Register | Mask);
}

void XCustom_layers_custom_layers_InterruptDisable(XCustom_layers_custom_layers *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_IER);
    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_IER, Register & (~Mask));
}

void XCustom_layers_custom_layers_InterruptClear(XCustom_layers_custom_layers *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCustom_layers_custom_layers_WriteReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_ISR, Mask);
}

u32 XCustom_layers_custom_layers_InterruptGetEnabled(XCustom_layers_custom_layers *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_IER);
}

u32 XCustom_layers_custom_layers_InterruptGetStatus(XCustom_layers_custom_layers *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCustom_layers_custom_layers_ReadReg(InstancePtr->Control_BaseAddress, XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_ISR);
}

