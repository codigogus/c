#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Prototipo de funciones


void encriptar(char ascii,int key){
    int i = 0;
    char *cesar;
    cesar = (char *)malloc(sizeof(char) * 20);
    if (ascii != ' ' && ascii != '\n')
    {
        if (ascii >= 65 && ascii <= 90)
        {
            cesar[i] = ascii;
            cesar[i] = (((cesar[i] - 65) + key) % 26) + 65;
            i++;
        }
        else if (ascii >= 97 && ascii <= 122)
        {
            cesar[i] = ascii;
            cesar[i] = (((cesar[i] - 97) + key) % 26) + 97;
            i++;
        }
        else
        {
            cesar[i] = ascii;
            i++;
        }
    }
    else
    {
        if (ascii == '\n')
        {
            printf("\n%s", cesar);
        }
        else
        {
            printf(" %s", cesar);
        }

        i = 0;
        free(cesar);
        cesar = (char *)malloc(sizeof(char) * 20);
    }
}

    int main(int argc, char *argv[])
{
    char *nombre = "telegrama_Zimmermann.txt";
    char ascii;
    int key = 6;
    char *cesar;
    cesar = (char *)malloc(sizeof(char) * 20);
    int i=0;
    FILE *fichero;
    system("cls");

    fichero = fopen(nombre, "r");
    printf("Fichero: %s -> ", nombre);

    if (fichero)
    {
        printf("existe (ABIERTO)\n");
    }
    else
    {
        printf("Error (NO ABIERTO)\n");
        return 1;
    }
    printf("\n\nEl mensaje cifrado del fichero %s es:\n\n", nombre);
    while (!feof(fichero))
    {
        ascii = fgetc(fichero);
        encriptar(ascii,key);
    }
    if (cesar[0] != '\0')
    {
        cesar[i] = 0;
        printf(" %s\n", cesar);
    }

    if (!fclose(fichero))
    {
        printf("\nFichero cerrado\n");
    }
    else
    {
        printf("\nError: fichero NO CERRADO\n");
        return 1;
    }

    return (0);
}