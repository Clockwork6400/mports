PORTNAME=	lumina-fileinfo
DISTVERSIONPREFIX=	v
DISTVERSION=	1.6.2
PORTREVISION=	1
CATEGORIES=	deskutils

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	File properties utility from the Lumina Desktop

LICENSE=	bsd3
LICENSE_FILE=	${WRKSRC}/../../../LICENSE

USES=		compiler:c++11-lang gl qmake qt:5
USE_QT=		buildtools_build concurrent core gui \
		multimedia network svg widgets x11extras
USE_GL=		gl
USE_GITHUB=	yes
GH_ACCOUNT=	lumina-desktop
GH_PROJECT=	lumina

OPTIONS_DEFINE=	NLS
OPTIONS_SUB=	yes

NLS_QMAKE_ON=	CONFIG+=WITH_I18N
NLS_USE=	QT=linguist_build

CONFLICTS_INSTALL=	lumina-1.2.*

WRKSRC_SUBDIR=	src-qt5/desktop-utils/${PORTNAME}

.include <bsd.port.mk>
