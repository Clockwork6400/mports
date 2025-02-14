# Created by: Sunpoet Po-Chuan Hsieh <sunpoet@FreeBSD.org>

PORTNAME=	libquvi
PORTVERSION=	0.4.1
PORTREVISION=	1
CATEGORIES=	multimedia devel
MASTER_SITES=	SF/quvi/${PORTVERSION:R}/${PORTNAME}/

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Cross-platform library for parsing flash media stream URLs

LICENSE=	lgpl2.1 lgpl3
LICENSE_COMB=	dual

BUILD_DEPENDS=	libquvi-scripts>=0.4.0:multimedia/libquvi-scripts
LIB_DEPENDS=	libcurl.so:ftp/curl
RUN_DEPENDS:=	${BUILD_DEPENDS}

OPTIONS_DEFINE=	DOCS LUAJIT
LUAJIT_DESC=	Use LuaJIT instead of Lua

CPPFLAGS+=	-I${LOCALBASE}/include
GNU_CONFIGURE=	yes
INSTALL_TARGET=	install-strip
USES=		iconv libtool pathfix pkgconfig tar:xz
USE_LDCONFIG=	yes

PORTDOCS=	*

LUAJIT_LIB_DEPENDS=	libluajit-5.1.so:lang/luajit
LUAJIT_USES_OFF=	lua

.include <bsd.mport.options.mk>

post-patch:
.if ! ${PORT_OPTIONS:MLUAJIT}
	${REINPLACE_CMD} 's|lua-5.1|lua-${LUA_VER}|g' ${WRKSRC}/configure
.else
	${REINPLACE_CMD} 's|lua >= 5.1|luajit|g' ${WRKSRC}/configure
.endif

post-install:
	${MKDIR} ${DOCSDIR}/
	cd ${WRKSRC}/doc/nd/ && ${COPYTREE_SHARE} . ${DOCSDIR}/

.include <bsd.port.mk>
