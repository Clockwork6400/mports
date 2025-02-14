PORTNAME=	cmake
DISTVERSION=	${_CMAKE_VERSION}
PORTREVISION=	2
CATEGORIES=	devel
PKGNAMESUFFIX=	-core

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Cross-platform Makefile generator
WWW=		https://www.cmake.org/

LICENSE=	bsd3
LICENSE_FILE=	${WRKSRC}/Copyright.txt

USES=		cmake:_internal compiler:c++11-lang cpe ncurses ssl
CONFIGURE_ENV=	MAKE=make
CONFIGURE_ARGS=	--prefix=${PREFIX} \
		--datadir="/${DATADIR_REL}" \
		--docdir="/${DOCSDIR_REL}" \
		--system-libs \
		--parallel=${MAKE_JOBS_NUMBER} \
		--init="${WRKSRC}/InitialCache.cmake"

OPTIONS_DEFINE=	DOCS
OPTIONS_SUB=	yes
HAS_CONFIGURE=	yes

LIB_DEPENDS=	libcurl.so:ftp/curl \
		libexpat.so:textproc/expat2 \
		libjsoncpp.so:devel/jsoncpp \
		libuv.so:devel/libuv \
		librhash.so:security/rhash

CXXFLAGS+=	-D__BSD_VISIBLE

.include <bsd.port.pre.mk>

.if defined(STRIP) && ${STRIP} != "" && !defined(WITH_DEBUG)
INSTALL_TARGET=	install/strip
.endif

# CMake >= 3.1.0 needs libarchive3 because it calls
# archive_entry_copy_sourcepath_w and archive_write_set_format_7zip.
LIB_DEPENDS+=	libarchive.so.13:archivers/libarchive

pre-configure:
	@${CP} "${FILESDIR}/InitialCache.cmake" "${WRKSRC}/InitialCache.cmake"


post-patch:
	@${CP} ${FILESDIR}/MidnightBSD.cmake ${WRKSRC}/Modules/Platform
	@(${FIND} ${WRKSRC}/Modules -name "*.cmake" -print0; \
		${FIND} ${WRKSRC}/Tests -name "CMakeLists.txt" -print0 ) | \
		${XARGS} -0 -n 100 ${REINPLACE_CMD} -e 's,/usr/local,${LOCALBASE},g; \
			s,/usr/X11R6,${LOCALBASE},g'
	@${REINPLACE_CMD} -e 's,/usr/local,${LOCALBASE},g' \
		${WRKSRC}/Source/cmLocalGenerator.cxx \
		${WRKSRC}/Source/CPack/cmCPackGenerator.cxx \
		${WRKSRC}/bootstrap
	@${REINPLACE_CMD} -e 's,/opt/kde4,${PREFIX},g' \
		${WRKSRC}/Modules/FindKDE4.cmake
	@${REINPLACE_CMD} -e 's,/usr/include,${LOCALBASE}/include,' \
	   	${WRKSRC}/Modules/FindDCMTK.cmake
	@${FIND} ${WRKSRC} -name "*.bak" -delete -o -name "*.orig" -delete

# cmake-gui(1) is installed by devel/cmake-gui. Remove the man page's source to
# prevent it from being built/installed by devel/cmake.
	@${RM} ${WRKSRC}/Help/manual/cmake-gui.1.rst

post-install:
	${INSTALL_DATA} ${WRKSRC}/Auxiliary/cmake-mode.el ${PREFIX}/share/emacs/site-lisp
	@${FIND} ${STAGEDIR}${PREFIX} -name ".NoDartCoverage" -delete

.include <bsd.port.post.mk>
