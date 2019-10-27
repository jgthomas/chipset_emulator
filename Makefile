
SUBDIRS = core assembler run shell tests

all clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

test:
	$(MAKE) -C tests test

.PHONY: all $(SUBDIRS)
