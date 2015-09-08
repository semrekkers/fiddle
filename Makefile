# Root Makefile
# check src/Makefile for the actual file

default: all

%:
	cd src && $(MAKE) $@
