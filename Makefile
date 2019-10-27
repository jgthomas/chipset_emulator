
SUBDIRS = core assembler run shell tests
TESTDIR = tests

all clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

test:
	$(MAKE) -C $(TESTDIR) $(MAKECMDGOALS)

.PHONY: all $(SUBDIRS)
