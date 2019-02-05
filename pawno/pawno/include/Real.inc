#include a_samp

#define VERDE 0x33AA33AA

new Real[MAX_PLAYERS];
new Text:TextReal[MAX_PLAYERS];

forward GivePlayerReal(playerid, real);
forward GetPlayerReal(playerid);
forward ResetPlayerReal(playerid);

public GivePlayerReal(playerid, real)
{
	TextDrawHideForPlayer(playerid, TextReal[playerid]);
	Real[playerid] += real;
	new str[256];
	format(str, 256, "~g~R$~r~:~w~%d", Real[playerid]);
	TextReal[playerid] = TextDrawCreate(499.600,101.0000,str);
	TextDrawColor(TextReal[playerid], VERDE);
	TextDrawLetterSize(TextReal[playerid], 0.600, 2.1);
	TextDrawFont(TextReal[playerid], 3);
	TextDrawBackgroundColor(TextReal[playerid], 0x00000AA);
	TextDrawSetOutline(TextReal[playerid], 2);
	TextDrawShowForPlayer(playerid,TextReal[playerid]);
	return 1;
}

public GetPlayerReal(playerid)
{
	return Real[playerid];
}

public ResetPlayerReal(playerid)
{
	Real[playerid] = 0;
	return Real[playerid];
}