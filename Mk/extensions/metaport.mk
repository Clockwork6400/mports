#
# Sets the default variables to handle metaports
#
# Feature:	metaport
# Usage:	USES=metaport
#
# Take no arguments

.if !defined(_INCLUDE_USES_METAPORT_MK)
_INCLUDE_USES_METAPORT_MK=	yes

MASTER_SITES=	#
DISTFILES=	#
EXTRACT_ONLY=	#
NO_BUILD=	yes
NO_MTREE=	yes
NO_ARCH=	yes

do-install: #nothing

.endif
