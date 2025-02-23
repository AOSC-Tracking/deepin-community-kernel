/*
 * Copyright © 2021 Glenfly Tech Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */


#include "CBiosChipShare.h"
#include "CBiosChipFunc.h"


CBIOS_VOID cbSetCRTimingReg(PCBIOS_VOID pvcbe, PCBIOS_TIMING_ATTRIB pTiming, CBIOS_U32 IGAIndex, CBIOS_TIMING_FLAGS Flags)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);

    if (pFuncTbl->pfncbSetCRTimingReg != CBIOS_NULL)
    {
        pFuncTbl->pfncbSetCRTimingReg(pcbe, pTiming, IGAIndex, Flags);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbSetCRTimingReg: function not implemented! Fatal Error\n"));
    }
}

CBIOS_VOID cbSetSRTimingReg(PCBIOS_VOID pvcbe, PCBIOS_TIMING_ATTRIB pTiming, CBIOS_U32 IGAIndex, CBIOS_TIMING_FLAGS Flags)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);

    if (pFuncTbl->pfncbSetSRTimingReg != CBIOS_NULL)
    {
        pFuncTbl->pfncbSetSRTimingReg(pcbe, pTiming, IGAIndex, Flags);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbSetSRTimingReg: function not implemented! Fatal Error\n"));
    }
}

CBIOS_VOID cbGetModeInfoFromReg(PCBIOS_VOID pvcbe,
                                          CBIOS_ACTIVE_TYPE ulDevice,
                                          PCBIOS_TIMING_ATTRIB pTiming,
                                          PCBIOS_TIMING_FLAGS pFlags,
                                          CBIOS_U32  IGAIndex,
                                          CBIOS_TIMING_REG_TYPE TimingRegType)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);

    if (pFuncTbl->pfncbGetModeInfoFromReg != CBIOS_NULL)
    {
        pFuncTbl->pfncbGetModeInfoFromReg(pcbe, ulDevice, pTiming, pFlags, IGAIndex, TimingRegType);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbGetModeInfoFromReg: function not implemented!\n"));
    }
}

CBIOS_BOOL cbInitVCP(PCBIOS_VOID pvcbe, PCBIOS_VOID pVCPInfo, PCBIOS_VOID pRomBase)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PVCP_INFO pVCP = (PVCP_INFO)pVCPInfo;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);
    CBIOS_BOOL bStatus = CBIOS_FALSE;

    if (pFuncTbl->pfncbInitVCP != CBIOS_NULL)
    {
        bStatus = pFuncTbl->pfncbInitVCP(pcbe, pVCP, pRomBase);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbInitVCP: function not implemented!\n"));
        bStatus = CBIOS_FALSE;
    }
    return bStatus;
}

CBIOS_VOID cbDoHDTVFuncSetting(PCBIOS_VOID pvcbe,
                             PCBIOS_DISP_MODE_PARAMS pModeParams,
                             CBIOS_U32 IGAIndex,
                             CBIOS_ACTIVE_TYPE ulDevices)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);

    if (pFuncTbl->pfncbDoHDTVFuncSetting != CBIOS_NULL)
    {
        pFuncTbl->pfncbDoHDTVFuncSetting(pcbe, pModeParams, IGAIndex, ulDevices);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbDoHDTVFuncSetting: function not implemented!\n"));
    }
}

CBIOS_VOID cbLoadSSC(PCBIOS_VOID pvcbe, CBIOS_U32 CenterFreq, CBIOS_U8 IGAIndex, CBIOS_ACTIVE_TYPE LCDType)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);

    if (pFuncTbl->pfncbLoadSSC != CBIOS_NULL)
    {
        pFuncTbl->pfncbLoadSSC(pcbe, CenterFreq, IGAIndex, LCDType);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbLoadSSC: function not implemented!\n"));
    }
}

CBIOS_VOID cbEnableSpreadSpectrum(PCBIOS_VOID pvcbe, CBIOS_U8 IGAIndex)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);

    if (pFuncTbl->pfncbEnableSpreadSpectrum != CBIOS_NULL)
    {
        pFuncTbl->pfncbEnableSpreadSpectrum(pcbe, IGAIndex);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbEnableSpreadSpectrum: function not implemented!\n"));
    }
}

CBIOS_VOID cbDisableSpreadSpectrum(PCBIOS_VOID pvcbe, CBIOS_U8 IGAIndex)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);

    if (pFuncTbl->pfncbDisableSpreadSpectrum != CBIOS_NULL)
    {
        pFuncTbl->pfncbDisableSpreadSpectrum(pcbe, IGAIndex);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbDisableSpreadSpectrum: function not implemented!\n"));
    }
}

CBIOS_STATUS cbInterruptEnableDisable(PCBIOS_VOID pvcbe, PCBIOS_INT_ENABLE_DISABLE_PARA pIntPara)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    if (pFuncTbl->pfncbInterruptEnableDisable != CBIOS_NULL)
    {
        Status = pFuncTbl->pfncbInterruptEnableDisable(pcbe, pIntPara);
    }
    else
    {
        Status = CBIOS_ER_NOT_YET_IMPLEMENTED;
    }
    return Status;
}

CBIOS_STATUS cbCECEnableDisable(PCBIOS_VOID pvcbe, PCBIOS_CEC_ENABLE_DISABLE_PARA pCECEnableDisablePara)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    if (pFuncTbl->pfncbCECEnableDisable != CBIOS_NULL)
    {
        Status = pFuncTbl->pfncbCECEnableDisable(pcbe, pCECEnableDisablePara);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(HDMI, ERROR), "cbCECEnableDisable: function not implemented!\n"));
        Status = CBIOS_ER_NOT_YET_IMPLEMENTED;
    }
    return Status;
}

CBIOS_STATUS cbSetGamma(PCBIOS_VOID pvcbe, PCBIOS_GAMMA_PARA pGammaParam)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    if (pFuncTbl->pfncbSetGamma != CBIOS_NULL)
    {
        Status = pFuncTbl->pfncbSetGamma(pcbe, pGammaParam);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbSetGamma: function not implemented!\n"));
        Status = CBIOS_ER_NOT_YET_IMPLEMENTED;
    }
    return Status;
}

CBIOS_STATUS cbUpdateFrame(PCBIOS_VOID pvcbe, PCBIOS_UPDATE_FRAME_PARA pUpdateFrame)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    if (pFuncTbl->pfncbUpdateFrame != CBIOS_NULL)
    {
        Status = pFuncTbl->pfncbUpdateFrame(pcbe, pUpdateFrame);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbUpdateFrame: function not implemented!\n"));
        Status = CBIOS_ER_NOT_YET_IMPLEMENTED;
    }
    return Status;
}

CBIOS_STATUS cbDoCSCAdjust(PCBIOS_VOID pvcbe, CBIOS_ACTIVE_TYPE Device, PCBIOS_CSC_ADJUST_PARA pCSCAdjustPara)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    if (pFuncTbl->pfncbDoCSCAdjust != CBIOS_NULL)
    {
        Status = pFuncTbl->pfncbDoCSCAdjust(pcbe, Device, pCSCAdjustPara);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbDoCSCAdjust: function not implemented!\n"));
        Status = CBIOS_ER_NOT_YET_IMPLEMENTED;
    }

    return Status;
}

CBIOS_STATUS cbAdjustStreamCSC(PCBIOS_VOID pvcbe, PCBIOS_STREAM_CSC_PARA pCSCAdjustPara)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    if (pFuncTbl->pfncbAdjustStreamCSC != CBIOS_NULL)
    {
        Status = pFuncTbl->pfncbAdjustStreamCSC(pcbe, pCSCAdjustPara);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbDoCSCAdjust: function not implemented!\n"));
        Status = CBIOS_ER_NOT_YET_IMPLEMENTED;
    }

    return Status;
}

CBIOS_STATUS cbCheckSurfaceOnDisplay(PCBIOS_VOID pvcbe, PCBIOS_CHECK_SURFACE_ON_DISP pChkSurfacePara)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    if (pFuncTbl->pfncbCheckSurfaceOnDisplay != CBIOS_NULL)
    {
        Status = pFuncTbl->pfncbCheckSurfaceOnDisplay(pcbe, pChkSurfacePara);
    }
    else
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "cbCheckSurfaceOnDisplay: function not implemented!\n"));
        Status = CBIOS_ER_NOT_YET_IMPLEMENTED;
    }
    return Status;
}

CBIOS_STATUS  cbGetDispAddr(PCBIOS_VOID  pvcbe,  PCBIOS_GET_DISP_ADDR   pGetDispAddr)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    if (pFuncTbl->pfncbGetDispAddr != CBIOS_NULL)
    {
        Status = pFuncTbl->pfncbGetDispAddr(pcbe, pGetDispAddr);
    }
    else
    {
        Status = CBIOS_ER_NOT_YET_IMPLEMENTED;
    }
    return Status;
}

CBIOS_STATUS cbSetHwCursor(PCBIOS_VOID pvcbe, PCBIOS_CURSOR_PARA pSetCursor)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);
    CBIOS_STATUS Status = CBIOS_ER_NOT_YET_IMPLEMENTED;

    if (pFuncTbl->pfncbSetHwCursor != CBIOS_NULL)
    {
        Status = pFuncTbl->pfncbSetHwCursor(pcbe, pSetCursor);
    }
    else
    {
        Status = CBIOS_ER_NOT_YET_IMPLEMENTED;
    }
    return Status;
}

CBIOS_VOID cbDisableStream(PCBIOS_VOID pvcbe, CBIOS_U32 IGAIndex)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    PCBIOS_CHIP_FUNC_TABLE pFuncTbl = &(pcbe->ChipFuncTbl);
    if(pFuncTbl->pfncbDisableStream != CBIOS_NULL)
    {
        pFuncTbl->pfncbDisableStream(pcbe, IGAIndex);
    }
}

