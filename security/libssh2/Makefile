PORTNAME=	libssh2
PORTVERSION=	1.9.0
PORTEPOCH=	3
CATEGORIES=	security devel
MASTER_SITES=	https://www.libssh2.org/download/ \
		FREEBSD_LOCAL/sbz

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Library implementing the SSH2 protocol

LICENSE=	bsd3
LICENSE_FILE=	${WRKSRC}/COPYING

GNU_CONFIGURE=	yes
INSTALL_TARGET=	install-strip
USES=		compiler:c11 libtool pathfix
USE_LDCONFIG=	yes

OPTIONS_DEFINE=	GCRYPT TRACE ZLIB
OPTIONS_DEFAULT=	ZLIB

TRACE_DESC=	Enable debug packet traces

TRACE_CONFIGURE_ENABLE=	debug
GCRYPT_LIB_DEPENDS=	libgcrypt.so:security/libgcrypt
GCRYPT_CONFIGURE_ON=	--with-crypto=libgcrypt
GCRYPT_CONFIGURE_OFF=	--with-crypto=openssl
GCRYPT_CPPFLAGS=	-I${LOCALBASE}/include
GCRYPT_LIBS=		-L${LOCALBASE}/lib
GCRYPT_USES_OFF=	ssl
ZLIB_CONFIGURE_WITH=	libz

.include <bsd.port.pre.mk>

post-patch:
	@${REINPLACE_CMD} -e '/Libs:/s/@LIBS@//' \
		${WRKSRC}/libssh2.pc.in
.if ! ${PORT_OPTIONS:MGCRYPT}
.  if ${SSL_DEFAULT} == base
	@${REINPLACE_CMD} -e 's/LIBSREQUIRED="$$LIBSREQUIRED$${LIBSREQUIRED:+ }libssl libcrypto"/LIBS="$$LIBS -lssl -lcrypto"/' \
		${WRKSRC}/configure
.  endif
.endif

.include <bsd.port.post.mk>
