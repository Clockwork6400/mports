PORTNAME=	kyua
PORTVERSION=	0.13
PORTEPOCH=	3
CATEGORIES=	devel
MASTER_SITES=	https://github.com/jmmv/kyua/releases/download/${PORTNAME}-${PORTVERSION}/ \
		FREEBSD_LOCAL/jmmv

MAINTAINER=	jmmv@FreeBSD.org
COMMENT=	Testing framework for infrastructure software

LICENSE=	bsd3

LIB_DEPENDS=	liblutok.so:devel/lutok

CONFLICTS=	kyua-atf-compat-[0-9]* kyua-cli-[0-9]* kyua-testers-[0-9]*

GNU_CONFIGURE=	yes
USES=		lua pkgconfig

TESTS_USER=	tests
USERS=		${TESTS_USER}
GROUPS=		tests
SUB_FILES=	kyua.conf
SUB_LIST=	TESTS_USER=${TESTS_USER}

OPTIONS_DEFINE=	DOCS EXAMPLES TEST
OPTIONS_DEFAULT=TEST

OPTIONS_SUB=		yes
TEST_CONFIGURE_WITH=	atf
TEST_BUILD_DEPENDS=	atf>=0.21:devel/atf
TEST_RUN_DEPENDS=	atf>=0.21:devel/atf

.include <bsd.mport.options.mk>

CONFIGURE_ARGS+=	--without-doxygen
CONFIGURE_ARGS+=	--docdir=${DOCSDIR}
MAKE_FLAGS+=	examplesdir=${FAKE_DESTDIR}${EXAMPLESDIR}
MAKE_FLAGS+=	pkgdatadir=${DATADIR}

.if ! ${PORT_OPTIONS:MDOCS}
MAKE_FLAGS+=	doc_DATA=
.endif
.if ! ${PORT_OPTIONS:MEXAMPLES}
MAKE_FLAGS+=	dist_examples_DATA=
.endif

post-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/etc/kyua/
	${INSTALL_DATA} ${WRKDIR}/kyua.conf ${STAGEDIR}${PREFIX}/etc/kyua/kyua.conf.sample
	${INSTALL_DATA} ${WRKSRC}/examples/Kyuafile.top \
		${STAGEDIR}${PREFIX}/tests/Kyuafile
	${MKDIR} ${PREFIX}/share/examples/kyua
	${INSTALL_DATA} ${WRKSRC}/examples/Kyuafile.top ${PREFIX}/share/examples/kyua/
	${INSTALL_DATA} ${WRKDIR}/kyua.conf ${PREFIX}/share/examples/kyua/kyua.conf

.include <bsd.port.mk>
