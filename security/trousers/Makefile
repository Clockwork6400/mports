PORTNAME=	trousers
PORTVERSION=	0.3.14
PORTREVISION=	3
CATEGORIES=	security
MASTER_SITES=	SF

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Open-source TCG Software Stack

LICENSE=	bsd3

BUILD_DEPENDS=	tpm-emulator>=0.7.4_1:emulators/tpm-emulator
RUN_DEPENDS:=	${BUILD_DEPENDS}

USES=		cpe dos2unix autoreconf gmake iconv libtool pkgconfig ssl
CPE_VENDOR=	${PORTNAME}_project
NO_WRKSUBDIR=	yes
DOS2UNIX_GLOB=	*.h *.c
USE_LDCONFIG=	YES
USE_RC_SUBR=	tcsd
INSTALL_TARGET=	install-strip
GNU_CONFIGURE=	YES
CONFIGURE_ARGS=	--with-gui=none --enable-static \
		--localstatedir=${PREFIX}/var \
		--with-tssuser=${USERS} \
		--with-tssgroup=${GROUPS} \
		--with-openssl=${OPENSSLBASE} \
		RANLIB=:
MAKE_ENV=	ICONV_LIB=${ICONV_LIB} \
		ICONV_PREFIX=${ICONV_PREFIX}
CFLAGS+=	-I${OPENSSLINC}
LDFLAGS+=	-L${OPENSSLLIB}
SUB_FILES=	pkg-message
SUB_LIST=	USERS="${USERS}" GROUPS="${GROUPS}"
PLIST_SUB=	USERS="${USERS}" GROUPS="${GROUPS}"
USERS=		_tss
GROUPS=		_tss

OPTIONS_DEFINE=	DEBUG
DEBUG_CONFIGURE_ENABLE=	debug

pre-patch: dos2unix

post-install:
	${INSTALL_DATA} \
	    ${WRKSRC}/dist/tcsd.conf ${STAGEDIR}${PREFIX}/etc/tcsd.conf.sample
	${MKDIR} ${STAGEDIR}${PREFIX}/var/lib/tpm

.include <bsd.port.mk>
