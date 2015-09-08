# Root Makefile
# check src/Makefile for the actual file

all:
	cd src && $(MAKE) $@

%:
	cd src && $(MAKE) $@
