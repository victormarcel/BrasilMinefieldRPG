/*  
	xStreamer by Boylett
 */

#if defined _xstreamer_included
	#endinput
#endif
#define _xstreamer_included
#pragma library xstreamer

#include <a_samp>

//------------------------------------------------------------------------------

native CreateStreamedObject(modelid,Float:xdrakon,Float:ydrakon,Float:zdrakon,Float:rx,Float:ry,Float:rz,virtualworld = 0,interior = 0);
native DestroyStreamedObject(objectid);
native MoveStreamedObject(objectid,Float:xdrakon,Float:ydrakon,Float:zdrakon,Float:speed);
native StopStreamedObject(objectid);
native DestroyObjectsCreatedByMe();
native StreamObjects(playerid,Float:xdrakon,Float:ydrakon,Float:zdrakon,virtualworld = 0,interior = 0);
native UpdateMovingObjects();

forward OnStreamedObjectMoved(objectid);

stock xStreamer_SetPlayerPos(playerid,Float:xdrakon,Float:ydrakon,Float:zdrakon)
{
	UpdateMovingObjects();
	StreamObjects(playerid,xdrakon,ydrakon,zdrakon,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid));
	SetPlayerPos(playerid,xdrakon,ydrakon,zdrakon);
}

stock xStreamer_SetPlayerInterior(playerid,interiorid)
{
	new
		Float:xdrakon,
		Float:ydrakon,
		Float:zdrakon;
	GetPlayerPos(playerid,xdrakon,ydrakon,zdrakon);
	UpdateMovingObjects();
	StreamObjects(playerid,xdrakon,ydrakon,zdrakon,GetPlayerVirtualWorld(playerid),interiorid);
	SetPlayerInterior(playerid,interiorid);
}

stock xStreamer_SetPlayerVirtualWorld(playerid,vwid)
{
	new
		Float:xdrakon,
		Float:ydrakon,
		Float:zdrakon;
	GetPlayerPos(playerid,xdrakon,ydrakon,zdrakon);
	UpdateMovingObjects();
	StreamObjects(playerid,xdrakon,ydrakon,zdrakon,vwid,GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(playerid,vwid);
}

#if !defined DONT_REPLACE_NATIVES

#define SetPlayerPos xStreamer_SetPlayerPos
#define SetPlayerInterior xStreamer_SetPlayerInterior
#define SetPlayerVirtualWorld xStreamer_SetPlayerVirtualWorld
#define CreateObject CreateStreamedObject
#define DestroyObject DestroyStreamedObject
#define MoveObject MoveStreamedObject
#define StopObject StopStreamedObject

#endif