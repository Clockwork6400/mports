# Created by: Sergey Kozlov <sergey.kozlov@intel.com>

PORTNAME?=	ixl
PORTVERSION?=	1.12.2
PORTREVISION?=	0
CATEGORIES=	net
MASTER_SITES?=	https://downloadmirror.intel.com/${MASTER_SITE_SUBDIR}/ \
		http://downloadmirror.intel.com/${MASTER_SITE_SUBDIR}/
MASTER_SITE_SUBDIR?=	25160/eng
PKGNAMEPREFIX=	intel-
PKGNAMESUFFIX=	-kmod

MAINTAINER?=	ports@MidnightBSD.org
COMMENT?=	40 gigabit FreeBSD Base Driver for Intel(R) Network Connections

LICENSE=	bsd2

USES=		kmod

OPTIONS_SINGLE=		NETMAP
OPTIONS_SINGLE_NETMAP=	NETMAP_AUTO NETMAP_ON NETMAP_OFF
OPTIONS_DEFAULT=	NETMAP_AUTO

NETMAP_AUTO_DESC=	Enable netmap(4) support on supported OS versions
NETMAP_ON_DESC=		Enable netmap(4) support unconditionally
NETMAP_OFF_DESC=	Disable netmap(4) support unconditionally

NETMAP_ON_CFLAGS=	-DDEV_NETMAP
NETMAP_OFF_CFLAGS=	-UDEV_NETMAP

WRKSRC_SUBDIR=	src

SUB_FILES=	pkg-message
SUB_LIST=	PORTNAME=${PORTNAME}
MANPAGENAME?=	${PORTNAME}
MANPAGELINKS?=	if_${PORTNAME}
PLIST_FILES=	${KMODDIR}/if_${PORTNAME}_updated.ko \
		man/man4/${MANPAGENAME}.4.gz
MAKE_ENV+=	WERROR=""

.for link in ${MANPAGELINKS}
PLIST_FILES+=	man/man4/${link}.4.gz
.endfor

MAX_NETMAP_OSVERSION?=	1200500  # Maximum OSVERSION for which NETMAP support works

.include <bsd.port.pre.mk>

# Fixup for slave ports that use this as a master port. sbruno
.if ${PORTNAME} == ixl
PATCH_SITES=	https://svnweb.freebsd.org/base/head/sys/dev/ixl/
PATCHFILES=	ixl_pf_main.c?view=patch&r1=358698&r2=358697&pathrev=358698:-p4
ONLY_FOR_ARCHS=		amd64 powerpc64 powerpc64le
ONLY_FOR_ARCHS_REASON=	Not supported on other architectures, amd64 and powerpc64 only.
.endif

.if ${PORT_OPTIONS:MNETMAP_AUTO} && ${OSVERSION} <= ${MAX_NETMAP_OSVERSION}
CFLAGS+=	-DDEV_NETMAP
.endif

do-install:
	${MKDIR} ${KMODDIR}
	${INSTALL_KLD} ${WRKSRC}/if_${PORTNAME}.ko ${KMODDIR}/if_${PORTNAME}_updated.ko
	${INSTALL_MAN} ${WRKSRC}/${MANPAGENAME}.4 ${STAGEDIR}${MAN4PREFIX}/man/man4/

.for link in ${MANPAGELINKS}
	${LN} ${STAGEDIR}${MAN4PREFIX}/man/man4/${MANPAGENAME}.4 ${STAGEDIR}${MAN4PREFIX}/man/man4/${link}.4
.endfor

.include <bsd.port.post.mk>
