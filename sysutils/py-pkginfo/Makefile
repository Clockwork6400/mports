PORTNAME=	pkginfo
DISTVERSION=	1.8.3
CATEGORIES=	sysutils python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Query metadatdata from sdists / bdists / installed packages
WWW=		https://pypi.org/project/pkginfo/

LICENSE=	mit
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

USES=		python:3.6+
USE_PYTHON=	autoplist concurrent distutils

NO_ARCH=	yes
PORTDOCS=	*

OPTIONS_DEFINE=	DOCS
DOCS_BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}sphinx>=0,1:textproc/py-sphinx@${PY_FLAVOR}
DOCS_VARS=		PYDISTUTILS_BUILD_TARGET+="build_sphinx -a -E"

post-install-DOCS-on:
	@${MKDIR} ${FAKE_DESTDIR}${DOCSDIR}
	@(cd ${WRKSRC}/build/sphinx/html && \
		${COPYTREE_SHARE} . ${FAKE_DESTDIR}${DOCSDIR} \
		"! -name .buildinfo -and ! -name objects.inv")

.include <bsd.port.mk>
