PORTNAME=	llfuse
PORTVERSION=	1.3.8
CATEGORIES=	devel python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Python bindings for low-level FUSE API

LICENSE=	lgpl

py27_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}contextlib2>0:devel/py-contextlib2@${PY_FLAVOR}

USES=		compiler:c++11-lang fuse pkgconfig python:3.6+
USE_PYTHON=	distutils autoplist

post-install:
	${STRIP_CMD} ${FAKE_DESTDIR}${PYTHONPREFIX_SITELIBDIR}/llfuse*.so

.include <bsd.port.mk>
