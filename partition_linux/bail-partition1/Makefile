PARTITIONS=bail-partition1.pef
# BAIL_PATH: path to the BAIL directory
BAIL_PATH=/home/prtos/prtos-sdk/bail

ID=2
# XMLCF: path to the XML configuration file
PRTOS_CF=../prtos_cf.xml

all: ${PARTITIONS}
include $(BAIL_PATH)/common/rules.mk

bail-partition1: bail-partition.o
	$(TARGET_LD) -o $@ $^ $(TARGET_LDFLAGS) -Ttext=$(call xpathstart,${ID},$(PRTOS_CF))

pclean: clean
	@$(RM) -f dep.mk *.o *.a *.pef *~ *.bin *.xmc xm_cf resident_sw
	@find -name "*~" -exec rm '{}' \;
	@find -name "*.o" -exec rm '{}' \;
	@find -name "dep.mk" -exec rm '{}' \;
