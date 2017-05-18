	;; R5 is my color
start:
	move 	@1, r5
	move	#0x100, sp
	xor	r0, r0
	xor	r1, r1
	jsr	configure_timer	; configure the timer

        move    #255, r0
loop:
        move    r0, r1
        lsl     #8, r1
        or      #1, r1
        move    r5, (r1)
        sub     #1, r0
        jne     loop
        move    #255, r0
        bra     loop

;;; Configure the timer to triger every 50 cycle, periodic
configure_timer:
	push 	r0
	move	overwrite_color_isr, r0
	move	r0, @4		; configure isr
	move	#50, r0
	move.l	r0, @A		; trigger value
	xor	r0, r0		; 
	move.l	r0, @B		; set clock to 0
	add	#1, r0
	move.l	r0, @C		; 1 cycle per clock
	add	#1, r0
	move.l	r0, @D		; 2 to @D -> periodic timer
	pop	r0
	rts
	
	
;;; force my color to be in @0
overwrite_color_isr:
	move	R5, @1		; protect my color
	rte
