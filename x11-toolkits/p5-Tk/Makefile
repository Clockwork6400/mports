# Created by: James FitzGibbon <jfitz@FreeBSD.org>

PORTNAME=	Tk
PORTVERSION=	804.035
CATEGORIES=	x11-toolkits tk perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Re-port of a perl5 interface to Tk8.4

LICENSE=	artistic

LIB_DEPENDS=	libpng.so:graphics/png \
		libfreetype.so:print/freetype2 \
		libfontconfig.so:x11-fonts/fontconfig

OPTIONS_DEFINE=	XFT
OPTIONS_DEFAULT=	XFT
XFT_DESC=	Client-side fonts via libXft

CONFIGURE_ARGS=	X11INC=${LOCALBASE}/include X11LIB=${LOCALBASE}/lib
MAKE_JOBS_UNSAFE=	yes
USES=		jpeg perl5 shebangfix xorg
SHEBANG_FILES=	pTk/Tcl-pTk \
		pTk/mkVFunc
USE_PERL5=	configure
USE_XORG=	x11

.include <bsd.mport.options.mk>

.if ${PORT_OPTIONS:MXFT}
CONFIGURE_ARGS=	XFT=1
USE_XORG+=	xft
.else
CONFIGURE_ARGS=	XFT=0
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|%%LOCALBASE%%|${LOCALBASE}|g' \
		${WRKSRC}/JPEG/Makefile.PL \
		${WRKSRC}/PNG/Makefile.PL \
		${WRKSRC}/pTk/Makefile.PL

post-configure:
	@${REINPLACE_CMD} \
		-e '/^CC = / s|.*|CC = ${CC}|' \
		-e '/^CCFLAGS = / s|.*|CCFLAGS = ${CFLAGS}|' \
		-e '/^LD = / s|.*|LD = ${CC} ${CFLAGS} ${LDFLAGS}|' \
		-e '/^FULL_AR = / s|.*|FULL_AR = ${AR}|' \
		`${FIND} ${WRKSRC} -name Makefile`

post-install:
	@${RM} ${STAGEDIR}${PREFIX}/${SITE_ARCH_REL}/auto/Tk/pTk/extralibs.ld
	@${RMDIR} ${STAGEDIR}${PREFIX}/${SITE_ARCH_REL}/auto/Tk/pTk
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/${SITE_ARCH_REL}/auto/Tk/Tk.so
.for i in Canvas Compound Entry Event HList IO InputO JPEG Listbox Menubutton Mwm NBFrame PNG Pixmap Scale Scrollbar TList Text TixGrid WinPhoto X Xlib
		${STRIP_CMD} \
		    ${STAGEDIR}${PREFIX}/${SITE_ARCH_REL}/auto/Tk/${i}/${i}.so
.endfor

.include <bsd.port.mk>
