#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

char palavraSecreta[20];
char chutes[26];
int chutesDados = 0;

void imprimeCabecalho(){
    // imprime cabecalho
    printf("*******************\n");
    printf("** Jogo de Forca **\n");
    printf("*******************\n\n");
}

void chuta(){
    char chute;
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados++;
}

int jaChutou(char letra){
    
    int achou = 0;

    for (int j = 0; j < chutesDados; j++){

        if (chutes[j] == letra){
            achou = 1;
            break;
        }       
    }
    return achou;
}

void desenhaForca(){

    for (int i = 0; i < strlen(palavraSecreta); i++){

        int achou = jaChutou(palavraSecreta[i]);

        if(achou){
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
            
     }
    printf("\n");
}

void adicionaPalavra() {
    
    char quer;

    printf("Voce deseja adicionar uma nova palavra no jogo? (S/N): ");
    scanf(" %c", &quer);
    if(quer == 'S') {

        char novaPalavra[20];
        printf("Qual a nova palavra? ");
        scanf("%s", novaPalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0){
            printf("Desculpe, banco de dados nao disponivel");
            exit(1);
        }

        int quantidade;
        fscanf(f, "%d", &quantidade);
        quantidade++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", quantidade);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novaPalavra);

        fclose(f);
    }
}

void escolhePalavra(){
    FILE* f;
    
    f = fopen("palavras.txt", "r");
    if(f == 0){
        printf("Desculpe, banco de dados nao disponivel");
        exit(1);
    }

    int quantidadeDePalavras;
    fscanf(f, "%d", &quantidadeDePalavras);

    srand(time(0));
    int randomico = rand() % quantidadeDePalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavraSecreta);
    }

    fclose(f);
}

int ganhou() {
    for(int i = 0; i < strlen(palavraSecreta); i++) {
        if(!jaChutou(palavraSecreta[i])) {
            return 0;
        }
    }
    return 1;
}

int enforcou(){

    int erros = 0;

    for (int i = 0; i < chutesDados; i++){
        
        int existe = 0;

        for (int j = 0; j < strlen(palavraSecreta); j++){

            if(chutes[i] == palavraSecreta[j]){

                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros >= 5;
}

int main() {

    escolhePalavra();
    imprimeCabecalho();

    int acertou = 0;

    do{

        desenhaForca();
        chuta();
        
    } while (!ganhou() && !enforcou());

    printf("%s\n", palavraSecreta);

    adicionaPalavra();
}