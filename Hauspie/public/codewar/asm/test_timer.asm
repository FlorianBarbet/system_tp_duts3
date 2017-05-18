start:
	move 	#0x100, sp		; init stack
	jmp	main			; start program

;;; Timer initialisation function
;;; sets the timer to trigger every 5 cycle, but do not start it
set_timer:
	push	r0
	push	r1
	xor	r0, r0			; clear r0
	move.l	r0, @B			; set timer clock to 0
	move.l	#1, r0
	move.l	#20, r1
	move.l	r0, @C		; increment timer every cycle
	move.l	r1, @A		; trigger timer when 5 cycle has been done
	pop	r1
	pop	r0
	rts

;;; Timer interrupt routine. Simply increment r1 and restart timer
timer_int:
	push 	r0
	add	#1, r1		; increment r1
	jsr	set_timer	; reconfigure timer
	move.l	#1, r0
	move.l	r0, @D		; starts it
	pop	r0
	rte

main:
	move.l	timer_int, r0
	move.l	r0, @4		; load timer interruption routine in the interruption vector
	jsr	set_timer	; configure timer
	move.l	#1, r0
	move.l	r0, @D		; start timer
	
	move	#0, r0		; init counter
	move	#0, r1
loop:
	add	#1, r0		; increment counter
	bra	loop		; infinite loop
