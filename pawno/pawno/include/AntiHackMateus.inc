new GranaHack[MAX_PLAYERS];

stock GivePlayerGrana(playerid, dinheiro)
{
   GranaHack[playerid] += dinheiro;
   GivePlayerMoney(playerid, dinheiro);
}

stock VerificarGrana(playerid)
{
 if(GranaHack[playerid] < GetPlayerMoney(playerid) || GranaHack[playerid] > GetPlayerMoney(playerid))
  {
   SetPlayerMoney(playerid, GranaHack[playerid]);
  }
}