

PORTNAME=	eggdbus
PORTVERSION=	0.6
PORTREVISION=	2
CATEGORIES=	devel
MASTER_SITES=	http://hal.freedesktop.org/releases/

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	D-Bus bindings for GObject
LICENSE=	lgpl

LIB_DEPENDS=	libdbus-glib-1.so:${PORTSDIR}/devel/dbus-glib

USE_GNOME=	glib20
USES=		gettext gmake libtool:keepla pathfix pkgconfig
MAKE_JOBS_UNSAFE=yes
GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes
INSTALL_TARGET=	install-strip
CONFIGURE_ARGS=	--localstatedir=/var
CPPFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib

BUILD_DEPENDS+=	docbook-sgml>0:${PORTSDIR}/textproc/docbook-sgml \
    		xsltproc:${PORTSDIR}/textproc/libxslt \
		${LOCALBASE}/share/xsl/docbook/manpages/docbook.xsl:${PORTSDIR}/textproc/docbook-xsl

post-patch:
	@${REINPLACE_CMD} -e 's|-Wl,--as-needed||' \
	    	${WRKSRC}/configure

.include <bsd.port.mk>
