

PORTNAME=	gnustep-app
PORTVERSION=	2.0.0
PORTREVISION=	0
CATEGORIES=	x11 gnustep
MASTER_SITES=   # empty
DISTFILES=      # empty
EXTRACT_ONLY=   # empty

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Metaport for GNUstep applications

LICENSE=	agg

USES=		gnustep
USE_GNUSTEP=	back base gui

NO_BUILD=       yes
APP_DIR=	${LOCALBASE}/GNUstep/System/Applications
RUN_DEPENDS=	aclock>0:x11-clocks/aclock \
		addresses>0:mail/addresses \
		addresses-goodies>0:mail/addresses-goodies \
		${APP_DIR}/Affiche.app/Affiche:deskutils/affiche \
		appwrapper>0:deskutils/appwrapper \
		batmon>0:sysutils/batmon \
		camera>0:graphics/camera \
		camerakit>0:graphics/camerakit \
		cartotheque>0:deskutils/cartotheque \
		cddb-bundle>0:audio/cddb-bundle \
		gnustep-cdplayer>0:audio/gnustep-cdplayer \
		cenon>0:graphics/cenon \
		displaycalibrator>0:deskutils/displaycalibrator \
		duncan>0:textproc/duncan \
		easydiff>0:textproc/easydiff \
		edenmath>0:math/edenmath \
		expense>0:finance/expense \
		fortunate>0:games/fortunate \
		fortytwo-bdb>0:databases/fortytwo-bdb \
		fortytwo-encore>0:devel/fortytwo-encore \
		fortytwo>0:graphics/fortytwo \
		freetar>0:archivers/freetar \
		gmastermind>0:games/gmastermind \
		gmines>0:games/gmines \
		gnumail>0:mail/gnumail \
		gnustep-ftp>0:ftp/gnustep-ftp \
		gnustep-ladder>0:games/gnustep-ladder \
		gnustep-slideshowkit>0:graphics/gnustep-slideshowkit \
		gnustep-slideshow>0:graphics/gnustep-slideshow \
		gnustep-sudoku>0:games/gnustep-sudoku \
		gnustep-wrapper>0:deskutils/gnustep-wrapper \
		gorm>0:devel/gorm \
		grubik>0:games/grubik \
		gscheme>0:lang/gscheme \
		gshisen>0:games/gshisen \
		gskrab>0:x11/gskrab \
		gspdf>0:print/gspdf \
		gtamsanalyzer>0:science/gtamsanalyzer \
		gworkspace-gwmetadata>0:deskutils/gworkspace-gwmetadata \
		gworkspace>0:deskutils/gworkspace \
		helpviewer>0:deskutils/helpviewer \
		highlighterkit>0:devel/highlighterkit \
		imageviewer>0:graphics/imageviewer \
		innerspace>0:x11/innerspace \
		jigsaw>0:games/jigsaw \
		lapispuzzle>0:games/lapispuzzle \
		laternamagica>0:graphics/laternamagica \
		latex-service>0:textproc/latex-service \
		localize>0:textproc/localize \
		lusernet>0:news/lusernet \
		mpdcon>0:audio/mpdcon \
		nextgo>0:games/nextgo \
		gnustep-notebook>0:deskutils/gnustep-notebook \
		paje>0:science/paje \
		pantomime>0:mail/pantomime \
		pixen>0:graphics/pixen \
		plopfolio>0:deskutils/plopfolio \
		poe>0:multimedia/poe \
		popup>0:textproc/popup \
		gnustep-preview>0:graphics/preview \
		price>0:graphics/price \
		remotedesk>0:net/remotedesk \
		simpleagenda>0:deskutils/simpleagenda \
		systempreferences>0:deskutils/systempreferences \
		terminal.app>0:x11/terminal.app \
		timemon>0:sysutils/timemon \
		toolboxkit>0:deskutils/toolboxkit \
		waiho>0:ftp/waiho \
		wizardkit>0:devel/wizardkit \
		zillion>0:net/zillion \
		zipper>0:archivers/zipper

do-install:
	-mkdir ${PREFIX}/share/gnustep-app
	-touch ${PREFIX}/share/gnustep-app/.installed

.include <bsd.port.mk>
