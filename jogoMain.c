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

    tabuleiro[0][2]=1;
}

void exibirTabuleiro(int tabuleiro[][N]){
    system("cls");
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
        printf("Entre linha e coluna\n");
        scanf("%d",&linha);
        scanf("%d",&coluna);
        disponibilidade = verificarDisponibilidade(tabuleiro,linha, coluna, vez);   
    }while(!disponibilidade);

}

bool verificarTrinca(int tabuleiro[][N], int resultado){
    int i, j, somaL =0, somaC = 0, somaD = 0;

    //verifica trinca nas linhas e colunas
    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
           //verifica linhas
            switch(tabuleiro[i][j]){
                case 1: somaL++;
                case 0: somaL--;
            } 
            //verifica colunas
            switch(tabuleiro[j][i]){
                case 1: somaC++;
                case 0: somaC--;
            } 

        }

      if ((somaL ==3) || (somaL == -3) || (somaC ==3) || (somaC == -3))
        return true;
      
      somaL = 0;
      somaC = 0;
      //verifica diagonal principal
      switch(tabuleiro[j][j]){
                case 1: somaD++;
                case 0: somaD--;
      }

      if((somaD ==3) || (somaD == -3))
        return true            
    }

    //verifica diagonal secundária
    if((tabuleiro[2][0]==1) && (tabuleiro[1][1]==1) && (tabuleiro[0][2]==1))
        return true
    if((tabuleiro[2][0]==0) && (tabuleiro[1][1]==0) && (tabuleiro[0][2]==0))
        return true    

}

void jogoEmDupla(int tabuleiro[][N],contadorJogadas){
    int vez=1;
    bool resultado;
    
    while(!resultado && (contadorJogadas <= 9)){
        jogadasDupla(tabuleiro,vez);
        contadorJogadas++;
        exibirTabuleiro(tabuleiro);
        verificarTrinca(tabuleiro, resultado);//implementar isso.
        vez == 1? vez = 2 : vez:1;      
        
    }    

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



