/* Easy TextDrawCountDown by Littlejohny (TextDrawCountDown) */
/*         Copyright by Littlejohny 2009           */
/*         Credits: E4sTsId3 (Hilfe)               */

#if defined _TextDrawCountDown_included
  #endinput
#endif

#include <a_samp>

#define _TextDrawCountDown_included
#pragma library TextDrawCountDown

#define RED 0xE60000FF

new Text:tdcd;
new cdtime;
new tdtimer;
new COUNT_ON = 0;
forward TextDrawCountDown(seconds);
forward cdtimer();
forward HideCountDown();

stock TextDrawCountDownInit()
{
    tdcd = TextDrawCreate(320.000000,410.000000, "TDCD");
	TextDrawTextSize(tdcd,636.000000,824.000000);
	TextDrawAlignment(tdcd, 2);
	TextDrawFont(tdcd,3);
	TextDrawLetterSize(tdcd,0.499999,1.800000);
	TextDrawColor(tdcd,0xffffffff);
	TextDrawSetProportional(tdcd,2);
	TextDrawSetShadow(tdcd,1);
	TextDrawSetOutline(tdcd, 1);
	return 1;
}

public TextDrawCountDown(seconds)
{
    if(COUNT_ON == 1) { return 1; }
    
	cdtime = seconds;
	if(cdtime < 1 || cdtime > 30)
	{
	    cdtime = 0;
		return 1;
	}
	tdtimer = SetTimer("cdtimer",1000,1);
	COUNT_ON = 1;
	return 1;
}

public cdtimer()
{
   	new str[256];
	
	if(cdtime <= 30 && cdtime >= 1)
	{
	    format(str,sizeof(str), "~w~CountDown: ~r~%d ~w~second/s",cdtime);
	    TextDrawSetString(tdcd, str);
	    TextDrawShowForAll(tdcd);
	    cdtime--;
	    PlaySoundForAll(1058, 0.0, 0.0, 0.0);
	}
	else if(cdtime == 0)
	{
			KillTimer(tdtimer);
			TextDrawSetString(tdcd, "~w~CountDown: ~g~GO !~g~ GO !~g~ GO !");
			TextDrawShowForAll(tdcd);
			SetTimer("HideCountDown", 3000, 0);
			PlaySoundForAll(1056, 0.0, 0.0, 0.0);
			COUNT_ON = 0;
	}
	return 1;
}

public HideCountDown()
{
	TextDrawHideForAll(tdcd);
	return 1;
}

PlaySoundForAll(soundid, Float:x, Float:y, Float:z) {
    for (new i=0; i<MAX_PLAYERS; i++)
	{
    	if (IsPlayerConnected(i))
		{
    		PlayerPlaySound(i, soundid, x, y, z);
		}
	}
}