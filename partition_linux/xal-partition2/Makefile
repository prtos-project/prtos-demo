PARTITIONS=xal-partition2.xef
# XAL_PATH: path to the XAL directory
XAL_PATH=/home/prtos/prtos-sdk/xal
ID=3
# XMLCF: path to the XML configuration file
PRTOS_CF=../prtos_cf.xml

all: ${PARTITIONS}
include $(XAL_PATH)/common/rules.mk

xal-partition2: xal-partition.o
	$(TARGET_LD) -o $@ $^ $(TARGET_LDFLAGS) -Ttext=$(call xpathstart,${ID},$(PRTOS_CF))

pclean: clean
	@$(RM) -f dep.mk *.o *.a *.xef *~ *.bin *partition *.bin.xmc *.c.xmc *.xmc xm_cf resident_sw *.o.lcfg
	@find -name "*~" -exec rm '{}' \;
	@find -name "*.o" -exec rm '{}' \;
	@find -name "dep.mk" -exec rm '{}' \;
