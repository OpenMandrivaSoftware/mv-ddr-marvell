/*******************************************************************************
Copyright (C) 2016 Marvell International Ltd.

This software file (the "File") is owned and distributed by Marvell
International Ltd. and/or its affiliates ("Marvell") under the following
alternative licensing terms.  Once you have made an election to distribute the
File under one of the following license alternatives, please (i) delete this
introductory statement regarding license alternatives, (ii) delete the three
license alternatives that you have not elected to use and (iii) preserve the
Marvell copyright notice above.

********************************************************************************
Marvell Commercial License Option

If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.

********************************************************************************
Marvell GPL License Option

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 2 of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************************
Marvell GNU General Public License FreeRTOS Exception

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File in accordance with the terms and conditions of the Lesser
General Public License Version 2.1 plus the following FreeRTOS exception.
An independent module is a module which is not derived from or based on
FreeRTOS.
Clause 1:
Linking FreeRTOS statically or dynamically with other modules is making a
combined work based on FreeRTOS. Thus, the terms and conditions of the GNU
General Public License cover the whole combination.
As a special exception, the copyright holder of FreeRTOS gives you permission
to link FreeRTOS with independent modules that communicate with FreeRTOS solely
through the FreeRTOS API interface, regardless of the license terms of these
independent modules, and to copy and distribute the resulting combined work
under terms of your choice, provided that:
1. Every copy of the combined work is accompanied by a written statement that
details to the recipient the version of FreeRTOS used and an offer by yourself
to provide the FreeRTOS source code (including any modifications you may have
made) should the recipient request it.
2. The combined work is not itself an RTOS, scheduler, kernel or related
product.
3. The independent modules add significant and primary functionality to
FreeRTOS and do not merely extend the existing functionality already present in
FreeRTOS.
Clause 2:
FreeRTOS may not be used for any competitive or comparative purpose, including
the publication of any form of run time or compile time metric, without the
express permission of Real Time Engineers Ltd. (this is the norm within the
industry and is intended to ensure information accuracy).

********************************************************************************
Marvell BSD License Option

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File under the following licensing terms.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.

	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.

	* Neither the name of Marvell nor the names of its contributors may be
	  used to endorse or promote products derived from this software without
	  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

#ifndef _DDR3_TRAINING_IP_FLOW_H_
#define _DDR3_TRAINING_IP_FLOW_H_

#include "ddr3_training_ip.h"
#include "ddr3_training_ip_pbs.h"

#define MRS0_CMD			0x3
#define MRS1_CMD			0x4
#define MRS2_CMD			0x8
#define MRS3_CMD			0x9

/*
 * Definitions of INTERFACE registers
 */

#define READ_BUFFER_SELECT		0x14a4

/*
 * Definitions of PHY registers
 */

#define KILLER_PATTERN_LENGTH		32
#define EXT_ACCESS_BURST_LENGTH		8

#define IS_ACTIVE(mask, id) \
	((mask) & (1 << (id)))

#define VALIDATE_ACTIVE(mask, id)		\
	{					\
	if (IS_ACTIVE(mask, id) == 0)		\
		continue;			\
	}

#define IS_IF_ACTIVE(if_mask, if_id) \
	((if_mask) & (1 << (if_id)))

#define VALIDATE_IF_ACTIVE(mask, id)		\
	{					\
	if (IS_IF_ACTIVE(mask, id) == 0)	\
		continue;			\
	}

#define IS_BUS_ACTIVE(if_mask , if_id) \
	(((if_mask) >> (if_id)) & 1)

#define VALIDATE_BUS_ACTIVE(mask, id)		\
	{					\
	if (IS_BUS_ACTIVE(mask, id) == 0)	\
		continue;			\
	}

#define DDR3_IS_ECC_PUP3_MODE(if_mask) \
	(((if_mask) == 0xb) ? 1 : 0)
#define DDR3_IS_ECC_PUP4_MODE(if_mask) \
	(((((if_mask) & 0x10) == 0)) ? 0 : 1)
#define DDR3_IS_16BIT_DRAM_MODE(mask) \
	(((((mask) & 0x4) == 0)) ? 1 : 0)

#define MEGA				1000000
#define BUS_WIDTH_IN_BITS		8

/*
 * DFX address Space
 * Table 2: DFX address space
 * Address Bits   Value   Description
 * [31 : 20]   0x? DFX base address bases PCIe mapping
 * [19 : 15]   0...Number_of_client-1   Client Index inside pipe.
 *             See also Table 1 Multi_cast = 29 Broadcast = 28
 * [14 : 13]   2'b01   Access to Client Internal Register
 * [12 : 0]   Client Internal Register offset   See related Client Registers
 * [14 : 13]   2'b00   Access to Ram Wrappers Internal Register
 * [12 : 6]   0 Number_of_rams-1   Ram Index inside Client
 * [5 : 0]   Ram Wrapper Internal Register offset   See related Ram Wrappers
 * Registers
 */

/* nsec */
#define  TREFI_LOW				7800
#define  TREFI_HIGH				3900

#define  TR2R_VALUE_REG				0x180
#define  TR2R_MASK_REG				0x180
#define  TRFC_MASK_REG				0x7f
#define  TR2W_MASK_REG				0x600
#define  TW2W_HIGH_VALUE_REG			0x1800
#define  TW2W_HIGH_MASK_REG			0xf800
#define  TRFC_HIGH_VALUE_REG			0x20000
#define  TRFC_HIGH_MASK_REG			0x70000
#define  TR2R_HIGH_VALUE_REG			0x0
#define  TR2R_HIGH_MASK_REG			0x380000
#define  TMOD_VALUE_REG				0x16000000
#define  TMOD_MASK_REG				0x1e000000
#define  T_VALUE_REG				0x40000000
#define  T_MASK_REG				0xc0000000
#define  AUTO_ZQC_TIMING			15384
#define  WRITE_XBAR_PORT1			0xc03f8077
#define  READ_XBAR_PORT1			0xc03f8073
#define  DISABLE_DDR_TUNING_DATA		0x02294285
#define  ENABLE_DDR_TUNING_DATA			0x12294285

#define ODPG_TRAINING_STATUS_REG		0x18488
#define ODPG_TRAINING_TRIGGER_REG		0x1030
#define ODPG_STATUS_DONE_REG			0x16fc
#define ODPG_ENABLE_REG				0x186d4
#define ODPG_ENABLE_OFFS			0
#define ODPG_DISABLE_OFFS			8

#define ODPG_TRAINING_CONTROL_REG		0x1034
#define ODPG_OBJ1_OPCODE_REG			0x103c
#define ODPG_OBJ1_ITER_CNT_REG			0x10b4
#define CALIB_OBJ_PRFA_REG			0x10c4
#define ODPG_WRITE_LEVELING_DONE_CNTR_REG	0x10f8
#define ODPG_WRITE_READ_MODE_ENABLE_REG		0x10fc
#define TRAINING_OPCODE_1_REG			0x10b4
#define SDRAM_CONFIGURATION_REG			0x1400
#define DDR_CONTROL_LOW_REG			0x1404
#define SDRAM_TIMING_LOW_REG			0x1408
#define SDRAM_TIMING_HIGH_REG			0x140c
#define SDRAM_ACCESS_CONTROL_REG		0x1410
#define SDRAM_OPEN_PAGE_CONTROL_REG		0x1414
#define SDRAM_OPERATION_REG			0x1418
#define DUNIT_CONTROL_HIGH_REG			0x1424
#define ODT_TIMING_LOW				0x1428
#define DDR_TIMING_REG				0x142c
#define ODT_TIMING_HI_REG			0x147c
#define SDRAM_INIT_CONTROL_REG			0x1480
#define SDRAM_ODT_CONTROL_HIGH_REG		0x1498
#define DUNIT_ODT_CONTROL_REG			0x149c
#define READ_BUFFER_SELECT_REG			0x14a4
#define DUNIT_MMASK_REG				0x14b0
#define CALIB_MACHINE_CTRL_REG			0x14cc
#define DRAM_DLL_TIMING_REG			0x14e0
#define DRAM_ZQ_INIT_TIMIMG_REG			0x14e4
#define DRAM_ZQ_TIMING_REG			0x14e8
#define DFS_REG					0x1528
#define READ_DATA_SAMPLE_DELAY			0x1538
#define READ_DATA_READY_DELAY			0x153c
#define TRAINING_REG				0x15b0
#define TRAINING_SW_1_REG			0x15b4
#define TRAINING_SW_2_REG			0x15b8
#define TRAINING_PATTERN_BASE_ADDRESS_REG	0x15bc
#define TRAINING_DBG_1_REG			0x15c0
#define TRAINING_DBG_2_REG			0x15c4
#define TRAINING_DBG_3_REG			0x15c8
#define RANK_CTRL_REG				0x15e0
#define TIMING_REG				0x15e4
#define DRAM_PHY_CONFIGURATION			0x15ec
#define MR0_REG					0x15d0
#define MR1_REG					0x15d4
#define MR2_REG					0x15d8
#define MR3_REG					0x15dc
#define TIMING_REG				0x15e4
#define ODPG_CTRL_CONTROL_REG			0x1600
#define ODPG_DATA_CONTROL_REG			0x1630
#define ODPG_PATTERN_ADDR_OFFSET_REG		0x1638
#define ODPG_DATA_BUF_SIZE_REG			0x163c
#define PHY_LOCK_STATUS_REG			0x1674
#define PHY_REG_FILE_ACCESS			0x16a0
#define TRAINING_WRITE_LEVELING_REG		0x16ac
#define ODPG_PATTERN_ADDR_REG			0x16b0
#define ODPG_PATTERN_DATA_HI_REG		0x16b4
#define ODPG_PATTERN_DATA_LOW_REG		0x16b8
#define ODPG_BIST_LAST_FAIL_ADDR_REG		0x16bc
#define ODPG_BIST_DATA_ERROR_COUNTER_REG	0x16c0
#define ODPG_BIST_FAILED_DATA_HI_REG		0x16c4
#define ODPG_BIST_FAILED_DATA_LOW_REG		0x16c8
#define ODPG_WRITE_DATA_ERROR_REG		0x16cc
#define CS_ENABLE_REG				0x16d8
#define WR_LEVELING_DQS_PATTERN_REG		0x16dc

#define ODPG_BIST_DONE				0x186d4
#define ODPG_BIST_DONE_BIT_OFFS			0
#define ODPG_BIST_DONE_BIT_VALUE_REV2		1
#define ODPG_BIST_DONE_BIT_VALUE_REV3		0

#define RESULT_CONTROL_BYTE_PUP_0_REG		0x1830
#define RESULT_CONTROL_BYTE_PUP_1_REG		0x1834
#define RESULT_CONTROL_BYTE_PUP_2_REG		0x1838
#define RESULT_CONTROL_BYTE_PUP_3_REG		0x183c
#define RESULT_CONTROL_BYTE_PUP_4_REG		0x18b0

#define RESULT_CONTROL_PUP_0_BIT_0_REG		0x18b4
#define RESULT_CONTROL_PUP_0_BIT_1_REG		0x18b8
#define RESULT_CONTROL_PUP_0_BIT_2_REG		0x18bc
#define RESULT_CONTROL_PUP_0_BIT_3_REG		0x18c0
#define RESULT_CONTROL_PUP_0_BIT_4_REG		0x18c4
#define RESULT_CONTROL_PUP_0_BIT_5_REG		0x18c8
#define RESULT_CONTROL_PUP_0_BIT_6_REG		0x18cc
#define RESULT_CONTROL_PUP_0_BIT_7_REG		0x18f0
#define RESULT_CONTROL_PUP_1_BIT_0_REG		0x18f4
#define RESULT_CONTROL_PUP_1_BIT_1_REG		0x18f8
#define RESULT_CONTROL_PUP_1_BIT_2_REG		0x18fc
#define RESULT_CONTROL_PUP_1_BIT_3_REG		0x1930
#define RESULT_CONTROL_PUP_1_BIT_4_REG		0x1934
#define RESULT_CONTROL_PUP_1_BIT_5_REG		0x1938
#define RESULT_CONTROL_PUP_1_BIT_6_REG		0x193c
#define RESULT_CONTROL_PUP_1_BIT_7_REG		0x19b0
#define RESULT_CONTROL_PUP_2_BIT_0_REG		0x19b4
#define RESULT_CONTROL_PUP_2_BIT_1_REG		0x19b8
#define RESULT_CONTROL_PUP_2_BIT_2_REG		0x19bc
#define RESULT_CONTROL_PUP_2_BIT_3_REG		0x19c0
#define RESULT_CONTROL_PUP_2_BIT_4_REG		0x19c4
#define RESULT_CONTROL_PUP_2_BIT_5_REG		0x19c8
#define RESULT_CONTROL_PUP_2_BIT_6_REG		0x19cc
#define RESULT_CONTROL_PUP_2_BIT_7_REG		0x19f0
#define RESULT_CONTROL_PUP_3_BIT_0_REG		0x19f4
#define RESULT_CONTROL_PUP_3_BIT_1_REG		0x19f8
#define RESULT_CONTROL_PUP_3_BIT_2_REG		0x19fc
#define RESULT_CONTROL_PUP_3_BIT_3_REG		0x1a30
#define RESULT_CONTROL_PUP_3_BIT_4_REG		0x1a34
#define RESULT_CONTROL_PUP_3_BIT_5_REG		0x1a38
#define RESULT_CONTROL_PUP_3_BIT_6_REG		0x1a3c
#define RESULT_CONTROL_PUP_3_BIT_7_REG		0x1ab0
#define RESULT_CONTROL_PUP_4_BIT_0_REG		0x1ab4
#define RESULT_CONTROL_PUP_4_BIT_1_REG		0x1ab8
#define RESULT_CONTROL_PUP_4_BIT_2_REG		0x1abc
#define RESULT_CONTROL_PUP_4_BIT_3_REG		0x1ac0
#define RESULT_CONTROL_PUP_4_BIT_4_REG		0x1ac4
#define RESULT_CONTROL_PUP_4_BIT_5_REG		0x1ac8
#define RESULT_CONTROL_PUP_4_BIT_6_REG		0x1acc
#define RESULT_CONTROL_PUP_4_BIT_7_REG		0x1af0

#define WL_PHY_REG				0x0
#define WRITE_CENTRALIZATION_PHY_REG		0x1
#define RL_PHY_REG				0x2
#define READ_CENTRALIZATION_PHY_REG		0x3
#define PBS_RX_PHY_REG				0x50
#define PBS_TX_PHY_REG				0x10
#define PHY_CONTROL_PHY_REG			0x90
#define BW_PHY_REG				0x92
#define RATE_PHY_REG				0x94
#define CMOS_CONFIG_PHY_REG			0xa2
#define PAD_ZRI_CALIB_PHY_REG			0xa4
#define PAD_ODT_CALIB_PHY_REG			0xa6
#define PAD_CONFIG_PHY_REG			0xa8
#define PAD_PRE_DISABLE_PHY_REG			0xa9
#define TEST_ADLL_REG				0xbf
#define CSN_IOB_VREF_REG(cs)			(0xdb + (cs * 12))
#define CSN_IO_BASE_VREF_REG(cs)		(0xd0 + (cs * 12))

#define RESULT_DB_PHY_REG_ADDR			0xc0
#define RESULT_DB_PHY_REG_RX_OFFSET		5
#define RESULT_DB_PHY_REG_TX_OFFSET		0

/* TBD - for NP5 use only CS 0 */
#define PHY_WRITE_DELAY(cs)			WL_PHY_REG
/*( ( _cs_ == 0 ) ? 0x0 : 0x4 )*/
/* TBD - for NP5 use only CS 0 */
#define PHY_READ_DELAY(cs)			RL_PHY_REG

#define DDR0_ADDR_1				0xf8258
#define DDR0_ADDR_2				0xf8254
#define DDR1_ADDR_1				0xf8270
#define DDR1_ADDR_2				0xf8270
#define DDR2_ADDR_1				0xf825c
#define DDR2_ADDR_2				0xf825c
#define DDR3_ADDR_1				0xf8264
#define DDR3_ADDR_2				0xf8260
#define DDR4_ADDR_1				0xf8274
#define DDR4_ADDR_2				0xf8274

#define GENERAL_PURPOSE_RESERVED0_REG		0x182e0

#define GET_BLOCK_ID_MAX_FREQ(dev_num, block_id)	800000
#define CS0_RD_LVL_REF_DLY_OFFS			0
#define CS0_RD_LVL_REF_DLY_LEN			0
#define CS0_RD_LVL_PH_SEL_OFFS			0
#define CS0_RD_LVL_PH_SEL_LEN			0

#define CS_REGISTER_ADDR_OFFSET			4
#define CALIBRATED_OBJECTS_REG_ADDR_OFFSET	0x10

#define MAX_POLLING_ITERATIONS			100000

#define PHASE_REG_OFFSET			32
#define NUM_BYTES_IN_BURST			31
#define NUM_OF_CS				4
#define CS_REG_VALUE(cs_num)			(cs_mask_reg[cs_num])
#define ADLL_LENGTH				32

struct write_supp_result {
	enum hws_wl_supp stage;
	int is_pup_fail;
};

struct page_element {
	enum hws_page_size page_size_8bit;
	/* page size in 8 bits bus width */
	enum hws_page_size page_size_16bit;
	/* page size in 16 bits bus width */
	u32 ui_page_mask;
	/* Mask used in register */
};

int ddr3_tip_write_leveling_static_config(u32 dev_num, u32 if_id,
					  enum hws_ddr_freq frequency,
					  u32 *round_trip_delay_arr);
int ddr3_tip_read_leveling_static_config(u32 dev_num, u32 if_id,
					 enum hws_ddr_freq frequency,
					 u32 *total_round_trip_delay_arr);
int ddr3_tip_if_write(u32 dev_num, enum hws_access_type interface_access,
		      u32 if_id, u32 reg_addr, u32 data_value, u32 mask);
int ddr3_tip_if_polling(u32 dev_num, enum hws_access_type access_type,
			u32 if_id, u32 exp_value, u32 mask, u32 offset,
			u32 poll_tries);
int ddr3_tip_if_read(u32 dev_num, enum hws_access_type interface_access,
		     u32 if_id, u32 reg_addr, u32 *data, u32 mask);
int ddr3_tip_bus_read_modify_write(u32 dev_num,
				   enum hws_access_type access_type,
				   u32 if_id, u32 phy_id,
				   enum hws_ddr_phy phy_type,
				   u32 reg_addr, u32 data_value, u32 reg_mask);
int ddr3_tip_bus_read(u32 dev_num, u32 if_id, enum hws_access_type phy_access,
		      u32 phy_id, enum hws_ddr_phy phy_type, u32 reg_addr,
		      u32 *data);
int ddr3_tip_bus_write(u32 dev_num, enum hws_access_type e_interface_access,
		       u32 if_id, enum hws_access_type e_phy_access, u32 phy_id,
		       enum hws_ddr_phy e_phy_type, u32 reg_addr,
		       u32 data_value);
int ddr3_tip_freq_set(u32 dev_num, enum hws_access_type e_access, u32 if_id,
		      enum hws_ddr_freq memory_freq);
int ddr3_tip_adjust_dqs(u32 dev_num);
int ddr3_tip_init_controller(u32 dev_num);
int ddr3_tip_ext_read(u32 dev_num, u32 if_id, u32 reg_addr,
		      u32 num_of_bursts, u32 *addr);
int ddr3_tip_ext_write(u32 dev_num, u32 if_id, u32 reg_addr,
		       u32 num_of_bursts, u32 *addr);
int ddr3_tip_dynamic_read_leveling(u32 dev_num, u32 ui_freq);
int ddr3_tip_legacy_dynamic_read_leveling(u32 dev_num);
int ddr3_tip_dynamic_per_bit_read_leveling(u32 dev_num, u32 ui_freq);
int ddr3_tip_legacy_dynamic_write_leveling(u32 dev_num);
int ddr3_tip_dynamic_write_leveling(u32 dev_num);
int ddr3_tip_dynamic_write_leveling_supp(u32 dev_num);
int ddr3_tip_static_init_controller(u32 dev_num);
int ddr3_tip_configure_phy(u32 dev_num);
int ddr3_tip_load_pattern_to_odpg(u32 dev_num, enum hws_access_type access_type,
				  u32 if_id, enum hws_pattern pattern,
				  u32 load_addr);
int ddr3_tip_load_pattern_to_mem(u32 dev_num, enum hws_pattern e_pattern);
int ddr3_tip_configure_odpg(u32 dev_num, enum hws_access_type access_type,
			    u32 if_id, enum hws_dir direction, u32 tx_phases,
			    u32 tx_burst_size, u32 rx_phases,
			    u32 delay_between_burst, u32 rd_mode, u32 cs_num,
			    u32 addr_stress_jump, u32 single_pattern);
int ddr3_tip_set_atr(u32 dev_num, u32 flag_id, u32 value);
int ddr3_tip_write_mrs_cmd(u32 dev_num, u32 *cs_mask_arr, u32 cmd, u32 data,
			   u32 mask);
int ddr3_tip_write_cs_result(u32 dev_num, u32 offset);
int ddr3_tip_get_first_active_if(u8 dev_num, u32 interface_mask, u32 *if_id);
int ddr3_tip_reset_fifo_ptr(u32 dev_num);
int read_pup_value(int pup_values[MAX_INTERFACE_NUM * MAX_BUS_NUM],
		   int reg_addr, u32 mask);
int read_adll_value(u32 pup_values[MAX_INTERFACE_NUM * MAX_BUS_NUM],
		    int reg_addr, u32 mask);
int write_adll_value(u32 pup_values[MAX_INTERFACE_NUM * MAX_BUS_NUM],
		     int reg_addr);
int ddr3_tip_tune_training_params(u32 dev_num,
				  struct tune_train_params *params);

#endif /* _DDR3_TRAINING_IP_FLOW_H_ */