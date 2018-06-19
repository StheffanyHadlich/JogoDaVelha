jogo: jogoMain.o biblioteca.o
    gcc jogoMain.o biblioteca.o -o jogo

jogoMain.o: jogoMain.c
    gcc -c jogoMain.c

biblioteca.o: biblioteca.c biblioteca.h
    gcc -c biblioteca.c

clean:
    rm *.o jogo