	jmp	main

func:	push	r1		; stack r1 @ret param
	push	r2		; stack r2 r1 @ret param
	move	sp, r1
	add	#4, r1		; r1 has now the addr of the param
	move	(r1), r2	; r2 is the param
	move	-(r1), r2	; r2 is the param
	move	(r1)+, r2	; r2 is the param
	add	#1, r2		; increment r2
	move	r2, r0		; r0 is the return value
	pop	r2		; stack r1 @ret param
	pop	r1		; stack @ret param
	rts			; stack param
	

main:	
	move 	#12, r0
	move.l	@14, r1
	add	r0,  r1
	push	r1		; stack r1
	jsr	func		;
	add	#2, sp		; empty stack
	move	r0, @0		; move the return value to the 0 address
