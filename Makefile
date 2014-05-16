default: build

.DEFAULT:
	cd Chapter-1 && $(MAKE) $@
	cd Chapter-2 && $(MAKE) $@
