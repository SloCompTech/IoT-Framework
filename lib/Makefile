#
# Compile each of libs which has makefile
#

SUBDIRS := $(wildcard */.)

all:
	for dir in $(SUBDIRS); do \
      $(MAKE) -C $$dir; \
  done
