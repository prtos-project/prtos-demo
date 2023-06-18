#include <irqs.h>   // virtual irq services provided by the libbail library
#include <prtos.h>  // hypercall services provided by the libprtos library
#include <stdio.h>  // stdio services provided by the libbail library
#include <string.h> // string services provided by the libbail library

#include "os_sources/includes.h"

#define APP_KERNEL_START_PRIO 0
#define APP_TASK_1_PRIO 10
#define APP_TASK_1_ID 10

#define APP_TASK_START_STK_SIZE 256
#define APP_TASK_1_STK_SIZE 256

static void KernelStart(void *pdata);
static void AppTask1(void *pdata);

OS_STK AppStartTaskStk[APP_TASK_START_STK_SIZE];
OS_STK AppTask1Stk[APP_TASK_1_STK_SIZE];

#define PRINT(...)                                                             \
  do {                                                                         \
    printf("[%d] ", PRTOS_PARTITION_SELF);                                     \
    printf(__VA_ARGS__);                                                       \
  } while (0)

void HwTimerHandler(trap_ctxt_t *ctxt) { /* XAL trap API */
  OSTickISR();
}

void TimerKicker() {
  prtos_time_t hwClock, execClock;

  install_trap_handler(BAIL_PRTOSEXT_TRAP(PRTOS_VT_EXT_HW_TIMER),
                     HwTimerHandler); /* Install timer handler */

  hw_sti();                                              /* Enable irqs */
  prtos_clear_irqmask(0, (1 << PRTOS_VT_EXT_HW_TIMER)); /* Unmask timer irqs */

  prtos_get_time(PRTOS_HW_CLOCK, &hwClock);     /* Read hardware clock */
  prtos_get_time(PRTOS_EXEC_CLOCK, &execClock); /* Read execution clock */

  PRINT("Setting HW timer at 1 sec period\n");
  prtos_set_timer(PRTOS_HW_CLOCK, hwClock + 1000000LL,
                  1000000LL); /* Set hardware time driven timer */
}

static void KernelStart(void *pdata) {
#if OS_CRITICAL_METHOD == 3
  OS_CPU_SR cpu_sr;
#endif
  PRINT("KernelStart\n");
  pdata = pdata;

  TimerKicker();

  OSTaskCreateExt(AppTask1, (void *)0,
                  (OS_STK *)&AppTask1Stk[APP_TASK_1_STK_SIZE - 1],
                  APP_TASK_1_PRIO, APP_TASK_1_ID, (OS_STK *)&AppTask1Stk[0],
                  APP_TASK_1_STK_SIZE, (void *)0,
                  OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

  while (TRUE) {
    OSCtxSwCtr = 0;
    PRINT("KernelStart running on Partiton [%d]\n", PRTOS_PARTITION_SELF);
    OSTimeDly(1);
  }
}

static void AppTask1(void *pdata) {
  INT8U err;
  OS_STK_DATA data;
  pdata = pdata;
  while (TRUE) { /* Task body, always written as an infinite */
    err = OSTaskStkChk(APP_TASK_1_PRIO, &data);
    if (OS_NO_ERR == err) {
      PRINT("AppTask1 Stack size:%d used:%d free:%d\n",
            data.OSFree + data.OSUsed, data.OSUsed, data.OSFree);
    }
    printf("AppTask1 running on Partition [%d]\n", PRTOS_PARTITION_SELF);
    OSTimeDly(1); /* Delay task execution for half second     */
  }
}

void partition_main(void) {

  OSInit();
  OSTaskCreateExt(KernelStart, (void *)0,
                  (OS_STK *)&AppStartTaskStk[APP_TASK_START_STK_SIZE - 1],
                  APP_KERNEL_START_PRIO, APP_KERNEL_START_PRIO,
                  (OS_STK *)&AppStartTaskStk[0], APP_TASK_START_STK_SIZE,
                  (void *)0, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
  OSStart();
}
