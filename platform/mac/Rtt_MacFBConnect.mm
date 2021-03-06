//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Corona Labs Inc.
// Contact: support@coronalabs.com
//
// This file is part of the Corona game engine.
//
// Commercial License Usage
// Licensees holding valid commercial Corona licenses may use this file in
// accordance with the commercial license agreement between you and 
// Corona Labs Inc. For licensing terms and conditions please contact
// support@coronalabs.com or visit https://coronalabs.com/com-license
//
// GNU General Public License Usage
// Alternatively, this file may be used under the terms of the GNU General
// Public license version 3. The license is as published by the Free Software
// Foundation and appearing in the file LICENSE.GPL3 included in the packaging
// of this file. Please review the following information to ensure the GNU 
// General Public License requirements will
// be met: https://www.gnu.org/licenses/gpl-3.0.html
//
// For overview and more information on licensing please refer to README.md
//
//////////////////////////////////////////////////////////////////////////////

#include "Core/Rtt_Build.h"

#include "Rtt_MacFBConnect.h"

// ----------------------------------------------------------------------------

namespace Rtt
{

// ----------------------------------------------------------------------------

MacFBConnect::MacFBConnect()
:	Super()
{
}

void
MacFBConnect::Login( const char *appId, const char *permissions[], int numPermissions ) const
{
	Rtt_TRACE_SIM( ( "WARNING: facebook.login() not supported on the simulator.\n" ) );
}

void
MacFBConnect::Logout() const
{
	Rtt_TRACE_SIM( ( "WARNING: facebook.logout() not supported on the simulator.\n" ) );
}

void
MacFBConnect::Request( lua_State *L, const char *path, const char *httpMethod, int index ) const
{
	Rtt_TRACE_SIM( ( "WARNING: facebook.request() not supported on the simulator.\n" ) );
}

void
MacFBConnect::RequestOld( lua_State *L, const char *method, const char *httpMethod, int index ) const
{
	Rtt_TRACE_SIM( ( "WARNING: facebook.requestOld() not supported on the simulator.\n" ) );
}

void
MacFBConnect::ShowDialog( lua_State *L, int index ) const
{
	Rtt_TRACE_SIM( ( "WARNING: facebook.showDialog() not supported on the simulator.\n" ) );
}

void
MacFBConnect::PublishInstall( const char *appId ) const
{
	Rtt_TRACE_SIM( ( "WARNING: facebook.publishInstall() not supported on the simulator.\n" ) );
}

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------

