// SPDX-License-Identifier: GPL-2.0-only
//
// rt1019.c  --  RT1019 ALSA SoC audio amplifier driver
// Author: Jack Yu <jack.yu@realtek.com>
//
// Copyright(c) 2021 Realtek Semiconductor Corp.
//
//

#include <linux/acpi.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/regmap.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/firmware.h>
#include <linux/gpio.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/initval.h>
#include <sound/tlv.h>

#include "rl6231.h"
#include "rt1019.h"

static const struct reg_default rt1019_reg[] = {
	{ 0x0000, 0x00 },
	{ 0x0002, 0x55 },
	{ 0x0003, 0x55 },
	{ 0x0005, 0x54 },
	{ 0x0006, 0x05 },
	{ 0x0007, 0x01 },
	{ 0x0008, 0x70 },
	{ 0x0009, 0x28 },
	{ 0x000a, 0x7f },
	{ 0x0011, 0x04 },
	{ 0x0013, 0x00 },
	{ 0x0015, 0x00 },
	{ 0x0017, 0x00 },
	{ 0x0019, 0x30 },
	{ 0x001b, 0x01 },
	{ 0x001d, 0x18 },
	{ 0x001f, 0x29 },
	{ 0x0021, 0x09 },
	{ 0x0023, 0x02 },
	{ 0x0025, 0x00 },
	{ 0x0026, 0x00 },
	{ 0x0028, 0x03 },
	{ 0x0053, 0x00 },
	{ 0x0055, 0x00 },
	{ 0x0056, 0x00 },
	{ 0x0057, 0x00 },
	{ 0x0058, 0x00 },
	{ 0x005a, 0x00 },
	{ 0x005c, 0x00 },
	{ 0x005d, 0x00 },
	{ 0x005e, 0x10 },
	{ 0x005f, 0xec },
	{ 0x0061, 0x10 },
	{ 0x0062, 0x19 },
	{ 0x0064, 0x00 },
	{ 0x0066, 0x08 },
	{ 0x0068, 0x00 },
	{ 0x006a, 0x00 },
	{ 0x006c, 0x00 },
	{ 0x006e, 0x00 },
	{ 0x0100, 0x80 },
	{ 0x0100, 0x51 },
	{ 0x0102, 0x23 },
	{ 0x0102, 0x0f },
	{ 0x0104, 0x6c },
	{ 0x0105, 0xec },
	{ 0x0106, 0x00 },
	{ 0x0107, 0x00 },
	{ 0x0108, 0x00 },
	{ 0x0200, 0x40 },
	{ 0x0201, 0x00 },
	{ 0x0202, 0x00 },
	{ 0x0203, 0x00 },
	{ 0x0301, 0x02 },
	{ 0x0302, 0xaa },
	{ 0x0303, 0x2a },
	{ 0x0304, 0x6a },
	{ 0x0306, 0xb0 },
	{ 0x0308, 0x48 },
	{ 0x030a, 0x0a },
	{ 0x030b, 0x4b },
	{ 0x030d, 0x7d },
	{ 0x030e, 0xef },
	{ 0x030f, 0x5a },
	{ 0x0311, 0x00 },
	{ 0x0312, 0x3e },
	{ 0x0313, 0x86 },
	{ 0x0315, 0xa8 },
	{ 0x0318, 0x1b },
	{ 0x031a, 0x3d },
	{ 0x031c, 0x40 },
	{ 0x031d, 0x40 },
	{ 0x031e, 0x30 },
	{ 0x031f, 0xbb },
	{ 0x0320, 0xa5 },
	{ 0x0321, 0xa5 },
	{ 0x0323, 0x5a },
	{ 0x0324, 0xaa },
	{ 0x0325, 0x80 },
	{ 0x0326, 0xaa },
	{ 0x0327, 0x66 },
	{ 0x0328, 0x94 },
	{ 0x0329, 0x00 },
	{ 0x0330, 0x00 },
	{ 0x0331, 0x30 },
	{ 0x0332, 0x05 },
	{ 0x0400, 0x03 },
	{ 0x0401, 0x02 },
	{ 0x0402, 0x01 },
	{ 0x0403, 0x23 },
	{ 0x0404, 0x45 },
	{ 0x0405, 0x67 },
	{ 0x0500, 0x80 },
	{ 0x0501, 0x00 },
	{ 0x0502, 0x00 },
	{ 0x0503, 0x00 },
	{ 0x0504, 0xff },
	{ 0x0505, 0x24 },
	{ 0x0600, 0x75 },
	{ 0x0601, 0x41 },
	{ 0x0602, 0x60 },
	{ 0x0603, 0x7f },
	{ 0x0604, 0x65 },
	{ 0x0605, 0x43 },
	{ 0x0606, 0x00 },
	{ 0x0607, 0x00 },
	{ 0x0608, 0x00 },
	{ 0x0609, 0x00 },
	{ 0x060a, 0x00 },
	{ 0x060b, 0x00 },
	{ 0x060c, 0x00 },
	{ 0x060d, 0x00 },
	{ 0x060e, 0x00 },
	{ 0x060f, 0x00 },
	{ 0x0700, 0x15 },
	{ 0x0701, 0xc8 },
	{ 0x0704, 0x02 },
	{ 0x0705, 0x00 },
	{ 0x0706, 0x00 },
	{ 0x0707, 0x80 },
	{ 0x0708, 0x08 },
	{ 0x0709, 0x00 },
	{ 0x0800, 0x00 },
	{ 0x0801, 0x00 },
	{ 0x0802, 0x09 },
	{ 0x0803, 0x00 },
	{ 0x0900, 0x87 },
	{ 0x0a01, 0x99 },
	{ 0x0a02, 0x40 },
	{ 0x0a03, 0x10 },
	{ 0x0b00, 0x50 },
	{ 0x0b01, 0xc3 },
	{ 0x0c00, 0x84 },
	{ 0x0c01, 0x00 },
	{ 0x0c02, 0xbb },
	{ 0x0c03, 0x80 },
	{ 0x0c04, 0x10 },
	{ 0x0c05, 0x30 },
	{ 0x0c06, 0x00 },
	{ 0x0d00, 0x80 },
	{ 0x0d01, 0xbb },
	{ 0x0d02, 0x80 },
	{ 0x0d03, 0x00 },
	{ 0x0d04, 0x00 },
	{ 0x0d05, 0x00 },
	{ 0x0e00, 0x80 },
	{ 0x0e01, 0xbb },
	{ 0x0e02, 0x80 },
	{ 0x0e03, 0x00 },
	{ 0x0e04, 0x10 },
	{ 0x0e05, 0x30 },
	{ 0x0f00, 0x80 },
	{ 0x0f01, 0xbb },
	{ 0x0f02, 0x80 },
	{ 0x0f03, 0x00 },
	{ 0x0f04, 0x10 },
	{ 0x0f05, 0x30 },
	{ 0x0f06, 0x88 },
	{ 0x0f07, 0x88 },
	{ 0x0f08, 0x00 },
	{ 0x0f09, 0x00 },
};

static bool rt1019_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case RT1019_PWR_STRP_1:
	case RT1019_PWR_STRP_2:
	case RT1019_SIL_DET_GAT:
	case RT1019_PHASE_SYNC:
	case RT1019_STAT_MACH_2:
	case RT1019_FS_DET_1:
	case RT1019_FS_DET_2:
	case RT1019_FS_DET_3:
	case RT1019_FS_DET_4:
	case RT1019_FS_DET_5:
	case RT1019_FS_DET_6:
	case RT1019_FS_DET_7:
	case RT1019_ANA_READ:
	case RT1019_VER_ID:
	case RT1019_CUSTOM_ID:
	case RT1019_VEND_ID_1:
	case RT1019_VEND_ID_2:
	case RT1019_DEV_ID_1:
	case RT1019_DEV_ID_2:
	case RT1019_CAL_TOP_3:
	case RT1019_CAL_TOP_7:
	case RT1019_CAL_TOP_17:
	case RT1019_CAL_TOP_18:
	case RT1019_CAL_TOP_19:
	case RT1019_CAL_TOP_20:
	case RT1019_CAL_TOP_21:
	case RT1019_CAL_TOP_22:
	case RT1019_MDRE_CTRL_2:
	case RT1019_MDRE_CTRL_3:
	case RT1019_MDRE_CTRL_4:
	case RT1019_SIL_DET_2:
	case RT1019_PWM_DC_DET_1:
	case RT1019_PMC_8:
	case RT1019_PMC_9:
	case RT1019_SPKDRC_7:
	case RT1019_HALF_FREQ_7:
	case RT1019_CUR_CTRL_11:
	case RT1019_CUR_CTRL_12:
	case RT1019_CUR_CTRL_13:
		return true;

	default:
		return false;
	}
}

static bool rt1019_readable_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case RT1019_RESET:
	case RT1019_PAD_DRV_1:
	case RT1019_PAD_DRV_2:
	case RT1019_PAD_PULL_1:
	case RT1019_PAD_PULL_2:
	case RT1019_PAD_PULL_3:
	case RT1019_I2C_CTRL_1:
	case RT1019_I2C_CTRL_2:
	case RT1019_I2C_CTRL_3:
	case RT1019_IDS_CTRL:
	case RT1019_ASEL_CTRL:
	case RT1019_PLL_RESET:
	case RT1019_PWR_STRP_1:
	case RT1019_PWR_STRP_2:
	case RT1019_BEEP_TONE:
	case RT1019_SIL_DET_GAT:
	case RT1019_CLASSD_TIME:
	case RT1019_CLASSD_OCP:
	case RT1019_PHASE_SYNC:
	case RT1019_STAT_MACH_1:
	case RT1019_STAT_MACH_2:
	case RT1019_EFF_CTRL:
	case RT1019_FS_DET_1:
	case RT1019_FS_DET_2:
	case RT1019_FS_DET_3:
	case RT1019_FS_DET_4:
	case RT1019_FS_DET_5:
	case RT1019_FS_DET_6:
	case RT1019_FS_DET_7:
	case RT1019_ANA_CTRL:
	case RT1019_DUMMY_A:
	case RT1019_DUMMY_B:
	case RT1019_DUMMY_C:
	case RT1019_DUMMY_D:
	case RT1019_ANA_READ:
	case RT1019_VER_ID:
	case RT1019_CUSTOM_ID:
	case RT1019_VEND_ID_1:
	case RT1019_VEND_ID_2:
	case RT1019_DEV_ID_1:
	case RT1019_DEV_ID_2:
	case RT1019_TEST_PAD:
	case RT1019_SDB_CTRL:
	case RT1019_TEST_CTRL_1:
	case RT1019_TEST_CTRL_2:
	case RT1019_TEST_CTRL_3:
	case RT1019_SCAN_MODE:
	case RT1019_CLK_TREE_1:
	case RT1019_CLK_TREE_2:
	case RT1019_CLK_TREE_3:
	case RT1019_CLK_TREE_4:
	case RT1019_CLK_TREE_5:
	case RT1019_CLK_TREE_6:
	case RT1019_CLK_TREE_7:
	case RT1019_CLK_TREE_8:
	case RT1019_CLK_TREE_9:
	case RT1019_ASRC_1:
	case RT1019_ASRC_2:
	case RT1019_ASRC_3:
	case RT1019_ASRC_4:
	case RT1019_SYS_CLK:
	case RT1019_BIAS_CUR_1:
	case RT1019_BIAS_CUR_2:
	case RT1019_BIAS_CUR_3:
	case RT1019_BIAS_CUR_4:
	case RT1019_CHOP_CLK_DAC:
	case RT1019_CHOP_CLK_ADC:
	case RT1019_LDO_CTRL_1:
	case RT1019_LDO_CTRL_2:
	case RT1019_PM_ANA_1:
	case RT1019_PM_ANA_2:
	case RT1019_PM_ANA_3:
	case RT1019_PLL_1:
	case RT1019_PLL_2:
	case RT1019_PLL_3:
	case RT1019_PLL_INT_1:
	case RT1019_PLL_INT_3:
	case RT1019_MIXER:
	case RT1019_CLD_OUT_1:
	case RT1019_CLD_OUT_2:
	case RT1019_CLD_OUT_3:
	case RT1019_CLD_OUT_4:
	case RT1019_CLD_OUT_5:
	case RT1019_CLD_OUT_6:
	case RT1019_CLS_INT_REG_1:
	case RT1019_CLS_INT_REG_2:
	case RT1019_CLS_INT_REG_3:
	case RT1019_CLS_INT_REG_4:
	case RT1019_CLS_INT_REG_5:
	case RT1019_CLS_INT_REG_6:
	case RT1019_CLS_INT_REG_7:
	case RT1019_CLS_INT_REG_8:
	case RT1019_CLS_INT_REG_9:
	case RT1019_CLS_INT_REG_10:
	case RT1019_TDM_1:
	case RT1019_TDM_2:
	case RT1019_TDM_3:
	case RT1019_TDM_4:
	case RT1019_TDM_5:
	case RT1019_TDM_6:
	case RT1019_DVOL_1:
	case RT1019_DVOL_2:
	case RT1019_DVOL_3:
	case RT1019_DVOL_4:
	case RT1019_DMIX_MONO_1:
	case RT1019_DMIX_MONO_2:
	case RT1019_CAL_TOP_1:
	case RT1019_CAL_TOP_2:
	case RT1019_CAL_TOP_3:
	case RT1019_CAL_TOP_4:
	case RT1019_CAL_TOP_5:
	case RT1019_CAL_TOP_6:
	case RT1019_CAL_TOP_7:
	case RT1019_CAL_TOP_8:
	case RT1019_CAL_TOP_9:
	case RT1019_CAL_TOP_10:
	case RT1019_CAL_TOP_11:
	case RT1019_CAL_TOP_12:
	case RT1019_CAL_TOP_13:
	case RT1019_CAL_TOP_14:
	case RT1019_CAL_TOP_15:
	case RT1019_CAL_TOP_16:
	case RT1019_CAL_TOP_17:
	case RT1019_CAL_TOP_18:
	case RT1019_CAL_TOP_19:
	case RT1019_CAL_TOP_20:
	case RT1019_CAL_TOP_21:
	case RT1019_CAL_TOP_22:
	case RT1019_MDRE_CTRL_1:
	case RT1019_MDRE_CTRL_2:
	case RT1019_MDRE_CTRL_3:
	case RT1019_MDRE_CTRL_4:
	case RT1019_MDRE_CTRL_5:
	case RT1019_MDRE_CTRL_6:
	case RT1019_MDRE_CTRL_7:
	case RT1019_MDRE_CTRL_8:
	case RT1019_MDRE_CTRL_9:
	case RT1019_MDRE_CTRL_10:
	case RT1019_SCC_CTRL_1:
	case RT1019_SCC_CTRL_2:
	case RT1019_SCC_CTRL_3:
	case RT1019_SCC_DUMMY:
	case RT1019_SIL_DET_1:
	case RT1019_SIL_DET_2:
	case RT1019_PWM_DC_DET_1:
	case RT1019_PWM_DC_DET_2:
	case RT1019_PWM_DC_DET_3:
	case RT1019_PWM_DC_DET_4:
	case RT1019_BEEP_1:
	case RT1019_BEEP_2:
	case RT1019_PMC_1:
	case RT1019_PMC_2:
	case RT1019_PMC_3:
	case RT1019_PMC_4:
	case RT1019_PMC_5:
	case RT1019_PMC_6:
	case RT1019_PMC_7:
	case RT1019_PMC_8:
	case RT1019_PMC_9:
	case RT1019_SPKDRC_1:
	case RT1019_SPKDRC_2:
	case RT1019_SPKDRC_3:
	case RT1019_SPKDRC_4:
	case RT1019_SPKDRC_5:
	case RT1019_SPKDRC_6:
	case RT1019_SPKDRC_7:
	case RT1019_HALF_FREQ_1:
	case RT1019_HALF_FREQ_2:
	case RT1019_HALF_FREQ_3:
	case RT1019_HALF_FREQ_4:
	case RT1019_HALF_FREQ_5:
	case RT1019_HALF_FREQ_6:
	case RT1019_HALF_FREQ_7:
	case RT1019_CUR_CTRL_1:
	case RT1019_CUR_CTRL_2:
	case RT1019_CUR_CTRL_3:
	case RT1019_CUR_CTRL_4:
	case RT1019_CUR_CTRL_5:
	case RT1019_CUR_CTRL_6:
	case RT1019_CUR_CTRL_7:
	case RT1019_CUR_CTRL_8:
	case RT1019_CUR_CTRL_9:
	case RT1019_CUR_CTRL_10:
	case RT1019_CUR_CTRL_11:
	case RT1019_CUR_CTRL_12:
	case RT1019_CUR_CTRL_13:
		return true;
	default:
		return false;
	}
}

static const DECLARE_TLV_DB_SCALE(dac_vol_tlv, -9525, 75, 0);

static const char * const rt1019_din_source_select[] = {
	"Left",
	"Right",
	"Left + Right average",
};

static SOC_ENUM_SINGLE_DECL(rt1019_mono_lr_sel, RT1019_IDS_CTRL, 0,
	rt1019_din_source_select);

static const struct snd_kcontrol_new rt1019_snd_controls[] = {
	SOC_SINGLE_TLV("DAC Playback Volume", RT1019_DMIX_MONO_1, 0,
		127, 0, dac_vol_tlv),
	SOC_ENUM("Mono LR Select", rt1019_mono_lr_sel),
};

static int r1019_dac_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_write(component, RT1019_SDB_CTRL, 0xb);
		break;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_write(component, RT1019_SDB_CTRL, 0xa);
		break;
	default:
		break;
	}

	return 0;
}

static const struct snd_soc_dapm_widget rt1019_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("AIFRX", "AIF Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC_E("DAC", NULL, SND_SOC_NOPM, 0, 0,
		r1019_dac_event, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUTPUT("SPO"),
};

static const struct snd_soc_dapm_route rt1019_dapm_routes[] = {
	{ "DAC", NULL, "AIFRX" },
	{ "SPO", NULL, "DAC" },
};

static int rt1019_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct rt1019_priv *rt1019 = snd_soc_component_get_drvdata(component);
	int pre_div, bclk_ms, frame_size;
	unsigned int val_len = 0, sys_div_da_filter = 0;
	unsigned int sys_dac_osr = 0, sys_fifo_clk = 0;
	unsigned int sys_clk_cal = 0, sys_asrc_in = 0;

	rt1019->lrck = params_rate(params);
	pre_div = rl6231_get_clk_info(rt1019->sysclk, rt1019->lrck);
	if (pre_div < 0) {
		dev_err(component->dev, "Unsupported clock setting\n");
		return -EINVAL;
	}

	frame_size = snd_soc_params_to_frame_size(params);
	if (frame_size < 0) {
		dev_err(component->dev, "Unsupported frame size: %d\n", frame_size);
		return -EINVAL;
	}

	bclk_ms = frame_size > 32;
	rt1019->bclk = rt1019->lrck * (32 << bclk_ms);

	dev_dbg(dai->dev, "bclk is %dHz and lrck is %dHz\n",
		rt1019->bclk, rt1019->lrck);
	dev_dbg(dai->dev, "bclk_ms is %d and pre_div is %d for iis %d\n",
				bclk_ms, pre_div, dai->id);

	switch (pre_div) {
	case 0:
		sys_div_da_filter = RT1019_SYS_DIV_DA_FIL_DIV1;
		sys_dac_osr = RT1019_SYS_DA_OSR_DIV1;
		sys_asrc_in = RT1019_ASRC_256FS_DIV1;
		sys_fifo_clk = RT1019_SEL_FIFO_DIV1;
		sys_clk_cal = RT1019_SEL_CLK_CAL_DIV1;
		break;
	case 1:
		sys_div_da_filter = RT1019_SYS_DIV_DA_FIL_DIV2;
		sys_dac_osr = RT1019_SYS_DA_OSR_DIV2;
		sys_asrc_in = RT1019_ASRC_256FS_DIV2;
		sys_fifo_clk = RT1019_SEL_FIFO_DIV2;
		sys_clk_cal = RT1019_SEL_CLK_CAL_DIV2;
		break;
	case 3:
		sys_div_da_filter = RT1019_SYS_DIV_DA_FIL_DIV4;
		sys_dac_osr = RT1019_SYS_DA_OSR_DIV4;
		sys_asrc_in = RT1019_ASRC_256FS_DIV4;
		sys_fifo_clk = RT1019_SEL_FIFO_DIV4;
		sys_clk_cal = RT1019_SEL_CLK_CAL_DIV4;
		break;
	default:
		return -EINVAL;
	}

	switch (params_width(params)) {
	case 16:
		break;
	case 20:
		val_len = RT1019_I2S_DL_20;
		break;
	case 24:
		val_len = RT1019_I2S_DL_24;
		break;
	case 32:
		val_len = RT1019_I2S_DL_32;
		break;
	case 8:
		val_len = RT1019_I2S_DL_8;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, RT1019_TDM_2, RT1019_I2S_DL_MASK,
			val_len);
	snd_soc_component_update_bits(component, RT1019_CLK_TREE_1,
			RT1019_SEL_FIFO_MASK, sys_fifo_clk);
	snd_soc_component_update_bits(component, RT1019_CLK_TREE_2,
			RT1019_SYS_DIV_DA_FIL_MASK | RT1019_SYS_DA_OSR_MASK |
			RT1019_ASRC_256FS_MASK, sys_div_da_filter | sys_dac_osr |
			sys_asrc_in);
	snd_soc_component_update_bits(component, RT1019_CLK_TREE_3,
			RT1019_SEL_CLK_CAL_MASK, sys_clk_cal);

	return 0;
}

static int rt1019_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct snd_soc_component *component = dai->component;
	unsigned int reg_val = 0, reg_val2 = 0;

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		reg_val2 |= RT1019_TDM_BCLK_INV;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		break;

	case SND_SOC_DAIFMT_LEFT_J:
		reg_val |= RT1019_I2S_DF_LEFT;
		break;

	case SND_SOC_DAIFMT_DSP_A:
		reg_val |= RT1019_I2S_DF_PCM_A_R;
		break;

	case SND_SOC_DAIFMT_DSP_B:
		reg_val |= RT1019_I2S_DF_PCM_B_R;
		break;

	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, RT1019_TDM_2,
		RT1019_I2S_DF_MASK, reg_val);
	snd_soc_component_update_bits(component, RT1019_TDM_1,
		RT1019_TDM_BCLK_MASK, reg_val2);

	return 0;
}

static int rt1019_set_dai_sysclk(struct snd_soc_dai *dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct rt1019_priv *rt1019 = snd_soc_component_get_drvdata(component);
	unsigned int reg_val = 0;

	if (freq == rt1019->sysclk && clk_id == rt1019->sysclk_src)
		return 0;

	switch (clk_id) {
	case RT1019_SCLK_S_BCLK:
		reg_val |= RT1019_CLK_SYS_PRE_SEL_BCLK;
		break;

	case RT1019_SCLK_S_PLL:
		reg_val |= RT1019_CLK_SYS_PRE_SEL_PLL;
		break;

	default:
		dev_err(component->dev, "Invalid clock id (%d)\n", clk_id);
		return -EINVAL;
	}

	rt1019->sysclk = freq;
	rt1019->sysclk_src = clk_id;

	dev_dbg(dai->dev, "Sysclk is %dHz and clock id is %d\n", freq, clk_id);

	snd_soc_component_update_bits(component, RT1019_CLK_TREE_1,
		RT1019_CLK_SYS_PRE_SEL_MASK, reg_val);

	return 0;
}

static int rt1019_set_dai_pll(struct snd_soc_dai *dai, int pll_id, int source,
			unsigned int freq_in, unsigned int freq_out)
{
	struct snd_soc_component *component = dai->component;
	struct rt1019_priv *rt1019 = snd_soc_component_get_drvdata(component);
	struct rl6231_pll_code pll_code;
	int ret;

	if (!freq_in || !freq_out) {
		dev_dbg(component->dev, "PLL disabled\n");
		rt1019->pll_in = 0;
		rt1019->pll_out = 0;
		return 0;
	}

	if (source == rt1019->pll_src && freq_in == rt1019->pll_in &&
		freq_out == rt1019->pll_out)
		return 0;

	switch (source) {
	case RT1019_PLL_S_BCLK:
		snd_soc_component_update_bits(component, RT1019_CLK_TREE_1,
			RT1019_PLL_SRC_MASK, RT1019_PLL_SRC_SEL_BCLK);
		break;

	case RT1019_PLL_S_RC25M:
		snd_soc_component_update_bits(component, RT1019_CLK_TREE_1,
			RT1019_PLL_SRC_MASK, RT1019_PLL_SRC_SEL_RC);
		break;

	default:
		dev_err(component->dev, "Unknown PLL source %d\n", source);
		return -EINVAL;
	}

	ret = rl6231_pll_calc(freq_in, freq_out, &pll_code);
	if (ret < 0) {
		dev_err(component->dev, "Unsupport input clock %d\n", freq_in);
		return ret;
	}

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
		pll_code.m_bp, (pll_code.m_bp ? 0 : pll_code.m_code),
		pll_code.n_code, pll_code.k_code);

	snd_soc_component_update_bits(component, RT1019_PWR_STRP_2,
		RT1019_AUTO_BITS_SEL_MASK | RT1019_AUTO_CLK_SEL_MASK,
		RT1019_AUTO_BITS_SEL_MANU | RT1019_AUTO_CLK_SEL_MANU);
	snd_soc_component_update_bits(component, RT1019_PLL_1,
		RT1019_PLL_M_MASK | RT1019_PLL_M_BP_MASK | RT1019_PLL_Q_8_8_MASK,
		(pll_code.m_bp ? 0 : pll_code.m_code) << RT1019_PLL_M_SFT |
		pll_code.m_bp << RT1019_PLL_M_BP_SFT |
		((pll_code.n_code >> 8) & RT1019_PLL_Q_8_8_MASK));
	snd_soc_component_update_bits(component, RT1019_PLL_2,
		RT1019_PLL_Q_7_0_MASK, pll_code.n_code & RT1019_PLL_Q_7_0_MASK);
	snd_soc_component_update_bits(component, RT1019_PLL_3,
		RT1019_PLL_K_MASK, pll_code.k_code);

	rt1019->pll_in = freq_in;
	rt1019->pll_out = freq_out;
	rt1019->pll_src = source;

	return 0;
}

static int rt1019_set_tdm_slot(struct snd_soc_dai *dai, unsigned int tx_mask,
			unsigned int rx_mask, int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	unsigned int val = 0, rx_slotnum;
	int ret = 0, first_bit;

	switch (slots) {
	case 4:
		val |= RT1019_I2S_TX_4CH;
		break;
	case 6:
		val |= RT1019_I2S_TX_6CH;
		break;
	case 8:
		val |= RT1019_I2S_TX_8CH;
		break;
	case 2:
		break;
	default:
		return -EINVAL;
	}

	switch (slot_width) {
	case 20:
		val |= RT1019_I2S_DL_20;
		break;
	case 24:
		val |= RT1019_I2S_DL_24;
		break;
	case 32:
		val |= RT1019_I2S_DL_32;
		break;
	case 8:
		val |= RT1019_I2S_DL_8;
		break;
	case 16:
		break;
	default:
		return -EINVAL;
	}

	/* Rx slot configuration */
	rx_slotnum = hweight_long(rx_mask);
	if (rx_slotnum != 1) {
		ret = -EINVAL;
		dev_err(component->dev, "too many rx slots or zero slot\n");
		goto _set_tdm_err_;
	}
	/* This is an assumption that the system sends stereo audio to the
	 * amplifier typically. And the stereo audio is placed in slot 0/2/4/6
	 * as the starting slot. The users could select the channel from
	 * L/R/L+R by "Mono LR Select" control.
	 */
	first_bit = __ffs(rx_mask);
	switch (first_bit) {
	case 0:
	case 2:
	case 4:
	case 6:
		snd_soc_component_update_bits(component,
			RT1019_TDM_3,
			RT1019_TDM_I2S_TX_L_DAC1_1_MASK |
			RT1019_TDM_I2S_TX_R_DAC1_1_MASK,
			(first_bit << RT1019_TDM_I2S_TX_L_DAC1_1_SFT) |
			((first_bit + 1) << RT1019_TDM_I2S_TX_R_DAC1_1_SFT));
		break;
	case 1:
	case 3:
	case 5:
	case 7:
		snd_soc_component_update_bits(component,
			RT1019_TDM_3,
			RT1019_TDM_I2S_TX_L_DAC1_1_MASK |
			RT1019_TDM_I2S_TX_R_DAC1_1_MASK,
			((first_bit - 1) << RT1019_TDM_I2S_TX_L_DAC1_1_SFT) |
			(first_bit << RT1019_TDM_I2S_TX_R_DAC1_1_SFT));
		break;
	default:
		ret = -EINVAL;
		goto _set_tdm_err_;
	}

	snd_soc_component_update_bits(component, RT1019_TDM_2,
		RT1019_I2S_CH_TX_MASK | RT1019_I2S_DF_MASK, val);

_set_tdm_err_:
	return ret;
}

static int rt1019_probe(struct snd_soc_component *component)
{
	struct rt1019_priv *rt1019 = snd_soc_component_get_drvdata(component);

	rt1019->component = component;
	snd_soc_component_write(component, RT1019_SDB_CTRL, 0xa);

	return 0;
}

#define RT1019_STEREO_RATES SNDRV_PCM_RATE_8000_192000
#define RT1019_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

static struct snd_soc_dai_ops rt1019_aif_dai_ops = {
	.hw_params = rt1019_hw_params,
	.set_fmt = rt1019_set_dai_fmt,
	.set_sysclk = rt1019_set_dai_sysclk,
	.set_pll = rt1019_set_dai_pll,
	.set_tdm_slot = rt1019_set_tdm_slot,
};

static struct snd_soc_dai_driver rt1019_dai[] = {
	{
		.name = "rt1019-aif",
		.id = 0,
		.playback = {
			.stream_name = "AIF Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT1019_STEREO_RATES,
			.formats = RT1019_FORMATS,
		},
		.ops = &rt1019_aif_dai_ops,
	}
};

static const struct snd_soc_component_driver soc_component_dev_rt1019 = {
	.probe = rt1019_probe,
	.controls		= rt1019_snd_controls,
	.num_controls		= ARRAY_SIZE(rt1019_snd_controls),
	.dapm_widgets		= rt1019_dapm_widgets,
	.num_dapm_widgets	= ARRAY_SIZE(rt1019_dapm_widgets),
	.dapm_routes		= rt1019_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt1019_dapm_routes),
	.non_legacy_dai_naming	= 1,
};

static const struct regmap_config rt1019_regmap = {
	.reg_bits = 16,
	.val_bits = 8,
	.use_single_read = true,
	.use_single_write = true,
	.max_register = RT1019_CUR_CTRL_13,
	.volatile_reg = rt1019_volatile_register,
	.readable_reg = rt1019_readable_register,
	.cache_type = REGCACHE_RBTREE,
	.reg_defaults = rt1019_reg,
	.num_reg_defaults = ARRAY_SIZE(rt1019_reg),
};

static const struct i2c_device_id rt1019_i2c_id[] = {
	{ "rt1019", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, rt1019_i2c_id);

static const struct of_device_id rt1019_of_match[] = {
	{ .compatible = "realtek,rt1019", },
	{},
};
MODULE_DEVICE_TABLE(of, rt1019_of_match);

#ifdef CONFIG_ACPI
static const struct acpi_device_id rt1019_acpi_match[] = {
	{ "10EC1019", 0},
	{ },
};
MODULE_DEVICE_TABLE(acpi, rt1019_acpi_match);
#endif

static int rt1019_i2c_probe(struct i2c_client *i2c,
	const struct i2c_device_id *id)
{
	struct rt1019_priv *rt1019;
	int ret;
	unsigned int val, val2, dev_id;

	rt1019 = devm_kzalloc(&i2c->dev, sizeof(struct rt1019_priv),
				GFP_KERNEL);
	if (!rt1019)
		return -ENOMEM;

	i2c_set_clientdata(i2c, rt1019);

	rt1019->regmap = devm_regmap_init_i2c(i2c, &rt1019_regmap);
	if (IS_ERR(rt1019->regmap)) {
		ret = PTR_ERR(rt1019->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	regmap_read(rt1019->regmap, RT1019_DEV_ID_1, &val);
	regmap_read(rt1019->regmap, RT1019_DEV_ID_2, &val2);
	dev_id = val << 8 | val2;
	if (dev_id != RT1019_DEVICE_ID_VAL && dev_id != RT1019_DEVICE_ID_VAL2) {
		dev_err(&i2c->dev,
			"Device with ID register 0x%x is not rt1019\n", dev_id);
		return -ENODEV;
	}

	return devm_snd_soc_register_component(&i2c->dev,
		&soc_component_dev_rt1019, rt1019_dai, ARRAY_SIZE(rt1019_dai));
}

static struct i2c_driver rt1019_i2c_driver = {
	.driver = {
		.name = "rt1019",
		.of_match_table = of_match_ptr(rt1019_of_match),
		.acpi_match_table = ACPI_PTR(rt1019_acpi_match),
	},
	.probe = rt1019_i2c_probe,
	.id_table = rt1019_i2c_id,
};
module_i2c_driver(rt1019_i2c_driver);

MODULE_DESCRIPTION("ASoC RT1019 driver");
MODULE_AUTHOR("Jack Yu <jack.yu@realtek.com>");
MODULE_LICENSE("GPL v2");
