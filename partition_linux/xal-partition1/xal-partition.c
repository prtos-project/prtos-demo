/*
 * $FILE: xal-partition
 *
 * Event example
 *
 * $VERSION$
 *
 * $AUTHOR
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <prtos.h>

#define SPORT1_WRITER_NAME "portS1"
#define SPORT0_READER_NAME "portS0"

#define PRINTF(fmt, ...) \
    printf("[P%d] " fmt , PRTOS_PARTITION_SELF, ## __VA_ARGS__)

int
Proc1(void)
{
	prtos_s32_t ret;
    prtos_s32_t sWriterDesc;
    prtos_s32_t sReaderDesc;
    prtos_u32_t flags;
    prtos_u32_t sSeq = 0;
	char sMessage[32];

	sReaderDesc = prtos_create_sampling_port(SPORT0_READER_NAME, 128, PRTOS_DESTINATION_PORT, 0);
    PRINTF("Port %s created\n", SPORT0_READER_NAME);
	if (sReaderDesc < 0)
	{
		PRINTF("Port %s error %d\n", SPORT0_READER_NAME, sReaderDesc);
		return -1;
	}

    PRINTF("Port %s created\n", SPORT1_WRITER_NAME);
	sWriterDesc = prtos_create_sampling_port(SPORT1_WRITER_NAME, 128, PRTOS_SOURCE_PORT, 0);
	if (sWriterDesc < 0)
	{
		PRINTF("Port %s error %d\n", SPORT1_WRITER_NAME, sWriterDesc);
		return -1;	
	}

	while (1)
	{
        ret=prtos_read_sampling_message(sReaderDesc, sMessage, sizeof(sMessage), &flags);

		if (ret > 0)
		{
				PRINTF("Port%d read message [%s] %d\n", sReaderDesc, sMessage, ret);
		} else
		{
				memset(sMessage, 0, sizeof(sMessage));
				sprintf(sMessage, "message payload%d", sSeq++);
		}

		ret=prtos_write_sampling_message(sWriterDesc, sMessage, sizeof(sMessage));
		PRINTF("Port%d write message [%s] %d\n", sWriterDesc, sMessage, ret);

		prtos_idle_self();
    }

    return 0;
}

void
PartitionMain(void)
{
    PRINTF("Sender Partition.\n");

	PRINTF("Initialisation completed\n");

	Proc1();
}
