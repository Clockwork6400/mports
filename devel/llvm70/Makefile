PORTNAME=	llvm
DISTVERSION=	7.0.1
CATEGORIES=	devel lang
MASTER_SITES=	http://${PRE_}releases.llvm.org/${LLVM_RELEASE}/${RCDIR}
PKGNAMESUFFIX=	${LLVM_SUFFIX}
DISTNAME=	${PORTNAME}-${DISTVERSION}.src
DISTFILES=	${PORTNAME}-${DISTVERSION}.src${EXTRACT_SUFX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	LLVM and Clang

.include "${.CURDIR}/../llvm-devel/Makefile.LICENSE"

LLVM_RELEASE=	${DISTVERSION:C/rc.*//}
LLVM_MAJOR=	${LLVM_RELEASE:C/\.[0-9]\.[0-9]$//}
RCDIR=		${DISTVERSION:S/${LLVM_RELEASE}//:C|(rc.*)|\1/|}
PRE_=		${DISTVERSION:C/.*rc.*/pre/:N*[0-9]*}
LLVM_SUFFIX=	${LLVM_RELEASE:C/\.[0-9]$//:C/\.//}

LLVM_PREFIX=	${PREFIX}/llvm${LLVM_SUFFIX}
DOCSDIR=	${PREFIX}/share/doc/${PORTNAME}${LLVM_SUFFIX}
DATADIR=	${PREFIX}/share/${PORTNAME}${LLVM_SUFFIX}

USES=		cmake compiler:c++11-lib cpe libedit perl5 tar:xz \
		shebangfix
_USES_PYTHON?=	python:2.7,build
USES+=		${_USES_PYTHON}
USE_LDCONFIG=	${LLVM_PREFIX}/lib
NO_TEST=	yes
SHEBANG_FILES=	utils/lit/lit.py utils/llvm-lit/llvm-lit.in \
		tools/clang/utils/hmaptool/hmaptool

SUB_FILES=	llvm-wrapper.sh
SUB_LIST=	LLVM_PREFIX="${LLVM_PREFIX}" LLVM_SUFFIX="${LLVM_SUFFIX}"

MAKE_ENV+=	DESTDIR=${FAKE_DESTDIR}

CMAKE_INSTALL_PREFIX=	${LLVM_PREFIX}
CMAKE_ARGS=	-DLLVM_BUILD_LLVM_DYLIB=ON 
#-DLLVM_LINK_LLVM_DYLIB=ON
CMAKE_ARGS+=	-DLLVM_ENABLE_RTTI=ON
CMAKE_ARGS+=	-DLLVM_DEFAULT_TARGET_TRIPLE=${CONFIGURE_TARGET}
CMAKE_ARGS+=	-DLLVM_HOST_TRIPLE=${CONFIGURE_TARGET}
# Following commit https://github.com/kitware/cmake/commit/956054
# we need to either change the whole man-shuffle below, or simply
# redefine CMAKE_INSTALL_MANDIR
CMAKE_ARGS+=	-DCMAKE_INSTALL_MANDIR:PATH="share/man"
CMAKE_ARGS+=	-DLLVM_PARALLEL_LINK_JOBS=1

# Disable assertions.  They should be disabled by cmake, but USES=cmake
# overrides -DCMAKE_*_FLAGS_RELEASE.
CFLAGS+=	-DNDEBUG
CXXFLAGS+=	-DNDEBUG

OPTIONS_DEFINE=	CLANG DOCS EXTRAS LIT LLD LLDB
OPTIONS_DEFINE_amd64=	COMPILER_RT GOLD OPENMP
OPTIONS_DEFINE_i386=	COMPILER_RT OPENMP
OPTIONS_DEFAULT=	CLANG EXTRAS LIT LLD
# LLDB should be default when fixed.
OPTIONS_DEFAULT_amd64=	COMPILER_RT OPENMP
OPTIONS_DEFAULT_i386=	COMPILER_RT OPENMP
OPTIONS_SUB=	yes

CLANG_DESC=	Build clang
CLANG_EXTRA_PATCHES=	${PATCHDIR}/clang
CLANG_DISTFILES=	cfe-${DISTVERSION}.src${EXTRACT_SUFX}
CLANG_CMAKE_ON=		-DCLANG_DEFAULT_OPENMP_RUNTIME=libomp
CLANG_PORTDOCS=		clang
CLANG_USE=		GNOME=libxml2
COMPILER_RT_DESC=	Sanitizer libraries
COMPILER_RT_DISTFILES=	compiler-rt-${DISTVERSION}.src${EXTRACT_SUFX}
COMPILER_RT_PLIST_FILES=${_COMPILER_RT_LIBS:S|^|${_CRTLIBDIR}/|} \
			${_COMPILER_RT_BLACKLISTS:S|^|${_CRTBLDIR}/|}
DOCS_BUILD_DEPENDS=     sphinx-build:textproc/py-sphinx
DOCS_PORTDOCS=		llvm
DOCS_CMAKE_ON=		-DLLVM_ENABLE_SPHINX=ON \
			-DSPHINX_WARNINGS_AS_ERRORS=OFF \
			-DLLVM_BUILD_DOCS=ON
DOCS_PLIST_FILES=	${MAN1SRCS:S|^|man/man1/|:S|.1$|${LLVM_SUFFIX}.1.gz|}
EXTRAS_DESC=		Extra clang tools
EXTRAS_IMPLIES=		CLANG
EXTRAS_DISTFILES=	clang-tools-extra-${DISTVERSION}.src${EXTRACT_SUFX}
GOLD_DESC=		Build the LLVM Gold plugin for LTO
GOLD_CMAKE_ON=		-DLLVM_BINUTILS_INCDIR=${LOCALBASE}/include
GOLD_BUILD_DEPENDS=	${LOCALBASE}/bin/ld.gold:devel/binutils
LIT_DESC=		Install lit and FileCheck test tools
LIT_VARS=		_USES_PYTHON=python:2.7
LLD_DESC=		Install lld, the LLVM linker
LLD_DISTFILES=		lld-${DISTVERSION}.src${EXTRACT_SUFX}
LLD_EXTRA_PATCHES=	${PATCHDIR}/lld
LLDB_BUILD_DEPENDS=	swig3.0:devel/swig30 \
			${PY_ENUM34}
LLDB_DESC=		Install lldb, the LLVM debugger
LLDB_DISTFILES=		lldb-${DISTVERSION}.src${EXTRACT_SUFX}
LLDB_EXTRA_PATCHES=	${PATCHDIR}/lldb
LLDB_IMPLIES=		CLANG
LLDB_VARS=		_USES_PYTHON=python:2.7
OPENMP_DESC=		Install libomp, the LLVM OpenMP runtime library
OPENMP_DISTFILES=	openmp-${DISTVERSION}.src${EXTRACT_SUFX}
OPENMP_EXTRA_PATCHES=	${PATCHDIR}/openmp

.if defined(WITH_DEBUG)
CMAKE_BUILD_TYPE=	RelWithDebInfo
STRIP=
.endif

# Emulate USE_GITHUB's ${WRKSRC_tag} to reduce diffs to ../llvm-devel
.for option in CLANG COMPILER_RT EXTRAS LLD LLDB OPENMP
WRKSRC_${option:tl}=		${WRKDIR}/${${option}_DISTFILES:S/${EXTRACT_SUFX}//}
.endfor

PLIST_SUB+=	LLVM_RELEASE=${LLVM_RELEASE} \
		LLVM_SUFFIX=${LLVM_SUFFIX} \
		LLVM_MAJOR=${LLVM_MAJOR}

COMMANDS=	${LLVM_COMMANDS}
FIRST_COMMAND=	${COMMANDS:C/^/XXXX/1:MXXXX*:C/^XXXX//}

STRIP_LIBS=	BugpointPasses.so \
		LLVMHello.so \
		${LIBNAME}.0 \
		libLTO.so

EXTRAS_LIBS=	libclangApplyReplacements \
		libclangChangeNamespace \
		libclangDaemon \
		libclangDoc \
		libclangIncludeFixer \
		libclangMove \
		libclangQuery \
		libclangRename \
		libclangReorderFields \
		libclangTidy \
		libclangTidyGoogleModule \
		libclangTidyLLVMModule \
		libclangTidyMiscModule \
		libclangTidyReadabilityModule \
		libclangTidyUtils \
		libfindAllSymbols \
		libmodernizeCore
EXTRAS_PATTERN=	${EXTRAS_COMMANDS:tW:C/  */|/g}|${EXTRAS_LIBS:tW:C/  */|/g}

.include <bsd.mport.options.mk>

# keep in sync with /usr/src/lib/clang/clang.build.mk
# ----------- start of sync block ------------------
# Armv6 and armv7 uses hard float abi, unless the CPUTYPE has soft in it.
# arm (for armv4 and armv5 CPUs) always uses the soft float ABI.
# For all other targets, we stick with 'unknown'.
.if ${ARCH:Marmv[67]*} && (!defined(CPUTYPE) || ${CPUTYPE:M*soft*} == "")
TARGET_ABI=	-gnueabihf
.elif ${ARCH:Marm*}
TARGET_ABI=	-gnueabi
.else
TARGET_ABI=
.endif

CONFIGURE_TARGET:=${ARCH:C/amd64/x86_64/:C/arm64/aarch64/}-portbld-freebsd10.4${TARGET_ABI}

# ----------- end of sync block --------------------

.if ${PORT_OPTIONS:MCLANG}
COMMANDS+=	${CLANG_COMMANDS}
MAN1SRCS+=	clang.1 \
		diagtool.1 \
		scan-build.1
CLANG_PATTERN=	(c-index-test|clang|scan-|Reporter.py|ScanView.py|scanview.css|sorttable.js|startfile.py|-analyzer)
SHEBANG_FILES+=	tools/clang/tools/scan-view/bin/scan-view \
		tools/clang/tools/clang-format/git-clang-format \
		tools/clang/tools/clang-format/clang-format-diff.py
USES+=		gnome
.endif

.if ${PORT_OPTIONS:MCOMPILER_RT}
COMPILER_RT_PATTERN=	(_blacklist.txt|sanitizer|include.xray)
.endif

.if ${PORT_OPTIONS:MEXTRAS}
COMMANDS+=	${EXTRAS_COMMANDS}
MAN1SRCS+=	extraclangtools.1
PORTDOCS+=	clang-tools
SHEBANG_FILES+=	tools/clang/tools/extra/clang-tidy/tool/clang-tidy-diff.py \
		tools/clang/tools/extra/clang-tidy/tool/run-clang-tidy.py \
		tools/clang/tools/extra/include-fixer/find-all-symbols/tool/run-find-all-symbols.py
.endif

.if ${PORT_OPTIONS:MLIT}
MAN1SRCS+=	lit.1 FileCheck.1
.endif

.if ${PORT_OPTIONS:MLLD}
COMMANDS+=	${LLD_COMMANDS}
PORTDOCS+=	lld
.endif

.if ${PORT_OPTIONS:MLLDB}
COMMANDS+=	${LLDB_COMMANDS}
.endif

MAN1SRCS+=	bugpoint.1 dsymutil.1 llc.1 lli.1 llvm-ar.1 llvm-as.1 \
		llvm-bcanalyzer.1 llvm-build.1 llvm-config.1 llvm-cov.1 \
		llvm-diff.1 llvm-dis.1 llvm-dwarfdump.1 \
		llvm-exegesis.1 \
		llvm-extract.1 llvm-lib.1 llvm-link.1 \
		llvm-mca.1 \
		llvm-nm.1 \
		llvm-pdbutil.1 \
		llvm-profdata.1 llvm-readobj.1 llvm-stress.1 llvm-symbolizer.1 \
		opt.1 tblgen.1

.include <bsd.port.pre.mk>
.include "${.CURDIR}/Makefile.COMMANDS"

_CRTLIBDIR=	${LLVM_PREFIX:S|${PREFIX}/||}/lib/clang/${LLVM_RELEASE}/lib/midnightbsd
_CRTBLDIR=	${LLVM_PREFIX:S|${PREFIX}/||}/share
_COMPILER_RT_BLACKLISTS=	cfi_blacklist.txt
.if ${ARCH} == "amd64"
_COMPILER_RT_BLACKLISTS+=	asan_blacklist.txt
_COMPILER_RT_BLACKLISTS+=	msan_blacklist.txt
_COMPILER_RT_LIBS= \
	libclang_rt.asan-preinit-x86_64.a \
	libclang_rt.asan-x86_64.a \
	libclang_rt.asan-x86_64.a.syms \
	libclang_rt.asan-x86_64.so \
	libclang_rt.asan_cxx-x86_64.a \
	libclang_rt.asan_cxx-x86_64.a.syms \
	libclang_rt.builtins-x86_64.a \
	libclang_rt.dd-x86_64.a \
	libclang_rt.dyndd-x86_64.so \
	libclang_rt.fuzzer-x86_64.a \
	libclang_rt.fuzzer_no_main-x86_64.a \
	libclang_rt.lsan-x86_64.a \
	libclang_rt.msan-x86_64.a \
	libclang_rt.msan-x86_64.a.syms \
	libclang_rt.msan_cxx-x86_64.a \
	libclang_rt.msan_cxx-x86_64.a.syms \
	libclang_rt.profile-x86_64.a \
	libclang_rt.safestack-x86_64.a \
	libclang_rt.stats-x86_64.a \
	libclang_rt.stats_client-x86_64.a \
	libclang_rt.tsan-x86_64.a \
	libclang_rt.tsan-x86_64.a.syms \
	libclang_rt.tsan_cxx-x86_64.a \
	libclang_rt.tsan_cxx-x86_64.a.syms \
	libclang_rt.ubsan_minimal-x86_64.a \
	libclang_rt.ubsan_minimal-x86_64.a.syms \
	libclang_rt.ubsan_minimal-x86_64.so \
	libclang_rt.ubsan_standalone-x86_64.a \
	libclang_rt.ubsan_standalone-x86_64.a.syms \
	libclang_rt.ubsan_standalone-x86_64.so \
	libclang_rt.ubsan_standalone_cxx-x86_64.a \
	libclang_rt.ubsan_standalone_cxx-x86_64.a.syms \
	libclang_rt.xray-basic-x86_64.a \
	libclang_rt.xray-fdr-x86_64.a \
	libclang_rt.xray-profiling-x86_64.a \
	libclang_rt.xray-x86_64.a
.endif
.if ${ARCH} == "i386"
_COMPILER_RT_BLACKLISTS+=	asan_blacklist.txt
_COMPILER_RT_LIBS+= \
	libclang_rt.asan-i386.a \
	libclang_rt.asan-i386.so \
	libclang_rt.asan-preinit-i386.a \
	libclang_rt.asan_cxx-i386.a \
	libclang_rt.builtins-i386.a \
	libclang_rt.lsan-i386.a \
	libclang_rt.profile-i386.a \
	libclang_rt.safestack-i386.a \
	libclang_rt.stats-i386.a \
	libclang_rt.stats_client-i386.a \
	libclang_rt.ubsan_minimal-i386.a \
	libclang_rt.ubsan_minimal-i386.so \
	libclang_rt.ubsan_standalone-i386.a \
	libclang_rt.ubsan_standalone-i386.so \
	libclang_rt.ubsan_standalone_cxx-i386.a
.endif

.if ${ARCH} == "armv6"
BUILD_DEPENDS+=	${LOCALBASE}/bin/ld:devel/binutils
CONFIGURE_ENV+=	COMPILER_PATH=${LOCALBASE}/bin
MAKE_ENV+=	COMPILER_PATH=${LOCALBASE}/bin
.endif

.if ! ${OPTIONS_DEFINE:MCOMPILER_RT}
# Hack to disable COMPILER_RT in plist of unsupported architectures
PLIST_SUB+=	COMPILER_RT="@comment "
.else
.endif

.if ! ${OPTIONS_DEFINE:MGOLD}
# Hack to disable GOLD in plist of unsupported architectures
PLIST_SUB+=	GOLD="@comment "
.else
.endif

.if ! ${OPTIONS_DEFINE:MOPENMP}
# Hack to disable OPENMP in plist of unsupported architectures
PLIST_SUB+=	OPENMP="@comment "
.else
.endif

post-extract-CLANG-on:
	${MV} ${WRKSRC_clang} ${PATCH_WRKSRC}/tools/clang

post-extract-EXTRAS-on:
	${MV} ${WRKSRC_extras} ${PATCH_WRKSRC}/tools/clang/tools/extra

post-extract-LLD-on:
	${MV} ${WRKSRC_lld} ${PATCH_WRKSRC}/tools/lld

post-extract-LLDB-on:
	${MV} ${WRKSRC_lldb} ${PATCH_WRKSRC}/tools/lldb

post-extract-OPENMP-on:
	${MV} ${WRKSRC_openmp} ${PATCH_WRKSRC}/projects/openmp

post-patch:
	${REINPLACE_CMD} -e 's|import lit|import lit${LLVM_SUFFIX}|' \
	    -e 's|from lit|from lit${LLVM_SUFFIX}|' \
	    -e 's|lit\.|lit${LLVM_SUFFIX}.|' \
	    ${WRKSRC}/utils/lit/lit.py ${WRKSRC}/utils/lit/lit/*.py \
	    ${WRKSRC}/utils/lit/lit/formats/*.py
	${REINPLACE_CMD} -e 's,/usr/local/,${LOCALBASE}/,' \
	    ${WRKSRC}/CMakeLists.txt

post-patch-CLANG-on:
	${REINPLACE_CMD} -e 's|%%LLVM_PREFIX%%|${LLVM_PREFIX}|' \
	    ${PATCH_WRKSRC}/tools/clang/lib/Driver/ToolChains/CommonArgs.cpp
	${REINPLACE_CMD} -e 's|%%LLVM_SUFFIX%%|${LLVM_SUFFIX}|' \
	    ${PATCH_WRKSRC}/tools/clang/tools/clang-format/clang-format.py \
	    ${PATCH_WRKSRC}/tools/clang/tools/clang-format/clang-format-sublime.py \
	    ${PATCH_WRKSRC}/tools/clang/tools/clang-format/git-clang-format

post-patch-COMPILER_RT-on:
	cd ${WRKSRC_compiler_rt} && patch < ${PATCHDIR}/compiler_rt/patch-rt_cmake_config-ix.cmake
	cd ${WRKSRC_compiler_rt) && patch < ${PATCHDIR}/compiler_rt/patch-rt_lib_sanitizer_common_sanitizer_platform.h
	${REINPLACE_CMD} -e 's/FreeBSD/MidnightBSD/g' ${WRKSRC_compiler_rt}/lib/tsan/CMakeLists.txt

post-patch-LLD-on:
	${REINPLACE_CMD} -e "s|'indexsidebar.html'|['indexsidebar.html']|" \
		${PATCH_WRKSRC}/tools/lld/docs/conf.py

post-build-COMPILER_RT-on:
	${MKDIR} ${WRKDIR}/compiler-rt-build
	cd ${WRKDIR}/compiler-rt-build && \
	${SETENV} ${CONFIGURE_ENV} ${CMAKE_BIN} ${CMAKE_ARGS} \
	    -DLLVM_CONFIG_PATH=${CONFIGURE_WRKSRC}/bin/llvm-config \
	    ${WRKSRC_compiler_rt} && \
	    ${MAKE_ENV} DESTDIR=${FAKE_DESTDIR} ${MAKE_CMD}

post-install:
	-${RM} -r ${FAKE_DESTDIR}${LLVM_PREFIX}/include/llvm/MC/MCAnalysis
	${INSTALL_SCRIPT} ${WRKDIR}/llvm-wrapper.sh \
	    ${PREFIX}/bin/${FIRST_COMMAND}${LLVM_SUFFIX}
.for command in ${COMMANDS:C/^/XXXX/1:NXXXX*}
	${LN} -f ${PREFIX}/bin/${FIRST_COMMAND}${LLVM_SUFFIX} \
	    ${PREFIX}/bin/${command}${LLVM_SUFFIX}
.endfor

post-install-DOCS-on:
	${MV} ${FAKE_DESTDIR}${LLVM_PREFIX}/share/doc ${FAKE_DESTDIR}${DOCSDIR}
.for _man in ${MAN1SRCS}
	${MV} ${FAKE_DESTDIR}${LLVM_PREFIX}/share/man/man1/${_man} \
	    ${FAKE_DESTDIR}${MANPREFIX}/man/man1/${_man:R}${LLVM_SUFFIX}.1
.endfor
.if ! ${PORT_OPTIONS:MLIT}
	-${RM} ${FAKE_DESTDIR}${LLVM_PREFIX}/share/man/man1/lit.1
	-${RM} ${FAKE_DESTDIR}${LLVM_PREFIX}/share/man/man1/FileCheck.1
.endif
	-${RMDIR} ${FAKE_DESTDIR}${LLVM_PREFIX}/share/man/man1/
	-${RMDIR} ${FAKE_DESTDIR}${LLVM_PREFIX}/share/man/

.if ${PORT_OPTIONS:MCLANG}
post-install-DOCS-off:
	-${RM} ${FAKE_DESTDIR}${LLVM_PREFIX}/share/man/man1/scan-build.1
	-${RMDIR} ${FAKE_DESTDIR}${LLVM_PREFIX}/share/man/man1/
	-${RMDIR} ${FAKE_DESTDIR}${LLVM_PREFIX}/share/man/
.endif

post-install-LLD-on:
	-${RMDIR} ${FAKE_DESTDIR}${LLVM_PREFIX}/include/llvm/BinaryFormat/WasmRelocs

post-install-CLANG-on:
	${LN} -f ${FAKE_DESTDIR}${LLVM_PREFIX}/bin/clang \
	   ${FAKE_DESTDIR}${LLVM_PREFIX}/bin/clang-cpp
	${INSTALL_PROGRAM} ${WRKDIR}/.build/bin/clang-tblgen \
	    ${FAKE_DESTDIR}${LLVM_PREFIX}/bin/

post-install-COMPILER_RT-on:
	cd ${WRKDIR}/compiler-rt-build && \
	    ${MAKE_ENV} ${FAKE_MAKEENV} DESTDIR=${FAKE_DESTDIR} ${MAKE_CMD} ${FAKE_MAKEARGS} ${INSTALL_TARGET}
.if ${ARCH} == "amd64"
	-${RM} ${FAKE_DESTDIR}${LLVM_PREFIX}/lib/midnightbsd/libclang_rt*i386*
.endif
	-${MKDIR} ${FAKE_DESTDIR}${PREFIX}/${_CRTLIBDIR}
	-${MV} ${FAKE_DESTDIR}${LLVM_PREFIX}/lib/midnightbsd/* \
	    ${FAKE_DESTDIR}${PREFIX}/${_CRTLIBDIR}
	-${RMDIR} ${FAKE_DESTDIR}${LLVM_PREFIX}/lib/midnightbsd

post-install-LIT-on:
	${INSTALL_SCRIPT} ${PATCH_WRKSRC}/utils/lit/lit.py \
	    ${FAKE_DESTDIR}${LLVM_PREFIX}/bin/lit
	${LN} -f ${FAKE_DESTDIR}${LLVM_PREFIX}/bin/lit \
	    ${FAKE_DESTDIR}${LLVM_PREFIX}/bin/llvm-lit
	${LN} -f ${FAKE_DESTDIR}${LLVM_PREFIX}/bin/lit \
	    ${FAKE_DESTDIR}${PREFIX}/bin/lit${LLVM_SUFFIX}
	${LN} -f ${FAKE_DESTDIR}${LLVM_PREFIX}/bin/lit \
	    ${FAKE_DESTDIR}${PREFIX}/bin/llvm-lit${LLVM_SUFFIX}
	${MKDIR} ${FAKE_DESTDIR}${PYTHONPREFIX_SITELIBDIR}/lit${LLVM_SUFFIX}
	${MKDIR} ${FAKE_DESTDIR}${PYTHONPREFIX_SITELIBDIR}/lit${LLVM_SUFFIX}/builtin_commands
	${MKDIR} ${FAKE_DESTDIR}${PYTHONPREFIX_SITELIBDIR}/lit${LLVM_SUFFIX}/formats
	${INSTALL_DATA} ${WRKSRC}/utils/lit/lit/*.py \
	    ${FAKE_DESTDIR}${PYTHONPREFIX_SITELIBDIR}/lit${LLVM_SUFFIX}
	${INSTALL_DATA} ${WRKSRC}/utils/lit/lit/builtin_commands/*.py \
			${FAKE_DESTDIR}${PYTHONPREFIX_SITELIBDIR}/lit${LLVM_SUFFIX}/builtin_commands
	${INSTALL_DATA} ${WRKSRC}/utils/lit/lit/formats/*.py \
			${FAKE_DESTDIR}${PYTHONPREFIX_SITELIBDIR}/lit${LLVM_SUFFIX}/formats
	${INSTALL_PROGRAM} ${WRKDIR}/.build/bin/FileCheck \
	    ${FAKE_DESTDIR}${LLVM_PREFIX}/bin/
	${LN} -f ${FAKE_DESTDIR}${LLVM_PREFIX}/bin/FileCheck \
	    ${FAKE_DESTDIR}${PREFIX}/bin/FileCheck${LLVM_SUFFIX}

build-plist:
	${RM} ${PLIST} ${PLIST}.tmp
	${ECHO_CMD} "@comment >>>>> GENERATED FILE, DO NOT EDIT <<<<<" >> ${PLIST}.tmp
	${ECHO_CMD} "@comment Alter build-plist target and regenerate as required" >> ${PLIST}.tmp
.for command in ${COMMANDS}
	${ECHO_CMD} bin/${command}%%LLVM_SUFFIX%% >> ${PLIST}.tmp
.endfor
.for command in ${LIT_COMMANDS}
	${ECHO_CMD} %%LIT%%bin/${command}%%LLVM_SUFFIX%% >> ${PLIST}.tmp
	${ECHO_CMD} %%LIT%%${LLVM_PREFIX:S|${PREFIX}/||:C|${LLVM_SUFFIX}|%%LLVM_SUFFIX%%|}/bin/${command} >> ${PLIST}.tmp
.endfor

	${FIND} ${FAKE_DESTDIR}${LLVM_PREFIX} -type f -o -type l | \
	    ${GREP} -v '_blacklist.txt$$' | \
	    ${GREP} -v '[/-]lit$$' | ${GREP} -v 'FileCheck$$' | \
	    ${GREP} -v man/man1 | ${SED} -e 's|${FAKE_DESTDIR}${TRUE_PREFIX}/||' \
	    -e 's|${PYTHON_SITELIBDIR:C|${PREFIX}/||}|%%PYTHON_SITELIBDIR%%|' \
	    -e 's|${LLVM_RELEASE}|%%LLVM_RELEASE%%|' \
	    -e 's|release.cmake|%%CMAKE_BUILD_TYPE%%.cmake|' \
	    -e 's|${LLVM_RELEASE:C/\./\\./g}|%%LLVM_RELEASE%%|' \
	    -e 's|${LLVM_SUFFIX:C/\./\\./g}|%%LLVM_SUFFIX%%|' \
	    -e 's|${LLVM_MAJOR}|%%LLVM_MAJOR%%|' \
	    | ${SORT} >> ${PLIST}.tmp
	${FIND} ${FAKE_DESTDIR}${PYTHON_SITELIBDIR}/lit${LLVM_SUFFIX} -type f | \
	    ${SED} -e 's|${FAKE_DESTDIR}${PYTHON_SITELIBDIR}|%%LIT%%%%PYTHON_SITELIBDIR%%|' \
	    -e 's|${LLVM_RELEASE:C/\./\\./g}|%%LLVM_RELEASE%%|' \
	    -e 's|${LLVM_SUFFIX:C/\./\\./g}|%%LLVM_SUFFIX%%|' \
	    -e 's|${LLVM_MAJOR}|%%LLVM_MAJOR%%|' \
	    | ${SORT} >> ${PLIST}.tmp
	${AWK} '{ \
	    if ($$0 ~ /${CLANG_PATTERN}/ && $$0 !~ /(omp.h|ompt.h|${EXTRAS_PATTERN}|libclang_rt)/) {printf "%%%%CLANG%%%%"} \
	    if ($$0 ~ /${COMPILER_RT_PATTERN}/) \
		{printf "%%%%COMPILER_RT%%%%"} \
	    if ($$0 ~ /(${EXTRAS_PATTERN})/) {printf "%%%%EXTRAS%%%%"} \
	    if ($$0 ~ /(lld|wasm-ld)/ && $$0 !~ /(lldb)/) {printf "%%%%LLD%%%%"} \
	    if ($$0 ~ /(argdumper|lldb|six.py)/) {printf "%%%%LLDB%%%%"} \
	    if ($$0 ~ /(lib.*omp|omp.h|ompt.h)/) {printf "%%%%OPENMP%%%%"} \
	    if ($$0 ~ /(LLVMgold)/) {printf "%%%%GOLD%%%%"} \
	    if ($$0 !~ /(libclang_rt)/) {print}}' ${PLIST}.tmp >> ${PLIST}
	${ECHO_CMD} '@postexec if type ccache-update-links >/dev/null 2>&1; then ccache-update-links -v; fi' >> ${PLIST}
	${ECHO_CMD} '@postunexec if type ccache-update-links >/dev/null 2>&1; then ccache-update-links -v; fi' >> ${PLIST}
	${RM} ${PLIST}.tmp

check-commands:
.for command in ${COMMANDS}
	test -e ${FAKE_DESTDIR}${LLVM_PREFIX}/bin/${command}
.endfor

.include <bsd.port.post.mk>
