#include "biblioteca.h"


void main(){
    int jogoCount = 0;
    int escolha, contadorJogadas;        
    

    for(;;){
        
        mensagens(0);
        scanf("%d",&escolha); 

        switch(escolha){
            case 1: // Iniciar novo jogo
                jogoCount++;
                iniciarTabuleiro();
                mensagens(1);
                scanf("%d",&escolha); 
                while ((escolha!= 1) && (escolha != 2)){
                    mensagens(2);
                    scanf("%d",&escolha);
                }
                jogo(escolha); 
                break;
                
            case 2: replay(jogoCount); break; // Replay

            case 3:  exit(1); break; //Sair
        } 
        
    }
   
}



