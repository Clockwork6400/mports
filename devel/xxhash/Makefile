PORTNAME=	xxhash
PORTVERSION=	0.8.1
DISTVERSIONPREFIX=	v
CATEGORIES=	devel

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Extremely fast non-cryptographic hash algorithm
WWW=		https://cyan4973.github.io/xxHash/

LICENSE=	bsd2
LICENSE_FILE=	${WRKSRC}/LICENSE

FAKE_OPTS=	trueprefix

USES=		gmake

USE_LDCONFIG=	yes

PLIST_SUB=	PORTVERSION=${PORTVERSION}

USE_GITHUB=	yes
GH_ACCOUNT=	Cyan4973
GH_PROJECT=	xxHash

.include <bsd.port.mk>
