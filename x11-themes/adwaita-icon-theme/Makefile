PORTNAME=	adwaita-icon-theme
DISTVERSION=	40.1.1
CATEGORIES=	x11-themes gnome
MASTER_SITES=	GNOME/sources/${PORTNAME}/${DISTVERSION:R:R}
DIST_SUBDIR=	gnome

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	GNOME Symbolic Icons

LICENSE=	lgpl3 CC-BY-SA-3.0
LICENSE_COMB=	dual

NO_ARCH=	yes
USES=		gettext-tools gmake gnome pathfix pkgconfig tar:xz
USE_GNOME=	intltool gtk-update-icon-cache
GNU_CONFIGURE=	yes
CONFIGURE_ENV=	ac_cv_path_GTK_ENCODE_SYMBOLIC_SVG="false"
INSTALLS_ICONS=	yes

post-install:
	-${RM} -r ${STAGEDIR}${PREFIX}/lib/locale
	-${RM} -r ${STAGEDIR}${PREFIX}/locale

.include <bsd.port.mk>
