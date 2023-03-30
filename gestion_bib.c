#define MAX_LEN 50
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct libro{
    char titulo[MAX_LEN];
    char autor[MAX_LEN];
    int stock;
    int borrowed;
    int indice;
} libro;
char* leer_cadena(char* mensaje) {
    char buffer[MAX_LEN];
    char* chain = NULL;
    int length = 0;
    printf("%s",mensaje);
    fgets(buffer, MAX_LEN, stdin);
    
    // Eliminar el espacio en blanco y caracter de nueva línea del final de la cadena leída
    buffer[strcspn(buffer," ")] = '_';
    buffer[strcspn(buffer, "\n")] = '\0';
    
    // Obtener la longitud de la cadena
    length = strlen(buffer);

    // Asignar memoria para la cadena
    chain = (char*)malloc((length + 1) * sizeof(char));

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
void agregar_libro(int* contador, libro* biblioteca){
    printf("\tADD BOOK MANAGER\n");
    while(1){
        FILE* dataBase;
        if(*contador == 0) dataBase = fopen("DataBase.txt","w");
        else dataBase = fopen("DataBase.txt","a");
        libro aux;
        char* cadena = leer_cadena("Registre el titulo del libro: ");
        strcpy(aux.titulo, cadena); free(cadena);
        cadena = leer_cadena("Registre el nombre del autor: ");
        strcpy(aux.autor, cadena); free(cadena);
        //Falta agregar funcion leerNum
        aux.stock = 5; aux.borrowed = 2; aux.indice = *contador;
        biblioteca[*contador] = aux;
        fprintf(dataBase,"%d %s %s %d %d\n",aux.indice, aux.titulo, aux.autor, aux.stock, aux.borrowed);
        fclose(dataBase);
        (*contador) ++;
        char* rep = leer_cadena("Desea registrar otro libro: Escriba 'Si' para continuar, 'No' para regresar al menu:\t");
        if(strcmp(rep,"NO") == 0){
            free(rep);
            break;
        }
        free(rep);
    }
}
libro buscarLibro(libro* biblioteca){
    libro aux;

    return aux;
}
int main(){
    FILE* dataBase = fopen("DataBase.txt","r");
    libro bib[100];
    int count =0; 
    while (fscanf(dataBase, "%d %s %s %d %d", &bib[count].indice, bib[count].titulo, bib[count].autor, &bib[count].stock, &bib[count].borrowed) == 5){
        count ++;
    };
    agregar_libro(&count,bib);
    fclose(dataBase);
    return 0;
}
/*
void mostrar_lista(struct libro *biblioteca){
    int i;
    for(i=0;i<100;i++){
        if(biblioteca[i].titulo!='\0'){
            printf("%c\n",biblioteca[i].titulo);
        }
    }
}

void remover_libro(struct libro *biblioteca, char *nombre){
    int i;
    for(i=0;i<100;i++){
        if(strcmp(biblioteca[i].titulo,nombre) == 0){
            *biblioteca[i].titulo='\0';
            return;
        }
    }
}
int buscar_libro(struct libro *biblioteca){
    int i;
    return biblioteca[i].stock;
}
void prestar_libro(struct libro *biblioteca){
    int i;    
    biblioteca[i].stock--;
    return; 
}
void devolver_libro(struct libro *biblioteca){
    int i;
    biblioteca[i].stock++;
}*/