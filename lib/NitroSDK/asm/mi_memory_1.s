	.include "asm/macros.inc"
	.include "include/mi_memory.inc"

	.text

;	arm_func_start MI_SwapWord
;MI_SwapWord: ; 0x0207C648
;	.word 0xE1010090
;	bx lr
;	arm_func_end MI_SwapWord

	arm_func_start MI_SwapWord
MI_SwapWord: ; 0x020D4BE0
	swp r0, r0, [r1]
	bx lr
	arm_func_end MI_SwapWord

