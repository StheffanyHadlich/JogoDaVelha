#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define N 3
#define MaximoJogadas 9
#define MinimoJogadas 5

int tabuleiro[N][N];
int tabuleiroExibido[N][N];
int replayLinhas[MaximoJogadas];
int replayColunas[MaximoJogadas];


void salvarReplay(int linha, int coluna);
void replay(int jogoCount);

void iniciarTabuleiro();
void exibirTabuleiro(int contadorJogadas, int showTabuleiro[][N]);
void mensagens(int etapa);
bool verificarDisponibilidade(int linha, int coluna,int vez);
void jogadasUsuario(int vez);
bool verificarLinhas(int vez);
bool verificarColunas(int vez);
bool verificarDiagonais( int vez);    
bool verificarTrinca(int vez);
bool posicaoLivreAleatoria(int vez);
bool colunaEstrategia(int b, int vez, int marcador);
bool linhaEstrategia(int a, int vez, int marcador);
bool diagonalPrincipalEstrategia(int vez, int marcador);
bool diagonalSecundariaEstrategia(int vez, int marcador);
bool verificarVizinhos(int a, int b, int vez, int marcador);
bool estrategia(int vez, int marcador);
void jogadasComputador( int vez, int nivel);
void jogo(int tipoJogo);