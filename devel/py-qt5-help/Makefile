PORTNAME=	help
PORTREVISION=	4
CATEGORIES=	devel python

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Python bindings for the Qt5 toolkit, QtHelp module

CONFIGURE_ARGS=	--enable QtHelp
PYQT_DIST=	yes

USES=		gl python:3.5+ pyqt:5 qt:5
USE_GL=		gl
USE_PYQT=	sip_build core_run widgets_run
USE_PYTHON=	concurrent flavors py3kplist
USE_QT=		core gui widgets help network sql buildtools_build qmake_build xml

OPTIONS_DEFINE=	API DEBUG
OPTIONS_DEFAULT=API
OPTIONS_SUB=	yes

API_DESC=		Install QtHelp API for QScintilla2
API_CONFIGURE_ON=	--qsci-api --qsci-api-destdir=${PYQT_APIDIR}
API_CONFIGURE_OFF=	--no-qsci-api
API_LIB_DEPENDS=	libqscintilla2_qt5.so:devel/qscintilla2-qt5
DEBUG_CONFIGURE_ON=	--debug --trace

post-install:
	${STRIP_CMD} ${FAKE_DESTDIR}${PYTHONPREFIX_SITELIBDIR}/PyQt5/QtHelp.so

.include <bsd.port.mk>
