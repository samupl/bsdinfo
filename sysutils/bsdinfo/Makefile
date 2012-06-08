# New ports collection makefile for:	bsdinfo
# Date created:        8 June 2012
# Whom:                samu <s@samu.pl>
#
# $FreeBSD$
#

PORTNAME=	bsdinfo
PORTVERSION=	0.1
CATEGORIES=	sysutils
MASTER_SITES=	http://cloud.github.com/downloads/samaelszafran/bsdinfo/

MAINTAINER=	s@samu.pl
COMMENT=	A simple utility to display system-based information

MAN1=		bsdinfo.1
MANCOMPRESSED=	yes

GNU_CONFIGURE=	yes

OPTIONS=        X256 "Build 256 color version" Off

.if !defined(WITH_X256)
CONFIGURE_ARGS+=--xterm-256

.endif

.include <bsd.port.options.mk>

.include <bsd.port.mk>
