	jmp main
swap:				;swap bytes in r1
	move.l	r0, r1
	lsl	#-8, r1
	move.h  r0, r1
	rts

main:	move	#0xCAFE, r1
	jsr	swap
	bsr	swap
	move.l	#b1010, r1 	; r1 now contains 0xFE0A
	push	-(PC)

