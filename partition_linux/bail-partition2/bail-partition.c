/*
 * $FILE: bail-partition
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <prtos.h>

#define SPORT0_READER_NAME "portS1"

#define PRINTF(fmt, ...)                                                       \
  printf("[P%d] " fmt, PRTOS_PARTITION_SELF, ##__VA_ARGS__)

int Proc1(void) {
  prtos_s32_t ret;
  prtos_s32_t sWriterDesc;
  prtos_s32_t sReaderDesc;
  prtos_u32_t flags;
  prtos_u32_t sSeq = 0;
  char sMessage[32];

  PRINTF("Port %s created\n", SPORT0_READER_NAME);
  sReaderDesc = prtos_create_sampling_port(SPORT0_READER_NAME, 128,
                                           PRTOS_DESTINATION_PORT, 0);
  if (sReaderDesc < 0) {
    PRINTF("Ports error %d\n", sReaderDesc);
    return -1;
  }

  while (1) {
    memset(sMessage, 0, sizeof(sMessage));
    ret = prtos_read_sampling_message(sReaderDesc, sMessage, sizeof(sMessage),
                                      &flags);
    PRINTF("Port%d read message [%s] %d\n", sReaderDesc, sMessage, ret);
    if (ret > 0) {
    }
    prtos_idle_self();
  }

  return 0;
}

void partition_main(void) {
  PRINTF("Receiver Partition.\n");

  PRINTF("Initialisation completed\n");

  Proc1();
}
