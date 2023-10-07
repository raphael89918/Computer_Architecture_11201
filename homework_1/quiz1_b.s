.data
fp32: .word 0x3f800000  # 32-bit float, value = 1.0

.text
.global _start

_start:
    lw a0, fp32            # Load the FP32 value
    
    li a1, 0x7F800000  # Mask for exponent
    li a2, 0x007FFFFF  # Mask for mantissa
    
    and t0, a0, a1     # t0 = exponent
    and t1, a0, a2     # t1 = mantissa

    or t2, t0, t1   # t2 = exponent|mantissa
    beqz t2, return_x

    li t2, a1   # load 0x7F800000 in t2
    beq t0, t2, return_x    # exponent==0x7F800000 goto return_x

    # Normalized number, round to nearest
    and a3, a0, a1             # a3 = r, same exponent as x, mantissa is 0
    
    li t3, 0x38800000          # 1/256 in IEEE 754 format
    flw fa1, t3                # Load 1/256 into fa1
    
    fmv.w.x fa2, a3            # Move integer r into fa2
    fdiv.s fa2, fa2, fa1       # Divide r by 256
    
    fadd.s fa0, fa0, fa2       # y = x + r
    
    li t4, 0xFFFF0000          # Mask to keep only exponent
    fmv.x.w a4, fa0            # Move y to integer register a4 (as bits)
    and a4, a4, t4
    fmv.w.x fa0, a4            # Move integer bits back to float


return_x:
    ret # return fp32
