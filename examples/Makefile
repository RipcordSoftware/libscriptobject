SUBDIRS=simple_object simple_array embed_lua json

SUBDIRS_CLEAN=$(addsuffix .clean, $(SUBDIRS))

.PHONY: all clean $(SUBDIRS) $(SUBDIRS_CLEAN)

all: $(SUBDIRS)

clean: $(SUBDIRS_CLEAN)

$(SUBDIRS):
	cd $@ && $(MAKE)

$(SUBDIRS_CLEAN):
	cd $(basename $@) && $(MAKE) clean
