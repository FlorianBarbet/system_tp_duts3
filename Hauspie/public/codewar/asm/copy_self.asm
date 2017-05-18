main:
	move	pc, r0		;store start of program
	sub	#4, r0		;substract size of move pc, r0 opcode to get the REAL pc
	move	@1, r5		;save color
	move	main, r3	;program start at originial position
	move	end, r4		;program end at original position
	sub	r3, r4		;r4 as the size of the program
	move	r0, r1
	add	r4, r1		;r1 now has the real end addr of the programm
	
	
	move	#0x100, sp
	move	#0xFF80, r2		;destination addr
	;; r0 has the addr of the start of the program
	;; r1 has the addr of the end of the program
	;; r2 has the attack address
loop:
	bsr 	duplicate
	move 	r5, @1
	move	#0x0100, r3
	sub	r3, r2
	bra 	loop

duplicate:
	push	r0
	push	r2
dup_loop:
	move	(r0)+, (r2)+	; copy me!
	cmp	r0, r1
	bne	dup_loop
	;; copy is done, lets jump in
	move.l	#0x05, r2
	move	#0x80, r0
	move.l	r0, (r2)	;initialise trap isr
	move.l	#0x01, r2
	move	r5, (r2)	;attack color
	trap	#0xFF		;start !
	pop	r2
	pop	r0
	rts

end:
	bra	end
