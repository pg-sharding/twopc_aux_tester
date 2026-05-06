# contrib/auth_delay/Makefile

PGFILEDESC = "twopc_aux_tester - SPQR tester support"


EXTENSION = twopc_aux_tester
DATA =  twopc_aux_tester--1.0.sql

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/twopc_aux_tester
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
