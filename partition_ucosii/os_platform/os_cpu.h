/*
*********************************************************************************************************
*                                               uC/OS-II
*                                        The Real-Time Kernel
*
*                         (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
*                                          All Rights Reserved
*
*                                       80x86/80x88 Specific code
*                                          LARGE MEMORY MODEL
*
*                                          Borland C/C++ V4.51
*
* File         : OS_CPU.H
* By           : Jean J. Labrosse
*********************************************************************************************************
*/
#ifndef __OS_CPU_H__     /* test for multiple inclusion */
#define __OS_CPU_H__   


#ifdef  OS_CPU_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT  extern
#endif


/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned int   INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   int   INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
typedef unsigned long long INT64U;
typedef signed long long   INT64S;

typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */

typedef unsigned int   OS_STK;                   /* Each stack entry is 32-bit wide                    */
typedef volatile unsigned int   OS_CPU_SR;                /* Define size of CPU status register (PSW = 32 bits) */

#ifndef  FALSE
  #define  FALSE    0
#endif

#ifndef  TRUE
  #define  TRUE     1
#endif

#ifndef  NULL
  #define  NULL     0
#endif

/*
*********************************************************************************************************
*                                              FLOATING POINT
* note: also enable or disable "OS_SAVE_CONTEXT_WITH_FPRS .equ 1" in os_cpu_a.h
*********************************************************************************************************
*/ 
#define FPSCR_INIT          0x4L             /*!< Init Value of the FPSCR Register (NI-Bit is set)     */

#define OS_SAVE_CONTEXT_WITH_FPRS 0

/*
*********************************************************************************************************
*                                              OS Task Swicth
*********************************************************************************************************
*/

#define PUSH_REGISTERS \
    "pushl %%eax\n\t" \
    "pushl %%ebp\n\t" \
    "pushl %%edi\n\t" \
    "pushl %%esi\n\t" \
    "pushl %%edx\n\t" \
    "pushl %%ecx\n\t" \
    "pushl %%ebx\n\t"

#define POP_REGISTERS \
    "popl %%ebx\n\t" \
    "popl %%ecx\n\t" \
    "popl %%edx\n\t" \
    "popl %%esi\n\t" \
    "popl %%edi\n\t" \
    "popl %%ebp\n\t" \
    "popl %%eax\n\t"

#define CONTEXT_SWITCH                                                 \
  __asm__ __volatile__(                                                \
      "movb (%%eax),%%al\n\t"                                          \
      "movb %%al,(%%edx)\n\t"                                          \
      "movl (%%ebx), %%edx\n\t"                                        \
      "pushl $1f\n\t" PUSH_REGISTERS                                   \
      "movl %%esp, 0(%%edx)\n\t"                                       \
      "movl 0(%%ecx), %%esp\n\t" /*restore OSTCBHighRdy->OSTCBStkPtr*/ \
      "movl %%ecx, (%%ebx)\n\t" POP_REGISTERS                          \
      "ret\n\t"                                                        \
      "1:\n\t"                                                         \
      :                                                                \
      : "c"(OSTCBHighRdy), "b"(&OSTCBCur), "a"(&OSPrioHighRdy), "d"(&OSPrioCur))

#define OS_TASK_SW() CONTEXT_SWITCH

/* 
*********************************************************************************************************
*                                           OS ENTER AND EXIT CRITICAL
*
* Method #1:  Disable/Enable interrupts using simple instructions.  After critical section, interrupts
*             will be enabled even if they were disabled before entering the critical section.
*
* Method #2:  Disable/Enable interrupts by preserving the state of interrupts.  In other words, if 
*             interrupts were disabled before entering the critical section, they will be disabled when
*             leaving the critical section.
*
* Method #3:  Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
*             would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
*             disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to 
*             disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
*             into the CPU's status register.
*
* NOTE(s)  :  This port only support the Method #3
*********************************************************************************************************
*/
#define    OS_CRITICAL_METHOD    1
                                                  
#define OS_ENTER_CRITICAL()  hw_cli()
#define OS_EXIT_CRITICAL()   hw_sti()


#define OS_STK_GROWTH       1         /* Stack grows from HIGH to LOW memory on X86*/

typedef struct stk_tag
{
  INT32U ebx;
  INT32U ecx;
  INT32U edx;
  INT32U esi;
  INT32U edi;
  INT32U ebp;
  INT32U eax;
  INT32U lret_eip;
  INT32U lret_cs;
  INT32U iflags;
  INT32U eip;
  INT32U cs;
  INT32U eflags;
  INT32U esp;
  INT32U ss;
#if (OS_SAVE_CONTEXT_WITH_FPRS == 1)
/*Not accounting FPRS*/
#endif
} STK;

#endif
