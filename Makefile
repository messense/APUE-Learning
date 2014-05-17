default: build

.DEFAULT:
	cd Chapter-1 && $(MAKE) $@
	cd Chapter-2 && $(MAKE) $@
	cd Chapter-3 && $(MAKE) $@
	cd Chapter-4 && $(MAKE) $@
