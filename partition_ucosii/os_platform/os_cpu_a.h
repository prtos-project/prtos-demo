/****************************************************************************************************
 *
 *                                      Micrium, Inc.
 *                                  949 Crestview Circle
 *                                 Weston,  FL 33327-1848
 *
 *                                 uC/OS-II
 *
 *                         (c) Copyright 2005 - 2009, Micrium, Inc.
 *                                  All rights reserved.
 *
 *         All rights reserved.  Protected by international copyright laws.
 *         Knowledge of the source code may not be used to write a similar
 *         product.  This file may only be used in accordance with a license
 *         and should not be redistributed in any way.
 *
 *
 * Version       : 1.00
 * File          : os_cpu_a.h
 * Programmer(s) : prtos.org
 ****************************************************************************************************/

#ifndef __OS_CPU_A_H__ // test for multiple inclusion
#define __OS_CPU_A_H__

/*                          DEFINITONS                      */

// set to 1 for floating point support also set in OS_CPU.h
// #define OS_SAVE_CONTEXT_WITH_FPRS  1

/***********************************************************
   Stack Frame Definition
   This Stack frame definitions have to be congruent with the
   Stack Frame usage in OS_CPU_C.c
************************************************************/

#if (OS_SAVE_CONTEXT_WITH_FPRS == 1)
/*Not accounting FPRS*/
#else
#define OFFSET_EAX 28
#define OFFSET_EBP 24
#define OFFSET_EDI 20
#define OFFSET_ESI 16
#define OFFSET_EDX 12
#define OFFSET_ECX 8
#define OFFSET_EBX 4
#define OFFSET_EIP 0
#endif

#define store_context    \
   pushl % eax;          \
   pushl % ebp;          \
   pushl % edi;          \
   pushl % esi;          \
   pushl % edx;          \
   pushl % ecx;          \
   pushl % ebx;

#define restore_context \
   popl % ebx;          \
   popl % ecx;          \
   popl % edx;          \
   popl % esi;          \
   popl % edi;          \
   popl % ebp;          \
   popl % eax;

#endif
