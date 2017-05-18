start:
	move 	#0, R0
	move 	#0xAABB, (R0)
	move	#0x0100, SP
	move	middle, R0
middle:
	push	R0
	push	(R0)
	push	-(R0)
	push	(R0)+
	pop	R1
	pop	R2
	pop	R3
	pop	R4
