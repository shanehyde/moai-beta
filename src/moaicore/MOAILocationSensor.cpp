// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAILocationSensor.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@brief <tt>( returns ) func ( self )</tt>\n
\n
	Description of method Coming Soon(tm).
	@param self (in)
	@param y (out)
*/
int MOAILocationSensor::_getLocation ( lua_State* L ) {
	LUA_SETUP ( MOAILocationSensor, "U" )
	
	lua_pushnumber ( state, self->mLongitude );
	lua_pushnumber ( state, self->mLatitude );
	lua_pushnumber ( state, self->mHAccuracy );
	lua_pushnumber ( state, self->mAltitude );
	lua_pushnumber ( state, self->mVAccuracy );
	lua_pushnumber ( state, self->mSpeed );
	
	return 6;
}

//----------------------------------------------------------------//
/**	@brief <tt>( returns ) func ( self )</tt>\n
\n
	Description of method Coming Soon(tm).
	@param self (in)
	@param y (out)
*/
int MOAILocationSensor::_setCallback ( lua_State* L ) {
	LUA_SETUP ( MOAILocationSensor, "U" )
	
	self->mCallback.SetRef ( state, 2, false );
	
	return 0;
}

//================================================================//
// MOAILocationSensor
//================================================================//

//----------------------------------------------------------------//
void MOAILocationSensor::HandleEvent ( USStream& eventStream ) {

	this->mLongitude	= eventStream.Read < double >();
	this->mLatitude		= eventStream.Read < double >();
	this->mAltitude		= eventStream.Read < double >();
	this->mHAccuracy	= eventStream.Read < float >();
	this->mVAccuracy	= eventStream.Read < float >();
	this->mSpeed		= eventStream.Read < float >();
	
	if ( this->mCallback ) {
		USLuaStateHandle state = this->mCallback.GetSelf ();
		lua_pushnumber ( state, this->mLongitude );
		lua_pushnumber ( state, this->mLatitude );
		lua_pushnumber ( state, this->mHAccuracy );
		lua_pushnumber ( state, this->mAltitude );
		lua_pushnumber ( state, this->mVAccuracy );
		lua_pushnumber ( state, this->mSpeed );
		state.DebugCall ( 6, 0 );
	}
}

//----------------------------------------------------------------//
MOAILocationSensor::MOAILocationSensor () :
	mLongitude ( 0.0 ),
	mLatitude ( 0.0 ),
	mAltitude ( 0.0 ),
	mHAccuracy ( 0.0f ),
	mVAccuracy ( 0.0f ),
	mSpeed ( 0.0f ) {

	RTTI_SINGLE ( MOAISensor )
}

//----------------------------------------------------------------//
MOAILocationSensor::~MOAILocationSensor () {
}

//----------------------------------------------------------------//
void MOAILocationSensor::RegisterLuaClass ( USLuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void MOAILocationSensor::RegisterLuaFuncs ( USLuaState& state ) {

	LuaReg regTable [] = {
		{ "getLocation",		_getLocation },
		{ "setCallback",		_setCallback },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAILocationSensor::WriteEvent ( USStream& eventStream, double longitude, double latitude, double altitude, float hAccuracy, float vAccuracy, float speed ) {

	eventStream.Write < double >( longitude );
	eventStream.Write < double >( latitude );
	eventStream.Write < double >( altitude );
	eventStream.Write < float >( hAccuracy );
	eventStream.Write < float >( vAccuracy );
	eventStream.Write < float >( speed );
}