PORTNAME=	xorgproto
PORTVERSION=	2021.5
CATEGORIES=	x11

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	xorg protocol headers

LICENSE=	mit

USES=		xorg-cat:proto

CONFIGURE_ARGS= --without-fop \
		--without-xmlto \
		--without-xsltproc \
		--disable-specs

OPTIONS_DEFINE=	DOCS

pre-patch:
	@${MKDIR} ${WRKSRC}/man

.include <bsd.port.mk>
