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

#include "Display/Rtt_ShaderCompositeAdapter.h"

#include "Display/Rtt_Display.h"
#include "Display/Rtt_ShaderData.h"
#include "Display/Rtt_ShaderFactory.h"
#include "Display/Rtt_ShaderResource.h"
#include "Renderer/Rtt_Uniform.h"
#include "Rtt_LuaContext.h"

// ----------------------------------------------------------------------------

namespace Rtt
{

// ----------------------------------------------------------------------------

const ShaderCompositeAdapter&
ShaderCompositeAdapter::Constant()
{
	static const ShaderCompositeAdapter sAdapter;
	return sAdapter;
}

// ----------------------------------------------------------------------------

ShaderCompositeAdapter::ShaderCompositeAdapter()
{
}

StringHash *
ShaderCompositeAdapter::GetHash( lua_State *L ) const
{
    static const char *keys[] =
    {
        "",
    };
	static StringHash sHash( *LuaContext::GetAllocator( L ), keys, sizeof( keys ) / sizeof( const char * ), 0, 0, 0, __FILE__, __LINE__ );
	return &sHash;
}

int
ShaderCompositeAdapter::ValueForKey(
	const LuaUserdataProxy& sender,
	lua_State *L,
	const char *key ) const
{
	int result = 0;

	Rtt_ASSERT( key ); // Caller should check at the top-most level

	const ShaderComposite *object = (const ShaderComposite *)sender.GetUserdata();

	if ( ! object ) { return result; }

	Shader *child = object->GetNamedShader( key );
	
	if ( child )
	{
		if (object->IsTerminal(child))
		{
			child->GetData()->PushProxy(L);
		}
		else
		{
			child->PushProxy( L );
		}

		//Lazilly set the root node on the children so that
		//each child node gets access to invalidate the attached paint object
		if ( ! child->IsOutermostTerminal() && child != object )
		{
			child->SetRoot( object );
		}

		result = 1;
	}

	return result;
}

bool
ShaderCompositeAdapter::SetValueForKey(
	LuaUserdataProxy& sender,
	lua_State *L,
	const char *key,
	int valueIndex ) const
{
	bool result = false;

	// This is a no-op b/c you can only set values on the ShaderData themselves
	// If we add settable properties then we need to be more careful.
	//
	/*
	Rtt_ASSERT( key ); // Caller should check at the top-most level

	ShaderComposite *object = (ShaderComposite *)sender.GetUserdata();
	if ( ! object ) { return result; }
	
	// Find named shader
	Shader *child = object->GetNamedShader( key );
	if ( child )
	{
		// Ignore set requests on shader b/c cannot change graph
	}
	
	if ( ! result )
	{
		// Call Super::SetValueForKey() if any
	}
	*/

	return result;
}

void
ShaderCompositeAdapter::WillFinalize( LuaUserdataProxy& sender ) const
{
	ShaderComposite *data = (ShaderComposite *)sender.GetUserdata();
	if ( ! data ) { return; }
	
	data->DetachProxy();
}

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------

