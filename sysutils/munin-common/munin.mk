MUNIN_VERSION=	2.0.11.1
MUNIN_SITES=	SF/${PORTNAME}/stable/2.0.11
MUNIN_DISTINFO=	${PORTSDIR}/sysutils/munin-common/distinfo
MUNIN_PATCHES=	${PORTSDIR}/sysutils/munin-common/files/patch-Makefile \
		${PORTSDIR}/sysutils/munin-common/files/patch-Makefile.config

DBDIR?=		/var/${PORTNAME}
DBDIRNODE?=	/var/${PORTNAME}
LOGDIR?=	/var/log/${PORTNAME}
STATEDIR?=	/var/run/${PORTNAME}
SPOOLDIR?=	/var/spool/${PORTNAME}
MUNIN_DIRS=	BINDIR=${FAKE_DESTDIR}${PREFIX}/bin \
		CGIDIR=${FAKE_DESTDIR}${PREFIX}/www/cgi-bin \
		CONFDIR=${FAKE_DESTDIR}${ETCDIR} \
		DBDIR=${DBDIR} \
		DBDIRNODE=${DBDIRNODE} \
		DOCDIR=${DOCSDIR} \
		HTMLDIR=${WWWDIR} \
		LIBDIR=${FAKE_DESTDIR}${DATADIR} \
		LOGDIR=${LOGDIR} \
		MANDIR=${MANPREFIX}/man \
		SBINDIR=${FAKE_DESTDIR}${PREFIX}/sbin \
		STATEDIR=${STATEDIR} \
		SPOOLDIR=${SPOOLDIR}
MAKE_ARGS=	${MUNIN_DIRS} \
		BASH=${LOCALBASE}/bin/bash \
		PERL=${PERL} PERLLIB=${FAKE_DESTDIR}${PREFIX}/${SITE_PERL_REL}
USERS=		munin
GROUPS=		munin
PLIST_SUB=	${MUNIN_DIRS} USER=${USERS} GROUP=${GROUPS}
