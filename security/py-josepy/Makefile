PORTNAME=	josepy
PORTVERSION=	1.9.0
CATEGORIES=	security python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	JOSE protocol implementation in Python
WWW=		https://josepy.readthedocs.io/en/latest/

LICENSE=	apache2
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}cryptography>=0.8:security/py-cryptography@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}openssl>=0.13:security/py-openssl@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}six>=1.9.0:devel/py-six@${PY_FLAVOR}

USES=		python:3.6+
USE_PYTHON=	autoplist concurrent distutils

NO_ARCH=	yes
# not magus compatible.
NO_TEST=	yes

.include <bsd.port.mk>
