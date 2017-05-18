start:
	jmp main

	;; This function computes \sum_{i=0}^{r0} i
calc_sum:
	move	#0, r1 		; initial value
calc_sum_loop:
	add	r0, r1		; u_n = u_{n-1} + n
	sub	#1, r0		; dec counter
	jne	calc_sum_loop	; jump if not finished
	rts			; end of function, computed value is in r1

main:
	move	#0x0100, sp	; init stack
	move	#5, r0
	jsr	calc_sum	; r0 is the parameter of the function
	move	r1, @0		; r1 is the return value

loop:
	bra loop		;infinite loop
