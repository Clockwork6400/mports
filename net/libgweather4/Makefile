PORTNAME=	libgweather
PORTVERSION=	4.0.0
CATEGORIES=	net gnome
MASTER_SITES=	GNOME
MASTER_SITE_SUBDIR=	sources/${PORTNAME}/${PORTVERSION:R}
DIST_SUBDIR=	gnome
PKGNAMESUFFIX=	4

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Library to access online weather information

LICENSE=	gpl2
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	gi-docgen:textproc/py-gi-docgen \
		vala:lang/vala
LIB_DEPENDS=	libgeocode-glib.so:net/geocode-glib \
		libsoup-2.4.so:devel/libsoup

PORTSCOUT=	limitw:1,even

USES=		gettext gnome localbase meson pkgconfig python:3.6+,build \
		shebangfix tar:xz
USE_GNOME=	gtk30 libxml2 pygobject3 introspection:build
USE_LDCONFIG=	yes

GLIB_SCHEMAS=	org.gnome.GWeather4.enums.xml \
		org.gnome.GWeather4.gschema.xml

BINARY_ALIAS=	python3=${PYTHON_VERSION}

NO_TEST=	yes

.include <bsd.port.mk>
