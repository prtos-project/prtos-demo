PARTITIONS=../linux-partition/linux-partition.pef ../bail-partition1/bail-partition1.pef ../bail-partition2/bail-partition2.pef
LINUX_PATH=/home/prtos/linux-sdk
PACK_ARGS=-h $(PRTOS_CORE):prtos_cf.pef  \
	-p 0:../linux-partition/linux-partition.pef:../linux-partition/cmdline.pef\
	-p 1:../bail-partition1/bail-partition1.pef\
	-p 2:../bail-partition2/bail-partition2.pef\

all: resident_sw

PRTOS_CF=../prtos_cf.xml
include $(LINUX_PATH)/common/rules.mk

prtos_cf.pef: $(PRTOS_CF)
	$(PRTOS_CPARSER) -o prtos_cf.bin $^
	$(PEF) -m prtos_cf.bin -c -o $@
	@$(RM) -f prtos_cf.bin

container.bin: $(PARTITIONS) prtos_cf.pef
	$(PRTOS_PACK) check prtos_cf.pef $(PACK_ARGS)
	$(PRTOS_PACK) build $(PACK_ARGS) $@

pclean: clean
