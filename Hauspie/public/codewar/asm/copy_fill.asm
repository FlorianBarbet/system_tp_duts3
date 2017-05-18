start:
	move	@1, r5
	move	#0x100, sp
	move	#0x0180, r2
	move	#0x100, r3
	xor 	r4,r4
dup_loop:	
	move	fill_color, r0
	move	fill_color_end, r1
copy_loop:	
	move	(r0)+, (r2)+
	cmp	r0, r1
	bne	copy_loop
	;; copy is done, let's attack color and trap
	move.l	#1, r2
	move	r5, (r2)	;install new color
	move.l	#5, r2
	move.l	#0x80, (r2)	;set trap ISR
	move.h	r2, r4
	trap	r4		;launch interrupt
	move.l	#0x80, r2
	add	r3, r2		;attack next cpu
	bra	dup_loop
	


fill_color:
	move	@1, r5
	move	#0x1000, r3
	move	#0x1, r2
fill_color_loop:
	add	r3, r2
	move	r5, (r2)
fill_color_end:
	bra fill_color_loop
	
