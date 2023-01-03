#include <stdio.h>

void imprimeCabecalho(){
    // imprime cabecalho
    printf("*******************\n");
    printf("** Jogo de Forca **\n");
    printf("*******************\n\n");
}

void chuta(char chutes[26], int* tentativas){
    char chute;
    scanf(" %c", &chute);

    chutes[(*tentativas)] = chute;
    (*tentativas)++;
}

int jaChutou(char letra, char chutes[26], int tentativas){
    int achou = 0;

    for (int j = 0; j < tentativas; j++){

        if (chutes[j] == letra){
            achou = 1;
            break;
        }       
    }
    return achou;
}

void desenhaForca(char palavraSecreta[20], char chutes[26], int tentativas){

    for (int i = 0; i < strlen(palavraSecreta); i++){

        int achou = jaChutou(palavraSecreta[i], chutes, tentativas);

        if(achou){
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
            
     }
    printf("\n");
}

void escolhePalavra(char palavraSecreta){
    sprintf(palavraSecreta, "MELANCIA");
}

int main() {

    char palavraSecreta[20];

    escolhePalavra(palavraSecreta);

    int acertou = 0;
    int enforcou = 0;

    char chutes[26];
    int tentativas = 0;

    imprimeCabecalho();

    do{

        desenhaForca(palavraSecreta, chutes, tentativas);

        chuta(chutes, &tentativas);
        tentativas++;
    
    } while (!acertou && !enforcou);

    printf("%s", palavraSecreta);
}