    PROCESSOR 6502
    ORG $FF00
    LDX #$12

loop:
    STX $1234
    JMP loop