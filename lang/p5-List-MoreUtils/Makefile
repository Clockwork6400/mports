# Created by: Lars Thegler <lth@FreeBSD.org>

PORTNAME=	List-MoreUtils
PORTVERSION=	0.428
CATEGORIES=	lang perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Provide the stuff missing in List::Util

LICENSE=	apache2
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-Exporter-Tiny>=0.038:devel/p5-Exporter-Tiny \
		p5-List-MoreUtils-XS>=0.426:lang/p5-List-MoreUtils-XS
TEST_DEPENDS=	p5-Test-LeakTrace>=0:devel/p5-Test-LeakTrace

NO_ARCH=	yes
USES=		perl5
USE_PERL5=	configure

.include <bsd.port.mk>
