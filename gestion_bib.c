#define MAX_LEN 50
#define SIZE 16
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct libro{
    char* titulo;
    char* autor;
    int* stock;
    int* borrowed;
} libro;
libro* bib = NULL;

char* leer_cadena(char* mensaje) {
    char* chain = NULL;
    char c; 
    int i;
    printf("%s",mensaje);
    while(chain == NULL) {
        i = 0;
        chain = calloc(1,sizeof(char) * SIZE);
        while(1){
            if( i >= SIZE) chain = realloc(chain,sizeof(char) * ( i + SIZE ));
            chain[i] = (c = getchar());
            if(i == 0 && chain[0] == '\n'){
                printf("Error: Debe ingrsar algun dato: ");
                free(chain);
                chain = NULL;
                break;
            }
            chain[i] = toupper(chain[i]);
            if(chain[i] == 32) chain[i] = 95;
            if(c == '\n') {
                chain[i] = '\0';
                i++;
                break;
            }
            i ++;
        }
    }
    chain = realloc(chain,sizeof(char) * (i + 1));
    return chain;
}
int* leerNum(char* mensaje) {
    /* 
    Name: leerNum
    Return: int*
    */
    int* num = malloc(sizeof(int));
    char* input = NULL;
    while (1) {
        input = leer_cadena(mensaje);
        int i = 0;
        while (input[i] != '\0') {
            if (!isdigit(input[i])) {
                printf("Error: Debe ingresar un numero entero.\n");
                free(input);
                break;
            }
            if(i >= 9){
                printf("Error: Intente nuevamente.\n");
                free(input);
                break;
            }
            i++;
        }
        if (input[i] == '\0') {
            *num = atoi(input);
            break;
        }
    }
    return num;
}
void agregar_libro(int* contador){
    libro* aux = calloc(1,sizeof(libro));
    FILE* dataBase = fopen("DataBase.txt","a");
    system("cls");
    printf("\tADD BOOK MANAGER\n");
    aux->titulo = leer_cadena("Registre el titulo del libro: ");
    aux->autor = leer_cadena("Registre el nombre del autor: "); ; 
    aux->stock = leerNum("Ingrese la cantidad en stock: ");
    aux->borrowed = leerNum("Registre la cantidad de libros prestados: ");

    if(bib != NULL) fputc('\n',dataBase);
    fprintf(dataBase,"%s %s %d %d",aux->titulo, aux->autor, *aux->stock, *aux->borrowed);
    bib = realloc(bib, sizeof(libro)*(*contador + 1));  
    bib[*contador] = *aux;
    (*contador) ++;
    fclose(dataBase);
    char* rep = leer_cadena("Desea registrar otro libro: Escriba 'Si' para continuar, 'No' para regresar al menu:\t");
    if(strcmp(rep,"SI") == 0) agregar_libro(contador);
    free(rep);
    return;
}
int findBook(int contador){
    int i;
    char* titulo = leer_cadena("Igrese el titulo del libro buscado: ");

    for(i = 0; i < contador; i ++){
        if(strcmp(titulo, bib[i].titulo) == 0){
            free(titulo);
            return i;
        }
    }
    free(titulo);
    return -1;
}
void leerDataBase(int* contador){
    libro* aux;
    FILE* dataBase = fopen("DataBase.txt","r");
    while (!feof(dataBase)){
        aux = calloc(1,sizeof(libro));
        aux->titulo = calloc(MAX_LEN,sizeof(char));
        aux->autor = calloc(MAX_LEN,sizeof(char));
        aux->stock = malloc(sizeof( int));
        aux->borrowed = malloc(sizeof( int));

        if(fscanf(dataBase, "%s %s %d %d", aux->titulo, aux->autor, aux->stock, aux->borrowed) == 4){
            bib = realloc(bib, sizeof(libro)*(*contador + 1));
            aux->titulo = realloc(aux->titulo,strlen(aux->titulo) + 1);
            aux->autor = realloc(aux->autor,strlen(aux->autor) + 1);
            bib[*contador] = *aux;
            (*contador) ++;
        }
        else{
            free(aux->titulo); free(aux->autor); free(aux->stock); free(aux->borrowed); free(aux);
        }
    };
    fclose(dataBase);
    return;
}

int main(){
    int count =0; 
    leerDataBase(&count);
    //printf("%d",*bib[count-1].stock);
    agregar_libro(&count);
    printf("%d\n", count);
    //findBook(count) >= 0 ? printf("Libro encontrado\n") : printf(" Libro no encontrado\n");
    printf("%s\n",bib[count - 1].autor);
    free(bib);
    return 0;
}