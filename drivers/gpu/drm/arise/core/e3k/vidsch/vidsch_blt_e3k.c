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
#include "gf_adapter.h"
#include "vidsch.h"
#include "vidschi.h"
#include "vidsch_blt_e3k.h"
#include "vidsch_engine_e3k.h"

static void vidschi_init_2dblt_cmd_e3k(engine_share_e3k_t *share)
{
    BITBLT_REGSETTING_E3K      *pKmdBitBltCmd  = &share->_2dblt_cmd_e3k;
    FASTCLEAR_REGSETTING_E3K   *pKmdFastClearCmd = &share->fast_clear_cmd_e3k;

    int RtIdx;

    gf_memset(pKmdBitBltCmd, 0, sizeof(BITBLT_REGSETTING_E3K));
    gf_memset(pKmdFastClearCmd, 0, sizeof(FASTCLEAR_REGSETTING_E3K));

    //Init BitBlt structure
    pKmdBitBltCmd->SetDstRTAddrCtrl = SET_REGISTER_FD_E3K(FF_BLOCK,
       REG_OFFSET_OF_GROUP(Reg_Rt_Addr_Ctrl_Offset, Reg_Rt_Addr_Ctrl_Group, reg_Rt_Addr, FF_RT_DST),
       sizeof(Reg_Rt_Addr_Ctrl_Group)>> 2);

    pKmdBitBltCmd->SetDstRTCtrl = SET_REGISTER_FD_E3K(FF_BLOCK,
       REG_OFFSET_OF_GROUP(Reg_Rt_Ctrl_Offset, Reg_Rt_Ctrl_Group, reg_Rt_Fmt, FF_RT_DST),
       sizeof(Reg_Rt_Ctrl_Group)>>2);

    pKmdBitBltCmd->SetSrcRTAddrCtrl = SET_REGISTER_FD_E3K(FF_BLOCK,
       REG_OFFSET_OF_GROUP(Reg_Rt_Addr_Ctrl_Offset, Reg_Rt_Addr_Ctrl_Group, reg_Rt_Addr, FF_RT_SRC),
       sizeof(Reg_Rt_Addr_Ctrl_Group)>> 2);

    pKmdBitBltCmd->SetSrcRTCtrl = SET_REGISTER_FD_E3K(FF_BLOCK,
       REG_OFFSET_OF_GROUP(Reg_Rt_Ctrl_Offset, Reg_Rt_Ctrl_Group, reg_Rt_Fmt, FF_RT_SRC),
       sizeof(Reg_Rt_Ctrl_Group)>>2);

    pKmdBitBltCmd->Set_Rast_Ctrl                   = SET_REGISTER_FD_E3K(FF_BLOCK, Reg_Rast_Ctrl_Offset, 1);
    pKmdBitBltCmd->Set_Iu_Ctrl_Ex                  = SET_REGISTER_FD_E3K(IU_BLOCK, Reg_Iu_Ctrl_Ex_Offset, 1);
    pKmdBitBltCmd->Set_Tasfe_Ctrl                  = SET_REGISTER_FD_E3K(TASFE_BLOCK, Reg_Tasfe_Ctrl_Offset, 1);
    pKmdBitBltCmd->Set_Resolution_Ctrl             = SET_REGISTER_FD_E3K(FF_BLOCK, Reg_Resolution_Ctrl_Offset, 1);
    pKmdBitBltCmd->Set_Dzs_Ctrl                    = SET_REGISTER_FD_E3K(FF_BLOCK, Reg_Dzs_Ctrl_Offset, 1);
    pKmdBitBltCmd->Set_Zs_Req_Ctrl               = SET_REGISTER_FD_E3K(FF_BLOCK, Reg_Zs_Req_Ctrl_Offset, 1);
    pKmdBitBltCmd->Set_Blend_Ctrl               = SET_REGISTER_FD_E3K(FF_BLOCK, Reg_Blend_Ctl_Offset, sizeof(Reg_Blend_Ctl_Group) >>2);


    pKmdBitBltCmd->BitBltCmd.Major_Opcode = CSP_OPCODE_Block_Command_Sg;
    pKmdBitBltCmd->BitBltCmd.Block_Id     = FF_BLOCK;
    pKmdBitBltCmd->BitBltCmd.Predicate_En = 0;
    pKmdBitBltCmd->BitBltCmd.Action_Type  = BLOCK_COMMAND_SG_ACTION_TYPE_BIT_BLT;
    pKmdBitBltCmd->BitBltCmd.Area_Target  = BLOCK_COMMAND_SG_AREA_TARGET_D;
    pKmdBitBltCmd->BitBltCmd.Type         = BLOCK_COMMAND_TEMPLATE_TYPE_SG;
    pKmdBitBltCmd->BitBltCmd.Dwc          = 3;

    pKmdBitBltCmd->D_Flush.Type                  = BLOCK_COMMAND_TEMPLATE_TYPE_FLUSH;
    pKmdBitBltCmd->D_Flush.Target                = BLOCK_COMMAND_FLUSH_TARGET_D_C;
    pKmdBitBltCmd->D_Flush.Block_Id              = FF_BLOCK;
    pKmdBitBltCmd->D_Flush.Major_Opcode          = CSP_OPCODE_Block_Command_Flush;

    pKmdBitBltCmd->D_Invalidate.Type             = BLOCK_COMMAND_TEMPLATE_TYPE_INVALIDATE_CACHE;
    pKmdBitBltCmd->D_Invalidate.Target           = BLOCK_COMMAND_FLUSH_TARGET_D_C;
    pKmdBitBltCmd->D_Invalidate.Block_Id         = FF_BLOCK;
    pKmdBitBltCmd->D_Invalidate.Major_Opcode     = CSP_OPCODE_Block_Command_Flush;

    //perhaps fastclear cmd initialize should not put in this func....
    //Init fastclear cmd
    pKmdFastClearCmd->SetDstRTAddrCtrl = pKmdBitBltCmd->SetDstRTAddrCtrl;
    pKmdFastClearCmd->SetDstRTCtrl = pKmdBitBltCmd->SetDstRTCtrl;

    pKmdFastClearCmd->Set_Rast_Ctrl                   = pKmdBitBltCmd->Set_Rast_Ctrl;
    pKmdFastClearCmd->Set_Iu_Ctrl_Ex                  = pKmdBitBltCmd->Set_Iu_Ctrl_Ex;
    pKmdFastClearCmd->Set_Tasfe_Ctrl                  = pKmdBitBltCmd->Set_Tasfe_Ctrl;
    pKmdFastClearCmd->Set_Resolution_Ctrl         = pKmdBitBltCmd->Set_Resolution_Ctrl;
    pKmdFastClearCmd->Set_Dzs_Ctrl                     = pKmdBitBltCmd->Set_Dzs_Ctrl;
    pKmdFastClearCmd->Set_Zs_Req_Ctrl               = SET_REGISTER_FD_E3K(FF_BLOCK, Reg_Zs_Req_Ctrl_Offset, 1);

    //disable RT1~7
    for(RtIdx = 1; RtIdx < 8; RtIdx++)
    {
        pKmdFastClearCmd->SetOtherRTDisable[(RtIdx-1) * 2] = SET_REGISTER_FD_E3K(FF_BLOCK,
            REG_OFFSET_OF_GROUP(Reg_Rt_Ctrl_Offset, Reg_Rt_Ctrl_Group, reg_Rt_Misc, RtIdx),
            1);
    }

    pKmdFastClearCmd->Set_Fast_Clear_Color            =  SET_REGISTER_FD_E3K(FF_BLOCK, Reg_Fast_Clear_Color_Offset, 4);

    *(DWORD*)&pKmdFastClearCmd->FastClearCmd          = *(DWORD*)&pKmdBitBltCmd->BitBltCmd;
    pKmdFastClearCmd->FastClearCmd.Action_Type        = BLOCK_COMMAND_SG_ACTION_TYPE_FAST_CLEAR_LINEAR;
    pKmdFastClearCmd->FastClearCmd.Dwc                = 2;

}

void vidschi_init_blt_cmd_e3k(engine_share_e3k_t *share)
{
    vidschi_init_2dblt_cmd_e3k(share);
}

