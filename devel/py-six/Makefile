PORTNAME=	six
PORTVERSION=	1.15.0
CATEGORIES=	devel python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Python 2 and 3 compatibility utilities

LICENSE=	mit
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		python:2.7+
USE_PYTHON=	autoplist concurrent distutils

NO_ARCH=	yes
# circular dependency
NO_TEST=	yes

.include <bsd.port.mk>
