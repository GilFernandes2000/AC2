    .equ SFR_BASE_HI, 0xBF88
    .equ TRISE, ox6100
    .equ PORTE, 0x6110
    .equ LATE, 0x6120

    .equ TRISB, 0x6040
    .equ PORTB, 0x6050
    .equ LATE, 0x6060

    .data
    .text
    .globl main

main:
    lui $t1, SFR_BASE_HI 
    lw $t2, TRISE($t1)      # READ (Mem_addr = 0xBF880000 + 0x6100)
    andi $t2, $t2, 0xFFF0   # MODIFY (bit0=bit1=bit2=bit3=0 (0 means OUTPUT))
    sw $t2, TRISE($t1)      # WRITE (Write TRISE register)

    lw $t2, TRISB($t1)      # READ (Mem_addr = 0xBF880000 + 0x6040)
    ori $t2,$t2,0x000F      # MODIFY (bit0=bit1=bit2=bit3=1 (1 means INPUT))
    sw $t2,TRISB($t1)       # WRITE (Write TRISE register)

whilea: 
    lw $t2, LATE($t1)
    and $t2, $t2, $t4
    move $a0, $t3
    jal delay
    xori $t4, $t4, 1
    sw $t2 ,LATE($t1)
    j whilea
    jr $ra

whileb:
    
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