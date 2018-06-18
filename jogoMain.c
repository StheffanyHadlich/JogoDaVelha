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
        if(disponibilidade==false)
            printf("Posicao invalida\n"); 
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

bool posicaoLivreAleatoria(int vez){
    int i, j;

    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            if (tabuleiro[i][j]==9){
                tabuleiro[i][j]=vez;
                printf("\nMarcador %d, inserido em (%d,%d)",vez,i,j);
                return true;
            }
        }
    }

    return false;

}

bool colunaEstrategia(int b, int vez){
    int i, soma = 0;
    for(i=0;i<N;i++){
        if((tabuleiro[i][b]==9) || (tabuleiro[i][b]==vez))
            soma++;
    }
    printf("\nSoma Coluna: %d\n",soma);
    if(soma==3){
        for(i=0;i<N;i++){
            if(verificarDisponibilidade(i,b,vez))
                return true;
        }
    }
        
    return false;
    
}

bool linhaEstrategia(int a, int vez){
    int i, soma = 0;
    for(i=0;i<N;i++){
        if((tabuleiro[a][i]==9) || (tabuleiro[a][i]==vez))
            soma++;
    }

    if(soma==3){
        for(i=0;i<N;i++){
            if(verificarDisponibilidade(a,i,vez))
                return true;
        }
    }
        
    return false;
    
}

bool diagonalPrincipalEstrategia(int vez){
    int i, soma = 0;
    for(i=0;i<N;i++){
        if((tabuleiro[i][i]==9) || (tabuleiro[i][i]==vez))
            soma++;
    }

    if(soma==3){
        for(i=0;i<N;i++){
            if(verificarDisponibilidade(i,i,vez))
                return true;
        }
    }
        
    return false;
    
}

bool diagonalSecundariaEstrategia(int vez){
    int i,j, soma = 0;
    for(i=2;i>=0;i--){
        for(j=0;j<N;j++){
            if((tabuleiro[i][j]==9) || (tabuleiro[i][j]==vez))
                soma++;
        }
        
    }

    if(soma==3){
        for(i=2;i>=0;i--){
            for(j=0;j<N;j++){
                if(verificarDisponibilidade(i,j,vez))
                    return true;
            }
        
        }
    }
        
    return false;
    
}

bool verificarVizinhos(int a, int b, int vez){ //testar todo esse método
    int i;

    if(((a==2)&&(b==0))||((a==0)&&(b==2)) || (a==b)){
        if(diagonalSecundariaEstrategia(vez))
            return true;

        if(a==b) {
            if(diagonalPrincipalEstrategia(vez))
                return true;
        }
       
    }    

    if(linhaEstrategia(a,vez))
        return true;

    if(colunaEstrategia(b,vez))
        return true;
    
    return false;
}

bool estrategia1(int vez){
    int i, j;

    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            if (tabuleiro[i][j] == vez){
                if (verificarVizinhos(i,j,vez))
                    return true;
            }
        }
    }
    
    return false;

}

void jogadasComputador( int vez){

    if (estrategia1(vez))
        return;

    //estratégia 2 - bloquear adversário

    if (posicaoLivreAleatoria(vez))
        return;
        
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
   
        contadorJogadas++;     

        exibirTabuleiro(contadorJogadas);   
        
        
        if(contadorJogadas>=MinimoJogadas)
        {
            resultado = verificarTrinca(vez);
            if(resultado){
                printf("Jogador %d ganhou",vez);
                break;
            }
        }

        vez == 1? vez-- : vez++;

             
    }    

    if(!resultado)
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



