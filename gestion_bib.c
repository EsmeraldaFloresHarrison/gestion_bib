#define MAX_LEN 50
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct libro{
    char* titulo;
    char* autor;
    unsigned int* stock;
    unsigned int* borrowed;
} libro;
libro* bib = NULL;
char* leer_cadena(char* mensaje) {
    char buffer[MAX_LEN];
    char* chain = calloc(1,sizeof(char));
    char c; int i = 0;
    printf("%s",mensaje);
    while(c = getchar() != '\n'){
        chain[i] = c;
        chain = realloc(chain,sizeof(char) + 1);
        i ++;
    }
    // Eliminar el espacio en blanco y caracter de nueva línea del final de la cadena leída
    for(int i = 0; i <= strlen(buffer); i ++){
        if(buffer[i] == 32) buffer[i] = 95;
        else if(buffer[i] == '\n') buffer[i] = '\0';
    }

    // Asignar memoria para la cadena
    chain = malloc((strlen(buffer) + 1) * sizeof(char));

    // Copiar la cadena leída al puntero asignado
    strcpy(chain, buffer);
    //Convertir la cadena a MAYUSC
    for(int i = 0; chain[i] != '\0'; ++ i){
        chain[i] = toupper(chain[i]);
    }
    // Limpiar el buffer
    fflush(stdin);  
    
    return chain;
}
unsigned int* leerNum(char* mensaje){
    /* 
    Name: leerNum
    Return: int
    */
   unsigned int* num = NULL;
    while(num == NULL) {
        num = malloc(sizeof(unsigned int));
        printf("%s",mensaje);
        if(scanf("%u",num) != 1){
            printf("Error. Ingrese un valor >= 0.\n");
            free(num);
            num = NULL;
        }
        fflush(stdin);
    }
    return num;
}
void agregar_libro(int* contador){
    libro* aux = calloc(1,sizeof(libro));
    FILE* dataBase = fopen("DataBase.txt","a");
    //system("clear");
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
        aux->stock = malloc(sizeof(unsigned int));
        aux->borrowed = malloc(sizeof(unsigned int));

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