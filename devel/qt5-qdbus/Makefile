PORTNAME=	qdbus
DISTVERSION=	${QT5_VERSION}
PORTREVISION=	1
CATEGORIES=	devel
PKGNAMEPREFIX=	qt5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Qt command-line interface to D-Bus

USES=		compiler:c++11-lang qmake qt-dist:5,tools
USE_QT=		core dbus xml buildtools_build

BUILD_WRKSRC=	${WRKSRC}/src/${PORTNAME}/${PORTNAME}
INSTALL_WRKSRC=	${BUILD_WRKSRC}

QT_BINARIES=	yes

post-install:
	${RLN} ${STAGEDIR}${QT_BINDIR}/${PORTNAME} ${STAGEDIR}${PREFIX}/bin/${PORTNAME}-qt5

.include <bsd.port.mk>
