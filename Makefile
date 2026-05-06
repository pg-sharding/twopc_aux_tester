# contrib/auth_delay/Makefile

MODULES = 2pc_aux_tester
PGFILEDESC = "2pc_aux_tester - SPQR tester support"

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/2pc_aux_tester
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
