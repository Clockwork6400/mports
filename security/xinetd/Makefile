

PORTNAME=	xinetd
PORTVERSION=	2.3.15
PORTREVISION=	3
CATEGORIES=	security ipv6
MASTER_SITES=	GENTOO

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Replacement for inetd with better control and logging

LICENSE=	other

FAKE_OPTS=	prefixhack

GNU_CONFIGURE=	yes
USE_RC_SUBR=	xinetd
ALL_TARGET=	build
CONFIGURE_ARGS+=	--with-loadavg

USES=		cpe shebangfix perl5
USE_PERL5=	run
SHEBANG_FILES=	${WRKSRC}/xinetd/xconv.pl

OPTIONS_DEFINE=	IPV6 LIBWRAP
OPTIONS_DEFAULT=	LIBWRAP

IPV6_CONFIGURE_WITH=	ipv6
LIBWRAP_CONFIGURE_WITH=	libwrap

post-patch:
	@${REINPLACE_CMD} 's|%%PREFIX%%|${PREFIX}|g' ${WRKSRC}/xinetd/xconfig.h

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/xinetd/xinetd ${STAGEDIR}${PREFIX}/sbin/xinetd
	${INSTALL_SCRIPT} ${WRKSRC}/xinetd/xconv.pl ${STAGEDIR}${PREFIX}/bin/xconv
	${INSTALL_MAN} ${WRKSRC}/xinetd/xinetd.conf.man ${STAGEDIR}${PREFIX}/man/man5/xinetd.conf.5
	${INSTALL_MAN} ${WRKSRC}/xinetd/xconv.pl.8 ${STAGEDIR}${PREFIX}/man/man8/xconv.8
	${INSTALL_MAN} ${WRKSRC}/xinetd/xinetd.man ${STAGEDIR}${PREFIX}/man/man8/xinetd.8
	${INSTALL_MAN} ${WRKSRC}/xinetd/xinetd.log.man ${STAGEDIR}${PREFIX}/man/man8/xinetd.log.8

.include <bsd.port.mk>
