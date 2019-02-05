// This MUST go ABOVE "#include <YSI>"
//#define FILTERSCRIPT

#include <YSI>

main()
{
	print("\n----------------------------------");
	print(" Advanced class selection example");
	print("----------------------------------\n");
}

new
	// City groups
	gGroupNC,
	gGroupLS,
	gGroupLV,
	gGroupSF,
	// Fake admin group
	gGroupAdmin;

// Kill yourself
Command_(kill)
{
	if (help)
	{
		// Player typed "/help kill"
	}
	else
	{
		// Player typed "/kill"
		SetPlayerHealth(playerid, 0.0);
	}
	return 1;
}

// Fake Login, used in place of an admin system
Command_(fl)
{
	if (help)
	{
		// Player typed "/help fl"
	}
	else
	{
		// Player typed "/fl"
		Group_AddPlayer(gGroupAdmin, playerid);
	}
	return 1;
}

public OnGameModeInit()
{
	//  Group setup
	// =============
	
	// Create the groups to save class selection
	gGroupNC = Group_Create(); // No city
	gGroupLV = Group_Create(); // Las Venturas
	gGroupLS = Group_Create(); // Los Santos
	gGroupSF = Group_Create(); // San Fierro
	
	// Create the group that our "admins" go in
	// This group is named so will be saved for registered players automatically
	gGroupAdmin = Group_Create("Admin");
	
	//  City selection
	// ================
	
	// Add classes to the no city group so people with no city can select one
	// Each class adds the player to one of the individual city groups
	Class_AddEx(gGroupNC, gGroupLV, 0, 0.0, 0.0, 0.0, 0.0);
	Class_AddEx(gGroupNC, gGroupLS, 0, 0.0, 0.0, 0.0, 0.0);
	Class_AddEx(gGroupNC, gGroupSF, 0, 0.0, 0.0, 0.0, 0.0);
	
	//  Skin selection
	// ================
	
	// Las Venturas skins
	
	// Only people in the LV group can see these skins
	// Location borrowed from LVDM
	// Spawns with no weapons
	Class_AddForGroup(gGroupLV, 171, 2150.0186, 2734.2297, 11.1763, 0.0);
	// Spawns with 1 weapon
	Class_AddForGroup(gGroupLV, 83,  2150.0186, 2734.2297, 11.1763, 0.0, WEAPON_COLT45, 100);
	// Spawns with armour (note armour is best last)
	Class_AddForGroup(gGroupLV, 172, 2150.0186, 2734.2297, 11.1763, 0.0, WEAPON_ARMOUR, 1);
	
	// Los Santos skins
	
	// Only people in the LS group can see these skins
	// Spawns with 3 weapons
	Class_AddForGroup(gGroupLS, 106, 667.0339, -1275.7842, 13.4609, 0.0, WEAPON_COLT45, 100, WEAPON_SAWEDOFF, 20, WEAPON_MINIGUN, 1000);
	// Spawns with 4 weapons
	Class_AddForGroup(gGroupLS, 104, 667.0339, -1275.7842, 13.4609, 0.0, WEAPON_COLT45, 100, WEAPON_SAWEDOFF, 20, WEAPON_MINIGUN, 1000, WEAPON_M4, 300);
	// Spawns with 7 weapons
	Class_AddForGroup(gGroupLS, 115, 667.0339, -1275.7842, 13.4609, 0.0, WEAPON_COLT45, 100, WEAPON_SAWEDOFF, 20, WEAPON_MINIGUN, 1000, WEAPON_M4, 300, WEAPON_UZI, 150, WEAPON_SNIPER, 10, WEAPON_FIREEXTINGUISHER, 5);
	
	// San Fierro skins
	
	// Only people in the SF group can see these skins
	// Borrowed from SFTDM
	// Spawns with 4 weapons and armour (note armour is best last)
	Class_AddForGroup(gGroupSF, 260, -2062.5583, 237.4662, 35.7149, 0.0, WEAPON_COLT45, 100, WEAPON_SAWEDOFF, 20, WEAPON_MINIGUN, 1000, WEAPON_M4, 300, WEAPON_ARMOUR, 1);
	// Spawns with 1 weapon and armour (note armour is best last)
	Class_AddForGroup(gGroupSF, 249, -2062.5583, 237.4662, 35.7149, 0.0, WEAPON_COLT45, 100, WEAPON_ARMOUR, 1);
	// Spawns with no weapons
	Class_AddForGroup(gGroupSF, 259, -2062.5583, 237.4662, 35.7149, 0.0);
	
	// Admin skin
	
	// This skin can be selected only be anyone who has previously typed "/fl"
	// This skin is always visible (wether in city or skin selection)
	Class_AddForGroup(gGroupAdmin, 217, 1958.0, 1343.0, 15.0, 269.0);
	
	//  Other stuff
	// =============
	
	// Set up languages
	Langs_AddFile("core", "YSI");
	Langs_AddLanguage("NL", "Nederlands");
	Langs_AddLanguage("EN", "English");
	
	// Add commands
	ycmd("kill");
	ycmd("fl");
	
	// End
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	switch (classid)
	{
		case 0:
		{
			// Las Venturas
		 	SetPlayerInterior(playerid, 0);
			SetPlayerPos(playerid, 258.4893, -41.4008, 1002.0234);
			SetPlayerCameraPos(playerid, 947.2557, 2586.8577, 17.2663);
			SetPlayerCameraLookAt(playerid, 959.7480, 2577.1262, 23.2179);
		}
		case 1:
		{
			// Los Santos
		 	SetPlayerInterior(playerid, 0);
			SetPlayerPos(playerid, 1414.0569, -879.7341, 70.3589);
			SetPlayerCameraPos(playerid, 1414.0569, -879.7341, 71.3589);
			SetPlayerCameraLookAt(playerid, 1415.6584, -821.6124, 76.4726);
		}
		case 2:
		{
			// San Fierro
		 	SetPlayerInterior(playerid, 0);
			SetPlayerPos(playerid, -1786.5815, -575.8611, 16.8192);
			SetPlayerCameraPos(playerid, -1786.5815, -575.8611, 16.8192);
			SetPlayerCameraLookAt(playerid, -1767.5608, -575.3600, 26.9292);
		}
		default:
		{
			// Skin
			// Borrowed from LVDM
		 	SetPlayerInterior(playerid, 14);
			SetPlayerPos(playerid, 258.4893, -41.4008, 1002.0234);
			SetPlayerFacingAngle(playerid, 270.0);
			SetPlayerCameraPos(playerid, 256.0815, -43.0475, 1004.0234);
			SetPlayerCameraLookAt(playerid, 258.4893, -41.4008, 1002.0234);
		}
	}
	return 1;
}

public OnPlayerRequestSpawnEx(playerid, classid) // Added extra
{
	// return 0 - Don't allow the spawn
	// return 1 - Allow the spawn
	// return -1 - Don't allow the spawn and re-process the current class
	
	// -1 is used here to show a different skin as they've selected a city
	// thus their group has changed, thus their current skin selection
	// options have changed
	if (classid < 3)
	{
		// City selection
		// Remove from the no city group
		Group_RemovePlayer(gGroupNC, playerid);
		// Redo selection with new groups
		return -1;
	}
	return 1;
}

public OnPlayerConnect(playerid)
{
	// Add them to the no city group as they don't have a city yet
	Group_AddPlayer(gGroupNC, playerid);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	// Reset the groups
	Group_AddPlayer(gGroupNC, playerid);
	Group_RemovePlayer(gGroupLS, playerid);
	Group_RemovePlayer(gGroupLV, playerid);
	Group_RemovePlayer(gGroupSF, playerid);
	
	// Reset the interior
	SetPlayerInterior(playerid, 0);
	return 1;
}

