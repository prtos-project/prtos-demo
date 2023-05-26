INTEGRATION=integration-project
PARTITIONS=\
	linux-partition\
	xal-partition1\
	xal-partition2\

	
ifndef V
MAKEFLAGS   += --no-print-directory --quiet
endif

all: resident_sw

resident_sw:
	@for dir in $(PARTITIONS) ; do \
		$(MAKE) -C $$dir all; \
	done
	@$(MAKE) -C ${INTEGRATION} ${MAKECMDGOALS}
	@cp ${INTEGRATION}/resident_sw* .

resident_sw.iso: resident_sw
	@$(MAKE) -C ${INTEGRATION} ${MAKECMDGOALS}
	@cp ${INTEGRATION}/resident_sw* .


run.x86:
	@$(MAKE) clean
	@$(MAKE) resident_sw.iso
	@qemu -m 1024 -cdrom resident_sw.iso -serial stdio -boot d -smp 4  # Create qemu simulation platform with 4 CPU enabled,
	                                                                  # so that PRTOS up/smp are supported.

pclean clean:
	@for dir in $(PARTITIONS) ; do \
		$(MAKE) -C $$dir $(MAKECMDGOALS); \
		$(RM) $$dir/*.xef; \
	done
	@$(MAKE) -C ${INTEGRATION} ${MAKECMDGOALS}
	@$(RM) ${INTEGRATION}/*.xef ${INTEGRATION}/resident_sw* resident_sw*
	@$(RM) *.iso

