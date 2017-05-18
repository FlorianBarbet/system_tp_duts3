start:
	move	#0x0100, sp	; init stack
	move 	trap_it, r0	; store address of interrupt routine
	move.l 	r0, @5		; put it in the trap interrupt vector
	move	#0x8000, r1
	lsl	#1, r1		; set carry and zero flag
	trap	#0		; trap myself
	move	r1, @0		; set color. r1 should be set to 2 and flags should be c:1, z:1, n:0
end:
	bra	end		; infinite loop
	
trap_it:
	move	#2, r1		; modify r1 (this will clear flags)
	rte
