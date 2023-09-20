PARTITION=linux-partition
LINUX_PATH=/home/prtos/linux-sdk
ID=0
CMDLINE=cmdline

include $(LINUX_PATH)/common/rules.mk

PRTOS_CF=../prtos_cf.xml
all: $(PARTITION).pef $(CMDLINE).pef

cmd=$(BUILD_LINUX) -r root -a $(shell $(XPATHSTART) $(ID) $(PRTOS_CF)) -o $@ #$(LINUX_PATH)/vmlinux
addr=$(XPATHSTART) $(ID) $(PRTOS_CF)
$(PARTITION):
	echo $(cmd)
	echo $(addr)
	$(BUILD_LINUX) -r root -a $(shell $(XPATHSTART) $(ID) $(PRTOS_CF)) -o $@ $(LINUX_PATH)/vmlinux

$(CMDLINE).pef: $(CMDLINE)
	$(PEF) -m -o $@ $<

pclean: clean
	$(RM) -f $(PARTITION)*

