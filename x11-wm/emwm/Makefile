# Created by: Kazuo Kuroi <kazuok@projectkitsune.com>

PORTNAME=		emwm
DISTVERSION=		1.0a
CATEGORIES=		x11-wm
MASTER_SITES=	http://fastestcode.org/dl/
DISTNAME=		emwm-src-1.0a

MAINTAINER=		kazuok@projectkitsune.com
COMMENT=		Enhanced Motif WM fork with multi-monitor and utf-8 support

LICENSE=		lgpl2.1

USES=			motif pkgconfig tar:xz xorg
USE_XORG=	x11 xt xext xinerama xpm xrandr xscrnsaver

post-patch:
	${LN} -sf ${WRKSRC}/mf/Makefile.FreeBSD ${WRKSRC}/mf/Makefile.MidnightBSD

.include <bsd.port.mk>
