# Created by: Eric Turgeon <ericbsd@FreeBSD.org>

PORTNAME=	xcffib
PORTVERSION=	0.9.0
CATEGORIES=	x11 python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Xcffib is a replacement for xpyb, also is a XCB python binding

LICENSE=	apache2
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}cffi>=1.1.0:devel/py-cffi@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}six>0:devel/py-six@${PY_FLAVOR}
LIB_DEPENDS=	libxcb.so:x11/libxcb
RUN_DEPENDS=	${BUILD_DEPENDS}

USES=		python:3.6+
USE_PYTHON=	autoplist distutils

NO_ARCH=	yes

.include <bsd.port.mk>
