// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of ap_return
//        bit 31~0 - ap_return[31:0] (Read)
// 0x18 : Data signal of in_r
//        bit 31~0 - in_r[31:0] (Read/Write)
// 0x1c : Data signal of in_r
//        bit 31~0 - in_r[63:32] (Read/Write)
// 0x20 : reserved
// 0x24 : Data signal of out_r
//        bit 31~0 - out_r[31:0] (Read/Write)
// 0x28 : Data signal of out_r
//        bit 31~0 - out_r[63:32] (Read/Write)
// 0x2c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_AP_CTRL    0x00
#define XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_GIE        0x04
#define XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_IER        0x08
#define XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_ISR        0x0c
#define XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_AP_RETURN  0x10
#define XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_BITS_AP_RETURN  32
#define XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_IN_R_DATA  0x18
#define XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_BITS_IN_R_DATA  64
#define XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_ADDR_OUT_R_DATA 0x24
#define XCUSTOM_LAYERS_CUSTOM_LAYERS_CONTROL_BITS_OUT_R_DATA 64

