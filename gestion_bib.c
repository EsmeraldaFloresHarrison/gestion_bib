#define MAX_LEN 60
#define INI_SIZE 15
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
typedef struct{
    char* name;
    char** titulos;
    int numLibros;
} clients;
char* leerCadena(char* mensaje) {
    char* chain = NULL;
    char c; 
    int i, size;
    
    while(chain == NULL) {
        i = 0;
        size = INI_SIZE;
        chain = calloc(1,sizeof(char) * size);
        printf("%s",mensaje);
        while(1){
            if( i == size - 1) {
                size += INI_SIZE;
                chain = realloc(chain,sizeof(char) * ( size));
            }
            if(i == MAX_LEN) {
                printf("Error: longitud maxima superada.\n");
                free(chain);
                chain = NULL;
                break;
            }
            chain[i] = (c = getchar());
            if(i == 0 && (chain[0] == '\n' || chain[0] == 9 || chain[0] == 32)){
                printf("Error: No ingrese espacios en blanco al inicio de la cadena.\n");
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
        input = leerCadena(mensaje);
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
void printBook(int index){
    char* tituloImprimir = strdup(bib[index].titulo);
    for (int i = 0; i < strlen(tituloImprimir); i++){
        if(tituloImprimir[i] == 95) tituloImprimir[i] = 32;
    }
    char* autorImprimir = strdup(bib[index].autor);
    for (int i = 0; i < strlen(autorImprimir); i++){
        if(autorImprimir[i] == 95) autorImprimir[i] = 32;
    }
    system("cls");
    printf("Titulo: %s\n",tituloImprimir);
    printf("Autor: %s\n",autorImprimir);
    printf("Stock: %d\n",*bib[index].stock);
    printf("Prestamos: %d\n",*bib[index].borrowed);
    free(tituloImprimir); free(autorImprimir);
}
int findBook(int contador, char* titulo){
    for(int i = 0; i < contador; i ++){
        if(strcmp(titulo, bib[i].titulo) == 0){
            printBook(i);
            free(titulo);
            return i;
        }
    }
    printf("El titulo no se encuentra en la base de datos.\n"); free(titulo); return -1;
}
void updateDataBase(int contador){
    FILE* aux = fopen("auxiliar.txt", "w");
    for(int i = 0; i < contador; i++){
        fprintf(aux,"%s %s %d %d",bib[i].titulo, bib[i].autor, *bib[i].stock, *bib[i].borrowed);
        if(i + 1 != contador) fputc('\n', aux); 
    }
    fclose(aux);
    remove("DataBase.txt");
    rename("auxiliar.txt","DataBase.txt");
}
void agregarLibro(int* contador){
    FILE* dataBase = fopen("DataBase.txt","a");
    if(bib != NULL) fputc('\n',dataBase);
    system("cls");
    printf("\tADD BOOK MANAGER\n");
    char* titulo = leerCadena("Registre el titulo del libro: ");;
    if(findBook(*contador,titulo) == -1){
        bib = realloc(bib, sizeof(libro)*(*contador + 1)); 
        bib[*contador].titulo = titulo;
        bib[*contador].autor = leerCadena("Registre el nombre del autor: "); ; 
        bib[*contador].stock = leerNum("Ingrese la cantidad en stock: ");
        bib[*contador].borrowed = leerNum("Registre la cantidad de libros prestados: ");
        fprintf(dataBase,"%s %s %d %d",bib[*contador].titulo, bib[*contador].autor, *bib[*contador].stock, *bib[*contador].borrowed);
        (*contador) ++;
    }
    else printf("El libro ya se encuentra registrado.\n");
    fclose(dataBase);
    char* rep = leerCadena("Desea registrar otro libro: Escriba 'Si' para continuar, 'No' para regresar al menu:\t");
    if(strcmp(rep,"SI") == 0) agregarLibro(contador);
    free(rep);
    return;
}
void leerDataBase(int* contador){
    FILE* dataBase = fopen("DataBase.txt","r");
    int size = INI_SIZE;
    bib = calloc(size,sizeof(libro));
    while (!feof(dataBase)){
        if(*contador == size){size += INI_SIZE; bib = realloc(bib,sizeof(libro) * size);}
        bib[*contador].titulo = calloc(MAX_LEN,sizeof(char));
        bib[*contador].autor = calloc(MAX_LEN,sizeof(char));
        bib[*contador].stock = malloc(sizeof( int));
        bib[*contador].borrowed = malloc(sizeof( int));

        if(fscanf(dataBase, "%s %s %d %d", bib[*contador].titulo, bib[*contador].autor, bib[*contador].stock, bib[*contador].borrowed) == 4){
            
            bib[*contador].titulo = realloc(bib[*contador].titulo,strlen(bib[*contador].titulo) + 1);
            bib[*contador].autor = realloc(bib[*contador].autor,strlen(bib[*contador].autor) + 1);
            (*contador) ++;
        }
        else {free(bib[*contador].titulo); free(bib[*contador].autor); free(bib[*contador].stock); free(bib[*contador].borrowed);}
    }
    if(*contador == 0) { free(bib); bib = NULL;}
    else bib = realloc(bib, sizeof(libro) * (*contador));
    fclose(dataBase);
    return;
}
void eliminarlibro(int* contador){
    if(contador == 0) {printf("La base de datos esta vacia.\n"); return;}
    int indice;
    char* titulo = leerCadena("Ingrese el titulo del libro a eliminar: ");
    char* input;
    if((indice = findBook(*contador,titulo)) < 0) return;
    else if(strcmp((input = leerCadena("Estas seguro que quieres elminar este libro? Escribe (Si) para confirmar, (No) para cancelar: ")),"SI") == 0){
        (*contador) --;
        free(bib[indice].titulo);
        free(bib[indice].autor);
        free(bib[indice].stock);
        free(bib[indice].borrowed);
        for(int i = indice; i < *contador; i++) {
            bib[i] = bib[i + 1];
        }
        bib = realloc(bib, sizeof(libro) * (*contador));
        updateDataBase(*contador);
    }
    free(input);
    return;
}
int main(){
    int count =0; 
    leerDataBase(&count);
    eliminarlibro(&count);
    printf("%d\n",count);
    free(bib);
    return 0;
}