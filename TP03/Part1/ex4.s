    .equ SFR_BASE_HI,0xBF88
    .equ TRISE, 0x6100
    .equ PORTE, 0x6110
    .equ LATE, 0x6120

    .equ resetCoreTimer,12
    .equ readCoreTimer,11

    .data
    .text
    .globl main

main:   
    lui $t1, SFR_BASE_HI
    lw $t2, TRISE($t1)      # READ (Mem_addr = 0xBF880000 + 0x6100)
    andi $t2, $t2, 0xFFFE   # MODIFY (bit0=0 (0 means OUTPUT))
    sw $t2, TRISE($t1)      # WRITE (Write TRISE register)

    li $t4, 0
    li $t3, 500
while1: 
    lw $t2, LATE($t1)
    and $t2, $t2, $t4
    move $a0, $t3
    jal delay
    xori $t4, $t4, 1
    sw $t2 ,LATE($t1)
    j while1
    jr $ra

delay:                      # da delay de x ms
    move $t0, $a0
for:
    ble $t0, 0, endfor
    li $v0, resetCoreTimer
while:
    li $v0, readCoreTimer
    bge $v0, 200000, endwhile
    j while
endwhile:
    addi $t0, $t0, -1
    j for
endfor:
    jr $ra
