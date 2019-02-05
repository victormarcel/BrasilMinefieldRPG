/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                                                       *
*                                                                       *
*	        ******* Include - KHouse *******                       		*
*                                                                       *
*	         Ken's House Include Functions  (KHouse)               		*
*                                                                       *
*	            Autor: rjjj ou [iPs]Ken.	                            *
*				Agradecimentos: [iPs] Team. 		                    *
*                                                                       *
*                                                                       *
*                                                                       *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "a_samp.inc"


#define Limite_Casas 400



//* * * * * * * * * * * *
/*
Funções:


native EnableHousesEnterExits(playerid);
native AddStaticHouse(houseid,Float:EntradaX,Float:EntradaY,Float:EntradaZ,Float:SaidaX,Float:SaidaY,Float:SaidaZ,InteriorID,VirtualWorldID);
native SetHouseOwner(houseid,playerid);
native SetHouseFree(houseid,playerid);
native SetHousePrice(houseid,valor);
native SetHouseText(houseid,text[]);
native SetHouseRequiredScore(houseid,score);
native SetVehicleHouseInfo(houseid,modelid,Float:X,Float:Y,Float:Z,Float:Angulo,color1,color2);
native AddVehicleToHouse(houseid,modelid,Float:X,Float:Y,Float:Z,Float:Angulo,color1,color2);
native GetHouseOwner(houseid);
native GetHousePrice(houseid);
native GetHouseRequiredScore(houseid);
native GetHouseVehicleID(houseid);
native LockHouse(houseid);
native UnLockHouse(houseid);
native LockVehicleHouse(houseid)
native UnLockVehicleHouse(houseid)
native LockAllVehicleHouse();
native UnLockAllVehicleHouse();


*/
//* * * * * * * * * * * *//



#if defined _KHouse_included
	#endinput
#endif
#define _KHouse_included



#define SetVehicleHouseInfo AddVehicleToHouse
new CasasConstruidas = 0;
new bool:CasaCriada[Limite_Casas];
new Float:EntradaX_Casa[Limite_Casas];
new Float:EntradaY_Casa[Limite_Casas];
new Float:EntradaZ_Casa[Limite_Casas];
new Float:SaidaX_Casa[Limite_Casas];
new Float:SaidaY_Casa[Limite_Casas];
new Float:SaidaZ_Casa[Limite_Casas];
new InteriorID_Casa[Limite_Casas];
new VirtualWorldID_Casa[Limite_Casas];
new Text3D:Texto3D_Casa_ID[Limite_Casas][5];
new Dono_Casa[Limite_Casas][MAX_PLAYER_NAME];
new Dinheiro_Casa[Limite_Casas];
new TipoTexto_Casa[Limite_Casas][50];
new ScoreRequerido[Limite_Casas];
new Veiculo_Casa[Limite_Casas];
new Pickup_Casa[Limite_Casas];
new bool:CasaAberta[Limite_Casas];


forward EnableHousesEnterExits(playerid);


public EnableHousesEnterExits(playerid)
{
	if(CasasConstruidas != 0)
	{
		for(new CasaCheck = 1; CasaCheck <= CasasConstruidas; ++CasaCheck)
		{
		    if(CasaAberta[CasaCheck])
		    {
		        if(IsPlayerInRangeOfPoint(playerid,3.0,EntradaX_Casa[CasaCheck],EntradaY_Casa[CasaCheck],EntradaZ_Casa[CasaCheck]))
				{
					SetPlayerPos(playerid,SaidaX_Casa[CasaCheck],SaidaY_Casa[CasaCheck],SaidaZ_Casa[CasaCheck]);
					SetPlayerInterior(playerid,InteriorID_Casa[CasaCheck]);
					SetPlayerVirtualWorld(playerid,VirtualWorldID_Casa[CasaCheck]);
				}
				else if(IsPlayerInRangeOfPoint(playerid,3.0,SaidaX_Casa[CasaCheck],SaidaY_Casa[CasaCheck],SaidaZ_Casa[CasaCheck]))
				{
					if(GetPlayerVirtualWorld(playerid) == VirtualWorldID_Casa[CasaCheck])
					{
						if(GetPlayerInterior(playerid) == InteriorID_Casa[CasaCheck])
						{
							SetPlayerInterior(playerid,false);
							SetPlayerVirtualWorld(playerid,false);
							SetPlayerPos(playerid,EntradaX_Casa[CasaCheck],EntradaY_Casa[CasaCheck],EntradaZ_Casa[CasaCheck]);
						}
					}
				}
			}
		}
	}
	return 1;
}



stock AddStaticHouse(houseid,Float:EntradaX,Float:EntradaY,Float:EntradaZ,Float:SaidaX,Float:SaidaY,Float:SaidaZ,InteriorID,VirtualWorldID)
{
    if(houseid >= 1 && houseid < Limite_Casas)
	{
        if(!CasaCriada[houseid])
		{
			CasasConstruidas++;
			CasaCriada[houseid] = true;
            EntradaX_Casa[houseid] = EntradaX;
            EntradaY_Casa[houseid] = EntradaY;
            EntradaZ_Casa[houseid] = EntradaZ;
            SaidaX_Casa[houseid] = SaidaX;
            SaidaY_Casa[houseid] = SaidaY;
            SaidaZ_Casa[houseid] = SaidaZ;
            InteriorID_Casa[houseid] = InteriorID;
            VirtualWorldID_Casa[houseid] = VirtualWorldID;
            Texto3D_Casa_ID[houseid][0] = Create3DTextLabel("Dono: Ninguem.",0x00FF7FFF,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid],50,0);
            Texto3D_Casa_ID[houseid][1] = Create3DTextLabel("\nPreço: Indefinido.",0x00FF7FFF,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid],50,0);
            Texto3D_Casa_ID[houseid][2] = Create3DTextLabel("\n\nTipo: Indefinido.",0x00FF7FFF,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid],50,0);
            Texto3D_Casa_ID[houseid][3] = Create3DTextLabel("\n\n\nScore Requerido: 0.",0x00FF7FFF,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid],50,0);
            Texto3D_Casa_ID[houseid][4] = Create3DTextLabel("\n\n\n\nAperte F para entrar.",0x00FF7FFF,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid],50,0);
            Pickup_Casa[houseid] = CreatePickup(1273,23,EntradaX,EntradaY,EntradaZ);
		}
	}
	return true;
}


stock SetHouseOwner(houseid,playerid)
{
    if(houseid >= 1 && houseid < Limite_Casas)
    {
		if(CasaCriada[houseid])
		{
			new Welcome[50],ProprietarioCasa[MAX_PLAYER_NAME];
			GetPlayerName(playerid,ProprietarioCasa,sizeof(ProprietarioCasa));
			format(Welcome,50,"Dono: %s.",ProprietarioCasa);
			Delete3DTextLabel(Texto3D_Casa_ID[houseid][0]);
			strmid(Dono_Casa[houseid],ProprietarioCasa,false,strlen(ProprietarioCasa),MAX_PLAYER_NAME);
			Texto3D_Casa_ID[houseid][0] = Create3DTextLabel(Welcome,0x00FF7FFF,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid],50,0);
			DestroyPickup(Pickup_Casa[houseid]);
			Pickup_Casa[houseid] = CreatePickup(1318,23,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid]);
		}
	}
	return true;
}



stock SetHouseFree(houseid)
{
    if(houseid >= 1 && houseid < Limite_Casas)
	{
		if(CasaCriada[houseid])
		{
			Delete3DTextLabel(Texto3D_Casa_ID[houseid][0]);
			DestroyPickup(Pickup_Casa[houseid]);
			strmid(Dono_Casa[houseid],"Ninguem",false,7,MAX_PLAYER_NAME);
			Texto3D_Casa_ID[houseid][0] = Create3DTextLabel("Dono: Ninguem.",0x00FF7FFF,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid],50,0);
			Pickup_Casa[houseid] = CreatePickup(1273,23,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid]);
		}
	}
	return true;
}


stock SetHousePrice(houseid,valor)
{
    if(houseid >= 1 && houseid < Limite_Casas)
    {
		if(CasaCriada[houseid])
		{
			new Valor[50];
			format(Valor,50,"\nPreço: %d.",valor);
			Delete3DTextLabel(Texto3D_Casa_ID[houseid][1]);
			Texto3D_Casa_ID[houseid][1] = Create3DTextLabel(Valor,0x00FF7FFF,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid],50,0);
			Dinheiro_Casa[houseid] = valor;
		}
	}
	return true;
}


stock SetHouseText(houseid,text[])
{
    if(houseid >= 1 && houseid < Limite_Casas)
    {
		if(CasaCriada[houseid])
		{
			new Texto_BemVindo[50];
			format(Texto_BemVindo,50,"\n\nTipo: %s.",text);
			Delete3DTextLabel(Texto3D_Casa_ID[houseid][2]);
			strmid(TipoTexto_Casa[houseid],text,false,strlen(text),50);
			Texto3D_Casa_ID[houseid][2] = Create3DTextLabel(Texto_BemVindo,0x00FF7FFF,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid],50,0);
		}
	}
	return true;
}


stock SetHouseRequiredScore(houseid,score)
{
    if(houseid >= 1 && houseid < Limite_Casas)
    {
		if(CasaCriada[houseid])
		{
			new Score_Requerido[50];
			format(Score_Requerido,50,"\n\n\nScore Requerido: %d.",score);
			Delete3DTextLabel(Texto3D_Casa_ID[houseid][3]);
			ScoreRequerido[houseid] = score;
			Texto3D_Casa_ID[houseid][3] = Create3DTextLabel(Score_Requerido,0x00FF7FFF,EntradaX_Casa[houseid],EntradaY_Casa[houseid],EntradaZ_Casa[houseid],50,0);
		}
	}
	return true;
}


stock AddVehicleToHouse(houseid,modelid,Float:X,Float:Y,Float:Z,Float:Angulo,color1,color2)
{
    if(houseid >= 1 && houseid < Limite_Casas)
    {
		if(CasaCriada[houseid])
		{
			DestroyVehicle(Veiculo_Casa[houseid]);
			Veiculo_Casa[houseid] = CreateVehicle(modelid,X,Y,Z,Angulo,color1,color2,60000);
			SetVehicleToRespawn(Veiculo_Casa[houseid]);
		}
	}
	return true;
}


stock LockHouse(houseid)
{
	if(CasaCriada[houseid])
	{
		CasaAberta[houseid] = false;
	}
	return true;
}

stock UnLockHouse(houseid)
{
	if(CasaCriada[houseid])
	{
		CasaAberta[houseid] = true;
	}
	return true;
}


stock LockVehicleHouse(houseid)
{
	if(CasaCriada[houseid])
	{
		new maquina, luzes, alarme, portas, capota, portamala, objective;
		GetVehicleParamsEx(Veiculo_Casa[houseid], maquina, luzes, alarme, portas, capota, portamala, objective);
		SetVehicleParamsEx(Veiculo_Casa[houseid], maquina, luzes, alarme, true, capota, portamala, objective);
	}
	return true;
}


stock LockAllVehicleHouse()
{
    for(new x = 1; x <= CasasConstruidas; x++)
    {
		if(CasaCriada[x])
		{
			LockVehicleHouse(x);
		}
	}
	return true;
}

stock UnLockAllVehicleHouse()
{
    for(new x = 1; x <= CasasConstruidas; x++)
    {
		if(CasaCriada[x])
		{
			UnLockVehicleHouse(x);
		}
	}
	return true;
}

stock UnLockVehicleHouse(houseid)
{
	if(CasaCriada[houseid])
	{
		new maquina, luzes, alarme, portas, capota, portamala, objective;
		GetVehicleParamsEx(Veiculo_Casa[houseid], maquina, luzes, alarme, portas, capota, portamala, objective);
		SetVehicleParamsEx(Veiculo_Casa[houseid], maquina, luzes, alarme, false, capota, portamala, objective);
	}
	return true;
}


stock GetHouseOwner(houseid)
{
	new OwnerName[MAX_PLAYER_NAME];
	if(CasaCriada[houseid])
	{
		format(OwnerName,MAX_PLAYER_NAME,"%s",Dono_Casa[houseid]);
	}
	else
	{
		format(OwnerName,MAX_PLAYER_NAME,"Casa Inválida.");
	}
	return OwnerName;
}

stock GetHouseText(houseid)
{
	new TipoTexto[50];
	if(CasaCriada[houseid])
	{
		format(TipoTexto,50,"%s",TipoTexto_Casa[houseid]);
	}
	else
	{
		format(TipoTexto,50,"Casa Inválida.");
	}
	return TipoTexto;
}


stock GetHousePrice(houseid)    return ((CasaCriada[houseid])?(Dinheiro_Casa[houseid]):0);


stock GetHouseVehicleID(houseid)		return ((CasaCriada[houseid])?(Veiculo_Casa[houseid]:0);


stock GetHouseRequiredScore(houseid)    return ((CasaCriada[houseid])?(ScoreRequerido[houseid]):0);






