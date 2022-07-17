/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2014-2021 Intel Corporation
 */

#ifndef _ABI_GUC_MESSAGES_ABI_H
#define _ABI_GUC_MESSAGES_ABI_H

#define INTEL_GUC_MSG_TYPE_SHIFT	28
#define INTEL_GUC_MSG_TYPE_MASK		(0xF << INTEL_GUC_MSG_TYPE_SHIFT)
#define INTEL_GUC_MSG_DATA_SHIFT	16
#define INTEL_GUC_MSG_DATA_MASK		(0xFFF << INTEL_GUC_MSG_DATA_SHIFT)
#define INTEL_GUC_MSG_CODE_SHIFT	0
#define INTEL_GUC_MSG_CODE_MASK		(0xFFFF << INTEL_GUC_MSG_CODE_SHIFT)

enum intel_guc_msg_type {
	INTEL_GUC_MSG_TYPE_REQUEST = 0x0,
	INTEL_GUC_MSG_TYPE_RESPONSE = 0xF,
};

#endif /* _ABI_GUC_MESSAGES_ABI_H */
