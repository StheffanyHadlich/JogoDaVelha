#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define N 3
#define MaximoJogadas 9
#define MinimoJogadas 5
int tabuleiro[N][N];

int menuInicial(){
    int escolha;
    printf("JOGO DA VELHA\n");
    printf("Pressione 1 para jogar contra o computador ou 2 para jogar em dupla: ");
    scanf("%d",&escolha); 

    while ((escolha != 1) && (escolha != 2)){
        printf("Entre com uma opção válida. Pressione 1 para jogar contra o computador ou 2 para jogar em dupla: ");
        scanf("%d",&escolha);
    } 

    return escolha;
}

void iniciarTabuleiro(){ // depois montar apresentação para o usuário
    int i, j;
    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            tabuleiro[i][j] =9;
        }
    }
}

void exibirTabuleiro(int contadorJogadas){
    printf("\nTabuleiro na jogada: %d\n",contadorJogadas);
    //system("clear");
    int i, j;
    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d  ",tabuleiro[i][j]);
        }
        printf("\n");
    }
    
}

bool verificarDisponibilidade(int linha, int coluna,int vez){
    if (tabuleiro[linha][coluna]==9){
        tabuleiro[linha][coluna]=vez;
          return true;
    }
    printf("Posicao invalida\n");
    return false;  
}

void jogadasUsuario(int vez){
    int linha, coluna;
    bool disponibilidade = false;
    
    do{
        printf("Jogador %d entre linha e coluna\n",vez);
        scanf("%d",&linha);
        scanf("%d",&coluna);
        disponibilidade = verificarDisponibilidade(linha, coluna, vez);   
    }while(!disponibilidade);

}

bool verificarLinhas(int vez){
    int i, j, somaL=0;

     for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            if (tabuleiro[i][j]==vez)
                somaL++;  
        }
        if (somaL == 3)
            return true;
        somaL = 0;
    }

    return false;
}

bool verificarColunas(int vez){
    int i, j, somaC=0;

     for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            if (tabuleiro[j][i]==vez)
                somaC++;  
        }
        if (somaC == 3)
            return true;
        somaC = 0;
    }

    return false;
}

bool verificarDiagonais( int vez){
    
    if((tabuleiro[2][0]==vez) && (tabuleiro[1][1]==vez) && (tabuleiro[0][2]==vez))
        return true;

    if((tabuleiro[0][0]==vez) && (tabuleiro[1][1]==vez) && (tabuleiro[2][2]==vez))
        return true;  

    return false;
      
}


bool verificarTrinca(int vez){

   if(verificarColunas(vez))
        return true;
   if(verificarLinhas(vez))
        return true;
   if (verificarDiagonais(vez))
         return true;
    

    return false;
   
}

void posicaoLivreAleatoria(int vez){
    int i, j;

    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            if (tabuleiro[i][j]==9){
                tabuleiro[i][j]=vez;
                printf("\nMarcador %d, inserido em (%d,%d)",vez,i,j);
                return;
            }
        }
    }

}

void jogadasComputador( int vez){
    posicaoLivreAleatoria(vez);
        
}

void jogo(int contadorJogadas, int tipoJogo){
    int vez=1;
    bool resultado;
    
    while(contadorJogadas < MaximoJogadas){

        if(tipoJogo==1)
        {
            if(vez==1)
                jogadasUsuario(vez);
            else
                jogadasComputador(vez);
        }
        else{
            jogadasUsuario(vez);
        }


        vez == 1? vez-- : vez++;   
        contadorJogadas++;     

        exibirTabuleiro(contadorJogadas);   
        
        
        if(contadorJogadas>=MinimoJogadas)
        {
            resultado = verificarTrinca(vez);
            if(resultado)
                break;
        }

             
    }    

    if (resultado)
        printf("Jogador %d ganhou",vez);
    else
        printf("Empate");

}

void main(){
    // apresentação
    int tipoJogo = menuInicial();
    
    //declarações e inicializações
    int contadorJogadas = 0;    
    iniciarTabuleiro();

    //Jogo
    jogo(contadorJogadas,tipoJogo);          
   
}



