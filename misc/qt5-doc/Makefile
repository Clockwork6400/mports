PORTNAME=	doc
QT5_VERSION=	5.12.2
DISTVERSION=	${QT5_VERSION}
CATEGORIES=	misc
MASTER_SITES=	QT/online/qtsdkrepository/linux_x64/desktop/qt5_${QT5_VERSION:S/.//g}_src_doc_examples/qt.qt5.${QT5_VERSION:S/.//g}.doc/
PKGNAMEPREFIX=	qt5-
DISTNAME=	${QT5_VERSION}-0-201903121945qt-everywhere-documentation
DIST_SUBDIR=	KDE/Qt/${QT5_VERSION}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Qt 5 documentation

WRKSRC=		${WRKDIR}/Docs/Qt-${QT5_VERSION}

USES=		7z qt:5
USE_QT=		# we just need access to QT5_VERSION and other variables.

DESCR=		${.CURDIR:H:H}/devel/qt5/pkg-descr
NO_ARCH=	yes
NO_BUILD=	yes

post-extract:
	${RM} ${WRKSRC}/Makefile
	${RM} -r ${WRKSRC}/global

do-install:
	${MKDIR} ${STAGEDIR}${QT_DOCDIR}
	cd ${WRKSRC} && \
		${COPYTREE_SHARE} \* ${STAGEDIR}${QT_DOCDIR}

.include <bsd.port.mk>
