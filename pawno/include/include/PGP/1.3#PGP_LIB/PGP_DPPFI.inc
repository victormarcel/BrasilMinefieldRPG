/*
*
*	-= PGP DEFINIÇÃO PADRÃO PARA FUNÇÕES INICIAIS =-
*	Protioso Gerenciamento de Pickups
*	Autor: Protioso ([VGS]Protioso_OC)
*
*/

#include <a_samp>
//      Definição do usuário
#include "PGP\PGP_USER_DEF"
//      Arquivos base
#include "PGP\1.3#PGP_LIB\#PGP_BASE\PGP_B.&DPB"
#include "PGP\1.3#PGP_LIB\#PGP_BASE\PGP_B.&1"
//      Arquivos para formulação padrão
#include "PGP\1.3#PGP_LIB\#PGP_FORMULAÇÃO\PGP_F.&FP"
#include "PGP\1.3#PGP_LIB\#PGP_FORMULAÇÃO\PGP_F.(FDS)"
#include "PGP\1.3#PGP_LIB\#PGP_FORMULAÇÃO\PGP_F.(FFD)"
#include "PGP\1.3#PGP_LIB\#PGP_FORMULAÇÃO\PGP_F.(FFJP)"
//-----------------------------------------------------------------------------|
stock pgp_ChecarPickups(playerid)
{
	for(new p=0; p<MAX_PGP; p++)
	{
		if(pgp_PickupPGPOn(p) == 1)
		{
		    if(PTP(1.0, playerid, PPickup[p][pgp_x], PPickup[p][pgp_y], PPickup[p][pgp_z]) == 1)
		    {
		        JogadorPickup[playerid] = p;
				if(PegouPickup[playerid] == 0) pgp_PegouPickup(playerid, p);
				if(PPickup[p][PMSGS] == 1 && GTJogador[playerid] == 0) pgp_PickGameText(p, playerid);
			}
			else if(JogadorPickup[playerid] > -1)
			{
			 	JogadorPickup[playerid] = -1;
                JogadorPickupPega[playerid] = -1;
			}
			if(PPickup[p][SPRaio] == 1 && PTP(PPickup[p][PRaio], playerid, PPickup[p][pgp_x], PPickup[p][pgp_y], PPickup[p][pgp_z]) == 1) pgp_JogadorEmRaio(playerid, p);
			else if(JogadorEmRaio[playerid] > -1) JogadorEmRaio[playerid] = -1;
		}
	}
}

stock PTP(Float:radi, playerid, Float:x, Float:y, Float:z)//PlayerToPoint (função feita por Astro/Denver)
{
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);
	tempposx = (oldposx -x);
	tempposy = (oldposy -y);
	tempposz = (oldposz -z);
	if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
	{
		return 1;
	}
	return 0;
}
