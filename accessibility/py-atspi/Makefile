PORTNAME=	atspi
PORTVERSION=	2.38.2
PORTREVISION=	0
CATEGORIES=	accessibility x11-toolkits python
MASTER_SITES=	GNOME/sources/pyatspi/${PORTVERSION:C/^([0-9]+\.[0-9]+).*/\1/}
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTNAME=	pyatspi-${PORTVERSION}
DIST_SUBDIR=	gnome

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Python API for the D-BUS based SPI framework
WWW=		https://gitlab.gnome.org/GNOME/pyatspi2

LICENSE=	lgpl

RUN_DEPENDS=	${LOCALBASE}/libexec/at-spi2-registryd:accessibility/at-spi2-core

CONFLICTS=	at-spi-1.[0-9]*
PORTSCOUT=	limitw:1,even

USES=		gettext gmake gnome localbase pathfix pkgconfig python:3.6+ tar:xz
USE_PYTHON=	flavors py3kplist
USE_GNOME=	intlhack pygobject3
GNU_CONFIGURE=	yes

.include <bsd.port.mk>
