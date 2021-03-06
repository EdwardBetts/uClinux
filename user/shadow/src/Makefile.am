
EXTRA_DIST = \
	.indent.pro

ubindir = ${prefix}/bin
usbindir = ${prefix}/sbin

INCLUDES = \
	-I${top_srcdir}/lib \
	-I$(top_srcdir)/libmisc

# XXX why are login and su in /bin anyway (other than for
# historical reasons)?
#
# if the system is screwed so badly that it can't mount /usr,
# you can (hopefully) boot single user, and then you're root
# so you don't need these programs for recovery.
#
# also /lib/libshadow.so.x.xx (if any) could be moved to /usr/lib
# and installation would be much simpler (just two directories,
# $prefix/bin and $prefix/sbin, no install-data hacks...)

bin_PROGRAMS   = groups login su
ubin_PROGRAMS  = faillog lastlog chage chfn chsh expiry gpasswd newgrp passwd
usbin_PROGRAMS = \
	chpasswd \
	groupadd \
	groupdel \
	groupmod \
	grpck \
	grpconv \
	grpunconv \
	logoutd \
	newusers \
	nologin \
	pwck \
	pwconv \
	pwunconv \
	useradd \
	userdel \
	usermod \
	vipw

# id and groups are from gnu, sulogin from sysvinit
noinst_PROGRAMS = id sulogin

suidbins       = su
suidubins      = chage chfn chsh expiry gpasswd newgrp passwd

LDADD 	       = $(top_builddir)/libmisc/libmisc.a \
		 $(top_builddir)/lib/libshadow.la
AM_CPPFLAGS    = -DLOCALEDIR=\"$(datadir)/locale\"

chage_LDADD    = $(LDADD) $(LIBPAM) $(LIBAUDIT)
chfn_LDADD     = $(LDADD) $(LIBPAM)
chsh_LDADD     = $(LDADD) $(LIBPAM)
chpasswd_LDADD = $(LDADD) $(LIBPAM)
gpasswd_LDADD  = $(LDADD) $(LIBAUDIT)
groupadd_LDADD = $(LDADD) $(LIBPAM) $(LIBAUDIT)
groupdel_LDADD = $(LDADD) $(LIBPAM) $(LIBAUDIT)
groupmod_LDADD = $(LDADD) $(LIBPAM) $(LIBAUDIT)
login_SOURCES  = \
	login.c \
	login_nopam.c
login_LDADD    = $(LDADD) $(LIBPAM) $(LIBAUDIT)
newgrp_LDADD   = $(LDADD) $(LIBPAM) $(LIBAUDIT)
newusers_LDADD = $(LDADD) $(LIBPAM)
nologin_LDADD  =
passwd_LDADD   = $(LDADD) $(LIBPAM) $(LIBCRACK) $(LIBAUDIT)
su_SOURCES     = \
	su.c \
	suauth.c
su_LDADD       = $(LDADD) $(LIBPAM)
useradd_LDADD  = $(LDADD) $(LIBPAM) $(LIBAUDIT)
userdel_LDADD  = $(LDADD) $(LIBPAM) $(LIBAUDIT)
usermod_LDADD  = $(LDADD) $(LIBPAM) $(LIBAUDIT)

install-am: all-am
	$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
	ln -sf newgrp	$(DESTDIR)$(ubindir)/sg
	ln -sf vipw	$(DESTDIR)$(usbindir)/vigr
	for i in $(suidbins); do \
		chmod -f 4755 $(DESTDIR)$(bindir)/$$i; \
	done
	for i in $(suidubins); do \
		chmod -f 4755 $(DESTDIR)$(ubindir)/$$i; \
	done
