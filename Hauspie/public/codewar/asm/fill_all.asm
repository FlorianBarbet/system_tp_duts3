start:
        move    #0x100, sp
        move    #255, r0
        move    @1, r2
loop:
        move    r0, r1
        lsl     #8, r1
        or      #1, r1
        move    r2, (r1)
        sub     #1, r0
        jne     loop
        move    #255, r0
        bra     loop

end:
        bra     end
        
        
