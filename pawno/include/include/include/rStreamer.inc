/*
*
*
*	rStreamer v1.0 by [WsR]RyDeR
*
*/

#include <a_samp>


stock CreateStreamedObject(oID,Float:X,Float:Y,Float:Z,Float:rX,Float:rY,Float:rZ)
{
	CallRemoteFunction("R_CreateStreamedObject","iffffff",oID,Float:X,Float:Y,Float:Z,Float:rX,Float:rY,Float:rZ);
	return 1;
}