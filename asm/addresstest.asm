    PROCESSOR 6502
    ORG $FF00

    LDX #$00
    LDY #$00
    JSR separate
    JSR separate
    JSR separate
    JSR separate
    JSR separate
    JMP loop

separate:
    LDA $1234
    RTS

range:
    CPX #$FF
    BEQ end
    RTS

loop:
    STX $00,Y
    INY
    INX
    JSR range
    JMP loop
    
end:
    BRK

; 0600: a2 01 a9 05 85 01 a9 07 85 02 a0 0a 8c 05 07 a1 
; 0610: 00 