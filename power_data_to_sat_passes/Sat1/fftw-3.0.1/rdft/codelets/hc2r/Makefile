# Makefile.in generated by automake 1.7.3 from Makefile.am.
# rdft/codelets/hc2r/Makefile.  Generated from Makefile.in by configure.

# Copyright 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003
# Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



# This Makefile.am specifies a set of codelets, efficient transforms
# of small sizes, that are used as building blocks (kernels) by FFTW
# to build up large transforms, as well as the options for generating
# and compiling them.

# You can customize FFTW for special needs, e.g. to handle certain
# sizes more efficiently, by adding new codelets to the lists of those
# included by default.  If you change the list of codelets, any new
# ones you added will be automatically generated when you run the
# bootstrap script (see "Generating your own code" in the FFTW
# manual).

# -*- makefile -*-
# This file contains special make rules to generate codelets.
# This file requires GNU make .

srcdir = .
top_srcdir = ../../..

pkgdatadir = $(datadir)/fftw
pkglibdir = $(libdir)/fftw
pkgincludedir = $(includedir)/fftw
top_builddir = ../../..

am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
INSTALL = /usr/bin/install -c
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_triplet = i686-pc-linux-gnu
ACLOCAL = ${SHELL} /export/data_1/rbradley/satellite/Sat1/fftw-3.0.1/missing --run aclocal-1.7
ALLOCA = 
AMDEP_FALSE = #
AMDEP_TRUE = 
AMTAR = ${SHELL} /export/data_1/rbradley/satellite/Sat1/fftw-3.0.1/missing --run tar
AS = gcc
ASFLAGS = 
AUTOCONF = ${SHELL} /export/data_1/rbradley/satellite/Sat1/fftw-3.0.1/missing --run autoconf
AUTOHEADER = ${SHELL} /export/data_1/rbradley/satellite/Sat1/fftw-3.0.1/missing --run autoheader
AUTOMAKE = ${SHELL} /export/data_1/rbradley/satellite/Sat1/fftw-3.0.1/missing --run automake-1.7
AWK = gawk
CC = gcc
CCAS = gcc
CCASFLAGS = 
CCDEPMODE = depmode=gcc3
CFLAGS = -O3 -fomit-frame-pointer -fno-schedule-insns -malign-double -fstrict-aliasing -mpreferred-stack-boundary=4 -mcpu=pentiumpro -O
CODELET_OPTIM = -O
CPP = gcc -E
CPPFLAGS = 
CYGPATH_W = echo
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
ECHO = echo
ECHO_C = 
ECHO_N = -n
ECHO_T = 
EGREP = grep -E
EXEEXT = 
F77 = g77
FFLAGS = -g -O2
FLIBS =  -L/usr/lib/gcc/i686-redhat-linux/3.4.6 -L/usr/lib/gcc/i686-redhat-linux/3.4.6/../../.. -lfrtbegin -lg2c -lm -lgcc_s
FMA_FALSE = 
FMA_TRUE = #
HAVE_K7_FALSE = 
HAVE_K7_TRUE = #
HAVE_SIMD_FALSE = 
HAVE_SIMD_TRUE = #
INSTALLED_OCAMLC = /usr/local/bin/-ocamlc
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
LDFLAGS = 
LDOUBLE_FALSE = 
LDOUBLE_TRUE = #
LIBOBJS = 
LIBS = -lm 
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
LTLIBOBJS = 
MAINT = #
MAINTAINER_MODE_FALSE = 
MAINTAINER_MODE_TRUE = #
MAKEINFO = ${SHELL} /export/data_1/rbradley/satellite/Sat1/fftw-3.0.1/missing --run makeinfo
OBJEXT = o
OCAMLC = 
OCAMLCFLAGS = 
OCAMLDEFS = 
OCAMLDEP = 
OCAMLLDFLAGS = 
OCAMLOPT = 
OCAMLOPTCFLAGS = 
PACKAGE = fftw
PACKAGE_BUGREPORT = fftw@fftw.org
PACKAGE_NAME = fftw
PACKAGE_STRING = fftw 3.0.1
PACKAGE_TARNAME = fftw
PACKAGE_VERSION = 3.0.1
PATH_SEPARATOR = :
POW_LIB = 
PRECISION = d
PREC_SUFFIX = 
PTHREAD_CC = 
PTHREAD_CFLAGS = 
PTHREAD_LIBS = 
RANLIB = ranlib
SET_MAKE = 
SHARED_VERSION_INFO = 3:1:0
SHELL = /bin/sh
SIMD_CFLAGS = 
SINGLE_FALSE = 
SINGLE_TRUE = #
STRIP = strip
TARGET_OCAMLBIN = /usr/local//bin
TARGET_OCAMLLIB = /usr/local//lib/fftw
TARGET_OCAMLRUN = /usr/local//bin/ocamlrun
THREADLIBS = 
THREADS_FALSE = 
THREADS_TRUE = #
VERSION = 3.0.1
ac_ct_CC = gcc
ac_ct_F77 = g77
ac_ct_RANLIB = ranlib
ac_ct_STRIP = strip
am__fastdepCC_FALSE = #
am__fastdepCC_TRUE = 
am__include = include
am__leading_dot = .
am__quote = 
bindir = ${exec_prefix}/bin
build = i686-pc-linux-gnu
build_alias = 
build_cpu = i686
build_os = linux-gnu
build_vendor = pc
datadir = ${prefix}/share
exec_prefix = ${prefix}
host = i686-pc-linux-gnu
host_alias = 
host_cpu = i686
host_os = linux-gnu
host_vendor = pc
includedir = ${prefix}/include
infodir = ${prefix}/info
install_sh = /export/data_1/rbradley/satellite/Sat1/fftw-3.0.1/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localstatedir = ${prefix}/var
mandir = ${prefix}/man
oldincludedir = /usr/include
prefix = /usr/local
program_transform_name = s,x,x,
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
sysconfdir = ${prefix}/etc
target_alias = 

###########################################################################
AM_CPPFLAGS = -I$(top_srcdir)/kernel -I$(top_srcdir)/rdft	\
-I$(top_srcdir)/rdft/codelets

noinst_LTLIBRARIES = librdft_codelets_hc2r.la

###########################################################################
# hc2r_<n> is a hard-coded complex-to-real FFT of size <n> (base cases
# of real-output FFT recursion)
HC2R = hc2r_3.c hc2r_4.c hc2r_5.c hc2r_6.c hc2r_7.c hc2r_8.c hc2r_9.c	\
hc2r_10.c hc2r_11.c hc2r_12.c hc2r_13.c hc2r_14.c hc2r_15.c hc2r_16.c	\
hc2r_32.c



# (hc2r_2.c is equivalent to r2hc_2.c)
MHC2R = mhc2r_32.c mhc2r_64.c mhc2r_128.c

###########################################################################
# hb_<r> is a "twiddle" FFT of size <r>, implementing a radix-r DIF
# step for a real-output FFT.  Every hb codelet must have a
# corresponding hc2rIII codelet (see below)!
HB = hb_2.c hb_3.c hb_4.c hb_5.c hb_6.c hb_7.c hb_8.c hb_9.c	\
hb_10.c hb_12.c hb_15.c hb_16.c hb_32.c hb_64.c


# like hb, but generates part of its trig table on the fly (good for large n)
HB2 = hb2_4.c hb2_8.c hb2_16.c hb2_32.c hb2_64.c

# an hc2r transform where the output is shifted by half a sample (input
# is multiplied by a phase).  This is needed as part of the DIF recursion;
# every hb_<r> or hb2_<r> codelet should have a corresponding hc2rIII_<r>
HC2RIII = hc2rIII_2.c hc2rIII_3.c hc2rIII_4.c hc2rIII_5.c hc2rIII_6.c	\
hc2rIII_7.c hc2rIII_8.c hc2rIII_9.c hc2rIII_10.c hc2rIII_12.c		\
hc2rIII_15.c hc2rIII_16.c hc2rIII_32.c


MHC2RIII = mhc2rIII_32.c mhc2rIII_64.c

###########################################################################
ALL_CODELETS = $(HC2R) $(MHC2R) $(HB) $(HC2RIII) $(MHC2RIII)

BUILT_SOURCES = $(ALL_CODELETS) $(CODLIST)

librdft_codelets_hc2r_la_SOURCES = $(BUILT_SOURCES)

SOLVTAB_NAME = X(solvtab_rdft_hc2r)

CODLIST = codlist.c
CODELET_NAME = codelet_

#INDENT = indent -kr -cs -i5 -l800 -fca -nfc1 -sc -sob -cli4 -TR -Tplanner -TV
#GENFFTDIR = ${top_builddir}/genfft
#K7GENFFTDIR = ${top_builddir}/genfft-k7
#GEN_NOTW = ${GENFFTDIR}/gen_notw
#GEN_NOTW_NOINLINE = ${GENFFTDIR}/gen_notw_noinline
#GEN_NOTW_C = ${GENFFTDIR}/gen_notw_c
#GEN_NOTW_NOINLINE_C = ${GENFFTDIR}/gen_notw_noinline_c
#K7GEN_NOTW = ${K7GENFFTDIR}/gen_notw
#GEN_TWIDDLE = ${GENFFTDIR}/gen_twiddle
#GEN_TWIDDLE_C = ${GENFFTDIR}/gen_twiddle_c
#K7GEN_TWIDDLE = ${K7GENFFTDIR}/gen_twiddle
#GEN_TWIDSQ = ${GENFFTDIR}/gen_twidsq
#GEN_TWIDSQ_C = ${GENFFTDIR}/gen_twidsq_c
#GEN_R2HC = ${GENFFTDIR}/gen_r2hc
#GEN_R2HC_NOINLINE = ${GENFFTDIR}/gen_r2hc_noinline
#GEN_HC2R = ${GENFFTDIR}/gen_hc2r
#GEN_HC2R_NOINLINE = ${GENFFTDIR}/gen_hc2r_noinline
#GEN_HC2HC = ${GENFFTDIR}/gen_hc2hc
#GEN_R2R = ${GENFFTDIR}/gen_r2r
#PRELUDE_DFT = ${top_srcdir}/support/codelet_prelude.dft
#PRELUDE_RDFT = ${top_srcdir}/support/codelet_prelude.rdft
#ASMPRELUDE = ${top_srcdir}/support/codelet_asmprelude
#ADD_DATE = sed -e s/@DATE@/"`date`"/

#COPYRIGHT = ${top_srcdir}/COPYRIGHT
#CODELET_DEPS = $(COPYRIGHT) $(PRELUDE) $(ASMPRELUDE)
#PRELUDE_COMMANDS_DFT = cat $(COPYRIGHT) $(PRELUDE_DFT)
#PRELUDE_COMMANDS_RDFT = cat $(COPYRIGHT) $(PRELUDE_RDFT)
#ASMPRELUDE_COMMANDS = cat $(COPYRIGHT) $(ASMPRELUDE)
#FLAGS_FMA = 

##FLAGS_FMA = -fma

#FLAGS_COMMON = -compact -variables 4 $(FLAGS_FMA) #-no-randomized-cse
#DFT_FLAGS_COMMON = $(FLAGS_COMMON) 
#RDFT_FLAGS_COMMON = $(FLAGS_COMMON)


# special rules for regenerating codelets.
#FLAGS_HC2R = $(RDFT_FLAGS_COMMON) -sign 1
#FLAGS_HB = $(RDFT_FLAGS_COMMON) -sign 1
#FLAGS_HB2 = $(RDFT_FLAGS_COMMON) -sign 1 -twiddle-log3
#FLAGS_HC2RIII = $(RDFT_FLAGS_COMMON) -sign 1
subdir = rdft/codelets/hc2r
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
LTLIBRARIES = $(noinst_LTLIBRARIES)

librdft_codelets_hc2r_la_LDFLAGS =
librdft_codelets_hc2r_la_LIBADD =
am__objects_1 = hc2r_3.lo hc2r_4.lo hc2r_5.lo hc2r_6.lo hc2r_7.lo \
	hc2r_8.lo hc2r_9.lo hc2r_10.lo hc2r_11.lo hc2r_12.lo hc2r_13.lo \
	hc2r_14.lo hc2r_15.lo hc2r_16.lo hc2r_32.lo
am__objects_2 = mhc2r_32.lo mhc2r_64.lo mhc2r_128.lo
am__objects_3 = hb_2.lo hb_3.lo hb_4.lo hb_5.lo hb_6.lo hb_7.lo hb_8.lo \
	hb_9.lo hb_10.lo hb_12.lo hb_15.lo hb_16.lo hb_32.lo hb_64.lo
am__objects_4 = hc2rIII_2.lo hc2rIII_3.lo hc2rIII_4.lo hc2rIII_5.lo \
	hc2rIII_6.lo hc2rIII_7.lo hc2rIII_8.lo hc2rIII_9.lo \
	hc2rIII_10.lo hc2rIII_12.lo hc2rIII_15.lo hc2rIII_16.lo \
	hc2rIII_32.lo
am__objects_5 = mhc2rIII_32.lo mhc2rIII_64.lo
am__objects_6 = $(am__objects_1) $(am__objects_2) $(am__objects_3) \
	$(am__objects_4) $(am__objects_5)
am__objects_7 = codlist.lo
am__objects_8 = $(am__objects_6) $(am__objects_7)
am_librdft_codelets_hc2r_la_OBJECTS = $(am__objects_8)
librdft_codelets_hc2r_la_OBJECTS = \
	$(am_librdft_codelets_hc2r_la_OBJECTS)

DEFAULT_INCLUDES =  -I. -I$(srcdir) -I$(top_builddir)
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__depfiles_maybe = depfiles
DEP_FILES = ./$(DEPDIR)/codlist.Plo ./$(DEPDIR)/hb_10.Plo \
	./$(DEPDIR)/hb_12.Plo ./$(DEPDIR)/hb_15.Plo \
	./$(DEPDIR)/hb_16.Plo ./$(DEPDIR)/hb_2.Plo \
	./$(DEPDIR)/hb_3.Plo ./$(DEPDIR)/hb_32.Plo \
	./$(DEPDIR)/hb_4.Plo ./$(DEPDIR)/hb_5.Plo \
	./$(DEPDIR)/hb_6.Plo ./$(DEPDIR)/hb_64.Plo \
	./$(DEPDIR)/hb_7.Plo ./$(DEPDIR)/hb_8.Plo \
	./$(DEPDIR)/hb_9.Plo ./$(DEPDIR)/hc2rIII_10.Plo \
	./$(DEPDIR)/hc2rIII_12.Plo \
	./$(DEPDIR)/hc2rIII_15.Plo \
	./$(DEPDIR)/hc2rIII_16.Plo \
	./$(DEPDIR)/hc2rIII_2.Plo ./$(DEPDIR)/hc2rIII_3.Plo \
	./$(DEPDIR)/hc2rIII_32.Plo \
	./$(DEPDIR)/hc2rIII_4.Plo ./$(DEPDIR)/hc2rIII_5.Plo \
	./$(DEPDIR)/hc2rIII_6.Plo ./$(DEPDIR)/hc2rIII_7.Plo \
	./$(DEPDIR)/hc2rIII_8.Plo ./$(DEPDIR)/hc2rIII_9.Plo \
	./$(DEPDIR)/hc2r_10.Plo ./$(DEPDIR)/hc2r_11.Plo \
	./$(DEPDIR)/hc2r_12.Plo ./$(DEPDIR)/hc2r_13.Plo \
	./$(DEPDIR)/hc2r_14.Plo ./$(DEPDIR)/hc2r_15.Plo \
	./$(DEPDIR)/hc2r_16.Plo ./$(DEPDIR)/hc2r_3.Plo \
	./$(DEPDIR)/hc2r_32.Plo ./$(DEPDIR)/hc2r_4.Plo \
	./$(DEPDIR)/hc2r_5.Plo ./$(DEPDIR)/hc2r_6.Plo \
	./$(DEPDIR)/hc2r_7.Plo ./$(DEPDIR)/hc2r_8.Plo \
	./$(DEPDIR)/hc2r_9.Plo ./$(DEPDIR)/mhc2rIII_32.Plo \
	./$(DEPDIR)/mhc2rIII_64.Plo \
	./$(DEPDIR)/mhc2r_128.Plo ./$(DEPDIR)/mhc2r_32.Plo \
	./$(DEPDIR)/mhc2r_64.Plo
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) --mode=compile $(CC) $(DEFS) $(DEFAULT_INCLUDES) \
	$(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(LIBTOOL) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
DIST_SOURCES = $(librdft_codelets_hc2r_la_SOURCES)
DIST_COMMON = $(top_srcdir)/support/Makefile.codelets Makefile.am \
	Makefile.in
SOURCES = $(librdft_codelets_hc2r_la_SOURCES)

all: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) all-am

.SUFFIXES:
.SUFFIXES: .c .lo .o .obj
$(srcdir)/Makefile.in: # Makefile.am $(top_srcdir)/support/Makefile.codelets $(top_srcdir)/configure.ac $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  rdft/codelets/hc2r/Makefile
Makefile: # $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)

clean-noinstLTLIBRARIES:
	-test -z "$(noinst_LTLIBRARIES)" || rm -f $(noinst_LTLIBRARIES)
	@list='$(noinst_LTLIBRARIES)'; for p in $$list; do \
	  dir="`echo $$p | sed -e 's|/[^/]*$$||'`"; \
	  test "$$dir" = "$$p" && dir=.; \
	  echo "rm -f \"$${dir}/so_locations\""; \
	  rm -f "$${dir}/so_locations"; \
	done
librdft_codelets_hc2r.la: $(librdft_codelets_hc2r_la_OBJECTS) $(librdft_codelets_hc2r_la_DEPENDENCIES) 
	$(LINK)  $(librdft_codelets_hc2r_la_LDFLAGS) $(librdft_codelets_hc2r_la_OBJECTS) $(librdft_codelets_hc2r_la_LIBADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT) core *.core

distclean-compile:
	-rm -f *.tab.c

include ./$(DEPDIR)/codlist.Plo
include ./$(DEPDIR)/hb_10.Plo
include ./$(DEPDIR)/hb_12.Plo
include ./$(DEPDIR)/hb_15.Plo
include ./$(DEPDIR)/hb_16.Plo
include ./$(DEPDIR)/hb_2.Plo
include ./$(DEPDIR)/hb_3.Plo
include ./$(DEPDIR)/hb_32.Plo
include ./$(DEPDIR)/hb_4.Plo
include ./$(DEPDIR)/hb_5.Plo
include ./$(DEPDIR)/hb_6.Plo
include ./$(DEPDIR)/hb_64.Plo
include ./$(DEPDIR)/hb_7.Plo
include ./$(DEPDIR)/hb_8.Plo
include ./$(DEPDIR)/hb_9.Plo
include ./$(DEPDIR)/hc2rIII_10.Plo
include ./$(DEPDIR)/hc2rIII_12.Plo
include ./$(DEPDIR)/hc2rIII_15.Plo
include ./$(DEPDIR)/hc2rIII_16.Plo
include ./$(DEPDIR)/hc2rIII_2.Plo
include ./$(DEPDIR)/hc2rIII_3.Plo
include ./$(DEPDIR)/hc2rIII_32.Plo
include ./$(DEPDIR)/hc2rIII_4.Plo
include ./$(DEPDIR)/hc2rIII_5.Plo
include ./$(DEPDIR)/hc2rIII_6.Plo
include ./$(DEPDIR)/hc2rIII_7.Plo
include ./$(DEPDIR)/hc2rIII_8.Plo
include ./$(DEPDIR)/hc2rIII_9.Plo
include ./$(DEPDIR)/hc2r_10.Plo
include ./$(DEPDIR)/hc2r_11.Plo
include ./$(DEPDIR)/hc2r_12.Plo
include ./$(DEPDIR)/hc2r_13.Plo
include ./$(DEPDIR)/hc2r_14.Plo
include ./$(DEPDIR)/hc2r_15.Plo
include ./$(DEPDIR)/hc2r_16.Plo
include ./$(DEPDIR)/hc2r_3.Plo
include ./$(DEPDIR)/hc2r_32.Plo
include ./$(DEPDIR)/hc2r_4.Plo
include ./$(DEPDIR)/hc2r_5.Plo
include ./$(DEPDIR)/hc2r_6.Plo
include ./$(DEPDIR)/hc2r_7.Plo
include ./$(DEPDIR)/hc2r_8.Plo
include ./$(DEPDIR)/hc2r_9.Plo
include ./$(DEPDIR)/mhc2rIII_32.Plo
include ./$(DEPDIR)/mhc2rIII_64.Plo
include ./$(DEPDIR)/mhc2r_128.Plo
include ./$(DEPDIR)/mhc2r_32.Plo
include ./$(DEPDIR)/mhc2r_64.Plo

distclean-depend:
	-rm -rf ./$(DEPDIR)

.c.o:
	if $(COMPILE) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" \
	  -c -o $@ `test -f '$<' || echo '$(srcdir)/'`$<; \
	then mv "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; \
	else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; \
	fi
#	source='$<' object='$@' libtool=no \
#	depfile='$(DEPDIR)/$*.Po' tmpdepfile='$(DEPDIR)/$*.TPo' \
#	$(CCDEPMODE) $(depcomp) \
#	$(COMPILE) -c `test -f '$<' || echo '$(srcdir)/'`$<

.c.obj:
	if $(COMPILE) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" \
	  -c -o $@ `if test -f '$<'; then $(CYGPATH_W) '$<'; else $(CYGPATH_W) '$(srcdir)/$<'; fi`; \
	then mv "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; \
	else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; \
	fi
#	source='$<' object='$@' libtool=no \
#	depfile='$(DEPDIR)/$*.Po' tmpdepfile='$(DEPDIR)/$*.TPo' \
#	$(CCDEPMODE) $(depcomp) \
#	$(COMPILE) -c `if test -f '$<'; then $(CYGPATH_W) '$<'; else $(CYGPATH_W) '$(srcdir)/$<'; fi`

.c.lo:
	if $(LTCOMPILE) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" \
	  -c -o $@ `test -f '$<' || echo '$(srcdir)/'`$<; \
	then mv "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Plo"; \
	else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; \
	fi
#	source='$<' object='$@' libtool=yes \
#	depfile='$(DEPDIR)/$*.Plo' tmpdepfile='$(DEPDIR)/$*.TPlo' \
#	$(CCDEPMODE) $(depcomp) \
#	$(LTCOMPILE) -c -o $@ `test -f '$<' || echo '$(srcdir)/'`$<

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool
uninstall-info-am:

ETAGS = etags
ETAGSFLAGS =

CTAGS = ctags
CTAGSFLAGS =

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	mkid -fID $$unique

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$tags$$unique" \
	  || $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	     $$tags $$unique

ctags: CTAGS
CTAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(CTAGS_ARGS)$$tags$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$tags $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && cd $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) $$here

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ../../..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	$(mkinstalldirs) $(distdir)/../../../support
	@srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's|.|.|g'`; \
	list='$(DISTFILES)'; for file in $$list; do \
	  case $$file in \
	    $(srcdir)/*) file=`echo "$$file" | sed "s|^$$srcdirstrip/||"`;; \
	    $(top_srcdir)/*) file=`echo "$$file" | sed "s|^$$topsrcdirstrip/|$(top_builddir)/|"`;; \
	  esac; \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    dir="/$$dir"; \
	    $(mkinstalldirs) "$(distdir)$$dir"; \
	  else \
	    dir=''; \
	  fi; \
	  if test -d $$d/$$file; then \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -pR $(srcdir)/$$file $(distdir)$$dir || exit 1; \
	    fi; \
	    cp -pR $$d/$$file $(distdir)$$dir || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) check-am
all-am: Makefile $(LTLIBRARIES)

installdirs:

install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  INSTALL_STRIP_FLAG=-s \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
	-test -z "$(BUILT_SOURCES)" || rm -f $(BUILT_SOURCES)
clean: clean-am

clean-am: clean-generic clean-libtool clean-local \
	clean-noinstLTLIBRARIES mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-compile distclean-depend \
	distclean-generic distclean-libtool distclean-tags

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am:

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am: uninstall-info-am

.PHONY: CTAGS GTAGS all all-am check check-am clean clean-generic \
	clean-libtool clean-local clean-noinstLTLIBRARIES ctags \
	distclean distclean-compile distclean-depend distclean-generic \
	distclean-libtool distclean-tags distdir dvi dvi-am info \
	info-am install install-am install-data install-data-am \
	install-exec install-exec-am install-info install-info-am \
	install-man install-strip installcheck installcheck-am \
	installdirs maintainer-clean maintainer-clean-generic \
	mostlyclean mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool pdf pdf-am ps ps-am tags uninstall \
	uninstall-am uninstall-info-am


# rule to build codlist
$(CODLIST): Makefile
	(								\
	echo "#include \"ifftw.h\"";					\
	echo;								\
	for i in $(ALL_CODELETS) NIL; do				\
	   if test "$$i" != NIL; then					\
	     j=`basename $$i | sed -e 's/[.][cS]$$//g'`;		\
             echo "extern void X($(CODELET_NAME)$$j)(planner *);";	\
           fi								\
	done;								\
	echo;								\
	echo;								\
	echo "extern const solvtab $(SOLVTAB_NAME);";		        \
	echo "const solvtab $(SOLVTAB_NAME) = {";		        \
	for i in $(ALL_CODELETS) NIL; do				\
	   if test "$$i" != NIL; then					\
	     j=`basename $$i | sed -e 's/[.][cS]$$//g'`;		\
	     echo "   SOLVTAB(X($(CODELET_NAME)$$j)),";			\
	   fi								\
	done;								\
	echo "   SOLVTAB_END";						\
	echo "};";							\
	) >$@

clean-local:
	rm -f codlist.c

# cancel the hideous builtin rules that cause an infinite loop
#%: %.o
#%: %.s
#%: %.c
#%: %.S

#hc2r_%.c:  $(CODELET_DEPS) $(GEN_HC2R)
#	($(PRELUDE_COMMANDS_RDFT); $(GEN_HC2R) $(FLAGS_HC2R) -n $* -name hc2r_$* -include "hc2r.h") | $(ADD_DATE) | $(INDENT) >$@

#mhc2r_%.c:  $(CODELET_DEPS) $(GEN_HC2R_NOINLINE)
#	($(PRELUDE_COMMANDS_RDFT); $(GEN_HC2R_NOINLINE) $(FLAGS_HC2R) -n $* -name mhc2r_$* -include "hc2r.h") | $(ADD_DATE) | $(INDENT) >$@

#hb_%.c:  $(CODELET_DEPS) $(GEN_HC2HC)
#	($(PRELUDE_COMMANDS_RDFT); $(GEN_HC2HC) $(FLAGS_HB) -n $* -dif -name hb_$* -include "hb.h") | $(ADD_DATE) | $(INDENT) >$@

#hb2_%.c:  $(CODELET_DEPS) $(GEN_HC2HC)
#	($(PRELUDE_COMMANDS_RDFT); $(GEN_HC2HC) $(FLAGS_HB2) -n $* -dif -name hb2_$* -include "hb.h") | $(ADD_DATE) | $(INDENT) >$@

#hc2rIII_%.c:  $(CODELET_DEPS) $(GEN_HC2R)
#	($(PRELUDE_COMMANDS_RDFT); $(GEN_HC2R) $(FLAGS_HC2R) -n $* -name hc2rIII_$* -dft-III -include "hc2rIII.h") | $(ADD_DATE) | $(INDENT) >$@

#mhc2rIII_%.c:  $(CODELET_DEPS) $(GEN_HC2R_NOINLINE)
#	($(PRELUDE_COMMANDS_RDFT); $(GEN_HC2R_NOINLINE) $(FLAGS_HC2R) -n $* -name mhc2rIII_$* -dft-III -include "hc2rIII.h") | $(ADD_DATE) | $(INDENT) >$@
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
