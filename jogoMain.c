#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define N 3

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

void iniciarTabuleiro(int tabuleiro[][N]){ // depois montar apresentação para o usuário
    int i, j;
    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            tabuleiro[i][j] =9;
            printf("%d  ",tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void exibirTabuleiro(int tabuleiro[][N]){
    //system("clear");
    int i, j;
    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d  ",tabuleiro[i][j]);
        }
        printf("\n");
    }
}

bool verificarDisponibilidade(int tabuleiro[][N], int linha, int coluna,int vez){
    if (tabuleiro[linha][coluna]==9){
        tabuleiro[linha][coluna]=vez;
          return true;
    }
    printf("Posicao invalida\n");
    return false;  
}

void jogadasDupla(int tabuleiro[][N],int vez){
    int linha, coluna;
    bool disponibilidade = false;
    
    do{
        printf("Jogador %d entre linha e coluna\n",vez);
        scanf("%d",&linha);
        scanf("%d",&coluna);
        disponibilidade = verificarDisponibilidade(tabuleiro,linha, coluna, vez);   
    }while(!disponibilidade);

}

bool verificarLinhas(int tabuleiro[][N], int vez){
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

bool verificarColunas(int tabuleiro[][N], int vez){
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

bool verificarDiagonais(int tabuleiro[][N], int vez){
    
    if((tabuleiro[2][0]==vez) && (tabuleiro[1][1]==vez) && (tabuleiro[0][2]==vez))
        return true;

    if((tabuleiro[0][0]==vez) && (tabuleiro[1][1]==vez) && (tabuleiro[2][2]==vez))
        return true;  

    return false;
      
}


bool verificarTrinca(int tabuleiro[][N], int vez){

   if(verificarColunas(tabuleiro,vez))
        return true;
   if(verificarLinhas(tabuleiro,vez))
        return true;
   if (verificarDiagonais(tabuleiro,vez))
         return true;
    

    return false;
   
}

void jogoEmDupla(int tabuleiro[][N],int contadorJogadas){
    int vez=1;
    bool resultado;
    
    while(contadorJogadas < 9){
        jogadasDupla(tabuleiro,vez);
        contadorJogadas++;
        exibirTabuleiro(tabuleiro);
        resultado = verificarTrinca(tabuleiro,vez);
        if(resultado)
            break;
        vez == 1? vez-- : vez++;             
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
    int tabuleiro[N][N];
    int contadorJogadas = 0;    
    iniciarTabuleiro(tabuleiro);

    
    switch (tipoJogo)
    {
        case 1: printf("\nJogo contra o computador");break;
        case 2: jogoEmDupla(tabuleiro,contadorJogadas);break;
    }   
    
    
}



