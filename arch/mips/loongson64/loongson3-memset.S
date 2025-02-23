/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1998, 1999, 2000 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2007 by Maciej W. Rozycki
 * Copyright (C) 2011, 2012 MIPS Technologies, Inc.
 */
#include <linux/export.h>
#include <asm/asm.h>
#include <asm/asm-offsets.h>
#include <asm/regdef.h>

#define LONG_S_L sdl
#define LONG_S_R sdr

#define STORSIZE 16
#define STORMASK 15

#define EX(insn,reg,addr,handler)			\
9:	insn	reg, addr;				\
	.section __ex_table,"a";			\
	PTR_WD	9b, handler;				\
	.previous

#define EX_GSSQ(reg, addr, handler)			\
	.set push;					\
	.set arch=loongson3a;				\
9:	gssq	reg, reg, addr;				\
	.set pop;					\
	.section __ex_table,"a";			\
	PTR_WD	9b, handler;				\
	.previous

	.macro	f_fill128 dst, offset, val, fixup
	EX_GSSQ(\val, (\offset +  0 * STORSIZE)(\dst), \fixup)
	EX_GSSQ(\val, (\offset +  1 * STORSIZE)(\dst), \fixup)
	EX_GSSQ(\val, (\offset +  2 * STORSIZE)(\dst), \fixup)
	EX_GSSQ(\val, (\offset +  3 * STORSIZE)(\dst), \fixup)
	EX_GSSQ(\val, (\offset +  4 * STORSIZE)(\dst), \fixup)
	EX_GSSQ(\val, (\offset +  5 * STORSIZE)(\dst), \fixup)
	EX_GSSQ(\val, (\offset +  6 * STORSIZE)(\dst), \fixup)
	EX_GSSQ(\val, (\offset +  7 * STORSIZE)(\dst), \fixup)
	.endm

/*
 * memset(void *s, int c, size_t n)
 *
 * a0: start of area to clear
 * a1: char to fill with
 * a2: size of area to clear
 */
	.set	noreorder
	.align	5
LEAF(memset)
EXPORT_SYMBOL(memset)
	beqz		a1, 1f
	 move		v0, a0			/* result */

	andi		a1, 0xff		/* spread fillword */
	LONG_SLL		t1, a1, 8
	or		a1, t1
	LONG_SLL		t1, a1, 16
	or		a1, t1
	LONG_SLL		t1, a1, 32
	or		a1, t1
1:

FEXPORT(__bzero)
EXPORT_SYMBOL(__bzero)
	sltiu		t0, a2, STORSIZE	/* very small region? */
	bnez		t0, .Lsmall_memset
	 andi		t0, a0, STORMASK	/* aligned? */

	.set		noat
	li		AT, STORSIZE
	beqz		t0, 1f
	 PTR_SUBU	t0, AT			/* alignment in bytes */
	.set		at

	EX(LONG_S_R, a1, (a0), .Lfirst_fixup)	/* make word/dword 8B aligned */
	.set		push
	.set		arch=mips64r2
	PTR_ADDIU	t1, a0, 8
	dins		t1, zero, 0, 3
	.set		pop
	EX(LONG_S, a1, (t1), .Lsecond_fixup)	/* May double copy 8B */

	PTR_SUBU	a0, t0			/* long align ptr */
	PTR_ADDU	a2, t0			/* correct size */

1:	ori		t1, a2, 0x7f		/* # of full blocks */
	xori		t1, 0x7f
	beqz		t1, .Lmemset_partial	/* no block to fill */
	 andi		t0, a2, 0x80-STORSIZE

	PTR_ADDU	t1, a0			/* end address */
	.set		reorder
1:	PTR_ADDIU	a0, 128
	f_fill128 a0, -128, a1, .Lfwd_fixup
	bne		t1, a0, 1b
	.set		noreorder

.Lmemset_partial:
	PTR_LA		t1, 2f			/* where to start */
	.set		noat
	LONG_SRL	AT, t0, 2
	PTR_SUBU	t1, AT
	.set		at
	jr		t1
	 PTR_ADDU	a0, t0			/* dest ptr */

	.set		push
	.set		noreorder
	.set		nomacro
	f_fill128 a0, -128, a1, .Lpartial_fixup	/* ... but first do 16Bs ... */
2:	.set		pop
	andi		a2, STORMASK		/* At most 15B to go */

	beqz		a2, 1f
	 PTR_ADDU	a0, a2			/* What's left */
	.set		push
	.set		arch=mips64r2
	PTR_ADDI	t1, a0, -8
	dins		t1, zero, 0, 3
	.set		pop
	EX(LONG_S, a1, (t1), .Lnotlast_fixup)	/* May double copy 8B */
	EX(LONG_S_L, a1, -1(a0), .Llast_fixup)
1:	jr		ra
	 move		a2, zero

.Lsmall_memset:
	andi		t1, a2, 7
	beq		t1, a2, 1f
	 LONG_SLL	t1, 2

	EX(LONG_S_R, a1, (a0), .Lfirst_fixup)
	EX(LONG_S_L, a1, 7(a0), .Lsmall_memset_fixup)

1:	PTR_LA		t0, 2f
	PTR_SUBU	t1, t0, t1
	jr		t1
	 PTR_ADDU	a0, a2

	EX(sb, a1, -7(a0), .Lsmall_memset_partial_fixup)
	EX(sb, a1, -6(a0), .Lsmall_memset_partial_fixup)
	EX(sb, a1, -5(a0), .Lsmall_memset_partial_fixup)
	EX(sb, a1, -4(a0), .Lsmall_memset_partial_fixup)
	EX(sb, a1, -3(a0), .Lsmall_memset_partial_fixup)
	EX(sb, a1, -2(a0), .Lsmall_memset_partial_fixup)
	EX(sb, a1, -1(a0), .Lsmall_memset_partial_fixup)

2:	jr		ra			/* done */
	 move		a2, zero
	END(memset)

.Lsmall_memset_fixup:
	PTR_ADDIU	t0, a0, 8
	.set		push
	.set		arch=mips64r2
	dins		t0, zero, 0, 3
	.set		pop
	LONG_ADDU	a2, a0
	jr		ra
	 LONG_SUBU	a2, t0

.Lsmall_memset_partial_fixup:
	PTR_L		t0, TI_TASK($28)
	LONG_L		t0, THREAD_BUADDR(t0)
	jr		ra
	 LONG_SUBU	a2, a0, t0

.Lfirst_fixup:
	jr	ra
	 nop

.Lsecond_fixup:
	LONG_ADDU	a2, a0
	jr		ra
	 LONG_SUBU	a2, t1

.Lfwd_fixup:
	PTR_L		t0, TI_TASK($28)
	andi		a2, 0x7f
	LONG_L		t0, THREAD_BUADDR(t0)
	LONG_ADDU	a2, t1
	jr		ra
	 LONG_SUBU	a2, t0

.Lpartial_fixup:
	PTR_L		t0, TI_TASK($28)
	andi		a2, STORMASK
	LONG_L		t0, THREAD_BUADDR(t0)
	LONG_ADDU	a2, a0
	jr		ra
	 LONG_SUBU	a2, t0

.Llast_fixup:
	jr		ra
	andi		a2, 0x7

.Lnotlast_fixup:
	jr		ra
	 PTR_SUBU	a2, a0, t1
