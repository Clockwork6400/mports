

PORTNAME=	libijs
PORTVERSION=	0.35
PORTREVISION=	4
CATEGORIES=	print
MASTER_SITES=	http://www.openprinting.org/download/ijs/download/
DISTNAME=	ijs-${PORTVERSION}
DIST_SUBDIR=	ghostscript

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	C library that supports plugin printer driver for Ghostscript

LICENSE=	mit

USES=		gmake libtool pkgconfig tar:bzip2
USE_LDCONFIG=	yes

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--enable-shared
INSTALL_TARGET=	install-strip

.include <bsd.port.mk>
