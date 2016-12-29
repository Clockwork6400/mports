# $MidnightBSD$ 

.if defined(_POSTMKINCLUDED) && !defined(Pgsql_Post_Include)

Pgsql_Post_Include=			pgsql.mk
Pgsql_Include_MAINTAINER=	ports@MidnightBSD.org

# USE_PGSQL		- Add PostgreSQL client dependency.
#				  If no version is given (by the maintainer via the port or
#				  by the user via defined variable), try to find the
#				  currently installed version.  Fall back to default if
#				  necessary (PostgreSQL-9.4 = 94).
# DEFAULT_PGSQL_VER
#				- PostgreSQL default version. Can be overridden within a port.
#				  Default: 84.
# WANT_PGSQL_VER
#				- Maintainer can set an arbitrary version of PostgreSQL by
#				  using it.
# IGNORE_WITH_PGSQL
#				- This variable can be defined if the ports doesn't support
#				  one or more versions of PostgreSQL.
# WITH_PGSQL_VER
#				- User defined variable to set PostgreSQL version.
# PGSQL_VER
#	Detected PostgreSQL version.  Do *not* use this
#	to add dependencies; use WANT_PGSQL as explained above
#

VALID_PGSQL_VER=	9.0 9.2 9.3 9.4 9.5 9.6

# Override non-default LIBVERS like this:
#PGSQL99_LIBVER=6

PGSQL_LIBVER=	5
.for v in ${VALID_PGSQL_VER:S,.,,}
PGSQL$v_LIBVER?=	${PGSQL_LIBVER}
.endfor

.include "${PORTSDIR}/Mk/components/default-versions.mk"

.for v in ${PGSQL_DEFAULT}
.  if ! ${VALID_PGSQL_VER:M$v}
IGNORE=		Invalid PGSQL default version ${PGSQL_DEFAULT}; valid versions are ${VALID_PGSQL_VER}
.  endif
.endfor

.  for w in WITH DEFAULT
.    ifdef $w_PGSQL_VER
WARNING+=	"$w_PGSQL_VER is defined, consider using DEFAULT_VERSIONS=pgsql=${$w_PGSQL_VER:C,^.,&.,} instead"
PGSQL_DEFAULT?=	${$w_PGSQL_VER:C,^.,&.,}
.    endif
.  endfor

.  ifdef DEFAULT_PGSQL_VER && WITH_PGSQL_VER
IGNORE=		will not allow setting both DEFAULT_PGSQL_VER and WITH_PGSQL_VER.  Use DEFAULT_VERSIONS=pgsql=9.0 instead
.  endif

# Setting/finding PostgreSQL version we want.
PG_CONFIG?=	${LOCALBASE}/bin/pg_config
.  if exists(${PG_CONFIG})
_PGSQL_VER!=	${PG_CONFIG} --version | ${SED} -n 's/PostgreSQL[^0-9]*\([0-9][0-9]*\.[0-9][0-9]*\)[^0-9].*/\1/p'
.  endif

# Handle the + and - version stuff
.  if !empty(pgsql_ARGS)
.    if ${pgsql_ARGS:M*+}
.      for version in ${VALID_PGSQL_VER}
.        if ${pgsql_ARGS:S/+//} <= ${version}
_WANT_PGSQL_VER+=${version}
.        endif
.      endfor
.    elif ${pgsql_ARGS:M*-}
.      for version in ${VALID_PGSQL_VER}
.        if ${pgsql_ARGS:S/-//} >= ${version}
_WANT_PGSQL_VER+=${version}
.        endif
.      endfor
.    endif
_WANT_PGSQL_VER?=	${pgsql_ARGS}
.  endif

# Try to match default version, otherwise just take the first version
# that matches
.  if !empty(_WANT_PGSQL_VER)
.    for version in ${_WANT_PGSQL_VER}
.      if ${PGSQL_DEFAULT} == ${version}
PGSQL_VER=	${version}
.      endif
PGSQL_VER?=	${version}
.    endfor
.    if !defined(PACKAGE_BUILDING) && defined(_PGSQL_VER) && ${_PGSQL_VER} != ${PGSQL_VER}
IGNORE?=	cannot install: the port wants postgresql-client version ${_WANT_PGSQL_VER} and you have version ${_PGSQL_VER} installed
.    endif
.  endif

# OK, so the port is ambivalent, we'll just take what's on the system.
PGSQL_VER?=	${_PGSQL_VER}

# After all that, we still have found nothing!
.  if empty(PGSQL_VER)
PGSQL_VER=	${PGSQL_DEFAULT}
.  endif

# We don't want to be :S,.,, the whole time when doing port version checks
PGSQL_VER_NODOT=	${PGSQL_VER:S,.,,}

# And now we are checking if we can use it
.   if defined(PGSQL${PGSQL_VER_NODOT}_LIBVER)
# Compat.  Please DO NOT use IGNORE_WITH_PGSQL!
.    if defined(IGNORE_WITH_PGSQL)
DEV_WARNING+=	"Do not set IGNORE_WITH_PGSQL, use the version argument to USES=pgsql"
.	for ver in ${IGNORE_WITH_PGSQL}
.		if (${PGSQL_VER} == ${ver})
IGNORE?=		cannot install: does not work with postgresql${PGSQL_VER_NODOT}-client (PostgreSQL ${IGNORE_WITH_PGSQL} not supported)
.		endif
.	endfor
.    endif # IGNORE_WITH_PGSQL

.if !defined(WANT_PGSQL) || ${WANT_PGSQL} == lib
LIB_DEPENDS+=	libpq.so.${PGSQL${PGSQL_VER_NODOT}_LIBVER}:${PORTSDIR}/databases/postgresql${PGSQL_VER_NODOT}-client
.endif

_USE_PGSQL_DEP=		client contrib docs pgtcl pltcl plperl server
_USE_PGSQL_DEP_client=	psql
_USE_PGSQL_DEP_contrib=	pgbench
_USE_PGSQL_DEP_docs=	postgresql${PGSQL_VER}-docs>0
_USE_PGSQL_DEP_pgtcl=	${LOCALBASE}/lib/pgtcl/pkgIndex.tcl
_USE_PGSQL_DEP_plperl=	postgresql${PGSQL_VER}-plperl>0
_USE_PGSQL_DEP_pltcl=	postgresql${PGSQL_VER}-pltcl>0
_USE_PGSQL_DEP_server=	postgres
.    if defined(WANT_PGSQL)
.      for depend in ${_USE_PGSQL_DEP}
.        if ${WANT_PGSQL:M${depend}}
BUILD_DEPENDS+=	${_USE_PGSQL_DEP_${depend}}:${PORTSDIR}/databases/postgresql${PGSQL_VER_NODOT}-${depend}
RUN_DEPENDS+=	${_USE_PGSQL_DEP_${depend}}:${PORTSDIR}/databases/postgresql${PGSQL_VER_NODOT}-${depend}
.        elif ${WANT_PGSQL:M${depend}\:*}
BUILD_DEPENDS+=	${NONEXISTENT}:${PORTSDIR}/databases/postgresql${PGSQL_VER_NODOT}-${depend}:${WANT_PGSQL:M${depend}\:*:C,^[^:]*\:,,}
.        endif
.      endfor
.    endif

.  else
IGNORE?=		cannot install: unknown PostgreSQL version: ${PGSQL_VER}
.  endif # Check for correct version
CPPFLAGS+=		-I${LOCALBASE}/include
LDFLAGS+=		-L${LOCALBASE}/lib

.endif #defined(_POSTMKINCLUDED) && !defined(Pgsql_Post_Include)
