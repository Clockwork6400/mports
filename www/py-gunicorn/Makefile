# Created by: Kristaps Kulis <kristaps.kulis@gmail.com>

PORTNAME=	gunicorn
PORTVERSION=	19.9.0
PORTREVISION=	1
CATEGORIES=	www python
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	WSGI HTTP Server for UNIX

LICENSE=	mit
LICENSE_FILE=	${WRKSRC}/LICENSE

OPTIONS_DEFINE=		PROCTITLE
OPTIONS_DEFAULT=	PROCTITLE
OPTIONS_GROUP=		WORKERS
OPTIONS_GROUP_WORKERS=	EVENTLET GAIOHTTP TORNADO

EVENTLET_DESC=	Eventlet async worker
GAIOHTTP_DESC=	gaiohttp async worker
PROCTITLE_DESC=	Custom process titles with setproctitle(3)
TORNADO_DESC=	Tornado async worker

EVENTLET_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}eventlet>=0.9.7:net/py-eventlet@${PY_FLAVOR}
GAIOHTTP_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}aiohttp>0:www/py-aiohttp@${PY_FLAVOR}
PROCTITLE_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}setproctitle>0:devel/py-setproctitle@${PY_FLAVOR}
TORNADO_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}tornado>=2.2:www/py-tornado@${PY_FLAVOR}

USES=			python:3.6+
USE_GITHUB=		yes
USE_PYTHON=		autoplist concurrent distutils

GH_ACCOUNT=	benoitc

NO_ARCH=	yes
NO_TEST=	yes

.include <bsd.port.mk>
