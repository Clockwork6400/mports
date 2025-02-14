# Based on the graphics/ilmbase port that was done by: nork@FreeBSD.org

PORTNAME=	Imath
PORTVERSION=	3.1.3
CATEGORIES=	math devel graphics

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	C++/Python lib of 2D/3D vector, matrix, math ops for computer graphics

LICENSE=	bsd3

USES=		cmake compiler:c++14-lang pkgconfig

USE_GITHUB=	yes
GH_TUPLE=	AcademySoftwareFoundation:Imath:v${PORTVERSION}
USE_LDCONFIG=	yes

CMAKE_ARGS+=	-DCMAKE_DEBUG_POSTFIX= \
		-DCMAKE_INSTALL_PREFIX=${PREFIX}

PATCH_STRIP=	-p1

PLIST_SUB=	MAJORVER=${_MAJORVER} \
		MINVER=${_MINVER} \
		PLVER=${_PLVER} \
		VER=${_VER} \
		PYVER=${PYTHON_VER:S/./_/}
PORTDOCS=	README.md

OPTIONS_DEFINE=	DOCS LARGE_STACK PYTHON
OPTIONS_SUB=	yes

LARGE_STACK_DESC=	Enable sys-dependent large stack optimizations
LARGE_STACK_CMAKE_BOOL=	IMATH_ENABLE_LARGE_STACK

PYTHON_BUILD_DEPENDS=	${PYNUMPY}
PYTHON_LIB_DEPENDS=	${PY_BOOST}
PYTHON_RUN_DEPENDS=	${PYNUMPY}
PYTHON_USES=		python
PYTHON_CMAKE_BOOL=	PYTHON

_MAJORVER=	3_1
_VER=		29
_MINVER=	2
_PLVER=		0

#magus issues
NO_TEST=	yes

post-install:
.for l in libImath
	${STRIP_CMD} ${PREFIX}/lib/${l}-${_MAJORVER}.so
.endfor

	@${MKDIR} ${DOCSDIR}
	${INSTALL_DATA} ${PORTDOCS:S|^|${WRKSRC}/|} ${DOCSDIR}

#do-test:
#	cd ${BUILD_WRKSRC} && ctest -j ${MAKE_JOBS_NUMBER}

.include <bsd.port.mk>
