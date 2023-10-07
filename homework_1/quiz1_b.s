.data
    pi:        .word 0x40490FDB  # 3.1415926
    val_875:   .word 0x410C0000  # 8.75
    val_7523:  .word 0x40F085C3  # 7.523

    zeromsg:    .string "zero\n"
    nanmsg:    .string "infiniti or NaN\n"
    finish:    .string "finish\n"
.text
    .globl _start

_start:
    # Set up stack space for a single word
    addi sp, sp, -4  # allocate 4 bytes on the stack

    # Input FP32 value, store it on the stack
    lw a0, val_875    # load data
    sw a0, 0(sp)      # store data to stack
    
    # Retrieve Exponent and Mantissa
    lw a1, 0(sp)
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
    li t0, 0xFFFF0000
    and a1, a1, a2
    srli a1, a1, 8     # Divide by 0x100
    add a1, a1, a0
    and a0, a1, t0
    j end
    
is_zero:
    la a0, zeromsg
    li a7, 4  # system call for printing string
    ecall
    j end
    
is_inf_or_nan:
    la a0, nanmsg
    li a7, 4  # system call for printing string
    ecall
    j end

end:
    # Exit simulation
    li a7, 10  # system call for exit
    ecall