include silent.mk

ifneq ($(DEVKITMINT),)
	export PATH		:=	$(DEVKITMINT)/../devkitMINT/bin:$(PATH)
endif

all:$(patsubst %,%/$(APP),$(TRGTDIRS))

#
# ONLY_68K: for faster developing; set to Y to build only the 68000 library
# BUILD_CF: Build ColfFire binaries.
# MINTLIB_COMPATIBLE: set to Y to build libcmini with mintlib-includes
#
ONLY_68K=N
BUILD_CF=Y
MINTLIB_COMPATIBLE=N
COMPILE_ELF=N
STDIO_WITH_LONG_LONG=N

ifeq (Y,$(COMPILE_ELF))
	PREFIX=m68k-elf-
else 
  	PREFIX=m68k-atari-mint-
endif

-include Make.config

CC=$(PREFIX)gcc
LD=$(PREFIX)ld
CPP=$(PREFIX)cpp
OBJCOPY=$(PREFIX)objcopy
AR=$(PREFIX)ar
RANLIB=$(PREFIX)ranlib

BUILD_FAST=$(shell if $(CC) -mfastcall -E - < /dev/null >/dev/null 2>&1; then echo Y; else echo N; fi)

CFLAGS=\
	   -Wall -Wstrict-prototypes -Wmissing-prototypes -Wdeclaration-after-statement -Werror \
	   -Os \
	   -fomit-frame-pointer

ifneq ($(MINTLIB_COMPATIBLE),Y)
	INCLUDE=-Iinclude
else
	INCLUDE=
	CFLAGS+=-D__MINTLIB_COMPATIBLE
endif

ifeq ($(STDIO_WITH_LONG_LONG),Y)
	CFLAGS+=-DSTDIO_WITH_LONG_LONG
endif


STARTUP= \
	$(SRCDIR)/crt0.S
	
CSRCS= $(wildcard $(SRCDIR)/*.c)
	
ASRCS= $(filter-out $(SRCDIR)/crt0.S $(SRCDIR)/minicrt0.S, $(wildcard $(SRCDIR)/*.S))

SRCDIR=sources
ifeq ($(ONLY_68K),Y)
	LIBDIRS=.
else
	ifeq ($(BUILD_FAST), Y)
		ifeq ($(BUILD_CF),Y)
			LIBDIRS=. ./m68020-60 ./m5475 ./mshort ./m68020-60/mshort ./m5475/mshort ./mfastcall ./m68020-60/mfastcall ./m5475/mfastcall ./mshort/mfastcall ./m68020-60/mshort/mfastcall ./m5475/mshort/mfastcall
		else
			LIBDIRS=. ./m68020-60 ./mshort ./m68020-60/mshort ./mfastcall ./m68020-60/mfastcall ./mshort/mfastcall ./m68020-60/mshort/mfastcall
		endif
	else
		ifeq ($(BUILD_CF),Y)
			LIBDIRS=. ./m68020-60 ./m5475 ./mshort ./m68020-60/mshort ./m5475/mshort
		else
			LIBDIRS=. ./m68020-60 ./mshort ./m68020-60/mshort
		endif
	endif
endif
OBJDIRS=$(patsubst %,%/objs,$(LIBDIRS))

COBJS=$(patsubst $(SRCDIR)/%.o,%.o,$(patsubst %.c,%.o,$(CSRCS)))
AOBJS=$(patsubst $(SRCDIR)/%.o,%.o,$(patsubst %.S,%.o,$(ASRCS)))
OBJS=$(COBJS) $(AOBJS)

IIO_OBJS = doprnt.o $(filter %printf.o, $(patsubst %,../%,$(OBJS)))

START_OBJ=crt0.o
LIBC=libcmini.a
LIBIIO=libiiomini.a

LIBS=$(patsubst %,%/$(LIBC),$(LIBDIRS))
LIBSIIO=$(patsubst %,%/$(LIBIIO),$(LIBDIRS))
STARTUPS=$(START_OBJ) minicrt0.o

TESTS:= $(shell ls tests | egrep -v '^(CVS)$$')

all: dirs libs startups tests
libs: $(LIBS) $(LIBSIIO)
	
dirs::
	mkdir -p $(LIBDIRS) $(OBJDIRS)


startups: $(STARTUPS)

tests:
	$(AM_V_at)echo make tests
	$(AM_V_at)for i in $(TESTS); do if test -e tests/$$i/Makefile ; then $(MAKE) -C tests/$$i || { exit 1;} fi; done;


clean:
	$(AM_V_at)rm -rf $(LIBS) $(LIBSIIO) $(patsubst %,%/objs/*.o,$(LIBDIRS)) $(patsubst %,%/objs/*.d,$(LIBDIRS)) $(patsubst %,%/objs/iio,$(LIBDIRS)) $(STARTUPS) $(STARTUPS:.o=.d) depend
	$(AM_V_at)for i in $(TESTS); do if test -e tests/$$i/Makefile ; then $(MAKE) -C tests/$$i clean || { exit 1;} fi; done;
	$(AM_V_at)rm -rf libcmini-*

all:$(patsubst %,%/$(APP),$(TRGTDIRS))

#
# multilib flags
#
m68020-60/%.a: CFLAGS += -m68020-60
mshort/%.a: CFLAGS += -mshort
m68020-60/mshort/%.a: CFLAGS += -m68020-60 -mshort
ifeq ($(BUILD_FAST), Y)
mfastcall/%.a: CFLAGS +=  -mfastcall
m68020-60/mfastcall/%.a: CFLAGS += -m68020-60 -mfastcall
mshort/mfastcall/%.a: CFLAGS += -mshort -mfastcall
m68020-60/mshort/mfastcall/%.a: CFLAGS += -m68020-60 -mshort -mfastcall
endif
ifeq ($(BUILD_CF),Y)
m5475/%.a: CFLAGS += -mcpu=5475
m5475/mshort/%.a: CFLAGS += -mcpu=5475 -mshort
ifeq ($(BUILD_FAST), Y)
m5475/mfastcall/%.a: CFLAGS += -mcpu=5475 -mfastcall
m5475/mshort/mfastcall/%.a: CFLAGS += -mcpu=5475 -mshort -mfastcall
endif
endif

#
# generate pattern rules for multilib object files
#
define CC_TEMPLATE
$(1)/objs/iio/%.o:$(SRCDIR)/iio/%.c
	$(AM_V_CC)$(CC) -MMD -MP -MF $$(@:.o=.d) $$(CFLAGS) $(INCLUDE) -c $$< -o $$@

$(1)/objs/%.o:$(SRCDIR)/%.c
	$(AM_V_CC)$(CC) -MMD -MP -MF $$(@:.o=.d) $$(CFLAGS) $(INCLUDE) -c $$< -o $$@

$(1)/objs/%.o:$(SRCDIR)/%.S
	$(AM_V_AS)$(CC) -MMD -MP -MF $$(@:.o=.d) $$(CFLAGS) $(INCLUDE) -c $$< -o $$@

$(1)/%.o:$(SRCDIR)/%.S
	$(AM_V_AS)$(CC) -MMD -MP -MF $$(@:.o=.d) $$(CFLAGS) $(INCLUDE) -c $$< -o $$@
endef
$(foreach DIR,$(LIBDIRS),$(eval $(call CC_TEMPLATE,$(DIR))))

#
# generate pattern rules for multilib archive
#
define ARC_TEMPLATE
$(1)_OBJS=$(patsubst %,$(1)/objs/%,$(OBJS))
$(1)/$(LIBC): $$($(1)_OBJS)
	$(AM_V_AR)$(AR) cr $$@ $$?
	$(AM_V_at)$(RANLIB) $$@
LIBDEPEND+=$$($1_OBJS)
LIBSE+=$(1)/$(LIBC)

$(shell mkdir -p $(1)/objs/iio)
$(1)_IIO_OBJS=$(patsubst %,$(1)/objs/iio/%,$(IIO_OBJS))
$(1)/$(LIBIIO): $$($(1)_IIO_OBJS)
	$(AM_V_AR)$(AR) cr $$@ $$?
	$(AM_V_at)$(RANLIB) $$@
endef
$(foreach DIR,$(LIBDIRS),$(eval $(call ARC_TEMPLATE,$(DIR))))

.PHONY: release
release: all
	RELEASETAG=$$(git tag --contains | sed -e 's/v//' | sed -e 's/ //g') ;\
    RELEASEDIR=libcmini-$$RELEASETAG ;\
	if [ "x$$RELEASETAG" != "x" ] ; then\
	    mkdir -p $$RELEASEDIR/lib ;\
	    cp -r include $$RELEASEDIR ;\
	    for i in m5475 m68020-60 mshort m5475/mshort m68020-60/mshort; do \
		    mkdir -p $$RELEASEDIR/lib/$$i ;\
	        cp $$i/libcmini.a $$RELEASEDIR/lib/$$i ;\
	    done ;\
	    cp crt0.o libcmini.a $$RELEASEDIR/lib ;\
		chown -R 0:0 $$RELEASEDIR/* ;\
		tar -C $$RELEASEDIR -cvzf $$RELEASEDIR.tar.gz . ;\
	    chmod 644 $$RELEASEDIR.tar.gz ;\
	fi ;\
	ls -l


DEPENDS := $(foreach dir,$(LIBDIRS), $(wildcard $(dir)/objs/*.d) $(wildcard $(dir)/objs/iio/*.d))

.PHONY: printvars tests
printvars:
	@$(foreach V,$(.VARIABLES),	$(if $(filter-out environment% default automatic, $(origin $V)),$(warning $V=$($V))))
		
install::
	for i in $(LIBDIRS); do \
		mkdir -p $(DESTDIR)/usr/lib/$$i; \
		cp -a $$i/$(LIBC) $$i/$(LIBIIO) $(DESTDIR)/usr/lib/$$i; \
	done
	cp -a $(STARTUPS) $(DESTDIR)/usr/lib

ifneq (clean,$(MAKECMDGOALS))
-include $(DEPENDS)
endif
