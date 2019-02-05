//#define FILTERSCRIPT

//#define YSI_NO_MODULES
//#define YSI_NO_OBJECTS
//#define YSI_NO_RACES
//#define YSI_NO_CHECKPOINTS
//#define YSI_NO_AREAS
//#define YSI_NO_GROUPS
//#define YSI_NO_PROPERTIES
//#define YSI_NO_ZONES

#include <a_samp>
#include <YSI/setup/YSI_master.own>
#include <YSI>

// Team stuff
new Attackers;
new Defenders;

// Checkpoint stuff
new CP_Plane;
new CP_A69;

// Color defines
#define COLOR_GREY 0xAFAFAFAA
#define COLOR_GREEN 0x33AA33AA
#define COLOR_RED 0xAA3333AA
#define COLOR_YELLOW 0xFFFF00AA

// Winner state
#define ATTACK_WIN 1
#define DEFENCE_WIN 2

// If the army defends the lab for this amount of time they win!
// Time is in minutes!
//new gRoundTime = 20;					// Round time - 20 mins
//new gRoundTime = 15;					// Round time - 15 mins
new gRoundTime = 10;					// Round time - 10 mins
//new gRoundTime = 5;					// Round time - 5 mins
//new gRoundTime = 2;					// Round time - 2 mins
//new gRoundTime = 1;					// Round time - 1 min

#if defined FILTERSCRIPT

Script_OnFilterScriptInit()
{
    print("\n------------------------------------");
    print(" YSI Filterscript by your name here");
    print("------------------------------------\n");

    ycmd(kill);
    ycmd("mycommand");
    Langs_AddLanguage("EN", "English");
    Langs_AddFile("core", "YSI");
    return 1;
}

Script_OnFilterScriptExit()
{
    return 1;
}

#else

main()
{
    print("\n-------------------------------------");
    print(" YSI Area 51 Recode by [AU]Hell_Demon");
    print("      Original Area 51 coded by");
    print("                 Mike");
    print("---------------------------------------\n");
}

#endif

Text_RegisterTag(tag_with_MY_KILL_HELP);

forward ycmd_kill(playerid, params[], help);
forward AddClasses();
forward DefenceWin();
forward GameModeExitFunc();

public ycmd_kill(playerid, params[], help)
{
    if (help) Text_Send(playerid, "MY_KILL_HELP");
    else SetPlayerHealth(playerid, 0.0);
    return 1;
}

Script_OnGameModeInit()
{
    // Don't use these lines if it's a filterscript
    SetGameModeText("Area 51 Break-in");
	ShowNameTags(1);
	ShowPlayerMarkers(0);
	SetWorldTime(0);
    AddClasses();
    SetTimer("DefenceWin", gRoundTime*60000, 0);
    
    Attackers = Group_Create("TEAM_ATTACK");
	Defenders = Group_Create("TEAM_DEFEND");
	
	CP_Plane = CreateCheckpoint(315.7353, 1035.6589, 1945.1191, 5.0);
	CP_A69 = CreateCheckpoint(268.5821, 1883.8224, -30.0938, 5.0);

    ycmd(kill);
    ycmd("mycommand");
    Langs_AddLanguage("EN", "English");
    Langs_AddFile("core", "YSI");
    return 1;
}

Command_(mycommand)
{
    // Your code here
    return 1;
}

Script_OnGameModeExit()
{
    Master_@Master();
    return 1;
}

Script_OnPlayerRequestClass(playerid, classid)
{
	SetupPlayerForClassSelection(playerid);
    switch (classid)
	{
		case 0:
	    {
			GameTextForPlayer(playerid, "~r~Attack", 1000, 3);
		}
	    case 1, 2:
        {
			GameTextForPlayer(playerid, "~g~Defence", 1000, 3);
		}
	}
    return 1;
}

SetupPlayerForClassSelection(playerid)
{
	SetPlayerInterior(playerid,9);
	SetPlayerFacingAngle(playerid,0.0);
	SetPlayerPos(playerid,315.7802,972.0253,1961.8705);
	SetPlayerCameraPos(playerid,315.7802,975.0253,1961.8705);
	SetPlayerCameraLookAt(playerid,315.7802,972.0253,1961.8705);
	return 1;
}

Script_OnPlayerRequestSpawnEx(playerid, classid)
{
	if(classid==0)
	{
		Checkpoint_AddPlayer(CP_Plane, playerid);
		Checkpoint_AddPlayer(CP_A69, playerid);
	}
	else
	{
	    Checkpoint_RemovePlayer(CP_Plane, playerid);
	    Checkpoint_RemovePlayer(CP_A69, playerid);
	}
    return 1;
}

Script_OnPlayerConnect(playerid)
{
    GameTextForPlayer(playerid,"~w~SA:MP Area51 Break-in!",4000,3);
	SetPlayerColor(playerid,COLOR_GREY);
	Checkpoint_RemovePlayer(CP_Plane, playerid);
	Checkpoint_RemovePlayer(CP_A69, playerid);
    return 1;
}

Script_OnPlayerDisconnect(playerid, reason)
{
    return 1;
}

SetPlayerToTeamColor(playerid)
{
	if(Group_HasPlayer(Attackers, playerid)==1)
	{
	    SetPlayerColor(playerid,COLOR_RED); // Red
	}
	else if(Group_HasPlayer(Defenders, playerid)==1)
	{
	    SetPlayerColor(playerid,COLOR_GREEN); // Green
	}
}

Script_OnPlayerSpawn(playerid)
{
	SetPlayerToTeamColor(playerid);
    return 1;
}

Script_OnPlayerDeath(playerid, killerid, reason)
{
    if (killerid != INVALID_PLAYER_ID)
	{
	    if(Group_HasPlayer(Attackers, playerid)==Group_HasPlayer(Attackers, killerid))
	    {
	        SetPlayerScore(killerid, GetPlayerScore(killerid) - 1);
		}
		else
		{
			SetPlayerScore(killerid, GetPlayerScore(killerid) + 1);
		}
	}
	SendDeathMessage(killerid, playerid, reason);

	SetPlayerColor(playerid,COLOR_GREY);
    return 1;
}

Script_OnVehicleSpawn(vehicleid)
{
    return 1;
}

Script_OnVehicleDeath(vehicleid, killerid)
{
    return 1;
}

Script_OnPlayerText(playerid, text[])
{
    return 1;
}

Script_OnPlayerPrivmsg(playerid, recieverid, text[])
{
    return 1;
}

Script_OnPlayerCommandText(playerid, cmdtext[])
{
    return 0;
}

Script_OnPlayerInfoChange(playerid)
{
    return 1;
}

Script_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    return 1;
}

Script_OnPlayerExitVehicle(playerid, vehicleid)
{
    return 1;
}

Script_OnPlayerStateChange(playerid, newstate, oldstate)
{
    return 1;
}

Script_OnPlayerEnterCheckpointEx(playerid, cpid)
{
	if(cpid == CP_Plane)
	{
	    GameTextForPlayer(playerid, "Now parachute to ~r~Area 51", 2000, 5);
        SetPlayerInterior(playerid,0);
        SetPlayerPos(playerid, 239.5148, 1813.7039, 500.6836);
	}
	
	if(cpid == CP_A69)
	{
	    EndTheRound(ATTACK_WIN);
	}
	    
    return 1;
}

Script_OnPlayerLeaveCheckpointEx(playerid, cpid)
{
    return 1;
}

Script_OnPlayerEnterRaceCheckpoint(playerid)
{
    return 1;
}

Script_OnPlayerLeaveRaceCheckpoint(playerid)
{
    return 1;
}

Script_OnRconCommand(cmd[])
{
    return 1;
}

Script_OnObjectMoved(objectid)
{
    return 1;
}

Script_OnPlayerObjectMoved(playerid, objectid)
{
    return 1;
}

Script_OnPlayerPickUpPickup(playerid, pickupid)
{
    return 1;
}

Script_OnPlayerSelectedMenuRow(playerid, row)
{
    return 1;
}

Script_OnPlayerExitedMenu(playerid)
{
    return 1;
}

Script_OnVehicleMod(vehicleid, componentid)
{
    return 1;
}

Script_OnVehiclePaintjob(vehicleid, paintjobid)
{
    return 1;
}

Script_OnVehicleRespray(vehicleid, color1, color2)
{
    return 1;
}

Script_OnPlayerLogin(playerid, yid)
{
    return 1;
}

Script_OnPlayerLogout(playerid)
{
    return 1;
}

Script_OnPlayerEnterArea(playerid, areaid)
{
    return 1;
}

Script_OnPlayerLeaveArea(playerid, areaid)
{
    return 1;
}

Script_OnRaceEnd(raceid)
{
    return 1;
}

Script_OnPlayerExitRace(playerid, raceid)
{
    return 1;
}

Script_OnPlayerFinishRace(playerid, raceid, position, prize, time)
{
    return 1;
}

public AddClasses()
{
	// Classes
	Class_AddWithGroupSet(Attackers, 111, 315.4792, 984.1290, 1959.1129, 353.5, 3, 0, 23, 1000, 25, 100); //Mafia skin in andromena - Attackers
	Class_AddWithGroupSet(Defenders, 287, 245.1233, 1859.1162, 14.0840, 358.717, 4, 0, 32, 1000, 31, 5000); // Army - Defender
	Class_AddWithGroupSet(Defenders, 70, 271.6828, 1873.8666, 8.7578, 229.4508, 4, 0, 24, 1000, 32, 1000); // Lab - Defender
	
	// Parachutes
	Pickup_Add(371, 319.3416, 1020.7169, 1950.6696);
	Pickup_Add(371, 312.6138, 1020.7346, 1950.6655);
}

EndTheRound(winner)
{
	switch (winner)
	{
	    case 1:
	    {
	        GameTextForAll("The attackers broke into Area 51.", 2000, 5);
	    }
	    case 2:
	    {
	        GameTextForAll("Area 51 was successfully defended.", 2000, 5);
	    }
	}
	SetTimer("GameModeExitFunc", 5000, 0);
}

public GameModeExitFunc()
{
	GameModeExit();
}

public DefenceWin()
{
	EndTheRound(DEFENCE_WIN);
}
