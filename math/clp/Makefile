PORTNAME=	Clp
DISTVERSION=	1.17.6
CATEGORIES=	math
MASTER_SITES=	https://www.coin-or.org/download/source/${PORTNAME}/
PKGNAMEPREFIX=	coin-or-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Linear Programming Solver
WWW=		https://www.coin-or.org/Clp/index.html

LICENSE=	epl

BUILD_DEPENDS=	coin-or-Data-Sample>0:math/coin-or-data-sample \
		coin-or-Data-Netlib>0:math/coin-or-data-netlib
LIB_DEPENDS=	libcoinasl.so:math/asl \
		libcoinmetis.so:math/coin-or-metis \
		libcoinmumps.so:math/coin-or-mumps \
		libCoinUtils.so:math/coinutils \
		libOsi.so:math/osi
RUN_DEPENDS=	coin-or-Data-Sample>0:math/coin-or-data-sample \
		coin-or-Data-Netlib>0:math/coin-or-data-netlib

USES=		blaslapack compiler:c++11-lang fortran libtool pathfix pkgconfig tar:tgz
GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes

INSTALL_TARGET=	install-strip

CONFIGURE_ARGS=	--with-lapack-lib="${LAPACKLIB} -L${LOCALBASE}/lib" \
		--with-blas-lib="${BLASLIB} -L${LOCALBASE}/lib" \
		--with-osi-incdir="${LOCALBASE}/include/coin" --with-osi-lib="${LOCALBASE}/lib/libOsi.so" \
		--with-coinutils-incdir="${LOCALBASE}/include/coin" --with-coinutils-lib="${LOCALBASE}/lib/libCoinUtils.so" \
		--with-netlib-datadir="${LOCALBASE}/share/coin/Data/Netlib" \
		--with-sample-datadir="${LOCALBASE}/share/coin/Data/Sample" \
		--datadir=${DATADIR}

TEST_TARGET=	unitTest
TEST_WRKSRC=	${WRKSRC}/${PORTNAME}

OPTIONS_DEFINE=	DEBUG DOCS
PORTDOCS=	*

CXXFLAGS+=	-ffast-math
DEBUG_CXXFLAGS=	-fomit-frame-pointer

.include <bsd.port.mk>
