PORTNAME=	libaudiofile
PORTVERSION=	0.3.6
PORTREVISION=	4
CATEGORIES=	audio
MASTER_SITES=	GNOME/sources/${PORTNAME:S/lib//}/${PORTVERSION:C/^([0-9]+\.[0-9]+).*/\1/}
DISTNAME=	audiofile-${PORTVERSION}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Sound library for SGI audio file

LICENSE=	lgpl2.1

LIB_DEPENDS=	libFLAC.so:audio/flac

CONFLICTS=	osalp-0.7.*

USES=		pathfix pkgconfig tar:xz libtool
USE_LDCONFIG=	yes
GNU_CONFIGURE=	yes

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/libaudiofile.so.1

.include <bsd.port.mk>
