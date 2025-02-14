

PORTNAME=	xlockmore
PORTVERSION=	5.43
CATEGORIES?=	x11
MASTER_SITES=	http://www.tux.org/~bagleyd/xlock/${PORTNAME}-${PORTVERSION}/ \
		ftp://ibiblio.org/pub/Linux/X11/screensavers/ \
		CRITICAL

MAINTAINER?=	ports@MidnightBSD.org
COMMENT=	Like XLock session locker/screen saver, but just more

LICENSE=	mit

FAKE_OPTS=	prefixhack

USES=		tar:bzip2
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--without-motif --without-ttf --without-editres \
		--without-dtsaver --without-rplay --without-nas \
		--without-gtk --without-esound

USE_GNOME=	#
USE_XORG=	x11 xaw ice

LIB_DEPENDS+=	libfreetype.so:${PORTSDIR}/print/freetype2

PLIST_FILES=	bin/xlock lib/X11/app-defaults/XLock man/man1/xlock.1.gz

OPTIONS_DEFINE=	MESAGL MB SYSLOG DISABLE_ALLOW_ROOT NICE_ONLY BLANK_ONLY \
		KERBEROS4 BAD_PAM GTK2 TIME_BOMB CUSTOMIZATION MAGICK

MESAGL_DESC=	Mesa 3D (for GL modes)
MB_DESC=	Xmb function series
SYSLOG_DESC=	Syslog logging
DISABLE_ALLOW_ROOT_DESC=	Allows users to turn off allowroot
NICE_ONLY_DESC=	Only low cpu modes
BLANK_ONLY_DESC=	Blank mode only (boring)
BAD_PAM_DESC=	Xlock will ask PAM with root rights
GTK2_DESC=	Build Gtk2 graphical shell
XLOCK_GROUP_DESC=	Allow xlock group to logout
TIME_BOMB_DESC=	Allow autologout
CUSTOMIZATION_DESC=	Allow tune through resource file

OPTIONS_RADIO=	ONE
OPTIONS_RADIO_ONE=	PAM XLOCK_GROUP

NO_OPTIONS_SORT=yes

FAKE_MAKEARGS+=	xapploaddir=${FAKE_DESTDIR}${LOCALBASE}/lib/X11/app-defaults \
		mandir=${FAKE_DESTDIR}${MANPREFIX}/man/man1

.include <bsd.mport.options.mk>

.if ${PORT_OPTIONS:MKERBEROS4}
CONFIGURE_ARGS+=--enable-kerberos4
KRB4LIB=	-lcom_err -lcrypto
.endif
.if defined(KRB5_HOME) && exists(${KRB5_HOME})
CONFIGURE_ARGS+=--enable-kerberos5
CFLAGS+=	-I${KRB5_HOME}/include
KRB5LIB=	-L${KRB5_HOME}/lib
.endif

.if ${PORT_OPTIONS:MMESAGL}
CONFIGURE_ARGS+=	--with-mesa
MESALIB=${PTHREAD_LIBS}
USE_GL=	yes
CFLAGS+=	-I${LOCALBASE}/include/FTGL
.else
CONFIGURE_ARGS+=	--without-mesa --without-opengl
.endif

.if ${PORT_OPTIONS:MNICE_ONLY}
CONFIGURE_ARGS+=	--enable-nice-only
.endif

.if ${PORT_OPTIONS:MBAD_PAM}
CONFIGURE_ARGS+=	--enable-bad-pam
.endif

.if ${PORT_OPTIONS:MPAM}
CONFIGURE_ARGS+=	--enable-pam
.endif

.if ${PORT_OPTIONS:MNICE_ONLY}
CONFIGURE_ARGS+=	--enable-nice-only
.endif

.if ${PORT_OPTIONS:MBLANK_ONLY}
CONFIGURE_ARGS+=	--enable-blank-only
.endif

.if ${PORT_OPTIONS:MMB}
CONFIGURE_ARGS+=	--enable-use-mb
.endif

.if ${PORT_OPTIONS:MXLOCKMORE_LANG}
CONFIGURE_ARGS+=	--with-lang=${XLOCKMORE_LANG}
.endif

.if ${PORT_OPTIONS:MSYSLOG}
CONFIGURE_ARGS+=	--enable-syslog
.endif

.if ${PORT_OPTIONS:MGTK2}
CONFIGURE_ARGS+=	--with-gtk2
USE_GNOME+=	gtk20
PLIST_FILES+=	bin/xglock share/xlock/xglockrc
PLIST_DIRS+=	share/xlock
.else
CONFIGURE_ARGS+=	--without-gtk2
.endif

.if ${PORT_OPTIONS:MXLOCK_GROUP}
CONFIGURE_ARGS+=	--enable-xlock-group
.endif

.if ${PORT_OPTIONS:MTIME_BOMB}
CONFIGURE_ARGS+=	--enable-bomb
.else
CONFIGURE_ARGS+=	--disable-bomb
.endif

.if ${PORT_OPTIONS:MCUSTOMIZATION}
CONFIGURE_ARGS+=	--enable-customization
.endif

.if ${PORT_OPTIONS:MMAGICK}
LIB_DEPENDS+=	libMagickCore-6.so:graphics/ImageMagick6
.else
CONFIGURE_ARGS+=	--without-magick
.endif

CONFIGURE_ENV+=		XLOCKLIBS="${KRB5LIB} ${KRB4LIB} ${MESALIB}"

.if ${PORT_OPTIONS:MDISABLE_ALLOW_ROOT}
CONFIGURE_ARGS+=	--disable-allow-root
.endif

.if ${PORT_OPTIONS:MPAM} && empty(PORT_OPTIONS:MBAD_PAM)
pre-extract:
	@${ECHO}
	@${ECHO} "You have enabled PAM support. If you want to authenticate against"
	@${ECHO} "root only accessible PAM modules then define WITH_BAD_PAM=yes also."
	@${ECHO} "For example, pam_unix requires root rights to access shadow passwords."
	@${ECHO}
.endif

post-patch:
	@${REINPLACE_CMD} -e '/xglockrc/ s|PROGRAM|DATA|' ${WRKSRC}/xglock/Makefile.in

post-configure:
	${REINPLACE_CMD} -e 's/-lXdpms//g' ${WRKSRC}/modes/Makefile

post-install:
	-${CP} ${PREFIX}/man/xlock.1 ${PREFIX}/man/man1/

.include <bsd.port.mk>
