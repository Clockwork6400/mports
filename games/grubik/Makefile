

PORTNAME=	grubik
PORTVERSION=	0.1
PORTREVISION=	1
CATEGORIES=	games gnustep
MASTER_SITES=	http://debian.uni-essen.de/misc/GNUstep/Apps/Recreational/
DISTNAME=	GRubik

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Virtual 3D Rubiks cube for GNUstep

LICENSE=	gpl2 # or later

USES=		tar:tgz gnustep
USE_GNUSTEP=	back build

post-patch:
	${RM} -rf ${WRKSRC}/GRubik.app/ix86

post-install:
	${STRIP_CMD} ${PREFIX}/GNUstep/System/Applications/GRubik.app/GRubik

.include <bsd.port.mk>
