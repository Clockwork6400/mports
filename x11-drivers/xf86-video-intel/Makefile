PORTNAME=	xf86-video-intel
DISTVERSION=	2.99.917-916
DISTVERSIONSUFFIX=	-g${GL_COMMIT:C/(.{12}).*/\1/}
PORTREVISION=	1
PORTEPOCH=	1
CATEGORIES=	x11-drivers

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	X.Org legacy driver for Intel integrated graphics chipsets

LICENSE=	mit	# various
LICENSE_FILE=	${WRKSRC}/COPYING

ONLY_FOR_ARCHS=	amd64 i386
ONLY_FOR_ARCHS_REASON=	Only Intel integrated GPUs on x86 are supported

WRKSRC=		${WRKDIR}/xf86-video-intel-31486f40f8e8f8923ca0799aea84b58799754564

LIB_DEPENDS=	libdrm_intel.so:graphics/libdrm

USES=		cpe libtool localbase xorg xorg-cat:driver
CPE_VENDOR=	x
USE_GITLAB=	yes
GL_COMMIT=	31486f40f8e8f8923ca0799aea84b58799754564
USE_XORG=	pciaccess pixman
CONFIGURE_ENV=	ac_cv_header_sys_sysinfo_h=no # XXX ports/242236
CONFIGURE_ARGS=	--with-builderstring="${DISTVERSIONFULL}"
CFLAGS+=	-Wincompatible-pointer-types -D_WITH_GETLINE
TEST_TARGET=	check

# XXX bug 214593: SNA crashes on pre-SandyBridge hardware
CONFIGURE_ARGS+=--with-default-accel=uxa

OPTIONS_DEFINE=	UDEV XVMC
OPTIONS_DEFAULT=UDEV XVMC
OPTIONS_SUB=	yes

UDEV_DESC=		udev-based monitor hotplug detection
UDEV_LIB_DEPENDS=	libudev.so:devel/libudev-devd
UDEV_CONFIGURE_ENABLE=	udev

XVMC_LIB_DEPENDS=	libxcb-util.so:x11/xcb-util
XVMC_USE=		XORG=x11,xcb,xvmc
XVMC_CONFIGURE_ENABLE=	xvmc
XVMC_VARS=		USE_LDCONFIG=yes

post-patch:
.if ${CONFIGURE_ARGS:M--with-default-accel=uxa}
	@${REINPLACE_CMD} '/^Default/s/SNA/UXA/' ${WRKSRC}/man/intel.man
.endif

.include <bsd.port.mk>
