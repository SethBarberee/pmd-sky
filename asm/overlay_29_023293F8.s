	.include "asm/macros.inc"
	.include "overlay_29_023293F8.inc"

	.text


; https://decomp.me/scratch/jggXS

	arm_func_start DoMoveMoonlight
DoMoveMoonlight: ; 0x023293F8
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	mov r4, r1
	bl GetApparentWeather
	mov ip, #1
	ldr r1, _02329434 ; =MOONLIGHT_HP_RESTORATION_TABLE
	mov r0, r0, lsl #1
	ldrsh r2, [r1, r0]
	mov r0, r5
	mov r1, r4
	mov r3, #0
	str ip, [sp]
	bl TryIncreaseHp
	mov r0, #1
	ldmia sp!, {r3, r4, r5, pc}
	.align 2, 0
_02329434: .word MOONLIGHT_HP_RESTORATION_TABLE
	arm_func_end DoMoveMoonlight

