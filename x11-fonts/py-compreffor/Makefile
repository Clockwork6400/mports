PORTNAME=	compreffor
PORTVERSION=	0.4.6
CATEGORIES=	x11-fonts python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	CFF subroutinizer for fontTools

LICENSE=	apache2
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		compiler:c++11-lang python:3.7+ zip
USE_PYTHON=	autoplist concurrent distutils

RUN_DEPENDS+=	${PYTHON_PKGNAMEPREFIX}fonttools>=3.1:print/py-fonttools@${PY_FLAVOR}

.include <bsd.port.mk>
