/*
*
*	-= PDS INCLUDE =-
*	Protioso Dinheiro Secundário
*
*	Autor: Protioso ([VGS]Protioso_OC)
*  	Primeira versão: 24 de maio de 2010 - 1.0
*   Atualizações:
*                   12 de junho de 2010 - 1.2 (versão em uso)
*
*/

#include "PGD"

#if !defined MAX_PDS_ARQ_CHAR
	#define MAX_PDS_ARQ_CHAR 64 // máximo de caracteres que o nome do arquivo pode ter
#endif
#if !defined PDS_ARQUIVO_SALVAR
	#define PDS_ARQUIVO_SALVAR "%s.txt" // onde %s é o nome do jogador NÃO remover.
#endif

/*Lista de funções do sistema PDS -----------------------------------------------------------------------------||

native pds_ManipularDinheiro(playerid, valor);
native pds_PegarDinheiroJogador(playerid);
native pds_ZerarDinheiroJogador(playerid);
native pds_DefinirDinheiroJogador(playerid, valor);
native pds_SalvarDinheiroJogador(playerid);
native pds_CarregarDinheiroJogador(playerid);
native pds_AtualizarTextDraw(playerid);
native pds_MudarTipoTextDraw(bool:tipo);
native pds_MudarTipoTextDrawJogador(playerid, bool:tipo);
native PDS_IncludeAutenticado();

/------------------------------------------------------------------------------------------------------------||*/
stock
	static
			Text:PDS_TDCaixa[3],
			bool:PDS_AUTENTICADO;

#define PDS_CTD(%1) Text:GetPVarInt(%1, "PDS_TD")
#define PDS_CTDCor(%1) GetPVarInt(%1, "PDS_TDCor")
#define PDS_CDJ(%1) GetPVarInt(%1, "PDS_DJ")
#define PDS_CSTD(%1) GetPVarInt(%1, "PDS_STD")
#define PDS_CTTDJ(%1) GetPVarInt(%1, "PDS_TTDJ")

#define PDS_STD(%1,%2) SetPVarInt(%1, "PDS_TD", %2)
#define PDS_STDCor(%1,%2) SetPVarInt(%1, "PDS_TDCor", %2)
#define PDS_SDJ(%1,%2) SetPVarInt(%1, "PDS_DJ", %2)
#define PDS_SSTD(%1,%2) SetPVarInt(%1, "PDS_STD", %2)
#define PDS_STTDJ(%1,%2) SetPVarInt(%1, "PDS_TTDJ", %2)

#define pds_ChecarSistema() if(!PDS_AUTENTICADO){PDS_AUTENTICADO = true;\
	if(PDS_IncludeAutenticado()){PDS_TDCaixa[0] = Text:getproperty(0, "PDS_TDC.0");\
	PDS_TDCaixa[1] = Text:getproperty(0, "PDS_TDC.1");PDS_TDCaixa[2] = Text:getproperty(0, "PDS_TDC.2");}\
	else{pds_CriarTDCaixa();PDS_AutenticarInclude();}}

#define pds_IsPlayerConnected(%1) IsPlayerConnected(%1) && !IsPlayerNPC(%1)

forward PDS_OnPlayerConnect(playerid);
forward PDS_OnPlayerDisconnect(playerid, reason);
forward PDS_OnPlayerRequestClass(playerid, classid);

public OnPlayerConnect(playerid)
{
    pds_ChecarSistema()
    if(!PDS_CTD(playerid))
    {
	    PDS_SDJ(playerid, 0);
	    PDS_SSTD(playerid, 0);
	    PDS_STTDJ(playerid, bool:getproperty(0, "PDS_TTD"));
		if(!PDS_CTTDJ(playerid))
		{
			PDS_STD(playerid, _:TextDrawCreate(517.000000, 130.000000, "$S 00000000"));
			TextDrawLetterSize(PDS_CTD(playerid), 0.349999, 1.000000);
			TextDrawSetShadow(PDS_CTD(playerid), 1);
		}
		else
		{
			PDS_STD(playerid, _:TextDrawCreate(498, 73, "$00000000"));
			TextDrawLetterSize(PDS_CTD(playerid), 0.600000, 2.799999);
			TextDrawSetShadow(PDS_CTD(playerid), 0);
		}
		TextDrawSetOutline(PDS_CTD(playerid), 1);
		TextDrawFont(PDS_CTD(playerid), 3);
		TextDrawSetProportional(PDS_CTD(playerid), 1);
		TextDrawAlignment(PDS_CTD(playerid), 1);
		TextDrawBackgroundColor(PDS_CTD(playerid), 255);
	}
	return CallLocalFunction("PDS_OnPlayerConnect", "d", playerid);
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect PDS_OnPlayerConnect

public OnPlayerDisconnect(playerid, reason)
{
    if(PDS_CTD(playerid))
	{
		TextDrawDestroy(PDS_CTD(playerid));
		PDS_STD(playerid, 0);
	}
    return CallLocalFunction("PDS_OnPlayerDisconnect", "dd", playerid, reason);
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect PDS_OnPlayerDisconnect

public OnPlayerRequestClass(playerid, classid)
{
	if(PDS_CSTD(playerid))
	{
		TextDrawHideForPlayer(playerid, PDS_CTD(playerid));
		if(!PDS_CTTDJ(playerid))
		{
			if(PDS_CTDCor(playerid)) TextDrawHideForPlayer(playerid, PDS_TDCaixa[1]);
			else TextDrawHideForPlayer(playerid, PDS_TDCaixa[0]);
		}
		else TextDrawHideForPlayer(playerid, PDS_TDCaixa[2]);
	}
    return CallLocalFunction("PDS_OnPlayerRequestClass", "dd", playerid, classid);
}
#if defined _ALS_OnPlayerRequestClass
    #undef OnPlayerRequestClass
#else
    #define _ALS_OnPlayerRequestClass
#endif

#define OnPlayerRequestClass PDS_OnPlayerRequestClass

stock pds_ManipularDinheiro(playerid, valor)
{
	if(!pds_IsPlayerConnected(playerid)) return 0;
	PDS_SDJ(playerid, PDS_CDJ(playerid) + valor);
	pds_AtualizarTextDraw(playerid);
	return 1;
}

stock pds_PegarDinheiroJogador(playerid) return PDS_CDJ(playerid);

stock pds_DefinirDinheiroJogador(playerid, valor)
{
	if(!pds_IsPlayerConnected(playerid)) return 0;
	pds_ZerarDinheiroJogador(playerid);
	return pds_ManipularDinheiro(playerid, valor);
}

stock pds_ZerarDinheiroJogador(playerid)
{
	if(!pds_IsPlayerConnected(playerid)) return 0;
	PDS_SDJ(playerid, 0);
	pds_AtualizarTextDraw(playerid);
	return 1;
}
	
stock pds_SalvarDinheiroJogador(playerid)
{
	if(!pds_IsPlayerConnected(playerid)) return 0;
	new
	    pdsarq[MAX_PDS_ARQ_CHAR],
		pdsnomej[MAX_PLAYER_NAME];
	GetPlayerName(playerid, pdsnomej, MAX_PLAYER_NAME);
	format(pdsarq, MAX_PDS_ARQ_CHAR, PDS_ARQUIVO_SALVAR, pdsnomej);
	pgd_EscreverInt(pdsarq, "pds_dinheirosec", ":", PDS_CDJ(playerid));
	return 1;
}

stock pds_CarregarDinheiroJogador(playerid)
{
	if(!pds_IsPlayerConnected(playerid)) return 0;
	new
	    pdsarq[MAX_PDS_ARQ_CHAR],
		pdsnomej[MAX_PLAYER_NAME];
	GetPlayerName(playerid, pdsnomej, MAX_PLAYER_NAME);
	format(pdsarq, MAX_PDS_ARQ_CHAR, PDS_ARQUIVO_SALVAR, pdsnomej);
	PDS_SDJ(playerid, pgd_CarregarInt(pdsarq, "pds_dinheirosec", ":"));
	return 1;
}


stock pds_AtualizarTextDraw(playerid)
{
	if(!pds_IsPlayerConnected(playerid)) return 0;
	new
	    pdsts,
		pdsdf[16];
	format(pdsdf, 16, "%d", PDS_CDJ(playerid));
	new pdsposn = strfind(pdsdf, "-");
	if(pdsposn != -1) strdel(pdsdf, pdsposn, pdsposn+1);
	pdsts = strlen(pdsdf);
	if(pdsts < 8)
	{
		new pdsz;
		pdsz = 8 - pdsts;
		for(new c; c < pdsz; c++) strins(pdsdf, "0", 0, 16);
	}
	else if(pdsts > 8)
	{
		new pdsz;
		pdsz = pdsts - 8;
		strdel(pdsdf, 0, pdsz);
	}
	if(PDS_CDJ(playerid) < 0)
	{
	    if(!PDS_CTTDJ(playerid))
	    {
		    strins(pdsdf, "~r~$S ", 0, 16);
			if(PDS_CTDCor(playerid))
			{
				TextDrawHideForPlayer(playerid, PDS_TDCaixa[1]);
				TextDrawShowForPlayer(playerid, PDS_TDCaixa[0]);
				PDS_STDCor(playerid, 0);
			}
		}
		else
		{
			strins(pdsdf, "~r~$", 0, 16);
			TextDrawShowForPlayer(playerid, PDS_TDCaixa[2]);
		}
	}
	else
	{
	    if(!PDS_CTTDJ(playerid))
	    {
		    strins(pdsdf, "~g~$S ", 0, 16);
			if(!PDS_CTDCor(playerid))
			{
				TextDrawHideForPlayer(playerid, PDS_TDCaixa[0]);
				TextDrawShowForPlayer(playerid, PDS_TDCaixa[1]);
				PDS_STDCor(playerid, 1);
			}
		}
		else
		{
			strins(pdsdf, "~g~$", 0, 16);
			TextDrawShowForPlayer(playerid, PDS_TDCaixa[2]);
		}
	}
	TextDrawSetString(PDS_CTD(playerid), pdsdf);
	TextDrawHideForPlayer(playerid, PDS_CTD(playerid));
	TextDrawShowForPlayer(playerid, PDS_CTD(playerid));
	PDS_SSTD(playerid, 1);
	return 1;
}

stock static pds_CriarTDCaixa()
{
	PDS_TDCaixa[0] = TextDrawCreate(505.000000, 130.000000, "_");
    setproperty(0, "PDS_TDC.0", _:PDS_TDCaixa[0]);
	TextDrawSetProportional(PDS_TDCaixa[0], 1);
	TextDrawAlignment(PDS_TDCaixa[0], 1);
	TextDrawLetterSize(PDS_TDCaixa[0], 5.000000, 1.000000);
	TextDrawUseBox(PDS_TDCaixa[0], 1);
	TextDrawBoxColor(PDS_TDCaixa[0], 0xFF0000AA);
	TextDrawTextSize(PDS_TDCaixa[0], 605.000000, 502.000000);
	PDS_TDCaixa[1] = TextDrawCreate(505.000000, 130.000000, "_");
    setproperty(0, "PDS_TDC.1", _:PDS_TDCaixa[1]);
	TextDrawSetProportional(PDS_TDCaixa[1], 1);
	TextDrawAlignment(PDS_TDCaixa[1], 1);
	TextDrawLetterSize(PDS_TDCaixa[1], 5.000000, 1.000000);
	TextDrawUseBox(PDS_TDCaixa[1], 1);
	TextDrawBoxColor(PDS_TDCaixa[1], 0x32CD32AA);
	TextDrawTextSize(PDS_TDCaixa[1], 605.000000, 502.000000);
	PDS_TDCaixa[2] = TextDrawCreate(610, 82, "_");
    setproperty(0, "PDS_TDC.2", _:PDS_TDCaixa[2]);
	TextDrawSetOutline(PDS_TDCaixa[2], 0);
	TextDrawFont(PDS_TDCaixa[2], 0);
	TextDrawSetProportional(PDS_TDCaixa[2], 1);
	TextDrawAlignment(PDS_TDCaixa[2], 0);
	TextDrawLetterSize(PDS_TDCaixa[2], 1.000000, 1.299999);
	TextDrawSetShadow(PDS_TDCaixa[2], 0);
	TextDrawBackgroundColor(PDS_TDCaixa[2], 0);
	TextDrawColor(PDS_TDCaixa[2], 48485454);
	TextDrawUseBox(PDS_TDCaixa[2], 1);
	TextDrawBoxColor(PDS_TDCaixa[2], 989);
	TextDrawTextSize(PDS_TDCaixa[2], 496.000000, 3.000000);
}

stock pds_MudarTipoTextDraw(bool:tipo)
{
    setproperty(0, "PDS_TTD", tipo);
    for(new j; j < MAX_PLAYERS; j++) pds_MudarTipoTextDrawJogador(j, tipo);
}

stock pds_MudarTipoTextDrawJogador(playerid, bool:tipo)
{
	if(pds_IsPlayerConnected(playerid))
	{
		TextDrawDestroy(PDS_CTD(playerid));
		TextDrawHideForPlayer(playerid, PDS_TDCaixa[0]);
		TextDrawHideForPlayer(playerid, PDS_TDCaixa[1]);
		TextDrawHideForPlayer(playerid, PDS_TDCaixa[2]);
		if(!tipo)
		{
			PDS_STD(playerid, _:TextDrawCreate(517.000000, 130.000000, "$S 00000000"));
			TextDrawLetterSize(PDS_CTD(playerid), 0.349999, 1.000000);
			TextDrawSetShadow(PDS_CTD(playerid), 1);
			if(PDS_CTDCor(playerid)) TextDrawShowForPlayer(playerid, PDS_TDCaixa[1]);
			else TextDrawShowForPlayer(playerid, PDS_TDCaixa[0]);
		}
		else
		{
			PDS_STD(playerid, _:TextDrawCreate(498, 73, "$00000000"));
			TextDrawLetterSize(PDS_CTD(playerid), 0.600000, 2.799999);
			TextDrawSetShadow(PDS_CTD(playerid), 0);
		}
		TextDrawSetOutline(PDS_CTD(playerid), 1);
		TextDrawFont(PDS_CTD(playerid), 3);
		TextDrawSetProportional(PDS_CTD(playerid), 1);
		TextDrawAlignment(PDS_CTD(playerid), 1);
		TextDrawBackgroundColor(PDS_CTD(playerid), 255);
		PDS_STTDJ(playerid, tipo);
		pds_AtualizarTextDraw(playerid);
	}
}

stock PDS_AutenticarInclude()
{
	setproperty(0, "PDS", 1);
	print("[PDS]: INCLUDE AUTENTICADO.");
}
stock PDS_IncludeAutenticado() return (!existproperty(0, "PDS")) ? 0 : 1;
