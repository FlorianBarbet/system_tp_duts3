start:
	move	#1, R0
	move	#2, R2
	add	R0, R2
	move	#0xFFFD, R0
	add	R2, R0
	sub	R0, R2
	move	#1, R0
	lsr	#1, R0
	move	#0x8800, R0
	lsl	#1, R0
	move	#0xFF00, R0
	move	#0x00FF, R1
	move 	#0xFF00, R2
	move	#0xFFFF, R3
	or	R1, R0
	and	R2, R0
	xor	R3, R0
	move	#0xF0F0, R0
	move	R0, @2
	move	#2, R0
	not	(R0)+
	not	-(R0)
	not	R0
