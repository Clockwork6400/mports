# Created by: William Grzybowski <wg@FreeBSD.org>

PORTNAME=	patchelf
DISTVERSION=	0.12
CATEGORIES=	sysutils
MASTER_SITES=	https://github.com/NixOS/${PORTNAME}/releases/download/${DISTVERSION}/

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Utility to modify the dynamic linker

LICENSE=	gpl3
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		autoreconf compiler:c++11-lang gmake tar:bz2
WRKSRC=		${WRKDIR}/${PORTNAME}-${DISTVERSION}.20200827.8d3a16e

GNU_CONFIGURE=	yes
NO_TEST=	yes

OPTIONS_DEFINE=	DOCS

CONFIGURE_TARGET=	${ARCH}-portbld-freebsd11.4

.include <bsd.port.mk>
