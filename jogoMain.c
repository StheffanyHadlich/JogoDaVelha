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
int jogos=0;

void iniciarTabuleiro(){ 
    int i, j;
    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            tabuleiro[i][j] =9;
            tabuleiroExibido[i][j]=95;
        }
    }

    for(i=0;i<MaximoJogadas;i++){
        replayLinhas[i]=0;
        replayColunas[i]=0;
    }       
}

void salvarReplay(int linha, int coluna){
    int i;
    for(i=0;i<MaximoJogadas;i++){
        if(replayLinhas[i]==0){
            replayLinhas[i]=linha;
            replayColunas[i]=coluna;
            return;
        }
    }
}

void replay(){
    if(jogos==0){
        printf("\nNenhum jogo foi realizado ainda");
        return;
    }

    int i,j,replay[N][N];
    int icone = 120;

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            replay[i][j]=95;
        }
    }

    for(i=0;i<MaximoJogadas;i++){
        replay[replayLinhas[i]][replayColunas[i]]=icone;
        if(icone==120)
            icone=111;
    }

    printf("\nReplay do último jogo\n");
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%c  ",replay[i][j]);
        }
        printf("\n");
    }


}

void exibirTabuleiro(int contadorJogadas){
    //system("clear");    
    printf("\nJogada: %d\n",contadorJogadas);
    int i, j;
    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%c  ",tabuleiroExibido[i][j]);
        }
        printf("\n");
    }
    
}

void mensagens(int etapa){
    //system("clear");
    printf("*** JOGO DA VELHA ****\n\n");

    if(etapa==0){
        printf("1 Iniciar novo Jogo\n2 Ver replay do ultimo jogo\n3 Sair\n");
    }
    
    if(etapa ==1){
        printf("Escolha o tipo de jogo:\n1 para jogar contra o computador \n2 para jogar em dupla\n\n");
    }

    if(etapa==2)
        printf("Entre com uma opção válida, pressione: \n1 para jogar contra o computador\n2 para jogar em dupla\n\n");

    if(etapa ==3)
        printf("Escolha o modo de jogo:\n1 Fácil\n2 Difícil\n\n");
    
    
  
}

bool verificarDisponibilidade(int linha, int coluna,int vez){
    int icone=120;

    if(vez==0)
        icone=111;

    if (tabuleiro[linha][coluna]==9){
        tabuleiro[linha][coluna]=vez;
        tabuleiroExibido[linha][coluna]=icone;
        salvarReplay(linha,coluna);
          return true;
    }
    return false;  
}

void jogadasUsuario(int vez){
    int linha, coluna;
    bool disponibilidade = false;
    
    do{
        printf("\nJogador %d entre com nova linha e coluna\n",vez);
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
    int i, j, icone=120;

    if(vez==0)
        icone=111;

    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            if (tabuleiro[i][j]==9){
                tabuleiro[i][j]=vez;
                tabuleiroExibido[i][j]=icone;
                salvarReplay(i,j);
                return true;
            }
        }
    }

    return false;

}

bool colunaEstrategia(int b, int vez, int marcador){
    int i, vazio = 0, x=0;
    for(i=0;i<N;i++){
        if(tabuleiro[i][b]==9)
            vazio++;
        if (tabuleiro[i][b]==marcador)
            x++;
    }

    if ((vez != marcador) && ((vazio==2)||(x==1)))
        return false;

    if(vazio+x==3){
        for(i=0;i<N;i++){
            if(verificarDisponibilidade(i,b,vez))
                return true;
        }
    }
        
    return false;
    
}

bool linhaEstrategia(int a, int vez, int marcador){
    int i, vazio = 0, x=0;
    for(i=0;i<N;i++){
        if(tabuleiro[a][i]==9)
            vazio++;
        if (tabuleiro[a][i]==marcador)
            x++;
    }

    if ((vez != marcador) && ((vazio==2)||(x==1)))
        return false;

    if(vazio+x==3){
        for(i=0;i<N;i++){
            if(verificarDisponibilidade(a,i,vez))
                return true;
        }
    }
        
    return false;
    
}

bool diagonalPrincipalEstrategia(int vez, int marcador){
    int i, vazio = 0, x=0;
    for(i=0;i<N;i++){
        if(tabuleiro[i][i]==9)
            vazio++;
        if(tabuleiro[i][i]==marcador)
            x++;
    }

    if ((vez != marcador) && ((vazio==2)||(x==1)))
        return false;

    if(x+vazio==3){
        for(i=0;i<N;i++){
            if(verificarDisponibilidade(i,i,vez))
                return true;
        }
    }
        
    return false;
    
}

bool diagonalSecundariaEstrategia(int vez, int marcador){
    int i,j, vazio = 0, x=0;

    for(i=2;i>=0;i--){
        for(j=0;j<N;j++){
            if(tabuleiro[i][j]==9)
                vazio++;
            if(tabuleiro[i][j]==marcador)
                x++;
            
        }
        
    }

    if ((vez != marcador) && ((vazio==2)||(x==1)))
        return false;

    if(vazio+x==3){
        for(i=2;i>=0;i--){
            for(j=0;j<N;j++){
                if(verificarDisponibilidade(i,j,vez))
                    return true;
            }
        
        }
    }
        
    return false;
    
}

bool verificarVizinhos(int a, int b, int vez, int marcador){ //testar todo esse método
    int i;

    if(((a==2)&&(b==0))||((a==0)&&(b==2)) || (a==b)){

        if(((a==2)&&(b==0))||((a==0)&&(b==2))||(a==1)){
            if(diagonalSecundariaEstrategia(vez, marcador))
                return true;
        }        

        if(a==b) {
            if(diagonalPrincipalEstrategia(vez,marcador))
                return true;
        }
       
    }    

    if(linhaEstrategia(a,vez, marcador))
        return true;

    if(colunaEstrategia(b,vez, marcador))
        return true;
    
    return false;
}

bool estrategia(int vez, int marcador){ // computador detecta possíveis trincas
    int i, j;

    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            if (tabuleiro[i][j] == marcador){
                if (verificarVizinhos(i,j,vez, marcador))
                    return true;
            }
        }
    }
    return false;

}

void jogadasComputador( int vez, int nivel){
    int adversario = vez;

    vez == 0 ? adversario++ : adversario--;

    if (nivel == 2){
        if (estrategia(vez, adversario)) // tenta impedir
            return;
    }  

    if (estrategia(vez,vez)) // Tenta formular uma trinca
        return;
    
    if (posicaoLivreAleatoria(vez))
        return;
        
}

void jogo(int contadorJogadas, int tipoJogo){
    int nivel,vez=1;
    bool resultado;

    if (tipoJogo ==1){
        mensagens(3);
        scanf("%d",&nivel);
    }
    
    while(contadorJogadas < MaximoJogadas){

        if(tipoJogo==1)
        {
            if(vez==1)
                jogadasUsuario(vez);
            else
                jogadasComputador(vez,nivel);
        }
        else{
            jogadasUsuario(vez);
        }
   
        contadorJogadas++;     

        //system("clear");
        exibirTabuleiro(contadorJogadas);       
        
        
        if(contadorJogadas>=MinimoJogadas)
        {
            resultado = verificarTrinca(vez);
            if(resultado){
                printf("\nResultado: Jogador %d ganhou\n",vez);
                break;
            }
        }

        vez == 1? vez-- : vez++;

             
    }    

    if(!resultado)
        printf("\nResultado: Empate");

}



void main(){
    // inicializaçoes

    int escolha, contadorJogadas;        
    // apresentação

    for(;;){
        
        mensagens(0);
        scanf("%d",&escolha); 

        switch(escolha){
            case 1: // Iniciar novo jogo
                jogos++;
                iniciarTabuleiro();
                contadorJogadas=0;
                mensagens(1);
                scanf("%d",&escolha); 
                while ((escolha!= 1) && (escolha != 2)){
                    mensagens(2);
                    scanf("%d",&escolha);
                }
                jogo(contadorJogadas,escolha); 
                break;
                
            case 2: replay(); break; // Replay

            case 3:  exit(1); break; //Sair
        } 
        
    }
   
}



