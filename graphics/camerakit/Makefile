

PORTNAME=	camerakit
PORTVERSION=	0.0.1
PORTREVISION=	1
CATEGORIES=	graphics gnustep
MASTER_SITES=	http://download.gna.org/gsimageapps/
DISTNAME=	CameraKit-20041011

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Framework that allows to access digital cameras

LICENSE=	unknown

LIB_DEPENDS=	libgphoto2.so:${PORTSDIR}/graphics/libgphoto2

USES=		tar:bzip2 gnustep
USE_GNUSTEP=	build back
USE_LDCONFIG=	${GNUSTEP_SYSTEM_LIBRARIES}

WRKSRC=		${WRKDIR}/CameraKit

post-install:
	${STRIP_CMD} ${PREFIX}/GNUstep/System/Library/Frameworks/CameraKit.framework/Versions/0/libCameraKit.so

.include <bsd.port.mk>
