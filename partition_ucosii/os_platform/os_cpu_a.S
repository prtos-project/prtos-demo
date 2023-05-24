/*
*******************************************************************************************************
                                               uC/OS-II
                                         The Real-Time Kernel

                          (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
                                          All Rights Reserved

File         : os_cpu_a.S
By           : prtos.org
*******************************************************************************************************
*/

#include "os_cpu_a.h"

/**************************************************************************************
           PUBLIC and EXTERNAL REFERENCES
*************************************************************************************/

.globl OSTickISR
.globl OSStartHighRdy
.globl OSCtxSw
.globl OSIntCtxSw
      
.extern OSIntExit
.extern OSTimeTick
.extern OSTaskSwHook
.extern OSIntNesting
.extern OSTickDOSCtr
.extern OSPrioHighRdy
.extern OSPrioCur
.extern OSRunning
.extern OSTCBCur
.extern OSTCBHighRdy



/** Description : This function is called by OSStart() to start the highest
priority task that was created by the application before calling OSStart().
Arguments : none
Note: OSStartHighRdy() MUST:
   a) Call OSTaskSwHook() then,
   b) Set OSRunning to TRUE,
   c) Switch to the highest priority task by loading the stack
      pointer of the highest priority task into the SP
      register and execute an rfi instruction.
**/

OSStartHighRdy:
   call OSTaskSwHook
   movb $1, %al
   movl $OSRunning, %ebx
   movb %al, (%ebx)
   
   movl $OSTCBHighRdy, %eax
   movl (%eax),%eax
   movl  0(%eax),%esp
   restore_context
   ret


/**
TASK LEVEL CONTEXT SWITCH
Description : This function is called when a task makes a higher priority task
              ready-to-run.
Arguments   : none
Note(s) : Upon entry,
          OSTCBCur points to the OS_TCB of the task to suspend
          OSTCBHighRdy points to the OS_TCB of the task to resume
**/

OSCtxSw:  

   movl $OSTCBHighRdy, %eax
   movl (%eax),%eax
   movl  0(%eax),%esp
   restore_context
   ret

OSIntCtxSw:
   movl $OSPrioHighRdy,%ebx
   movb (%ebx), %bl
   movl $OSPrioCur, %ecx
   movb %bl,(%ecx)          //OSPrioCur=OSPrioHighRdy
   movl $OSTCBHighRdy, %ebx
   movl (%ebx),%ebx
   movl $OSTCBCur, %ecx
   movl %ebx,(%ecx)         //OSTCBCur=OSTCBHighRdy
   
   movl 0(%ebx),%esp
   restore_context
   ret
   
/**
SYSTEM TICK ISR
Description :This function is the ISR to notify uC/OS-II that a system tick
             has occurred.
**/

OSTickISR:
  store_context
  call OSIntEnter
  movl $OSIntNesting, %ebx
  movb (%ebx),%bl
  cmpb $0x1,%bl
  jne Dec_NotSaveSP
  movl $OSTCBCur, %ebx
  movl (%ebx), %ebx
  movl %esp, 0(%ebx)
  
  
Dec_NotSaveSP:
  call OSTimeTick
  call OSIntExit
  restore_context
  ret
