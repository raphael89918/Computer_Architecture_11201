.section .data
    pi:        .word 0x40490FDB  # 3.1415926
    val_875:   .word 0x410C0000  # 8.75
    val_7523:  .word 0x40F085C3  # 7.523

    zeromsg:    .asciz "zero\n"
    nanmsg:    .asciz "infiniti or NaN\n"
    finish:    .asciz "finish\n"
.section .text
    .globl _start

_start:
    # Input FP32 value, store it in a memory address
    lw a0, val875  # load data
    sw a0, 0(t0)       # Assuming t0 points to a memory location for storage
    
    # Retrieve Exponent and Mantissa
    lw a1, 0(t0)
    li a2, 0x7F800000
    and a3, a1, a2     # a3 = exp
    
    li a2, 0x007FFFFF
    and a4, a1, a2     # a4 = man

    # Check if it is zero
    beqz a3, is_zero
    beqz a4, is_zero
    
    # Check if it is infinity or NaN
    li a2, 0x7F800000
    beq a3, a2, is_inf_or_nan

    # Perform rounding
    li a2, 0xFF800000
    and a1, a1, a2
    srli a1, a1, 8     # Divide by 0x100
    add a1, a1, a0
    andi a0, a1, 0xFFFF0000
    j end
    
is_zero:
    la a0, zeromsg
    ecall
    j end
    
is_inf_or_nan:
    la a0, nanmsg
    ecall
    j end

end:
    la a0, finish
    ecall