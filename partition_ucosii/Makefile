# BAIL_PATH: path to the PRTOS directory
BAIL_PATH=/home/prtos/prtos-sdk/bail


all: container.bin resident_sw
include $(BAIL_PATH)/common/rules.mk

root_dir = .
os_sources_dir    = $(root_dir)/os_sources
os_platform_dir   = $(root_dir)/os_platform

os_core_sources  = $(os_sources_dir)/ucos_ii.o
os_platform_objs_c    = $(os_platform_dir)/os_cpu_c.o 
os_platform_objs_s    = $(os_platform_dir)/os_cpu_a.o 



# XMLCF: path to the XML configuration file
XMLCF=prtos_cf.$(ARCH).xml

# PARTITIONS: partition files (pef format) composing the example
PARTITIONS=partition0.pef partition1.pef

partition0: partition_ucosii.o $(os_core_sources) $(os_platform_objs_c) $(os_platform_objs_s)
	$(TARGET_LD) -o $@ $^ $(TARGET_LDFLAGS) -Ttext=$(shell $(XPATHSTART) 0 $(XMLCF))
	
partition1: partition_ucosii.o $(os_core_sources) $(os_platform_objs_c) $(os_platform_objs_s)
	$(TARGET_LD) -o $@ $^ $(TARGET_LDFLAGS) -Ttext=$(shell $(XPATHSTART) 1 $(XMLCF))

PACK_ARGS=-h $(PRTOS_CORE):prtos_cf.pef.prtos_conf \
	-p 0:partition0.pef \
	-p 1:partition1.pef
	
container.bin: $(PARTITIONS) prtos_cf.pef.prtos_conf
	$(PRTOS_PACK) check prtos_cf.pef.prtos_conf $(PACK_ARGS)
	$(PRTOS_PACK) build $(PACK_ARGS) $@

run.x86:
	@$(MAKE) clean
	@$(MAKE) resident_sw.iso
	@qemu-system-i386 -m 512 -cdrom resident_sw.iso -serial stdio -boot d -smp 4  # Create qemu simulation platform with 4 CPU enabled,
	                                                                  # so that PRTOS up/smp are supported.

uclean:
	@$(RM) $(PARTITIONS) $(patsubst %.bin,%, $(PARTITIONS)) $(patsubst %.pef,%, $(PARTITIONS))  $(os_core_sources) $(os_platform_objs_c) $(os_platform_objs_s)
	@$(RM) container.bin resident_sw prtos_cf prtos_cf.bin prtos_cf.*.prtos_conf
	@$(RM) *.o *.*.prtos_conf dep.mk
	@$(RM) *.iso
