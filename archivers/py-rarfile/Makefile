# Created by: Kevin Golding <ports@caomhin.org>

PORTNAME=	rarfile
PORTVERSION=	4.0
CATEGORIES=	archivers python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Python module for RAR archive reading

LICENSE=	iscl
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	unrar:archivers/unrar

NO_ARCH=	yes
USES=		python:3.6+
USE_PYTHON=	autoplist distutils

.include <bsd.port.mk>
