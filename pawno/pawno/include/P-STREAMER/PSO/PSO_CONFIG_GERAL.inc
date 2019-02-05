/*
*
*	-= P-STREAMER =-
*	Protioso Streamer
*	Autor: Protioso ([VGS]Protioso_OC)
*   Obs.: os valores abaixo podem ser editados conforme sua necessidade!
*
*/

#define PSO_MULTI_SCRIPTS 0 /* Para compartilhar informações com outros scripts.
Deixe em 1 para habilitar (recomendado) e 0 para desabilitar. */
#define PSO_SUBSTITUIR_FUNCOES_ORIGINAIS 1 /* Substitui as funções originais
pelas do PSO. Por exemplo, você põe a função "CreateObject" e ela será
reconhecida como pso_CriarObjeto. Substitui todas as funções padrões de objeto,
sem você precisar alterar o nome da função, apenas deixando o nome original
(CreateObject - exemplo).
Deixe em 1 para habilitar e 0 para desabilitar. */
#define MAX_PSO 1500 /* Limite de objetos (altere como preferir). */
#define PSO_TEMPO_CHECAGEM 500 /* Tempo em milisegundos. */
#define MAX_OBJETOS_JOGADOR 180 /* Máximo que o jogador pode ver. Não pode
ultrapassar passar o limite do SA-MP!
Obs.: o limite de 180 foi definido a partir de vários testes. */
#define PSO_CONSERVAR_OBJETOS 0 /* 0 desativado e 1 ativado... Isto define se
você quer manter os objetos depois que o jogador sair da área e não tiver
excedido o lime de objetos por jogador. */
#define PSO_COMPARTILHAR_FUNC 0 /* 0 desativado e 1 ativado... Pouco recomendado
use apenas se realmente houver necessidade. Leia as últimas linhas do arquivo
PSO Manual.txt para saber mais! */
#define PSO_RAIO_STREAM_PADRAO 135.0 /* Se você não identificar um valor para o
raio que o objeto aparecerá nas funções para criar objeto, este valor irá ser
usado para o novo objeto criado. */
