// See LICENSE for license details.

#pragma once

#include <stddef.h>
#include <encoding.h>
#include <stdio.h>

typedef unsigned long uintptr_t;

#define die(str, ...) ({ \
  printf("%s:%d: " str "\n", __FILE__, __LINE__, ##__VA_ARGS__); })

#define assert(x) ({ if (!(x)) die("assertion failed: %s", #x); })

#define read_const_csr(reg) ({ unsigned long __tmp; \
  asm ("csrr %0, " #reg : "=r"(__tmp)); __tmp; })

#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); __tmp; })

#define write_csr(reg, val) ({ \
  asm volatile ("csrw " #reg ", %0" :: "rK"(val)); })

#define swap_csr(reg, val) ({ unsigned long __tmp; \
  asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "rK"(val)); __tmp; })

#define set_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); __tmp; })

#define clear_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); __tmp; })

static inline uintptr_t get_field(uintptr_t reg, uintptr_t mask)
{
    return ((reg & mask) / (mask & ~(mask << 1)));
}

static inline uintptr_t set_field(uintptr_t reg, uintptr_t mask, uintptr_t val)
{
    return ((reg & ~mask) | ((val * (mask & ~(mask << 1))) & mask));
}

__attribute__((noreturn)) static inline void mret()
{
    asm volatile ("mret");
    __builtin_unreachable();
}

/*
 * Privileged modes
 */

/*
 * mode_set_and_jump
 *
 * Set mstatus.mpp, sets mepc to passed function pointer and then issues mret
 * Note: the hart will continue running on the same stack
 */
static inline void mode_set_and_jump(unsigned mode, void (*fn)(void))
{
    write_csr(mstatus, set_field(read_csr(mstatus), MSTATUS_MPP, mode));
    write_csr(mepc, fn);
    mret();
}

/*
 * mode_set_and_continue
 *
 * Set mstatus.mpp, sets mepc to instruction after mret and then issues mret
 * Note: the hart will continue running on the same stack
 */
static inline void mode_set_and_continue(unsigned mode)
{
    write_csr(mstatus, set_field(read_csr(mstatus), MSTATUS_MPP, mode));
    asm volatile (
        "lla t0, 1f\n"
        "csrw mepc, t0\n"
        "mret\n"
        "1:"
        ::: "t0"
    );
}