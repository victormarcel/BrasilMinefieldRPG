new Pickup1;
Pickup1 = CreatePickup(358, 21, 2357.0881,61.2717,42.9320, 0);
public OnPlayerPickUpPickup(playerid, pickupid)
{

if(pickupid == Pickup1)
{
SetTimerEx("Reaparecerpick", 60000,false,"i",playerid);
DestroyPickup(Pickup1);
AddStaticVehicleEx(500,2357.0881,61.2717,42.9320,189.65490723,-1,-1,15); //Mesa
SendClientMessage(playerid, -1,"Você acho um Carro escondido.");
return 1;
}
return 1;
}

forward Reaparecerpick(playerid);
public Reaparecerpick(playerid)
{
	Pickup1 = CreatePickup(358, 2, 2357.0881,61.2717,42.9320, -1);
	return 1;
}

