# $Id: 35334b3609333ad2c87f9d3d6dab1165d59d377c $

MAKEFILE := $(lastword $(MAKEFILE_LIST))
MAKE := $(MAKE) -f $(MAKEFILE)
SUBDIRS = src man tools doc
ALLDIRS = include $(SUBDIRS) maxima matlab python windows cmake

all: src man tools

$(SUBDIRS):
	$(MAKE) -C $@

tools: src
install: install-headers install-lib install-tools install-man install-cmake \
	install-doc install-matlab install-python
clean: clean-src clean-tools clean-doc clean-man clean-matlab clean-python
distclean: clean distclean-doc distclean-man
install-headers:
	$(MAKE) -C include install
install-lib:
	$(MAKE) -C src install
install-tools: src
	$(MAKE) -C tools install
install-cmake:
	$(MAKE) -C cmake install
install-doc: doc
	$(MAKE) -C doc install
install-man: man
	$(MAKE) -C man install
install-matlab: matlab
	$(MAKE) -C matlab install
install-python: python
	$(MAKE) -C python install
clean-src:
	$(MAKE) -C src clean
clean-tools:
	$(MAKE) -C tools clean
clean-doc:
	$(MAKE) -C doc clean
clean-man:
	$(MAKE) -C man clean
clean-matlab: matlab
	$(MAKE) -C matlab clean
clean-python: python
	$(MAKE) -C python clean
distclean-doc:
	$(MAKE) -C doc distclean
distclean-man:
	$(MAKE) -C man distclean

VERSION:=$(shell grep '\bVERSION=' configure | cut -f2 -d\' | head -1)

.PHONY: all $(SUBDIRS) install \
	install-headers install-lib install-tools install-cmake install-man \
	install-matlab install-python \
	clean clean-src clean-tools clean-doc clean-man clean-matlab \
	clean-python distclean distclean-doc distclean-man
