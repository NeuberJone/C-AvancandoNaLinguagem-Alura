#include <stdio.h>
#include <string.h>

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

void escolhePalavra(){
    sprintf(palavraSecreta, "MELANCIA");
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
        printf("ERROS = %d\n", erros);
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
        
    } while (!acertou && !enforcou());

    printf("%s", palavraSecreta);
}