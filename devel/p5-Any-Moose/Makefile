PORTNAME=	Any-Moose
PORTVERSION=	0.27
CATEGORIES=	devel perl5
MASTER_SITES=	CPAN
MASTER_SITE_SUBDIR=	CPAN:ETHER
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Perl extension for/to use Moose or Mouse modules

LICENSE=	artistic gpl
LICENSE_COMB=	dual

DEPRECATED=	Use devel/p5-Moo instead

USES=		perl5
USE_PERL5=	configure
NO_ARCH=	YES
NO_TEST=	yes

OPTIONS_DEFINE=	MOOSE MOUSE
OPTIONS_DEFAULT=	MOUSE
MOOSE_DESC=	Use Moose
MOUSE_DESC=	Use Mouse

.include <bsd.mport.options.mk>

.if ${PORT_OPTIONS:MMOOSE}
BUILD_DEPENDS+=	p5-Moose>0:devel/p5-Moose
RUN_DEPENDS+=	p5-Moose>0:devel/p5-Moose
.endif

.if ${PORT_OPTIONS:MMOUSE}
BUILD_DEPENDS+=	p5-Mouse>=0.40:devel/p5-Mouse
RUN_DEPENDS+=	p5-Mouse>=0.40:devel/p5-Mouse
.endif

.include <bsd.port.mk>
