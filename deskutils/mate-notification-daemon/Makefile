# Created by: Andreas Kohn <andreas@syndrom23.de>

PORTNAME=	mate-notification-daemon
PORTVERSION=	1.26.0
PORTREVISION=	1
CATEGORIES=	deskutils mate
MASTER_SITES=	MATE
DIST_SUBDIR=	mate

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Send small notifications to your desktop

LICENSE=	gpl2 gpl3
LICENSE_COMB=	multi

LIB_DEPENDS=	libcanberra-gtk3.so:audio/libcanberra-gtk3 \
		libcanberra.so:audio/libcanberra \
		libdbus-1.so:devel/dbus \
		libdbus-glib-1.so:devel/dbus-glib \
		libmate-desktop-2.so:x11/mate-desktop \
		libmate-panel-applet-4.so:x11/mate-panel \
		libnotify.so:devel/libnotify

PORTSCOUT=	limitw:1,even

USES=		gettext gmake gnome libtool localbase pathfix pkgconfig tar:xz \
		xorg
USE_XORG=	x11
USE_GNOME=	cairo glib20 gtk30 intlhack librsvg2 libwnck3
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--with-dbus-services=${PREFIX}/share/dbus-1/services \
		--disable-static
INSTALLS_ICONS=	yes
INSTALL_TARGET=	install-strip

GLIB_SCHEMAS=	org.mate.NotificationDaemon.gschema.xml

.include <bsd.port.mk>
