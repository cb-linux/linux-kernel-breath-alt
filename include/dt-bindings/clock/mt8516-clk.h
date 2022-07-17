/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Copyright (c) 2019 BayLibre, SAS.
 * Author: James Liao <jamesjj.liao@mediatek.com>
 */

#ifndef _DT_BINDINGS_CLK_MT8516_H
#define _DT_BINDINGS_CLK_MT8516_H

/* APMIXEDSYS */

#define CLK_APMIXED_ARMPLL		0
#define CLK_APMIXED_MAINPLL		1
#define CLK_APMIXED_UNIVPLL		2
#define CLK_APMIXED_MMPLL		3
#define CLK_APMIXED_APLL1		4
#define CLK_APMIXED_APLL2		5
#define CLK_APMIXED_NR_CLK		6

/* INFRACFG */

#define CLK_IFR_MUX1_SEL		0
#define CLK_IFR_ETH_25M_SEL		1
#define CLK_IFR_I2C0_SEL		2
#define CLK_IFR_I2C1_SEL		3
#define CLK_IFR_I2C2_SEL		4
#define CLK_IFR_NR_CLK			5

/* TOPCKGEN */

#define CLK_TOP_CLK_NULL		0
#define CLK_TOP_I2S_INFRA_BCK		1
#define CLK_TOP_MEMPLL			2
#define CLK_TOP_DMPLL			3
#define CLK_TOP_MAINPLL_D2		4
#define CLK_TOP_MAINPLL_D4		5
#define CLK_TOP_MAINPLL_D8		6
#define CLK_TOP_MAINPLL_D16		7
#define CLK_TOP_MAINPLL_D11		8
#define CLK_TOP_MAINPLL_D22		9
#define CLK_TOP_MAINPLL_D3		10
#define CLK_TOP_MAINPLL_D6		11
#define CLK_TOP_MAINPLL_D12		12
#define CLK_TOP_MAINPLL_D5		13
#define CLK_TOP_MAINPLL_D10		14
#define CLK_TOP_MAINPLL_D20		15
#define CLK_TOP_MAINPLL_D40		16
#define CLK_TOP_MAINPLL_D7		17
#define CLK_TOP_MAINPLL_D14		18
#define CLK_TOP_UNIVPLL_D2		19
#define CLK_TOP_UNIVPLL_D4		20
#define CLK_TOP_UNIVPLL_D8		21
#define CLK_TOP_UNIVPLL_D16		22
#define CLK_TOP_UNIVPLL_D3		23
#define CLK_TOP_UNIVPLL_D6		24
#define CLK_TOP_UNIVPLL_D12		25
#define CLK_TOP_UNIVPLL_D24		26
#define CLK_TOP_UNIVPLL_D5		27
#define CLK_TOP_UNIVPLL_D20		28
#define CLK_TOP_MMPLL380M		29
#define CLK_TOP_MMPLL_D2		30
#define CLK_TOP_MMPLL_200M		31
#define CLK_TOP_USB_PHY48M		32
#define CLK_TOP_APLL1			33
#define CLK_TOP_APLL1_D2		34
#define CLK_TOP_APLL1_D4		35
#define CLK_TOP_APLL1_D8		36
#define CLK_TOP_APLL2			37
#define CLK_TOP_APLL2_D2		38
#define CLK_TOP_APLL2_D4		39
#define CLK_TOP_APLL2_D8		40
#define CLK_TOP_CLK26M			41
#define CLK_TOP_CLK26M_D2		42
#define CLK_TOP_AHB_INFRA_D2		43
#define CLK_TOP_NFI1X			44
#define CLK_TOP_ETH_D2			45
#define CLK_TOP_THEM			46
#define CLK_TOP_APDMA			47
#define CLK_TOP_I2C0			48
#define CLK_TOP_I2C1			49
#define CLK_TOP_AUXADC1			50
#define CLK_TOP_NFI			51
#define CLK_TOP_NFIECC			52
#define CLK_TOP_DEBUGSYS		53
#define CLK_TOP_PWM			54
#define CLK_TOP_UART0			55
#define CLK_TOP_UART1			56
#define CLK_TOP_BTIF			57
#define CLK_TOP_USB			58
#define CLK_TOP_FLASHIF_26M		59
#define CLK_TOP_AUXADC2			60
#define CLK_TOP_I2C2			61
#define CLK_TOP_MSDC0			62
#define CLK_TOP_MSDC1			63
#define CLK_TOP_NFI2X			64
#define CLK_TOP_PMICWRAP_AP		65
#define CLK_TOP_SEJ			66
#define CLK_TOP_MEMSLP_DLYER		67
#define CLK_TOP_SPI			68
#define CLK_TOP_APXGPT			69
#define CLK_TOP_AUDIO			70
#define CLK_TOP_PMICWRAP_MD		71
#define CLK_TOP_PMICWRAP_CONN		72
#define CLK_TOP_PMICWRAP_26M		73
#define CLK_TOP_AUX_ADC			74
#define CLK_TOP_AUX_TP			75
#define CLK_TOP_MSDC2			76
#define CLK_TOP_RBIST			77
#define CLK_TOP_NFI_BUS			78
#define CLK_TOP_GCE			79
#define CLK_TOP_TRNG			80
#define CLK_TOP_SEJ_13M			81
#define CLK_TOP_AES			82
#define CLK_TOP_PWM_B			83
#define CLK_TOP_PWM1_FB			84
#define CLK_TOP_PWM2_FB			85
#define CLK_TOP_PWM3_FB			86
#define CLK_TOP_PWM4_FB			87
#define CLK_TOP_PWM5_FB			88
#define CLK_TOP_USB_1P			89
#define CLK_TOP_FLASHIF_FREERUN		90
#define CLK_TOP_66M_ETH			91
#define CLK_TOP_133M_ETH		92
#define CLK_TOP_FETH_25M		93
#define CLK_TOP_FETH_50M		94
#define CLK_TOP_FLASHIF_AXI		95
#define CLK_TOP_USBIF			96
#define CLK_TOP_UART2			97
#define CLK_TOP_BSI			98
#define CLK_TOP_RG_SPINOR		99
#define CLK_TOP_RG_MSDC2		100
#define CLK_TOP_RG_ETH			101
#define CLK_TOP_RG_AUD1			102
#define CLK_TOP_RG_AUD2			103
#define CLK_TOP_RG_AUD_ENGEN1		104
#define CLK_TOP_RG_AUD_ENGEN2		105
#define CLK_TOP_RG_I2C			106
#define CLK_TOP_RG_PWM_INFRA		107
#define CLK_TOP_RG_AUD_SPDIF_IN		108
#define CLK_TOP_RG_UART2		109
#define CLK_TOP_RG_BSI			110
#define CLK_TOP_RG_DBG_ATCLK		111
#define CLK_TOP_RG_NFIECC		112
#define CLK_TOP_RG_APLL1_D2_EN		113
#define CLK_TOP_RG_APLL1_D4_EN		114
#define CLK_TOP_RG_APLL1_D8_EN		115
#define CLK_TOP_RG_APLL2_D2_EN		116
#define CLK_TOP_RG_APLL2_D4_EN		117
#define CLK_TOP_RG_APLL2_D8_EN		118
#define CLK_TOP_APLL12_DIV0		119
#define CLK_TOP_APLL12_DIV1		120
#define CLK_TOP_APLL12_DIV2		121
#define CLK_TOP_APLL12_DIV3		122
#define CLK_TOP_APLL12_DIV4		123
#define CLK_TOP_APLL12_DIV4B		124
#define CLK_TOP_APLL12_DIV5		125
#define CLK_TOP_APLL12_DIV5B		126
#define CLK_TOP_APLL12_DIV6		127
#define CLK_TOP_UART0_SEL		128
#define CLK_TOP_EMI_DDRPHY_SEL		129
#define CLK_TOP_AHB_INFRA_SEL		130
#define CLK_TOP_MSDC0_SEL		131
#define CLK_TOP_UART1_SEL		132
#define CLK_TOP_MSDC1_SEL		133
#define CLK_TOP_PMICSPI_SEL		134
#define CLK_TOP_QAXI_AUD26M_SEL		135
#define CLK_TOP_AUD_INTBUS_SEL		136
#define CLK_TOP_NFI2X_PAD_SEL		137
#define CLK_TOP_NFI1X_PAD_SEL		138
#define CLK_TOP_DDRPHYCFG_SEL		139
#define CLK_TOP_USB_78M_SEL		140
#define CLK_TOP_SPINOR_SEL		141
#define CLK_TOP_MSDC2_SEL		142
#define CLK_TOP_ETH_SEL			143
#define CLK_TOP_AUD1_SEL		144
#define CLK_TOP_AUD2_SEL		145
#define CLK_TOP_AUD_ENGEN1_SEL		146
#define CLK_TOP_AUD_ENGEN2_SEL		147
#define CLK_TOP_I2C_SEL			148
#define CLK_TOP_AUD_I2S0_M_SEL		149
#define CLK_TOP_AUD_I2S1_M_SEL		150
#define CLK_TOP_AUD_I2S2_M_SEL		151
#define CLK_TOP_AUD_I2S3_M_SEL		152
#define CLK_TOP_AUD_I2S4_M_SEL		153
#define CLK_TOP_AUD_I2S5_M_SEL		154
#define CLK_TOP_AUD_SPDIF_B_SEL		155
#define CLK_TOP_PWM_SEL			156
#define CLK_TOP_SPI_SEL			157
#define CLK_TOP_AUD_SPDIFIN_SEL		158
#define CLK_TOP_UART2_SEL		159
#define CLK_TOP_BSI_SEL			160
#define CLK_TOP_DBG_ATCLK_SEL		161
#define CLK_TOP_CSW_NFIECC_SEL		162
#define CLK_TOP_NFIECC_SEL		163
#define CLK_TOP_APLL12_CK_DIV0		164
#define CLK_TOP_APLL12_CK_DIV1		165
#define CLK_TOP_APLL12_CK_DIV2		166
#define CLK_TOP_APLL12_CK_DIV3		167
#define CLK_TOP_APLL12_CK_DIV4		168
#define CLK_TOP_APLL12_CK_DIV4B		169
#define CLK_TOP_APLL12_CK_DIV5		170
#define CLK_TOP_APLL12_CK_DIV5B		171
#define CLK_TOP_APLL12_CK_DIV6		172
#define CLK_TOP_USB_78M			173
#define CLK_TOP_MSDC0_INFRA		174
#define CLK_TOP_MSDC1_INFRA		175
#define CLK_TOP_MSDC2_INFRA		176
#define CLK_TOP_NR_CLK			177

/* AUDSYS */

#define CLK_AUD_AFE			0
#define CLK_AUD_I2S			1
#define CLK_AUD_22M			2
#define CLK_AUD_24M			3
#define CLK_AUD_INTDIR			4
#define CLK_AUD_APLL2_TUNER		5
#define CLK_AUD_APLL_TUNER		6
#define CLK_AUD_HDMI			7
#define CLK_AUD_SPDF			8
#define CLK_AUD_ADC			9
#define CLK_AUD_DAC			10
#define CLK_AUD_DAC_PREDIS		11
#define CLK_AUD_TML			12
#define CLK_AUD_NR_CLK			13

#endif /* _DT_BINDINGS_CLK_MT8516_H */
