SUBDIRS = lib cat revwords filter bufcat

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)

clean:
	$(MAKE) -C $(CURDIR)/lib clean
	$(MAKE) -C $(CURDIR)/cat clean
	$(MAKE) -C $(CURDIR)/revwords clean
	$(MAKE) -C $(CURDIR)/filter clean
	$(MAKE) -C $(CURDIR)/bufcat clean
	$(MAKE) -C $(CURDIR)/simplesh clean
	$(MAKE) -C $(CURDIR)/bipiper clean
	$(MAKE) -C $(CURDIR)/filesender clean
