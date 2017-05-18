	move	#1,R0
	move	R0,R1
	move	R1,R2
	move	R3,R4
	move	R4,R5
	move.	R5,-(R6)
	move	R6,(R7)+
	move.l	R7,@3
	bsr	function1
	
	
end:	jmp	end

function1:
	push	R0
	push	R1
loop:
	add	R0,R1
	cmp	#8,R1
	blt	loop
	beq	equal
	move 	R1,R2
return:
	pop	R1
	pop	R2
	rts

equal:
	lsl	#2,R0
	lsr	#3,R0
	xor	R1,R1
	and	R4,R1
	or	R1,R5
	not	R5
	trap	#2
	bra	loop
