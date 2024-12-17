#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int EstaEn(char *cadena, char c)
{
    /*Devuelve 1 si c esta en el string cad */
    // printf("Cadena = %s\n", token);
    while (*cadena != '\0')
    {
        if (*cadena == c)
        {
            return 1;
        }
        cadena++;
    }
    return 0;
}

int main(int args, char *argv[])
{
    char *nombre = "tokens.txt";
    int c = 0;
    int n = 100;
    int cont = 0;
    char *lexema;
    lexema = (char *)malloc(sizeof(char) * n); // Reserva de memoria para el vector lexema
    char simbolo;
    FILE *fichero;

    fichero = fopen(nombre, "rb");
    printf("Fichero: %s -> ", nombre);

    if (fichero)
    {
        printf("Existe -> (ABIERTO) \n");
    }
    else
    {
        printf("Error -> (NO ABIERTO) \n");
        return 1;
    }

    printf("Los tokens y lexemas encontrados en el fichero %s fueron: \n\n", nombre);
    while (!feof(fichero))
    {
        simbolo = fgetc(fichero);
        if (simbolo != ' ' && simbolo != '\n')
        {
            lexema[c] = simbolo; // Ingresa los caracteres al string 
            c++;                 // Si encuentra un caracter se mueve a la sig. posición del vector
        }
        else
        {
            printf("TOKEN = ");
            if (!(lexema[0] >= 48 && lexema[0] <= 57))
            {
                if (strcmp(lexema, "false") == 0 || strcmp(lexema, "true") == 0)
                { // Compara la cadena entre falso y verdadero
                    printf("Booleano,           ");
                }
                else
                {
                    printf("Cadena de caracter, ");
                }
            }
            else
            {
                char elem = '.';
                if (EstaEn(lexema, elem))
                { // Si hay algun valor difente de cero entonces es un flotante
                    printf("Flotante,           ");
                }
                else
                {
                    printf("Entero,             ");
                }
            }
            c = 0; // Restablecer el iterador de la cadena para re-construir otra cadena
            printf("LEXEMA := %s\n", lexema);
            cont++;
            free(lexema);
            lexema = (char *)malloc(sizeof(char) * n);
        }
    }
    if (lexema[0] != '\0') // En caso de que quede guardada una cadena fuera del ciclo, esta se imprimirá.
    {
        printf("TOKEN = ");
        lexema[c - 1] = 0;
        if (!(lexema[0] >= 48 && lexema[0] <= 57))
        {
            if (strcmp(lexema, "false") == 0 || strcmp(lexema, "true") == 0)
            { // Compara la cadena entre falso y verdadero
                printf("Booleano,           ");
            }
            else
            {
                printf("Cadena de caracter, ");
            }
        }
        else
        {
            char elem = '.';
            if (EstaEn(lexema, elem))
            { // Si hay algun valor difente de cero entonces es un flotante
                printf("Flotante,           ");
            }
            else
            {
                printf("Entero,             ");
            }
        }
        cont++;
        printf("LEXEMA := %s\n", lexema);
    }

    printf("\nSe encontraron %d elementos\n", cont);
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