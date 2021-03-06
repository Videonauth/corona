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

#include "Rtt_AppPackagerFactory.h"

#include "Rtt_WebAppPackager.h"

#include <string>

// ----------------------------------------------------------------------------

namespace Rtt
{

// ----------------------------------------------------------------------------

#if defined(CORONABUILDER_HTML5)

AppPackagerParams*
AppPackagerFactory::CreatePackagerParamsHTML5(
	lua_State *L,
	int index,
	TargetDevice::Platform targetPlatform,
	TargetDevice::Version targetPlatformVersion,
	const char *appName,
	const char *version,
	const char *certificatePath,
	const char *projectPath,
	const char *dstPath,
	const char *sdkPath,
	const char *customBuildId,
	const char *templateType ) const
{
	AppPackagerParams *result = NULL;

	if(targetPlatform != TargetDevice::kWebPlatform)
	{
		Rtt_ASSERT_NOT_REACHED();
		return NULL;
	}

	bool createFBInstantArchive = false;
	lua_getfield(L, index, "createFBInstantArchive");
	if(lua_type(L, -1) == LUA_TBOOLEAN)
	{
		createFBInstantArchive = lua_toboolean(L, -1);
	}
	lua_pop(L, 1);

	bool includeStandardResources = true;
	lua_getfield(L, index, "includeStandardResources");
	if(lua_type(L, -1) == LUA_TBOOLEAN)
	{
		includeStandardResources = lua_toboolean(L, -1);
	}
	lua_pop(L, 1);

	String webtemplate;
	lua_getfield(L, index, "webtemplate");
	if(lua_type(L, -1) == LUA_TSTRING)
	{
		webtemplate.Set(lua_tostring(L, -1));
	}
	lua_pop(L,1);

	result = new WebAppPackagerParams(appName,
									  version,
									  NULL,
									  NULL,
									  projectPath,
									  dstPath,
									  NULL,
									  targetPlatform,
									  targetPlatformVersion,
									  TargetDevice::kWebGenericBrowser,
									  customBuildId,
									  NULL,
									  "bundleId",
									  true,
									  includeStandardResources,
									  webtemplate.GetString(),
										createFBInstantArchive);


	if ( ! result )
	{
		fprintf( stderr, "ERROR: Unsupported platform: %s\n", TargetDevice::StringForPlatform( targetPlatform ) );
	}

	return result;
}

#endif // defined(CORONABUILDER_HTML5)

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------

