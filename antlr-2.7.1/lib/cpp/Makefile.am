SUBDIRS = src antlr
# Get global config
CXXFLAGS=@CXXFLAGS@ $(DEBUG_CXXFLAGS)

LIBTOOL_DEPS = @LIBTOOL_DEPS@
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck
