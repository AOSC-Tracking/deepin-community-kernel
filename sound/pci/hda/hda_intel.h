/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 */
#ifndef __SOUND_HDA_INTEL_H
#define __SOUND_HDA_INTEL_H

#include "hda_controller.h"

struct hda_intel {
	struct azx chip;

	/* for pending irqs */
	struct work_struct irq_pending_work;

	/* sync probing */
	struct completion probe_wait;
	struct delayed_work probe_work;

	/* card list (for power_save trigger) */
	struct list_head list;

	/* extra flags */
	unsigned int irq_pending_warned:1;
	unsigned int probe_continued:1;

	/* vga_switcheroo setup */
	unsigned int use_vga_switcheroo:1;
	unsigned int vga_switcheroo_registered:1;
	unsigned int init_failed:1; /* delayed init failed */
	unsigned int freed:1; /* resources already released */

	bool need_i915_power:1; /* the hda controller needs i915 power */

	int probe_retry;	/* being probe-retry */
};

struct gf_private {
	struct hda_intel hda;

	phys_addr_t diu_fb_stream_ofs[2];
	void __iomem *diu_fb_stream_vaddr[2];
	unsigned int diu_fb_stream_pos[2];

	phys_addr_t diu_fb_bdl_ofs[2];
	void __iomem *diu_fb_bdl_vaddr[2];
};

#endif
