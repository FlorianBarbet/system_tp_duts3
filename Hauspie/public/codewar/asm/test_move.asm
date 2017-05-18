start:
	move	#0, R0
	move	#0xCAFE, (R0)
	move	#0xFADE, R1
	move	#0xBEEF, R2
	move.l	(R0), R1
	move.h	(R0), R2
	move	#0xFE, R0
	move	#1, -(R0)
	move	#2, -(R0)
	move	#3, (R0)+
	move	#4, (R0)+
	move.l	R2, @70
	move.h  R2, @71
	move	@0, R1
	move.l  @0, R2
	move.h	@0, R3
	move	#0x0100, R0
	move	(R0), R1
	
