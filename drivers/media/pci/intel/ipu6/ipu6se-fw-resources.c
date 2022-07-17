// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2015 - 2019 Intel Corporation

#include <linux/err.h>
#include <linux/string.h>

#include "ipu-psys.h"
#include "ipu-fw-psys.h"
#include "ipu6se-platform-resources.h"

/* resources table */

/*
 * Cell types by cell IDs
 */
/* resources table */

/*
 * Cell types by cell IDs
 */
const u8 ipu6se_fw_psys_cell_types[IPU6SE_FW_PSYS_N_CELL_ID] = {
	IPU6SE_FW_PSYS_SP_CTRL_TYPE_ID,
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_ICA_ID */
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_LSC_ID */
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_DPC_ID */
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_B2B_ID */
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_BNLM_ID */
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_DM_ID */
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_R2I_SIE_ID */
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_R2I_DS_A_ID */
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_R2I_DS_B_ID */
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_AWB_ID */
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_AE_ID */
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID, /* IPU6SE_FW_PSYS_ISA_AF_ID*/
	IPU6SE_FW_PSYS_ACC_ISA_TYPE_ID  /* PAF */
};

const u16 ipu6se_fw_num_dev_channels[IPU6SE_FW_PSYS_N_DEV_CHN_ID] = {
	IPU6SE_FW_PSYS_DEV_CHN_DMA_EXT0_MAX_SIZE,
	IPU6SE_FW_PSYS_DEV_CHN_DMA_EXT1_READ_MAX_SIZE,
	IPU6SE_FW_PSYS_DEV_CHN_DMA_EXT1_WRITE_MAX_SIZE,
	IPU6SE_FW_PSYS_DEV_CHN_DMA_ISA_MAX_SIZE,
};

const u16 ipu6se_fw_psys_mem_size[IPU6SE_FW_PSYS_N_MEM_ID] = {
	IPU6SE_FW_PSYS_TRANSFER_VMEM0_MAX_SIZE,
	IPU6SE_FW_PSYS_LB_VMEM_MAX_SIZE,
	IPU6SE_FW_PSYS_DMEM0_MAX_SIZE,
	IPU6SE_FW_PSYS_DMEM1_MAX_SIZE
};

const u16 ipu6se_fw_psys_dfms[IPU6SE_FW_PSYS_N_DEV_DFM_ID] = {
	IPU6SE_FW_PSYS_DEV_DFM_ISL_FULL_PORT_ID_MAX_SIZE,
	IPU6SE_FW_PSYS_DEV_DFM_ISL_EMPTY_PORT_ID_MAX_SIZE
};

const u8
ipu6se_fw_psys_c_mem[IPU6SE_FW_PSYS_N_CELL_ID][IPU6SE_FW_PSYS_N_MEM_TYPE_ID] = {
	{ /* IPU6SE_FW_PSYS_SP0_ID */
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_DMEM0_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_ICA_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_LSC_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_DPC_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_B2B_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},

	{ /* IPU6SE_FW_PSYS_ISA_BNLM_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_DM_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_R2I_SIE_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_R2I_DS_A_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_R2I_DS_B_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_AWB_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_AE_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_AF_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	},
	{ /* IPU6SE_FW_PSYS_ISA_PAF_ID */
		IPU6SE_FW_PSYS_TRANSFER_VMEM0_ID,
		IPU6SE_FW_PSYS_LB_VMEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
		IPU6SE_FW_PSYS_N_MEM_ID,
	}
};

static const struct ipu_fw_resource_definitions ipu6se_defs = {
	.cells = ipu6se_fw_psys_cell_types,
	.num_cells = IPU6SE_FW_PSYS_N_CELL_ID,
	.num_cells_type = IPU6SE_FW_PSYS_N_CELL_TYPE_ID,

	.dev_channels = ipu6se_fw_num_dev_channels,
	.num_dev_channels = IPU6SE_FW_PSYS_N_DEV_CHN_ID,

	.num_ext_mem_types = IPU6SE_FW_PSYS_N_DATA_MEM_TYPE_ID,
	.num_ext_mem_ids = IPU6SE_FW_PSYS_N_MEM_ID,
	.ext_mem_ids = ipu6se_fw_psys_mem_size,

	.num_dfm_ids = IPU6SE_FW_PSYS_N_DEV_DFM_ID,

	.dfms = ipu6se_fw_psys_dfms,

	.cell_mem_row = IPU6SE_FW_PSYS_N_MEM_TYPE_ID,
	.cell_mem = &ipu6se_fw_psys_c_mem[0][0],
};

const struct ipu_fw_resource_definitions *ipu6se_res_defs = &ipu6se_defs;
