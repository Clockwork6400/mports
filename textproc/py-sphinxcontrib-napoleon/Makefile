PORTNAME=	sphinxcontrib-napoleon
DISTVERSION=	0.7
CATEGORIES=	textproc
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Sphinx extension that parses both NumPy and Google style docstrings
WWW=		https://pypi.org/project/sphinxcontrib-napoleon/

LICENSE=	bsd2
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}six>=1.5.2:devel/py-six@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pockets>=0.3:devel/py-pockets@${PY_FLAVOR}

USES=		python:3.6+
USE_PYTHON=	autoplist distutils

NO_ARCH=	yes

.include <bsd.port.mk>
