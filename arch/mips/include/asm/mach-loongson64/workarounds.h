/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_MACH_LOONGSON64_WORKAROUNDS_H_
#define __ASM_MACH_LOONGSON64_WORKAROUNDS_H_

#define WORKAROUND_CPUFREQ	0x00000001
#define WORKAROUND_CPUHOTPLUG	0x00000002
#define WORKAROUND_USB_TMCS	0x00000010

void gpio_lvds_off(void);
void turn_off_lvds(void);
void turn_on_lvds(void);

#endif
