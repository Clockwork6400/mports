PORTNAME=	dmake
PORTVERSION=	4.13.1
DISTVERSIONPREFIX=	v
PORTEPOCH=	1
CATEGORIES=	devel

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Another hyper make utility
WWW=		https://www.openoffice.org/tools/dmake/

LICENSE=	gpl
LICENSE_FILE=	${WRKSRC}/readme/license.txt

USES=		autoreconf

USE_GITHUB=	yes
GH_ACCOUNT=	jimjag

GNU_CONFIGURE=	yes
CONFIGURE_ARGS+=	--datarootdir=${DATADIR}

CONFLICTS_INSTALL=	sunpromake

post-install:
	${INSTALL_MAN} ${WRKSRC}/man/dmake.tf ${PREFIX}/man/man1/dmake.1

.include <bsd.port.mk>
