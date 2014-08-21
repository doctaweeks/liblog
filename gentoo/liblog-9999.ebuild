# Copyright 1999-2014 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI=5

inherit eutils

DESCRIPTION="This is a sample skeleton ebuild file"
HOMEPAGE="http://foo.example.org/"
if [[ ${PV} == "9999" ]] ; then
        EGIT_REPO_URI="git://dev.danweeks.net/liblog.git"
		EGIT_BOOTSTRAP="autogen.sh"
        SRC_URI=""
        inherit git-2
else
        SRC_URI=""
fi


LICENSE=""

SLOT="0"

KEYWORDS="amd64 x86"
