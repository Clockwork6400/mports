PORTNAME=	bsdisks
DISTVERSION=	0.23
CATEGORIES=	sysutils

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	UDisks2 service implementation for BSD

LICENSE=	bsd3

USES=		cmake compiler:c++11-lang qt:5

USE_QT=		qmake_build buildtools_build core dbus

USE_GITLAB=	yes
GL_SITE=	https://foss.heptapod.net
GL_ACCOUNT=	bsdutils
GL_COMMIT=	1ac33a13d21b136dba7106baf3cd2be2434bf6f8

WRKSRC=		${WRKDIR}/bsdisks-1ac33a13d21b136dba7106baf3cd2be2434bf6f8-1ac33a13d21b136dba7106baf3cd2be2434bf6f8

.include <bsd.port.mk>
