PORTNAME=	tomli
PORTVERSION=	2.0.1
PORTREVISION=	1
CATEGORIES=	textproc python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Lil' TOML parser
WWW=		https://github.com/hukkin/tomli

LICENSE=	mit
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		python
USE_PYTHON=	autoplist concurrent distutils pep517

NO_ARCH=	yes

PEP517_BUILD_CMD=	${PYTHON_CMD} -m flit_core.wheel
PEP517_BUILD_DEPEND=	${PYTHON_PKGNAMEPREFIX}flit-core>=3.2.0<4:devel/py-flit-core@${PY_FLAVOR}

post-patch:
	@${SED} -e 's|%%PORTVERSION%%|${PORTVERSION}|' ${FILESDIR}/setup.py > ${WRKSRC}/setup.py

.include <bsd.port.mk>
