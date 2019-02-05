/*
*
*	-= PGP INCLUDE =-
*	Protioso Gerenciamento de Pickups
*
*	Autor: Protioso ([VGS]Protioso_OC)
*  	Primeira versão: 10 de dezembro de 2008 - 1.0
* 	Atualizações: 15 de dezembro de 2008 - 1.15
*	 			  25 de janeiro de 2009 - 1.15D
*                 27 de janeiro de 2009 - 1.3 (versão em uso)
*
*/

#include "PGP\1.3#PGP_LIB\PGP_DPPFI"

/*Lista de funções do sistema PGP -----------------------------------------------------------------------------||

native pgp_JogadorEmPickup(playerid, pgpid);
native pgp_JogadorEntrouEmRaio(playerid, pgpid);
native pgp_CriarPickup(pmodeloid, tipo, Float:x, Float:y, Float:z); 
native pgp_CriarPickupEx(pmodeloid, tipo, Float:x, Float:y, Float:z, mensagem[], estilogametext);
native pgp_CriarPickupR(pmodeloid, tipo, Float:x, Float:y, Float:z, Float:raio);
native pgp_CriarPickupREx(pmodeloid, tipo, Float:x, Float:y, Float:z, Float: raio, mensagem[], estilogametext);
native pgp_PegarPosicaoPickup(pgpid, &Float:x, &Float:y, &Float:z);
native pgp_JogadorNaPickup(playerid, pgpid);
native pgp_JogadorPickup(playerid);
native pgp_JogadorEstaEmPickup(playerid);
native pgp_DesativarPickup(pgpid);
native pgp_DestruirPickup(pgpid);
native pgp_DestruirPickupEx(pgpid);
native pgp_RecriarPickup(pgpid);
native pgp_MudarModelo(pgpid, novomodeloid);
native pgp_MudarTipo(pgpid, novotipo);
native pgp_MudarEstiloGT(pgpid, novoestilo);
native pgp_MudarMensagem(pgpid, novamensagem[]);
native pgp_AdicionarMensagem(pgpid, mensagem[]);
native pgp_MudarRaio(pgpid, Float:novoraio);
native pgp_AdicionarRaio(pgpid, Float:raio);
native pgp_PickupExiste(pickup);
native pgp_JogadorPegaPickup(playerid, pgpid);
native pgp_JogadorEmPickupModelo(playerid, pmodeloid);
native pgp_JogadorRaio(playerid);
native pgp_MensagemPickup(pgpid);
native pgp_PickupPGPOn(pgpid);
native pgp_PickGameText(pgpid, playerid);
native pgp_JogadorPickupPega(playerid);
native pgp_ModeloPickup(pgpid);
native pgp_ZerarPickupPega(playerid);

/------------------------------------------------------------------------------------------------------------||*/
