    PROCESSOR 6502

    ORG $F00
    LDX #$01
    LDA #$05
    STA $01
    LDA #$07
    STA $02
    LDY #$0a
    STY $0705
    LDA ($00,X)

; 0600: a2 01 a9 05 85 01 a9 07 85 02 a0 0a 8c 05 07 a1 
; 0610: 00 