# Created by: Cheng-Lung Sung <clsung@FreeBSD.org>

PORTNAME=	JSON-Any
PORTVERSION=	1.39
CATEGORIES=	converters perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Perl Wrapper Class for the various JSON classes

LICENSE=	artistic gpl
LICENSE_COMB=	dual

TEST_DEPENDS=	p5-Cpanel-JSON-XS>=0:converters/p5-Cpanel-JSON-XS \
		p5-JSON>=0:converters/p5-JSON \
		p5-JSON-DWIW>=0:converters/p5-JSON-DWIW \
		p5-JSON-XS>=0:converters/p5-JSON-XS \
		p5-Test-Fatal>=0:devel/p5-Test-Fatal \
		p5-Test-Requires>=0:devel/p5-Test-Requires \
		p5-Test-Warnings>=0.009:devel/p5-Test-Warnings \
		p5-Test-Without-Module>=0.17:devel/p5-Test-Without-Module

# Author preference: Cpanel::JSON::XS > JSON::XS > JSON::PP > JSON > JSON::DWIW
OPTIONS_DEFINE=	CPANEL JSON_XS JSON_PP JSON JSON_DWIW
OPTIONS_DEFAULT=CPANEL
CPANEL_DESC=	Use Cpanel::JSON::XS
JSON_DESC=	Use JSON
JSON_DWIW_DESC=	Use JSON::DWIW
JSON_PP_DESC=	Use JSON::PP
JSON_XS_DESC=	Use JSON::XS

NO_ARCH=	yes
USES=		perl5
USE_PERL5=	configure

CPANEL_BUILD_DEPENDS=	p5-Cpanel-JSON-XS>=0:converters/p5-Cpanel-JSON-XS
CPANEL_RUN_DEPENDS=	p5-Cpanel-JSON-XS>=0:converters/p5-Cpanel-JSON-XS
JSON_BUILD_DEPENDS=	p5-JSON>=0:converters/p5-JSON
JSON_RUN_DEPENDS=	p5-JSON>=0:converters/p5-JSON
JSON_DWIW_BUILD_DEPENDS=p5-JSON-DWIW>=0:converters/p5-JSON-DWIW
JSON_DWIW_RUN_DEPENDS=	p5-JSON-DWIW>=0:converters/p5-JSON-DWIW
JSON_PP_BUILD_DEPENDS=	p5-JSON-PP>=0:converters/p5-JSON-PP
JSON_PP_RUN_DEPENDS=	p5-JSON-PP>=0:converters/p5-JSON-PP
JSON_XS_BUILD_DEPENDS=	p5-JSON-XS>=0:converters/p5-JSON-XS
JSON_XS_RUN_DEPENDS=	p5-JSON-XS>=0:converters/p5-JSON-XS

.include <bsd.port.mk>
