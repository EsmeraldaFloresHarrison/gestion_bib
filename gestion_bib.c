#define MAX_LEN 50
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct libro{
    char titulo[50];
    char autor[50];
    int stock;
    int borrowed;

};
char* leer_cadena() {
    char buffer[MAX_LEN];
    char* cadena = NULL;
    int longitud = 0;
    int caracter;

    fgets(buffer, MAX_LEN, stdin);

    // Eliminar el caracter de nueva línea del final de la cadena leída
    buffer[strcspn(buffer, "\n")] = '\0';

    // Obtener la longitud de la cadena
    longitud = strlen(buffer);

    // Asignar memoria para la cadena
    cadena = (char*)malloc((longitud + 1) * sizeof(char));

    // Copiar la cadena leída al puntero asignado
    strcpy(cadena, buffer);

    // Limpiar el buffer
    fflush(stdin);

    return cadena;
}
void agregar_libro(struct libro *biblioteca){
    int i = 0;
    printf("\tADD BOOK MANAGER\n"); printf("Registre el titulo del libro: ");
    char* title_to_add = leer_cadena();
    for(i = 0;i<100;i++){
        if(biblioteca[i].titulo == '\0'){
            strcpy(title_to_add, biblioteca[i].titulo);
            printf("\n%s\n",biblioteca[i].titulo);
            printf("\nhola hola\n");
            return;
        }
    }
    free(title_to_add);
}
int main(){
    struct libro biblioteca[5];
    memset(biblioteca,'\0',sizeof(biblioteca));
    if(strcmp(biblioteca[0].titulo,'\0') == 0){
        strcpy(biblioteca[0].titulo,"hola");
        printf("%s",biblioteca[0].titulo);
    }
    
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