    .equ SFR_BASE_HI,0xBF88
    .equ TRISE, 0x6100
    .equ PORTE, 0x6110
    .equ LATE, 0x6120

    .equ TRISB, 0x6040
    .equ PORTB, 0x6050
    .equ LATB, 0x6060

    .data
    .text
    .globl main

main:
    lui $t1, SFR_BASE_HI 
    lw $t2, TRISE($t1)      # READ (Mem_addr = 0xBF880000 + 0x6100)
    andi $t2, $t2, 0xFFF6   # MODIFY (bit0=bit3=0 (0 means OUTPUT))
    sw $t2, TRISE($t1)      # WRITE (Write TRISE register)

    
    lw $t2, TRISB($t1)
    ori $t2,$t2,0x0001      # bit0 é usado como innput
    sw $t2,TRISB($t1)

while:
    lw $t0, PORTB($t1)
    not $t2,$t2            # valor do B negado
    andi $t0, $t0, 0x0001   
    lw $t2, LATE($t1)       # READ LATE 
    andi $t2, $t2, 0xFFFE   # bit0 = 0
    or $t2, $t2, $t0
    sw $t2,LATE($t1)

    j while
    jr $ra