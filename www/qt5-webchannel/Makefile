PORTNAME=	webchannel
DISTVERSION=	${QT5_VERSION}
CATEGORIES=	www
PKGNAMEPREFIX=	qt5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Qt 5 library for integration of C++/QML with HTML/js clients

LICENSE=	lgpl2.1

USES=		compiler:c++11-lang qmake:norecursive qt-dist:5,webchannel
USE_QT=		core declarative \
		buildtools_build declarative-test_build testlib_build

# The default EXTRACT_AFTER_ARGS value excludes examples/ from the extracted
# tarball, which we need during the build.
EXTRACT_AFTER_ARGS=	--no-same-owner --no-same-permissions

post-install:
	${REINPLACE_CMD} 's|/../../../../|/../../../|g' \
		${PREFIX}/lib/cmake/Qt5*/Qt5*Config.cmake

.include <bsd.port.mk>
