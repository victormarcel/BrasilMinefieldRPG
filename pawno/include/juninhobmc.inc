#include <a_samp>
#include <dini>
#include <utils>
#if defined MAX_STRING
#undef MAX_STRING
#define MAX_STRING 1023
#else
#define MAX_STRING 1023
#endif
/*	>>> Exemplo como Usar o PCarregarTexto(nome[],key[]); <<<
	PSetarTexto(pNome(playerid),"Teste","Testando essa Merda carai!");
	format(string, sizeof(string), "vamos ver: %s",PCarregarTexto(pNome(playerid),"Teste"));
	SendClientMessage(playerid, verde, string);
*/
// Natives
/*
native pNome(playerid);
native PCriarConta(playerid,senha[]);tr
native PContaExiste(nome[]);
native PExcluirConta(nome[]);
native PChecarSenha(nome[],senha[]);
native PSetarSenha(nome[],senha[]);
native PSetarTexto(nome[],key[],texto[]);
native PSetarFloat(nome[],key[],Float:value);
native PSetarInteiro(nome[],key[],value);
native PCarregarTexto(nome[],key[],texto[],letras);
native PCarregarFloat(nome[],key[]);
native PCarregarInteiro(nome[],key[]);
native IsBike(veiculoid);
native IsMoto(veiculoid);
native IsAirVehicle(veiculoid);
native IsABoat(veiculoid);
native IsACaminhao(carid);
native GetPlayerCaminhao(playerid);
native AdicionarColete(playerid,colete);
native SetarDinheiro(playerid,grana);
native IsPlayerOnline(nome[]);
native GetPlayerID(string[]);
native GetDistanceToPoint(playerid,Float: X2,Float:Y2 ,Float: Z2);
native GetCargaEmp(carga);
native PoderosoData();
native PoderosoHorario();
native LoginLog(string[]);
native RegistroLog(string[]);
native SalvarContaLog(string[]);
native SetarMaxArmasLv(playerid);
native PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z);
native VeiculoToPoint(Float:radi, playerid, Float:x, Float:y, Float:z);
native IsaPostodeGasolina(playerid);
*/

stock pNome(playerid)
{
    new nome[MAX_PLAYER_NAME];
    GetPlayerName(playerid, nome, sizeof(nome));
    return nome;
}

stock PContaExiste(nome[])
{
	new arquivo[MAX_STRING];
	format(arquivo,sizeof(arquivo),"/Contas/%s.ini",nome);
	return dini_Exists(arquivo);
}

stock PCriarConta(playerid,senha[])
{
	if (PContaExiste(pNome(playerid))) return false;
	new arquivo[MAX_STRING];
	format(arquivo,sizeof(arquivo),"/Contas/%s.ini",pNome(playerid));
	dini_Create(arquivo);
	dini_Set(arquivo,"Senha",senha);
	return true;
}
stock PSetarSenha(pNome[],senha[])
{
	if (!PContaExiste(pNome(playerid))) return false;
	new arquivo[MAX_STRING];
	format(arquivo,sizeof(arquivo),"/Contas/%s.ini",pNome);
	dini_Set(arquivo,"Senha",senha);
	return true;
}
stock PExcluirConta(nome[])
{
	new arquivo[MAX_STRING];
	format(arquivo,sizeof(arquivo),"/Contas/%s.ini",nome);
	return dini_Remove(arquivo);
}

stock PChecarSenha(nome[],senha[])
{
    if(!PContaExiste(nome)) return false;
	new arquivo[MAX_STRING];
	format(arquivo,sizeof(arquivo),"/Contas/%s.ini",nome);
	if(strcmp(dini_Get(arquivo,"Senha"),senha,true)==0) { return true; }
	return false;
}

stock PSetarInteiro(nome[],key[],value)
{
	new arquivo[MAX_STRING];
	format(arquivo,sizeof(arquivo),"/Contas/%s.ini",nome);
	return dini_IntSet(arquivo,key,value);
}

stock PSetarFloat(nome[],key[],Float:value)
{
	new arquivo[MAX_STRING];
	format(arquivo,sizeof(arquivo),"/Contas/%s.ini",nome);
	return dini_FloatSet(arquivo,key,value);
}

stock PSetarTexto(nome[],key[],texto[])
{
	new arquivo[MAX_STRING];
	format(arquivo,sizeof(arquivo),"/Contas/%s.ini",nome);
	return dini_Set(arquivo,key,texto);
}

stock PCarregarTexto(nome[],key[])
{
	new arquivo[MAX_STRING];
	format(arquivo,sizeof(arquivo),"/Contas/%s.ini",nome);
	format(arquivo,sizeof(arquivo),dini_Get(arquivo,key));
  	return arquivo;
}

stock Float:PCarregarFloat(nome[],key[])
{
	new arquivo[MAX_STRING];
	format(arquivo,sizeof(arquivo),"/Contas/%s.ini",nome);
	return dini_Float(arquivo,key);
}

stock PCarregarInteiro(nome[],key[])
{
	new arquivo[MAX_STRING];
	format(arquivo,sizeof(arquivo),"/Contas/%s.ini",nome);
	return dini_Int(arquivo,key);
}

stock IsBike(carid)
{
    new Bikes[] = { 509, 481, 510 };
    for(new i = 0; i < sizeof(Bikes); i++)
    {
        if(GetVehicleModel(carid) == Bikes[i]) return 1;
    }
    return 0;
}

stock IsMoto(carid)
{
    new Moto[] = { 522, 462, 521, 461, 463, 581, 448, 586, 523, 468, 471 };
    for(new i = 0; i < sizeof(Moto); i++)
    {
        if(GetVehicleModel(carid) == Moto[i]) return 1;
    }
    return 0;
}

stock IsAirVehicle(carid)
{
    new AirVeh[] = { 592, 577, 511, 512, 593, 520, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 497, 563, 447, 469 };
    for(new i = 0; i < sizeof(AirVeh); i++)
    {
        if(GetVehicleModel(carid) == AirVeh[i]) return 1;
    }
    return 0;
}

stock IsABoat(carid)
{
    new Boats[] = { 472, 473, 493, 495, 484, 430, 454, 453, 452, 446 };
    for(new i = 0; i < sizeof(Boats); i++)
    {
	if(GetVehicleModel(carid) == Boats[i]) return 1;
    }
    return 0;
}

stock AdicionarColete(playerid,colete)
{
	new Float: ColeteAtual , Float: ColeteDepois;
	GetPlayerArmour(playerid, ColeteAtual);
	SetPlayerArmour(playerid, ColeteAtual+colete);
	GetPlayerArmour(playerid, ColeteDepois);
	if(ColeteDepois > 100){ SetPlayerArmour(playerid, 100); }
	return 1;
}

stock SetarDinheiro(playerid,grana)
{
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid,grana);
}

stock IsPlayerOnline(nome[])
{
	for(new i=0; i<MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	    	if(strcmp(nome,pNome(i),true)==0)
			{
			    return 1;
			}
		}
	}
	return 0;
}

stock GetPlayerID(string[])
{
    for(new i = 0; i <= MAX_PLAYERS; i++)
    {
    	if(IsPlayerConnected(i) == 1)
		{
        	new testname[MAX_PLAYER_NAME];
	    	GetPlayerName(i, testname, sizeof(testname));
	    	if(strcmp(testname, string, true, strlen(string)) == 0)
	    	{
	    	    return i;
	    	}
		}
    }
    return INVALID_PLAYER_ID;
}

stock IsACaminhao(carid)
{
    new Camihao[] = { 403, 514, 515 };
    for(new i = 0; i < sizeof(Camihao); i++)
    {
		if(GetVehicleModel(carid) == Camihao[i]) return 1;
    }
    return 0;
}

stock GetPlayerCaminhao(playerid)
{
    new caminhao = GetPlayerVehicleID(playerid);
    if(IsACaminhao(caminhao)) return caminhao;
	return 0;
}

stock Float:GetDistanceToPoint(playerid,Float: X2,Float:Y2 ,Float: Z2)
{
    new Float:X,Float:Y,Float:Z;
    GetPlayerPos(playerid,X,Y,Z);
	return floatsqroot ( floatpower ( floatabs ( floatsub ( X , X2 ) ) , 2 ) + floatpower ( floatabs ( floatsub ( Y , Y2 ) ) , 2 ) + floatpower ( floatabs ( floatsub ( Z , Z2 ) ) , 2 ) );
}

stock GetCargaEmp(carga)
{
    if(carga >= 631 && carga <= 638) // LS 1
	{
		return 22;
	}
	if(carga >= 639 && carga <= 646)  // LS 2
	{
		return 23;
	}
	if(carga >= 647 && carga <= 654) // LV 1
	{
		return 24;
	}
	if(carga >= 655 && carga <= 662) // LV 2
	{
		return 25;
	}
	if(carga >= 663 && carga <= 670) // LV 3
	{
		return 26;
	}
	if(carga >= 671 && carga <= 678)  // LS 3
	{
		return 27;
	}
	return 0;
}

stock PoderosoData()
{
	new poderosodata[62];
	new ano, mes,dia;
	getdate(ano, mes, dia);
	new hora, minuto;
	gettime(hora,minuto);
	format(poderosodata,sizeof(poderosodata),"%02d/%02d/%02d",dia, mes, ano);
  	return poderosodata;
}

stock PoderosoHorario()
{
	new poderosodata[62];
	new hora, minuto,segundo;
	gettime(hora,minuto,segundo);
	format(poderosodata,sizeof(poderosodata),"%02d:%02d:%02d",hora, minuto,segundo);
  	return poderosodata;
}

stock LoginLog(string[])
{
	new log[256];
	format(log, sizeof(log), "%s\n",string);
	new File:hFile;
	hFile = fopen("Logs/LoginLog.log", io_append);
	fwrite(hFile, log);
	fclose(hFile);
}

stock RegistroLog(string[])
{
	new log[256];
	format(log, sizeof(log), "%s\n",string);
	new File:hFile;
	hFile = fopen("Logs/RegistroLog.log", io_append);
	fwrite(hFile, log);
	fclose(hFile);
}

stock SalvarContaLog(string[])
{
	new log[256];
	format(log, sizeof(log), "%s\n",string);
	new File:hFile;
	hFile = fopen("Logs/SalvarContaLog.log", io_append);
	fwrite(hFile, log);
	fclose(hFile);
}

strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}
	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

stock SetarMaxArmasLv(playerid)
{
    SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 1000);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 1000);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 1000);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 1000);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 1000);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 1000);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 1000);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 1000);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 1000);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 1000);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 1000);
	return 1;
}

#define MAX_ZONE_NAME 28
enum MainZone{
Zone_Name[28], Float:Zone_Area[6] };

static const SanAndreasZones[][MainZone] = {

	{"The Big Ear",	                {-410.00,1403.30,-3.00,-137.90,1681.20,200.00}},
	{"Aldea Malvada",               {-1372.10,2498.50,0.00,-1277.50,2615.30,200.00}},
	{"Angel Pine",                  {-2324.90,-2584.20,-6.10,-1964.20,-2212.10,200.00}},
	{"Arco del Oeste",              {-901.10,2221.80,0.00,-592.00,2571.90,200.00}},
	{"Avispa Country Club",         {-2646.40,-355.40,0.00,-2270.00,-222.50,200.00}},
	{"Avispa Country Club",         {-2831.80,-430.20,-6.10,-2646.40,-222.50,200.00}},
	{"Avispa Country Club",         {-2361.50,-417.10,0.00,-2270.00,-355.40,200.00}},
	{"Avispa Country Club",         {-2667.80,-302.10,-28.80,-2646.40,-262.30,71.10}},
	{"Avispa Country Club",         {-2470.00,-355.40,0.00,-2270.00,-318.40,46.10}},
	{"Avispa Country Club",         {-2550.00,-355.40,0.00,-2470.00,-318.40,39.70}},
	{"Back o Beyond",               {-1166.90,-2641.10,0.00,-321.70,-1856.00,200.00}},
	{"Battery Point",               {-2741.00,1268.40,-4.50,-2533.00,1490.40,200.00}},
	{"Bayside",                     {-2741.00,2175.10,0.00,-2353.10,2722.70,200.00}},
	{"Bayside Marina",              {-2353.10,2275.70,0.00,-2153.10,2475.70,200.00}},
	{"Beacon Hill",                 {-399.60,-1075.50,-1.40,-319.00,-977.50,198.50}},
	{"Blackfield",                  {964.30,1203.20,-89.00,1197.30,1403.20,110.90}},
	{"Blackfield",                  {964.30,1403.20,-89.00,1197.30,1726.20,110.90}},
	{"Blackfield Chapel",           {1375.60,596.30,-89.00,1558.00,823.20,110.90}},
	{"Blackfield Chapel",           {1325.60,596.30,-89.00,1375.60,795.00,110.90}},
	{"Blackfield",     				{1197.30,1044.60,-89.00,1277.00,1163.30,110.90}},
	{"Blackfield",   				{1166.50,795.00,-89.00,1375.60,1044.60,110.90}},
	{"Blackfield",     				{1277.00,1044.60,-89.00,1315.30,1087.60,110.90}},
	{"Blackfield",     				{1375.60,823.20,-89.00,1457.30,919.40,110.90}},
	{"Blueberry",                   {104.50,-220.10,2.30,349.60,152.20,200.00}},
	{"Blueberry",                   {19.60,-404.10,3.80,349.60,-220.10,200.00}},
	{"Blueberry Acres",             {-319.60,-220.10,0.00,104.50,293.30,200.00}},
	{"Caligula's Palace",           {2087.30,1543.20,-89.00,2437.30,1703.20,110.90}},
	{"Caligula's Palace",           {2137.40,1703.20,-89.00,2437.30,1783.20,110.90}},
	{"Calton Heights",              {-2274.10,744.10,-6.10,-1982.30,1358.90,200.00}},
	{"Chinatown",                   {-2274.10,578.30,-7.60,-2078.60,744.10,200.00}},
	{"City Hall",                   {-2867.80,277.40,-9.10,-2593.40,458.40,200.00}},
	{"Castelo de LV",           	{2087.30,943.20,-89.00,2623.10,1203.20,110.90}},
	{"Commerce",                    {1323.90,-1842.20,-89.00,1701.90,-1722.20,110.90}},
	{"Commerce",                    {1323.90,-1722.20,-89.00,1440.90,-1577.50,110.90}},
	{"Commerce",                    {1370.80,-1577.50,-89.00,1463.90,-1384.90,110.90}},
	{"Commerce",                    {1463.90,-1577.50,-89.00,1667.90,-1430.80,110.90}},
	{"Commerce",                    {1583.50,-1722.20,-89.00,1758.90,-1577.50,110.90}},
	{"Commerce",                    {1667.90,-1577.50,-89.00,1812.60,-1430.80,110.90}},
	{"Conference Center",           {1046.10,-1804.20,-89.00,1323.90,-1722.20,110.90}},
	{"Conference Center",           {1073.20,-1842.20,-89.00,1323.90,-1804.20,110.90}},
	{"Cranberry Station",           {-2007.80,56.30,0.00,-1922.00,224.70,100.00}},
	{"Creek",                       {2749.90,1937.20,-89.00,2921.60,2669.70,110.90}},
	{"Dillimore",                   {580.70,-674.80,-9.50,861.00,-404.70,200.00}},
	{"Doherty",                     {-2270.00,-324.10,-0.00,-1794.90,-222.50,200.00}},
	{"Doherty",                     {-2173.00,-222.50,-0.00,-1794.90,265.20,200.00}},
	{"Downtown",                    {-1982.30,744.10,-6.10,-1871.70,1274.20,200.00}},
	{"Downtown",                    {-1871.70,1176.40,-4.50,-1620.30,1274.20,200.00}},
	{"Downtown",                    {-1700.00,744.20,-6.10,-1580.00,1176.50,200.00}},
	{"Downtown",                    {-1580.00,744.20,-6.10,-1499.80,1025.90,200.00}},
	{"Downtown",                    {-2078.60,578.30,-7.60,-1499.80,744.20,200.00}},
	{"Downtown",                    {-1993.20,265.20,-9.10,-1794.90,578.30,200.00}},
	{"Downtown Los Santos",         {1463.90,-1430.80,-89.00,1724.70,-1290.80,110.90}},
	{"Downtown Los Santos",         {1724.70,-1430.80,-89.00,1812.60,-1250.90,110.90}},
	{"Downtown Los Santos",         {1463.90,-1290.80,-89.00,1724.70,-1150.80,110.90}},
	{"Downtown Los Santos",         {1370.80,-1384.90,-89.00,1463.90,-1170.80,110.90}},
	{"Downtown Los Santos",         {1724.70,-1250.90,-89.00,1812.60,-1150.80,110.90}},
	{"Downtown Los Santos",         {1370.80,-1170.80,-89.00,1463.90,-1130.80,110.90}},
	{"Downtown Los Santos",         {1378.30,-1130.80,-89.00,1463.90,-1026.30,110.90}},
	{"Downtown Los Santos",         {1391.00,-1026.30,-89.00,1463.90,-926.90,110.90}},
	{"Downtown Los Santos",         {1507.50,-1385.20,110.90,1582.50,-1325.30,335.90}},
	{"East Beach",                  {2632.80,-1852.80,-89.00,2959.30,-1668.10,110.90}},
	{"East Beach",                  {2632.80,-1668.10,-89.00,2747.70,-1393.40,110.90}},
	{"East Beach",                  {2747.70,-1668.10,-89.00,2959.30,-1498.60,110.90}},
	{"East Beach",                  {2747.70,-1498.60,-89.00,2959.30,-1120.00,110.90}},
	{"East Los Santos",             {2421.00,-1628.50,-89.00,2632.80,-1454.30,110.90}},
	{"East Los Santos",             {2222.50,-1628.50,-89.00,2421.00,-1494.00,110.90}},
	{"East Los Santos",             {2266.20,-1494.00,-89.00,2381.60,-1372.00,110.90}},
	{"East Los Santos",             {2381.60,-1494.00,-89.00,2421.00,-1454.30,110.90}},
	{"East Los Santos",             {2281.40,-1372.00,-89.00,2381.60,-1135.00,110.90}},
	{"East Los Santos",             {2381.60,-1454.30,-89.00,2462.10,-1135.00,110.90}},
	{"East Los Santos",             {2462.10,-1454.30,-89.00,2581.70,-1135.00,110.90}},
	{"Easter Basin",                {-1794.90,249.90,-9.10,-1242.90,578.30,200.00}},
	{"Easter Basin",                {-1794.90,-50.00,-0.00,-1499.80,249.90,200.00}},
	{"Easter Bay Airport",          {-1499.80,-50.00,-0.00,-1242.90,249.90,200.00}},
	{"Easter Bay Airport",          {-1794.90,-730.10,-3.00,-1213.90,-50.00,200.00}},
	{"Easter Bay Airport",          {-1213.90,-730.10,0.00,-1132.80,-50.00,200.00}},
	{"Easter Bay Airport",          {-1242.90,-50.00,0.00,-1213.90,578.30,200.00}},
	{"Easter Bay Airport",          {-1213.90,-50.00,-4.50,-947.90,578.30,200.00}},
	{"Easter Bay Airport",          {-1315.40,-405.30,15.40,-1264.40,-209.50,25.40}},
	{"Easter Bay Airport",          {-1354.30,-287.30,15.40,-1315.40,-209.50,25.40}},
	{"Easter Bay Airport",          {-1490.30,-209.50,15.40,-1264.40,-148.30,25.40}},
	{"Easter Bay Chemicals",        {-1132.80,-768.00,0.00,-956.40,-578.10,200.00}},
	{"Easter Bay Chemicals",        {-1132.80,-787.30,0.00,-956.40,-768.00,200.00}},
	{"El Castillo del Diablo",      {-464.50,2217.60,0.00,-208.50,2580.30,200.00}},
	{"El Castillo del Diablo",      {-208.50,2123.00,-7.60,114.00,2337.10,200.00}},
	{"El Castillo del Diablo",      {-208.50,2337.10,0.00,8.40,2487.10,200.00}},
	{"El Corona",                   {1812.60,-2179.20,-89.00,1970.60,-1852.80,110.90}},
	{"El Corona",                   {1692.60,-2179.20,-89.00,1812.60,-1842.20,110.90}},
	{"El Quebrados",                {-1645.20,2498.50,0.00,-1372.10,2777.80,200.00}},
	{"Esplanade East",              {-1620.30,1176.50,-4.50,-1580.00,1274.20,200.00}},
	{"Esplanade East",              {-1580.00,1025.90,-6.10,-1499.80,1274.20,200.00}},
	{"Esplanade East",              {-1499.80,578.30,-79.60,-1339.80,1274.20,20.30}},
	{"Esplanade North",             {-2533.00,1358.90,-4.50,-1996.60,1501.20,200.00}},
	{"Esplanade North",             {-1996.60,1358.90,-4.50,-1524.20,1592.50,200.00}},
	{"Esplanade North",             {-1982.30,1274.20,-4.50,-1524.20,1358.90,200.00}},
	{"Fallen Tree",                 {-792.20,-698.50,-5.30,-452.40,-380.00,200.00}},
	{"Fallow Bridge",               {434.30,366.50,0.00,603.00,555.60,200.00}},
	{"Fern Ridge",                  {508.10,-139.20,0.00,1306.60,119.50,200.00}},
	{"Financial",                   {-1871.70,744.10,-6.10,-1701.30,1176.40,300.00}},
	{"Fisher's Lagoon",             {1916.90,-233.30,-100.00,2131.70,13.80,200.00}},
	{"Flint ",          			{-187.70,-1596.70,-89.00,17.00,-1276.60,110.90}},
	{"Flint Range",                 {-594.10,-1648.50,0.00,-187.70,-1276.60,200.00}},
	{"Fort Carson",                 {-376.20,826.30,-3.00,123.70,1220.40,200.00}},
	{"Foster Valley",               {-2270.00,-430.20,-0.00,-2178.60,-324.10,200.00}},
	{"Foster Valley",               {-2178.60,-599.80,-0.00,-1794.90,-324.10,200.00}},
	{"Foster Valley",               {-2178.60,-1115.50,0.00,-1794.90,-599.80,200.00}},
	{"Foster Valley",               {-2178.60,-1250.90,0.00,-1794.90,-1115.50,200.00}},
	{"Frederick Bridge",            {2759.20,296.50,0.00,2774.20,594.70,200.00}},
	{"Gant Bridge",                 {-2741.40,1659.60,-6.10,-2616.40,2175.10,200.00}},
	{"Gant Bridge",                 {-2741.00,1490.40,-6.10,-2616.40,1659.60,200.00}},
	{"Ganton",                      {2222.50,-1852.80,-89.00,2632.80,-1722.30,110.90}},
	{"Ganton",                      {2222.50,-1722.30,-89.00,2632.80,-1628.50,110.90}},
	{"Garcia",                      {-2411.20,-222.50,-0.00,-2173.00,265.20,200.00}},
	{"Garcia",                      {-2395.10,-222.50,-5.30,-2354.00,-204.70,200.00}},
	{"Garver Bridge",               {-1339.80,828.10,-89.00,-1213.90,1057.00,110.90}},
	{"Garver Bridge",               {-1213.90,950.00,-89.00,-1087.90,1178.90,110.90}},
	{"Garver Bridge",               {-1499.80,696.40,-179.60,-1339.80,925.30,20.30}},
	{"Glen Park",                   {1812.60,-1449.60,-89.00,1996.90,-1350.70,110.90}},
	{"Glen Park",                   {1812.60,-1100.80,-89.00,1994.30,-973.30,110.90}},
	{"Glen Park",                   {1812.60,-1350.70,-89.00,2056.80,-1100.80,110.90}},
	{"Green Palms",                 {176.50,1305.40,-3.00,338.60,1520.70,200.00}},
	{"Greenglass College",          {964.30,1044.60,-89.00,1197.30,1203.20,110.90}},
	{"Greenglass College",          {964.30,930.80,-89.00,1166.50,1044.60,110.90}},
	{"Hampton Barns",               {603.00,264.30,0.00,761.90,366.50,200.00}},
	{"Hankypanky Point",            {2576.90,62.10,0.00,2759.20,385.50,200.00}},
	{"Harry Gold Parkway",          {1777.30,863.20,-89.00,1817.30,2342.80,110.90}},
	{"Hashbury",                    {-2593.40,-222.50,-0.00,-2411.20,54.70,200.00}},
	{"Hilltop Farm",                {967.30,-450.30,-3.00,1176.70,-217.90,200.00}},
	{"Hunter Quarry",               {337.20,710.80,-115.20,860.50,1031.70,203.70}},
	{"Idlewood",                    {1812.60,-1852.80,-89.00,1971.60,-1742.30,110.90}},
	{"Idlewood",                    {1812.60,-1742.30,-89.00,1951.60,-1602.30,110.90}},
	{"Idlewood",                    {1951.60,-1742.30,-89.00,2124.60,-1602.30,110.90}},
	{"Idlewood",                    {1812.60,-1602.30,-89.00,2124.60,-1449.60,110.90}},
	{"Idlewood",                    {2124.60,-1742.30,-89.00,2222.50,-1494.00,110.90}},
	{"Idlewood",                    {1971.60,-1852.80,-89.00,2222.50,-1742.30,110.90}},
	{"Jefferson",                   {1996.90,-1449.60,-89.00,2056.80,-1350.70,110.90}},
	{"Jefferson",                   {2124.60,-1494.00,-89.00,2266.20,-1449.60,110.90}},
	{"Jefferson",                   {2056.80,-1372.00,-89.00,2281.40,-1210.70,110.90}},
	{"Jefferson",                   {2056.80,-1210.70,-89.00,2185.30,-1126.30,110.90}},
	{"Jefferson",                   {2185.30,-1210.70,-89.00,2281.40,-1154.50,110.90}},
	{"Jefferson",                   {2056.80,-1449.60,-89.00,2266.20,-1372.00,110.90}},
	{"Julius Thruway East",         {2623.10,943.20,-89.00,2749.90,1055.90,110.90}},
	{"Julius Thruway East",         {2685.10,1055.90,-89.00,2749.90,2626.50,110.90}},
	{"Julius Thruway East",         {2536.40,2442.50,-89.00,2685.10,2542.50,110.90}},
	{"Julius Thruway East",         {2625.10,2202.70,-89.00,2685.10,2442.50,110.90}},
	{"Julius Thruway North",        {2498.20,2542.50,-89.00,2685.10,2626.50,110.90}},
	{"Julius Thruway North",        {2237.40,2542.50,-89.00,2498.20,2663.10,110.90}},
	{"Julius Thruway North",        {2121.40,2508.20,-89.00,2237.40,2663.10,110.90}},
	{"Julius Thruway North",        {1938.80,2508.20,-89.00,2121.40,2624.20,110.90}},
	{"Julius Thruway North",        {1534.50,2433.20,-89.00,1848.40,2583.20,110.90}},
	{"Julius Thruway North",        {1848.40,2478.40,-89.00,1938.80,2553.40,110.90}},
	{"Julius Thruway North",        {1704.50,2342.80,-89.00,1848.40,2433.20,110.90}},
	{"Julius Thruway North",        {1377.30,2433.20,-89.00,1534.50,2507.20,110.90}},
	{"Julius Thruway South",        {1457.30,823.20,-89.00,2377.30,863.20,110.90}},
	{"Julius Thruway South",        {2377.30,788.80,-89.00,2537.30,897.90,110.90}},
	{"Julius Thruway West",         {1197.30,1163.30,-89.00,1236.60,2243.20,110.90}},
	{"Julius Thruway West",         {1236.60,2142.80,-89.00,1297.40,2243.20,110.90}},
	{"Juniper Hill",                {-2533.00,578.30,-7.60,-2274.10,968.30,200.00}},
	{"Juniper Hollow",              {-2533.00,968.30,-6.10,-2274.10,1358.90,200.00}},
	{"K.A.C.C. Military Fuels",     {2498.20,2626.50,-89.00,2749.90,2861.50,110.90}},
	{"Kincaid Bridge",              {-1339.80,599.20,-89.00,-1213.90,828.10,110.90}},
	{"Kincaid Bridge",              {-1213.90,721.10,-89.00,-1087.90,950.00,110.90}},
	{"Kincaid Bridge",              {-1087.90,855.30,-89.00,-961.90,986.20,110.90}},
	{"King's",                      {-2329.30,458.40,-7.60,-1993.20,578.30,200.00}},
	{"King's",                      {-2411.20,265.20,-9.10,-1993.20,373.50,200.00}},
	{"King's",                      {-2253.50,373.50,-9.10,-1993.20,458.40,200.00}},
	{"LVA Freight Depot",           {1457.30,863.20,-89.00,1777.40,1143.20,110.90}},
	{"LVA Freight Depot",           {1375.60,919.40,-89.00,1457.30,1203.20,110.90}},
	{"LVA Freight Depot",           {1277.00,1087.60,-89.00,1375.60,1203.20,110.90}},
	{"LVA Freight Depot",           {1315.30,1044.60,-89.00,1375.60,1087.60,110.90}},
	{"LVA Freight Depot",           {1236.60,1163.40,-89.00,1277.00,1203.20,110.90}},
	{"Las Barrancas",               {-926.10,1398.70,-3.00,-719.20,1634.60,200.00}},
	{"Las Brujas",                  {-365.10,2123.00,-3.00,-208.50,2217.60,200.00}},
	{"Morro de LS Parte 1",    {1994.30,-1100.80,-89.00,2056.80,-920.80,110.90}},
	{"Morro de LS Parte 1",    {2056.80,-1126.30,-89.00,2126.80,-920.80,110.90}},
	{"Morro de LS Parte 1",    {2126.80,-1126.30,-89.00,2185.30,-934.40,110.90}},
	{"Morro de LS Parte 1",    {2185.30,-1154.50,-89.00,2281.40,-934.40,110.90}},
	{"Morro de LS Parte 2",    {2281.40,-1135.00,-89.00,2632.70,-945.00,110.90}},
	{"Morro de LS Parte 3",    {2632.70,-1135.00,-89.00,2747.70,-945.00,110.90}},
	{"Morro de LS Parte 3",    {2747.70,-1120.00,-89.00,2900.30,-945.00,110.90}},
	{"Las Payasadas",               {-354.30,2580.30,2.00,-133.60,2816.80,200.00}},
	{"Las Venturas Airport",        {1236.60,1203.20,-89.00,1457.30,1883.10,110.90}},
	{"Las Venturas Airport",        {1457.30,1203.20,-89.00,1777.30,1883.10,110.90}},
	{"Las Venturas Airport",        {1457.30,1143.20,-89.00,1777.40,1203.20,110.90}},
	{"Las Venturas Airport",        {1515.80,1586.40,-12.50,1729.90,1714.50,87.50}},
	{"Last Dime Motel",             {1823.00,596.30,-89.00,1997.20,823.20,110.90}},
	{"Leafy Hollow",                {-1166.90,-1856.00,0.00,-815.60,-1602.00,200.00}},
	{"Liberty City",                {-1000.00,400.00,1300.00,-700.00,600.00,1400.00}},
	{"Lil' Probe Inn",              {-90.20,1286.80,-3.00,153.80,1554.10,200.00}},
	{"Linden Side",                 {2749.90,943.20,-89.00,2923.30,1198.90,110.90}},
	{"Linden Station",              {2749.90,1198.90,-89.00,2923.30,1548.90,110.90}},
	{"Linden Station",              {2811.20,1229.50,-39.50,2861.20,1407.50,60.40}},
	{"Little Mexico",               {1701.90,-1842.20,-89.00,1812.60,-1722.20,110.90}},
	{"Little Mexico",               {1758.90,-1722.20,-89.00,1812.60,-1577.50,110.90}},
	{"Los Flores",                  {2581.70,-1454.30,-89.00,2632.80,-1393.40,110.90}},
	{"Los Flores",                  {2581.70,-1393.40,-89.00,2747.70,-1135.00,110.90}},
	{"Aeroporto Los Santos",    			{1249.60,-2394.30,-89.00,1852.00,-2179.20,110.90}},
	{"Aeroporto Los Santos",    			{1852.00,-2394.30,-89.00,2089.00,-2179.20,110.90}},
	{"Aeroporto Los Santos",    			{1382.70,-2730.80,-89.00,2201.80,-2394.30,110.90}},
	{"Aeroporto Los Santos",    			{1974.60,-2394.30,-39.00,2089.00,-2256.50,60.90}},
	{"Aeroporto Los Santos",    			{1400.90,-2669.20,-39.00,2189.80,-2597.20,60.90}},
	{"Aeroporto Los Santos",    			{2051.60,-2597.20,-39.00,2152.40,-2394.30,60.90}},
	{"Marina",                      {647.70,-1804.20,-89.00,851.40,-1577.50,110.90}},
	{"Marina",                      {647.70,-1577.50,-89.00,807.90,-1416.20,110.90}},
	{"Marina",                      {807.90,-1577.50,-89.00,926.90,-1416.20,110.90}},
	{"Market",                      {787.40,-1416.20,-89.00,1072.60,-1310.20,110.90}},
	{"Market",                      {952.60,-1310.20,-89.00,1072.60,-1130.80,110.90}},
	{"Market",                      {1072.60,-1416.20,-89.00,1370.80,-1130.80,110.90}},
	{"Market",                      {926.90,-1577.50,-89.00,1370.80,-1416.20,110.90}},
	{"Market Station",              {787.40,-1410.90,-34.10,866.00,-1310.20,65.80}},
	{"Martin Bridge",               {-222.10,293.30,0.00,-122.10,476.40,200.00}},
	{"Missionary Hill",             {-2994.40,-811.20,0.00,-2178.60,-430.20,200.00}},
	{"Montgomery",                  {1119.50,119.50,-3.00,1451.40,493.30,200.00}},
	{"Montgomery",                  {1451.40,347.40,-6.10,1582.40,420.80,200.00}},
	{"Montgomery",     				{1546.60,208.10,0.00,1745.80,347.40,200.00}},
	{"Montgomery",     				{1582.40,347.40,0.00,1664.60,401.70,200.00}},
	{"Mulholland",                  {1414.00,-768.00,-89.00,1667.60,-452.40,110.90}},
	{"Mulholland",                  {1281.10,-452.40,-89.00,1641.10,-290.90,110.90}},
	{"Mulholland",                  {1269.10,-768.00,-89.00,1414.00,-452.40,110.90}},
	{"Mulholland",                  {1357.00,-926.90,-89.00,1463.90,-768.00,110.90}},
	{"Mulholland",                  {1318.10,-910.10,-89.00,1357.00,-768.00,110.90}},
	{"Mulholland",                  {1169.10,-910.10,-89.00,1318.10,-768.00,110.90}},
	{"Mulholland",                  {768.60,-954.60,-89.00,952.60,-860.60,110.90}},
	{"Mulholland",                  {687.80,-860.60,-89.00,911.80,-768.00,110.90}},
	{"Mulholland",                  {737.50,-768.00,-89.00,1142.20,-674.80,110.90}},
	{"Mulholland",                  {1096.40,-910.10,-89.00,1169.10,-768.00,110.90}},
	{"Mulholland",                  {952.60,-937.10,-89.00,1096.40,-860.60,110.90}},
	{"Mulholland",                  {911.80,-860.60,-89.00,1096.40,-768.00,110.90}},
	{"Mulholland",                  {861.00,-674.80,-89.00,1156.50,-600.80,110.90}},
	{"Mulholland",     				{1463.90,-1150.80,-89.00,1812.60,-768.00,110.90}},
	{"North Rock",                  {2285.30,-768.00,0.00,2770.50,-269.70,200.00}},
	{"Ocean Docks",                 {2373.70,-2697.00,-89.00,2809.20,-2330.40,110.90}},
	{"Ocean Docks",                 {2201.80,-2418.30,-89.00,2324.00,-2095.00,110.90}},
	{"Ocean Docks",                 {2324.00,-2302.30,-89.00,2703.50,-2145.10,110.90}},
	{"Ocean Docks",                 {2089.00,-2394.30,-89.00,2201.80,-2235.80,110.90}},
	{"Ocean Docks",                 {2201.80,-2730.80,-89.00,2324.00,-2418.30,110.90}},
	{"Ocean Docks",                 {2703.50,-2302.30,-89.00,2959.30,-2126.90,110.90}},
	{"Ocean Docks",                 {2324.00,-2145.10,-89.00,2703.50,-2059.20,110.90}},
	{"Ocean Flats",                 {-2994.40,277.40,-9.10,-2867.80,458.40,200.00}},
	{"Ocean Flats",                 {-2994.40,-222.50,-0.00,-2593.40,277.40,200.00}},
	{"Ocean Flats",                 {-2994.40,-430.20,-0.00,-2831.80,-222.50,200.00}},
	{"Octane Springs",              {338.60,1228.50,0.00,664.30,1655.00,200.00}},
	{"Old Venturas Strip",          {2162.30,2012.10,-89.00,2685.10,2202.70,110.90}},
	{"Palisades",                   {-2994.40,458.40,-6.10,-2741.00,1339.60,200.00}},
	{"Palomino Creek",              {2160.20,-149.00,0.00,2576.90,228.30,200.00}},
	{"Paradiso",                    {-2741.00,793.40,-6.10,-2533.00,1268.40,200.00}},
	{"Pershing Square",             {1440.90,-1722.20,-89.00,1583.50,-1577.50,110.90}},
	{"Pilgrim",                     {2437.30,1383.20,-89.00,2624.40,1783.20,110.90}},
	{"Pilgrim",                     {2624.40,1383.20,-89.00,2685.10,1783.20,110.90}},
	{"Pilson",         				{1098.30,2243.20,-89.00,1377.30,2507.20,110.90}},
	{"Pirates in Men's Pants",      {1817.30,1469.20,-89.00,2027.40,1703.20,110.90}},
	{"Playa del Seville",           {2703.50,-2126.90,-89.00,2959.30,-1852.80,110.90}},
	{"Prickle Pine",                {1534.50,2583.20,-89.00,1848.40,2863.20,110.90}},
	{"Prickle Pine",                {1117.40,2507.20,-89.00,1534.50,2723.20,110.90}},
	{"Prickle Pine",                {1848.40,2553.40,-89.00,1938.80,2863.20,110.90}},
	{"Prickle Pine",                {1938.80,2624.20,-89.00,2121.40,2861.50,110.90}},
	{"Queens",                      {-2533.00,458.40,0.00,-2329.30,578.30,200.00}},
	{"Queens",                      {-2593.40,54.70,0.00,-2411.20,458.40,200.00}},
	{"Queens",                      {-2411.20,373.50,0.00,-2253.50,458.40,200.00}},
	{"Randolph Industrial",         {1558.00,596.30,-89.00,1823.00,823.20,110.90}},
	{"Redsands East",               {1817.30,2011.80,-89.00,2106.70,2202.70,110.90}},
	{"Redsands East",               {1817.30,2202.70,-89.00,2011.90,2342.80,110.90}},
	{"Redsands East",               {1848.40,2342.80,-89.00,2011.90,2478.40,110.90}},
	{"Redsands West",               {1236.60,1883.10,-89.00,1777.30,2142.80,110.90}},
	{"Redsands West",               {1297.40,2142.80,-89.00,1777.30,2243.20,110.90}},
	{"Redsands West",               {1377.30,2243.20,-89.00,1704.50,2433.20,110.90}},
	{"Redsands West",               {1704.50,2243.20,-89.00,1777.30,2342.80,110.90}},
	{"Regular Tom",                 {-405.70,1712.80,-3.00,-276.70,1892.70,200.00}},
	{"Richman",                     {647.50,-1118.20,-89.00,787.40,-954.60,110.90}},
	{"Richman",                     {647.50,-954.60,-89.00,768.60,-860.60,110.90}},
	{"Richman",                     {225.10,-1369.60,-89.00,334.50,-1292.00,110.90}},
	{"Richman",                     {225.10,-1292.00,-89.00,466.20,-1235.00,110.90}},
	{"Richman",                     {72.60,-1404.90,-89.00,225.10,-1235.00,110.90}},
	{"Richman",                     {72.60,-1235.00,-89.00,321.30,-1008.10,110.90}},
	{"Richman",                     {321.30,-1235.00,-89.00,647.50,-1044.00,110.90}},
	{"Richman",                     {321.30,-1044.00,-89.00,647.50,-860.60,110.90}},
	{"Richman",                     {321.30,-860.60,-89.00,687.80,-768.00,110.90}},
	{"Richman",                     {321.30,-768.00,-89.00,700.70,-674.80,110.90}},
	{"Robada",         				{-1119.00,1178.90,-89.00,-862.00,1351.40,110.90}},
	{"Roca Escalante",              {2237.40,2202.70,-89.00,2536.40,2542.50,110.90}},
	{"Roca Escalante",              {2536.40,2202.70,-89.00,2625.10,2442.50,110.90}},
	{"Rockshore East",              {2537.30,676.50,-89.00,2902.30,943.20,110.90}},
	{"Rockshore West",              {1997.20,596.30,-89.00,2377.30,823.20,110.90}},
	{"Rockshore West",              {2377.30,596.30,-89.00,2537.30,788.80,110.90}},
	{"Rodeo",                       {72.60,-1684.60,-89.00,225.10,-1544.10,110.90}},
	{"Rodeo",                       {72.60,-1544.10,-89.00,225.10,-1404.90,110.90}},
	{"Rodeo",                       {225.10,-1684.60,-89.00,312.80,-1501.90,110.90}},
	{"Rodeo",                       {225.10,-1501.90,-89.00,334.50,-1369.60,110.90}},
	{"Rodeo",                       {334.50,-1501.90,-89.00,422.60,-1406.00,110.90}},
	{"Rodeo",                       {312.80,-1684.60,-89.00,422.60,-1501.90,110.90}},
	{"Rodeo",                       {422.60,-1684.60,-89.00,558.00,-1570.20,110.90}},
	{"Rodeo",                       {558.00,-1684.60,-89.00,647.50,-1384.90,110.90}},
	{"Rodeo",                       {466.20,-1570.20,-89.00,558.00,-1385.00,110.90}},
	{"Rodeo",                       {422.60,-1570.20,-89.00,466.20,-1406.00,110.90}},
	{"Rodeo",                       {466.20,-1385.00,-89.00,647.50,-1235.00,110.90}},
	{"Rodeo",                       {334.50,-1406.00,-89.00,466.20,-1292.00,110.90}},
	{"Royal Casino",                {2087.30,1383.20,-89.00,2437.30,1543.20,110.90}},
	{"San Andreas Sound",           {2450.30,385.50,-100.00,2759.20,562.30,200.00}},
	{"Santa Flora",                 {-2741.00,458.40,-7.60,-2533.00,793.40,200.00}},
	{"Santa Maria Beach",           {342.60,-2173.20,-89.00,647.70,-1684.60,110.90}},
	{"Santa Maria Beach",           {72.60,-2173.20,-89.00,342.60,-1684.60,110.90}},
	{"Shady Cabin",                 {-1632.80,-2263.40,-3.00,-1601.30,-2231.70,200.00}},
	{"Shady Creeks",                {-1820.60,-2643.60,-8.00,-1226.70,-1771.60,200.00}},
	{"Shady Creeks",                {-2030.10,-2174.80,-6.10,-1820.60,-1771.60,200.00}},
	{"Sobell Rail Yards",           {2749.90,1548.90,-89.00,2923.30,1937.20,110.90}},
	{"Spinybed",                    {2121.40,2663.10,-89.00,2498.20,2861.50,110.90}},
	{"Starfish Casino",             {2437.30,1783.20,-89.00,2685.10,2012.10,110.90}},
	{"Starfish Casino",             {2437.30,1858.10,-39.00,2495.00,1970.80,60.90}},
	{"Starfish Casino",             {2162.30,1883.20,-89.00,2437.30,2012.10,110.90}},
	{"Temple",                      {1252.30,-1130.80,-89.00,1378.30,-1026.30,110.90}},
	{"Temple",                      {1252.30,-1026.30,-89.00,1391.00,-926.90,110.90}},
	{"Temple",                      {1252.30,-926.90,-89.00,1357.00,-910.10,110.90}},
	{"Temple",                      {952.60,-1130.80,-89.00,1096.40,-937.10,110.90}},
	{"Temple",                      {1096.40,-1130.80,-89.00,1252.30,-1026.30,110.90}},
	{"Temple",                      {1096.40,-1026.30,-89.00,1252.30,-910.10,110.90}},
	{"The Camel's Toe",             {2087.30,1203.20,-89.00,2640.40,1383.20,110.90}},
	{"The Clown's Pocket",          {2162.30,1783.20,-89.00,2437.30,1883.20,110.90}},
	{"The Emerald Isle",            {2011.90,2202.70,-89.00,2237.40,2508.20,110.90}},
	{"The Farm",                    {-1209.60,-1317.10,114.90,-908.10,-787.30,251.90}},
	{"Four Dragons Casino",         {1817.30,863.20,-89.00,2027.30,1083.20,110.90}},
	{"The High Roller",             {1817.30,1283.20,-89.00,2027.30,1469.20,110.90}},
	{"The Mako Span",               {1664.60,401.70,0.00,1785.10,567.20,200.00}},
	{"The Panopticon",              {-947.90,-304.30,-1.10,-319.60,327.00,200.00}},
	{"The Pink Swan",               {1817.30,1083.20,-89.00,2027.30,1283.20,110.90}},
	{"The Sherman Dam",             {-968.70,1929.40,-3.00,-481.10,2155.20,200.00}},
	{"The Strip",                   {2027.40,863.20,-89.00,2087.30,1703.20,110.90}},
	{"The Strip",                   {2106.70,1863.20,-89.00,2162.30,2202.70,110.90}},
	{"The Strip",                   {2027.40,1783.20,-89.00,2162.30,1863.20,110.90}},
	{"The Strip",                   {2027.40,1703.20,-89.00,2137.40,1783.20,110.90}},
	{"The Visage",                  {1817.30,1863.20,-89.00,2106.70,2011.80,110.90}},
	{"The Visage",                  {1817.30,1703.20,-89.00,2027.40,1863.20,110.90}},
	{"Unity Station",               {1692.60,-1971.80,-20.40,1812.60,-1932.80,79.50}},
	{"Valle Ocultado",              {-936.60,2611.40,2.00,-715.90,2847.90,200.00}},
	{"Verdant Bluffs",              {930.20,-2488.40,-89.00,1249.60,-2006.70,110.90}},
	{"Verdant Bluffs",              {1073.20,-2006.70,-89.00,1249.60,-1842.20,110.90}},
	{"Verdant Bluffs",              {1249.60,-2179.20,-89.00,1692.60,-1842.20,110.90}},
	{"Verdant Meadows",             {37.00,2337.10,-3.00,435.90,2677.90,200.00}},
	{"Verona Beach",                {647.70,-2173.20,-89.00,930.20,-1804.20,110.90}},
	{"Verona Beach",                {930.20,-2006.70,-89.00,1073.20,-1804.20,110.90}},
	{"Verona Beach",                {851.40,-1804.20,-89.00,1046.10,-1577.50,110.90}},
	{"Verona Beach",                {1161.50,-1722.20,-89.00,1323.90,-1577.50,110.90}},
	{"Verona Beach",                {1046.10,-1722.20,-89.00,1161.50,-1577.50,110.90}},
	{"Vinewood",                    {787.40,-1310.20,-89.00,952.60,-1130.80,110.90}},
	{"Vinewood",                    {787.40,-1130.80,-89.00,952.60,-954.60,110.90}},
	{"Vinewood",                    {647.50,-1227.20,-89.00,787.40,-1118.20,110.90}},
	{"Vinewood",                    {647.70,-1416.20,-89.00,787.40,-1227.20,110.90}},
	{"Whitewood Estates",           {883.30,1726.20,-89.00,1098.30,2507.20,110.90}},
	{"Whitewood Estates",           {1098.30,1726.20,-89.00,1197.30,2243.20,110.90}},
	{"Willowfield",                 {1970.60,-2179.20,-89.00,2089.00,-1852.80,110.90}},
	{"Willowfield",                 {2089.00,-2235.80,-89.00,2201.80,-1989.90,110.90}},
	{"Willowfield",                 {2089.00,-1989.90,-89.00,2324.00,-1852.80,110.90}},
	{"Willowfield",                 {2201.80,-2095.00,-89.00,2324.00,-1989.90,110.90}},
	{"Willowfield",                 {2541.70,-1941.40,-89.00,2703.50,-1852.80,110.90}},
	{"Willowfield",                 {2324.00,-2059.20,-89.00,2541.70,-1852.80,110.90}},
	{"Willowfield",                 {2541.70,-2059.20,-89.00,2703.50,-1941.40,110.90}},
	{"Yellow Bell Station",         {1377.40,2600.40,-21.90,1492.40,2687.30,78.00}},
	// Citys Zones
	{"Los Santos",                  {44.60,-2892.90,-242.90,2997.00,-768.00,900.00}},
	{"Las Venturas",                {869.40,596.30,-242.90,2997.00,2993.80,900.00}},
	{"Bone County",                 {-480.50,596.30,-242.90,869.40,2993.80,900.00}},
	{"Tierra Robada",               {-2997.40,1659.60,-242.90,-480.50,2993.80,900.00}},
	{"Tierra Robada",               {-1213.90,596.30,-242.90,-480.50,1659.60,900.00}},
	{"San Fierro",                  {-2997.40,-1115.50,-242.90,-1213.90,1659.60,900.00}},
	{"Red County",                  {-1213.90,-768.00,-242.90,2997.00,596.30,900.00}},
	{"Flint County",                {-1213.90,-2892.90,-242.90,44.60,-768.00,900.00}},
	{"Whetstone",                   {-2997.40,-2892.90,-242.90,-1213.90,-1115.50,900.00}}
};

stock GetPlayer2DZone(playerid, zone[], len)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
 	for(new i = 0; i != sizeof(SanAndreasZones); i++ ){
	if(x >= SanAndreasZones[i][Zone_Area][0] && x <= SanAndreasZones[i][Zone_Area][3] && y >= SanAndreasZones[i][Zone_Area][1] && y <= SanAndreasZones[i][Zone_Area][4]){
	return format(zone, len, SanAndreasZones[i][Zone_Name], 0);}
	}
	return 0;
}

new VehiclesName[][] =
{
   "Landstalker",
   "Bravura",
   "Buffalo",
   "Linerunner",
   "Pereniel",
   "Sentinel",
   "Dumper",
   "Firetruck",
   "Trashmaster",
   "Stretch",
   "Manana",
   "Infernus",
   "Voodoo",
   "Pony",
   "Mule",
   "Cheetah",
   "Ambulance",
   "Leviathan",
   "Moonbeam",
   "Esperanto",
   "Taxi",
   "Washington",
   "Bobcat",
   "Mr Whoopee",
   "BF Injection",
   "Hunter",
   "Premier",
   "Enforcer",
   "Securicar",
   "Banshee",
   "Predator",
   "Bus",
   "Rhino",
   "Barracks",
   "Hotknife",
   "Trailer",
   "Previon",
   "Coach",
   "Cabbie",
   "Stallion",
   "Rumpo",
   "RC Bandit",
   "Romero",
   "Packer",
   "Monster Truck",
   "Admiral",
   "Squalo",
   "Seasparrow",
   "Pizzaboy",
   "Tram",
   "Trailer",
   "Turismo",
   "Speeder",
   "Reefer",
   "Tropic",
   "Flatbed",
   "Yankee",
   "Caddy",
   "Solair",
   "Berkley's RC Van",
   "Skimmer",
   "PCJ-600",
   "Faggio",
   "Freeway",
   "RC Baron",
   "RC Raider",
   "Glendale",
   "Oceanic",
   "Sanchez",
   "Sparrow",
   "Patriot",
   "Quad",
   "Coastguard",
   "Dinghy",
   "Hermes",
   "Sabre",
   "Rustler",
   "ZR-350",
   "Walton",
   "Regina",
   "Comet",
   "BMX",
   "Burrito",
   "Camper",
   "Marquis",
   "Baggage",
   "Dozer",
   "Maverick",
   "News Chopper",
   "Rancher",
   "FBI Rancher",
   "Virgo",
   "Greenwood",
   "Jetmax",
   "Hotring",
   "Sandking",
   "Blista Compact",
   "Police Maverick",
   "Boxville",
   "Benson",
   "Mesa",
   "RC Goblin",
   "Hotring Racer",
   "Hotring Racer",
   "Bloodring Banger",
   "Rancher",
   "Super GT",
   "Elegant",
   "Journey",
   "Bike",
   "Mountain Bike",
   "Beagle",
   "Cropdust",
   "Stunt",
   "Tanker",
   "RoadTrain",
   "Nebula",
   "Majestic",
   "Buccaneer",
   "Shamal",
   "Hydra",
   "FCR-900",
   "NRG-500",
   "HPV1000",
   "Cement Truck",
   "Tow Truck",
   "Fortune",
   "Cadrona",
   "FBI Truck",
   "Willard",
   "Forklift",
   "Tractor",
   "Combine",
   "Feltzer",
   "Remington",
   "Slamvan",
   "Blade",
   "Freight",
   "Streak",
   "Vortex",
   "Vincent",
   "Bullet",
   "Clover",
   "Sadler",
   "Firetruck",
   "Hustler",
   "Intruder",
   "Primo",
   "Cargobob",
   "Tampa",
   "Sunrise",
   "Merit",
   "Utility",
   "Nevada",
   "Yosemite",
   "Windsor",
   "Monster Truck",
   "Monster Truck",
   "Uranus",
   "Jester",
   "Sultan",
   "Stratum",
   "Elegy",
   "Raindance",
   "RC Tiger",
   "Flash",
   "Tahoma",
   "Savanna",
   "Bandito",
   "Freight",
   "Trailer",
   "Kart",
   "Mower",
   "Duneride",
   "Sweeper",
   "Broadway",
   "Tornado",
   "AT-400",
   "DFT-30",
   "Huntley",
   "Stafford",
   "BF-400",
   "Newsvan",
   "Tug",
   "Trailer",
   "Emperor",
   "Wayfarer",
   "Euros",
   "Hotdog",
   "Club",
   "Trailer",
   "Trailer",
   "Andromada",
   "Dodo",
   "RC Cam",
   "Launch",
   "Police Car (LS)",
   "Police Car (SF)",
   "Police Car (LV)",
   "Police Ranger",
   "Picador",
   "S.W.A.T. Van",
   "Alpha",
   "Phoenix",
   "Glendale",
   "Sadler",
   "Luggage Trailer",
   "Luggage Trailer",
   "Stair Trailer",
   "Boxville",
   "Farm Plow",
   "Utility Trailer"
};
new Float:poskm[3];
stock GetSpeed(playerid, mode = 1)
{
    GetVehicleVelocity(GetPlayerVehicleID(playerid), poskm[0], poskm[1], poskm[2]);
    return IsPlayerInAnyVehicle(playerid) ? floatround(((floatsqroot(((poskm[0] * poskm[0]) + (poskm[1] * poskm[1]) + (poskm[2] * poskm[2]))) * (!mode ? 105.0 : 170.0))) * 1) : 0;
}

stock PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
    if(IsPlayerConnected(playerid))
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
	}
	return 0;
}

stock VeiculoToPoint(Float:radi, veiculo, Float:x, Float:y, Float:z)
{
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;
	GetVehiclePos(veiculo, oldposx, oldposy, oldposz);
	tempposx = (oldposx -x);
	tempposy = (oldposy -y);
	tempposz = (oldposz -z);
	if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
	{
		return 1;
	}
	return 0;
}

stock IsaPostodeGasolina(playerid)
{
    if(IsPlayerConnected(playerid))
	{
		if(PlayerToPoint(6.0,playerid,1004.0070,-939.3102,42.1797) || PlayerToPoint(6.0,playerid,1944.3260,-1772.9254,13.3906))
		{//LS
		    return 1;
		}
		else if(PlayerToPoint(6.0,playerid,-90.5515,-1169.4578,2.4079) || PlayerToPoint(6.0,playerid,-1609.7958,-2718.2048,48.5391))
		{//LS
		    return 1;
		}
		else if(PlayerToPoint(6.0,playerid,-2029.4968,156.4366,28.9498) || PlayerToPoint(8.0,playerid,-2408.7590,976.0934,45.4175))
		{//SF
		    return 1;
		}
		else if(PlayerToPoint(5.0,playerid,-2243.9629,-2560.6477,31.8841) || PlayerToPoint(8.0,playerid,-1676.6323,414.0262,6.9484))
		{//Between LS and SF
		    return 1;
		}
		else if(PlayerToPoint(6.0,playerid,2202.2349,2474.3494,10.5258) || PlayerToPoint(10.0,playerid,614.9333,1689.7418,6.6968))
		{//LV
		    return 1;
		}
		else if(PlayerToPoint(8.0,playerid,-1328.8250,2677.2173,49.7665) || PlayerToPoint(6.0,playerid,70.3882,1218.6783,18.5165))
		{//LV
		    return 1;
		}
		else if(PlayerToPoint(8.0,playerid,2113.7390,920.1079,10.5255) || PlayerToPoint(6.0,playerid,-1327.7218,2678.8723,50.0625))
		{//LV
		    return 1;
		}
		else if(PlayerToPoint(8.0,playerid,1936.6622,-1774.5537,19.5250) || PlayerToPoint(8.0,playerid,1940.1401,-1773.8149,19.5250) || PlayerToPoint(8.0,playerid,1945.3495,-1773.6088,19.5250))
		{//Posto Sul LS em cima (para Helli)
		    return 1;
  		}
  		// novos postos lv e posto em ls em cima pra abastecer hellicopteros
  		else if(PlayerToPoint(8.0,playerid,1012.8469,-938.0317,48.2118) || PlayerToPoint(8.0,playerid,1006.0637,-938.0870,48.2118) || PlayerToPoint(8.0,playerid,997.0472,-938.8961,48.2118))
  		{// posto norte em cima
  		    return 1;
  		}
  		else if(PlayerToPoint(8.0,playerid,-93.1007,-1175.9906,7.7439) || PlayerToPoint(8.0,playerid,-91.7711,-1172.2506,7.7439) || PlayerToPoint(8.0,playerid,-89.2291,-1165.8230,7.7439))
  		{// posto entre LS e SF em cima pra Helli
  		    return 1;
  		}
  		else if(PlayerToPoint(8.0,playerid,-1661.2419,417.0566,12.4375) || PlayerToPoint(8.0,playerid,-1670.3346,426.3475,12.4375) || PlayerToPoint(8.0,playerid,-1679.4481,435.6314,12.4375)
		|| PlayerToPoint(8.0,playerid,-1688.1637,429.4580,12.4375) || PlayerToPoint(8.0,playerid,-1680.2806,421.0007,12.4375) || PlayerToPoint(8.0,playerid,-1670.9506,411.1093,12.4375)
		|| PlayerToPoint(8.0,playerid,-1674.7444,403.7433,12.4375) || PlayerToPoint(8.0,playerid,-1684.1880,413.3348,12.4375) || PlayerToPoint(8.0,playerid,-1693.2275,422.3407,12.4303)
		|| PlayerToPoint(8.0,playerid,-1698.6863,419.2854,12.4375) || PlayerToPoint(8.0,playerid,-1688.3983,408.8546,12.4303) || PlayerToPoint(8.0,playerid,-1680.5463,400.7513,12.4303))
  		{// Posto SF do lado do HQ EXE em cima para Helli
  		    return 1;
  		}
  		else if(PlayerToPoint(8.0,playerid,-2411.5181,959.2078,51.6816) || PlayerToPoint(8.0,playerid,-2411.2871,968.3094,51.6816) || PlayerToPoint(8.0,playerid,-2411.1687,979.5865,51.6816) || PlayerToPoint(8.0,playerid,-2410.8831,987.9509,51.6816))
  		{// posto sf em cima 2
  		    return 1;
  		}
  		else if(PlayerToPoint(8.0,playerid,2194.0344,2474.2964,10.8203) || PlayerToPoint(8.0,playerid,2205.6147,2474.9194,10.8203) || PlayerToPoint(8.0,playerid,2193.3459,2475.5112,17.0938) || PlayerToPoint(8.0,playerid,2199.2363,2475.3950,17.0938)
  		|| PlayerToPoint(8.0,playerid,2208.2173,2475.3098,17.0938))
  		{
  		    return 1;
  		}
  		else if(PlayerToPoint(8.0,playerid,2115.5449,927.9235,17.0547) || PlayerToPoint(8.0,playerid,2115.0149,922.3093,17.0547) || PlayerToPoint(8.0,playerid,2114.9443,913.1669,17.0547))
  		{
  		    return 1;
  		}
  		else if(PlayerToPoint(8.0,playerid,-1328.4664,2668.3730,56.1641) || PlayerToPoint(8.0,playerid,-1328.5859,2675.2805,56.1641) || PlayerToPoint(8.0,playerid,-1327.3739,2683.7720,56.1641))
  		{
  		    return 1;
  		}
  		else if(PlayerToPoint(8.0,playerid,2640.1094,1098.9368,10.8203) || PlayerToPoint(8.0,playerid,2639.6763,1110.0609,10.8203) || PlayerToPoint(8.0,playerid,2640.3928,1097.5302,17.0547)
  		|| PlayerToPoint(8.0,playerid,2640.4573,1102.9498,17.0547) || PlayerToPoint(8.0,playerid,2640.5471,1112.4362,17.0547))
  		{
  		    return 1;
  		}
  		else if(PlayerToPoint(8.0,playerid,2147.4551,2744.0596,10.3880) || PlayerToPoint(8.0,playerid,2147.5208,2752.1270,10.3944) || PlayerToPoint(8.0,playerid,2147.4202,2756.8237,17.0542)
		|| PlayerToPoint(8.0,playerid,2147.6714,2748.7803,17.0542) || PlayerToPoint(8.0,playerid,2147.5098,2739.4927,17.0542))
		{
		    return 1;
		}
		else if(PlayerToPoint(8.0,playerid,1596.4349,2202.8833,10.3854) || PlayerToPoint(8.0,playerid,1596.0420,2194.8379,10.3971) || PlayerToPoint(8.0,playerid,1597.5720,2190.1147,17.5938) || PlayerToPoint(8.0,playerid,1597.2673,2195.9971,17.5938) || PlayerToPoint(8.0,playerid,1596.6069,2206.4272,17.5938))
		{
		    return 1;
		}
	}
	return 0;
}
/*
stock PC_DarDinheiro(playerid,Dinheiro) return SetPVarInt(playerid,"dinheiro",GetPVarInt(playerid,"dinheiro")+Dinheiro);
stock PC_SetarDinheiro(playerid,Dinheiro) return SetPVarInt(playerid,"dinheiro",Dinheiro);
stock PC_GetarDinheiro(playerid) return GetPVarInt(playerid,"dinheiro");
stock PC_ResetarDinheiro(playerid) return SetPVarInt(playerid,"dinheiro",0);
stock ChefaoSetarDinheiro(playerid) { ResetPlayerMoney(playerid); GivePlayerMoney(playerid, GetPVarInt(playerid,"dinheiro")); }
stock PC_AtualizarDinheiro(playerid) if(GetPlayerMoney(playerid) != GetPVarInt(playerid,"dinheiro")) ChefaoSetarDinheiro(playerid);
*/


// Verssão 0.2x
/*new PC_Dinheiro[MAX_PLAYERS];
stock PC_DarDinheiro(playerid,Dinheiro) return PC_Dinheiro[playerid] += Dinheiro;
stock PC_SetarDinheiro(playerid,Dinheiro) return PC_Dinheiro[playerid] = Dinheiro;
stock PC_GetarDinheiro(playerid) return PC_Dinheiro[playerid];
stock PC_ResetarDinheiro(playerid) return PC_Dinheiro[playerid] = 0;
stock ChefaoSetarDinheiro(playerid) { ResetPlayerMoney(playerid); GivePlayerMoney(playerid, PC_Dinheiro[playerid]); }
stock PC_AtualizarDinheiro(playerid) if(GetPlayerMoney(playerid) != PC_Dinheiro[playerid]) ChefaoSetarDinheiro(playerid);*/


#define MAX_ROUBOS 27
enum R0ub0Inf0
{
	Float:RFX,
	Float:RFY,
	Float:RFZ,
	Float:RFAngulo,
	Float:RAX,
	Float:RAY,
	Float:RAZ,
	Float:RAAngulo,
	RouboNome[128],
	Cofre,
	Bomba,
	Playerid = INVALID_PLAYER_ID,
	BombaPlantada,
	BombaExplodida,
	CofreRoubado,
	GranaRecolhida,
};
static RouboInfo[MAX_ROUBOS][R0ub0Inf0], CofreGrana[5] = {30000,40000,50000,60000,70000};
//new CofreGrana[5] = {30000,40000,50000,60000,70000};

stock CriarCofre(id,Float:cofreX,Float:cofreY,Float:cofreZ,Float:RAngulo,RNome[],Float:cofreFX,Float:cofreFY,Float:cofreFZ,Float:RFSAngulo)
{
    RouboInfo[id][Cofre] = CreateObject(2332,cofreX,cofreY,cofreZ,0.0,0.0,RAngulo,200);
    Create3DTextLabel(RNome,0xFFFF00FF,cofreX,cofreY,cofreZ+1.0,25.0,0,0);
	RouboInfo[id][RFX] = cofreX;
    RouboInfo[id][RFY] = cofreY;
    RouboInfo[id][RFZ] = cofreZ;
    RouboInfo[id][RFAngulo] = RAngulo;
    RouboInfo[id][RAX] = cofreFX;
    RouboInfo[id][RAY] = cofreFY;
    RouboInfo[id][RAZ] = cofreFZ;
    RouboInfo[id][RAAngulo] = RFSAngulo;
    strmid(RouboInfo[id][RouboNome], RNome, 0, strlen(RNome), 128);
	return 1;
}
new WantedPoints[MAX_PLAYERS];
stock PlantarBombaCofre(playerid,id)
{
    if(RouboInfo[id][CofreRoubado] == 1)
		{
    		SendClientMessage(playerid,0xFFFF00AA,"O cofre ainda não foi restaurado.");
    		return 1;
		}
	SendClientMessage(playerid,0xFFFF00AA,"Você armou uma bomba em 5 segundos ela ira explodir!");
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
	new Float:bX,Float:bY,Float:bZ;
	GetPlayerPos(playerid,bX,bY,bZ);
	RouboInfo[id][Bomba] = CreateObject(1654,bX+0.3,bY-0.3,bZ-0.8,0.0,0.0,0.0,200);
	RouboInfo[id][Playerid] = playerid;
	RouboInfo[id][BombaPlantada] = 1;
    WantedPoints[playerid]+=4;
	SetPlayerCriminal(playerid,255,"Roubo de Cofre");
	return 1;
}


stock ExplodirCofre(playerid,id)
{
    new string[256];
    format(string, sizeof(string), "%s está roubando o %s", pNome(playerid), RouboInfo[id][RouboNome]);
	SendClientMessageToAll(0xE23B4BAA,string);
	CreateExplosion(RouboInfo[id][RFX], RouboInfo[id][RFY] , RouboInfo[id][RFZ], 0, 0);
	DestroyObject(RouboInfo[id][Bomba]);
	DestroyObject(RouboInfo[id][Cofre]);
	RouboInfo[id][CofreRoubado] = 1;
	RouboInfo[id][BombaExplodida] = 1;
	RouboInfo[id][Cofre] = CreateObject(1829,RouboInfo[id][RAX],RouboInfo[id][RAY],RouboInfo[id][RAZ],0.0,0.0,RouboInfo[id][RAAngulo],200);
    SendClientMessage(playerid,0xFFFF00AA,"Aguarde 2 minutos para recolher o dinheiro!");
	return 1;
}

stock ResetarCofre(id)
{
	new string[256];
    RouboInfo[id][CofreRoubado] = 0;
    RouboInfo[id][BombaPlantada] = 0;
    RouboInfo[id][BombaExplodida] = 0;
    RouboInfo[id][GranaRecolhida] = 0;
    RouboInfo[id][Playerid] = INVALID_PLAYER_ID;
    DestroyObject(RouboInfo[id][Cofre]);
    RouboInfo[id][Cofre] = CreateObject(2332,RouboInfo[id][RFX],RouboInfo[id][RFY],RouboInfo[id][RFZ],0.0,0.0,RouboInfo[id][RFAngulo],200);
    format(string, sizeof(string), "O %s foi restaurado e ja pode ser roubado de novo!", RouboInfo[id][RouboNome]);
	SendClientMessageToAll(0xFFFF00AA,string);
	return 1;
}
stock RecolherGranaCofre(playerid,id)
{
	new string[256];
    new rand = random(sizeof(CofreGrana));
	GivePlayerMoneyEx(playerid,CofreGrana[rand]);
	RouboInfo[id][GranaRecolhida] = 1;
	format(string, sizeof(string), "%s Explodiu e roubou O %s e faturou %d!",pNome(playerid), RouboInfo[id][RouboNome], CofreGrana[rand]);
	SendClientMessageToAll(0xE23B4BAA,string);
	PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
	return 1;
}
stock GetCofreID(playerid)
{
    for(new id=0; id<MAX_ROUBOS; id++)
    {
    	if(PlayerToPoint(4.0,playerid,RouboInfo[id][RFX],RouboInfo[id][RFY],RouboInfo[id][RFZ]))
    	{
    	    return id;
   		}
   	}
   	return MAX_ROUBOS+1;
}
stock AtualizarCofre()
{
    for(new id=0; id<MAX_ROUBOS; id++)
    {
        if(RouboInfo[id][BombaPlantada] >= 1)
        {
            RouboInfo[id][BombaPlantada] += 1;
            if(RouboInfo[id][BombaPlantada] >= 8)
            {
                if(IsPlayerConnected(RouboInfo[id][Playerid]))
                {
                	if(RouboInfo[id][BombaExplodida] <= 0) { ExplodirCofre(RouboInfo[id][Playerid],id); }
               	}
            }
            if(RouboInfo[id][BombaPlantada] >= 120)
            {
                if(IsPlayerConnected(RouboInfo[id][Playerid]))
                {
                    if(PlayerToPoint(4.0,RouboInfo[id][Playerid],RouboInfo[id][RFX],RouboInfo[id][RFY],RouboInfo[id][RFZ]))
                    {
                		if(RouboInfo[id][GranaRecolhida] <= 0) { RecolherGranaCofre(RouboInfo[id][Playerid],id); }
                	}
                	else
                	{
                	    if(RouboInfo[id][GranaRecolhida] <= 0)
			 			{
			 			    RouboInfo[id][GranaRecolhida] = 1;
			 				SendClientMessage(RouboInfo[id][Playerid],0xFFFF00AA,"Você não estáva perto do cofre e por isso não recolheu a grana!");
		 				}
                	}
               	}
            }
            if(RouboInfo[id][BombaPlantada] >= 1800)
            {
                ResetarCofre(id);
            }
        }
    }
    return 1;
}

stock SetPlayerCofrePos(playerid,cofreid)
{
    SetPlayerPos(playerid,RouboInfo[cofreid][RFX],RouboInfo[cofreid][RFY],RouboInfo[cofreid][RFZ]);
}

