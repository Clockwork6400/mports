PORTNAME=	DateTime-Format-MySQL
PORTVERSION=	0.0701
CATEGORIES=	devel perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Parse and format MySQL dates and times
WWW=		https://metacpan.org/release/DateTime-Format-MySQL

LICENSE=	artistic gpl+
LICENSE_COMB=	dual

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-DateTime>=0:devel/p5-DateTime \
		p5-DateTime-Format-Builder>=0.6:devel/p5-DateTime-Format-Builder

USES=		perl5
USE_PERL5=	modbuild

NO_TEST=	yes

.include <bsd.port.mk>
