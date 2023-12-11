/******************************************************************************
 *
 * ���������ļ�����OS�û��Զ���ӿں���
 * ��ע����������Ķ��Ĺ����з���bug���뼰ʱ��ϵ�ң�cwsun@mail.ustc.edu.cn or sunchenwei8@126.com�������ǹ�ͬŬ�����Ѵ���д�ø���³����
 * �޸ģ� ʱ��    ��  �� �������(�������ԭ�еĻ��������޸ģ���ע�����ں�����)
 * 		  2012-6-16 ���ΰ ��������
 *
 */

#define OS_CPU_GLOBALS
#include "../os_sources/includes.h"
/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                            (BEGINNING)
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void OSInitHookBegin(void)
{
}
#endif

/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                               (END)
*
* Description: This function is called by OSInit() at the end of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void OSInitHookEnd(void)
{
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0
void OSTaskCreateHook(OS_TCB *ptcb)
{
    ptcb = ptcb; /* Prevent compiler warning                                     */
}
#endif

/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0
void OSTaskDelHook(OS_TCB *ptcb)
{
    ptcb = ptcb; /* Prevent compiler warning                                     */
}
#endif

/*
*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0 && OS_VERSION >= 251
void OSTaskIdleHook(void)
{
    // printf("OSTaskIdleHook\n");
    //   printf("OSTaskIdleHook OSPrioCur=%d OSPrioHighRdy=%d\n",OSPrioCur,OSPrioHighRdy);
    //   printf("OSTaskIdleHook cur:%d\n",OSTCBCur->OSTCBY<<3+OSTCBCur->OSTCBX & 0x07);
    //	 printf("OSTaskIdleHook cur prio:%d\n",OSTCBCur->OSTCBPrio);
    //	 printf("OSTaskIdleHook ready prio:%d\n",OSTCBHighRdy->OSTCBPrio);
}
#endif

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/

#if OS_CPU_HOOKS_EN > 0
void OSTaskStatHook(void)
{
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                        INITIALIZE A TASK'S STACK
*
* Description: This function is called by either OSTaskCreate() or OSTaskCreateExt() to initialize the
*              stack frame of the task being created.  This function is highly processor specific.
*
* Arguments  : task          is a pointer to the task code
*
*              pdata         is a pointer to a user supplied data area that will be passed to the task
*                            when the task first executes.
*
*              ptos          is a pointer to the top of stack.  It is assumed that 'ptos' points to
*                            a 'free' entry on the task stack.  If OS_STK_GROWTH is set to 1 then
*                            'ptos' will contain the HIGHEST valid address of the stack.  Similarly, if
*                            OS_STK_GROWTH is set to 0, the 'ptos' will contains the LOWEST valid address
*                            of the stack.
*
*              opt           specifies options that can be used to alter the behavior of OSTaskStkInit().
*                            (see uCOS_II.H for OS_TASK_OPT_???).
*
* Returns    : Always returns the location of the new top-of-stack' once the processor registers have
*              been placed on the stack in the proper order.
*
* Note(s)    : Interrupts are enabled when your task starts executing. You can change this by setting the
*              PSW to 0x0002 instead.  In this case, interrupts would be disabled upon task startup.  The
*              application code would be responsible for enabling interrupts at the beginning of the task
*              code.  You will need to modify OSTaskIdle() and OSTaskStat() so that they enable
*              interrupts.  Failure to do this will make your system crash!
*********************************************************************************************************
*/
OS_STK *OSTaskStkInit(void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
    STK *stkp;
    OS_CPU_SR INITIAL_SRR1;

    opt = opt; /* suppress compiler warning                */

    ptos = ptos - 8; /* Leave buffer area for locals "above the  */
                     /* stack" in case the compiler prolog puts  */
                     /*   variables above the stack              */

    /* 16-byte align task's stack pointer */
    /* (EABI)                             */
    stkp = (STK *)((INT32U)(ptos) & (INT32U)0xFFFFFFF0); 
                                                         

    stkp--; /* set structure within stack space         */

    /*****************************************************************/
    /* Ensure any changes to the order of these initializations      */
    /* are congruent with the Stack Frame definitions in OS_CPU_A.s  */
    /*****************************************************************/
    /* to improve debugging, fill all registers with the mame */
    stkp->ebx = 0x66666666L;     /* EBX */
    stkp->ecx = 0x55555555L;     /* ECX */
    stkp->edx = 0x44444444L;     /* EDX */
    stkp->esi = 0x33333333L;     /* ESI */
    stkp->edi = 0x22222222L;     /* EDI */
    stkp->ebp = 0x11111111L;     /* EBP */
    stkp->eax = 0x00000000L;     /* EAX */
    stkp->lret_eip = task;       /* RET ADDR*/
    stkp->iflags = 0x0;          /* IFLAGS*/
    stkp->eip = task;            /* PC*/

#if (OS_SAVE_CONTEXT_WITH_FPRS == 1)
/*Not accouting FPRS*/
#endif

    return (OS_STK *)stkp;
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0
void OSTaskSwHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                           OSTCBInit() HOOK
*
* Description: This function is called by OS_TCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void OSTCBInitHook(OS_TCB *ptcb)
{
    ptcb = ptcb; /* Prevent Compiler warning                 */
}
#endif

/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0
void OSTimeTickHook(void)
{
}

#endif
