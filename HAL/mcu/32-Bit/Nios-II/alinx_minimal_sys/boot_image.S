    .text
    .global boot_image_wrapper
    .type  boot_image_wrapper, @function
    .align 2

/*
 * void boot_image_wrapper(uint32_t addr) __attribute__((noreturn));
 *
 * ABI: first argument is in r4 on Nios II.
 * This function does NOT return; it simply jumps to the address in r4.
 *
 * The jmp instruction on Nios II has a delay slot: the instruction
 * immediately after jmp executes before the PC changes. We put a nop
 * in the delay slot to be safe.
 */
boot_image_wrapper:
    /* Move address (arg in r4) into a temporary register r8 and jump */
    addi    r8, r4, 0     /* r8 = r4 (pseudoinstr mov) */
    jmp     r8
    nop                   /* delay slot - executed before jump takes effect */

    /* assembler/bookkeeping */
    .size boot_image_wrapper, .-boot_image_wrapper
