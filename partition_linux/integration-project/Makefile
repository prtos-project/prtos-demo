PARTITIONS=../linux-partition/linux-partition.xef ../xal-partition1/xal-partition1.xef ../xal-partition2/xal-partition2.xef
LINUX_PATH=/home/prtos/linux-sdk
PACK_ARGS=-h $(PRTOSCORE):prtos_cf.xef  \
	-p 0:../linux-partition/linux-partition.xef:../linux-partition/cmdline.xef\
	-p 1:../xal-partition1/xal-partition1.xef\
	-p 2:../xal-partition2/xal-partition2.xef\

all: resident_sw

PRTOS_CF=../prtos_cf.xml
include $(LINUX_PATH)/common/rules.mk

prtos_cf.xef: $(PRTOS_CF)
	$(PRTOSCPARSER) -o prtos_cf.bin $^
	$(XEF) -m prtos_cf.bin -c -o $@
	@$(RM) -f prtos_cf.bin

container.bin: $(PARTITIONS) prtos_cf.xef
	$(PRTOSPACK) check prtos_cf.xef $(PACK_ARGS)
	$(PRTOSPACK) build $(PACK_ARGS) $@

pclean: clean
