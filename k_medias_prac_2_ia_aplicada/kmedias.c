#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void transformacionAscii(int[], char *[], int);
int generaBaseDeDatos(int *, int *, int *, int *, int *, int *, int *);
void k_medias(int);
void k_medias_ejemplo_semana3();
void k_medias_IRIS();

int main()
{
    // INICIA ALGORITMO K-MEDIAS
    k_medias_ejemplo_semana3();
    for (int i = 2; i < 6; i++)
        k_medias(i);
    k_medias_IRIS();
    printf("\n Terminado... Los resultados han sido guardados en el archivo resultados.dat\n");
    return 0;
}

void k_medias(int itera)
{
    // sol inicial aleatoria
    int solucionInicial[7200], i, j, k, muestrasCero = 0, muestrasUno = 0;
    for (int i = 0; i < 7200; i++)
    {
        int random = rand() % 10;
        if (random < 5)
        {
            solucionInicial[i] = 0;
        }
        else
        {
            solucionInicial[i] = 1;
        }
    }
    // Obtener las muestas del archivo BD_ASCII.dat y las guardamos en una matriz
    FILE *archivo = fopen("BD_ASCII.dat", "rb");
    int numLinea = 0;
    char *linea = (char *)malloc(sizeof(char) * 100);
    int muestras[7200][7];
    while (!feof(archivo))
    {
        fgets(linea, 500, archivo);
        i = 0;
        char *token = strtok(linea, ",");
        while (token)
        {
            muestras[numLinea][i] = atoi(token);
            token = strtok(NULL, ",");
            i++;
        }
        numLinea++;
    }
    fclose(archivo);

    // Calculo de centroides, 2 centroides
    int a = itera;
    while (itera >= 0)
    {
        itera--;
        double C[2][7];
        for (i = 0; i < 2; i++)
            for (j = 0; j < 7; j++)
                C[i][j] = 0;
        int contador[2] = {0, 0};
        for (i = 0; i < 2; i++)
            for (j = 0; j < 7200; j++)
                if (solucionInicial[j] == i)
                {
                    for (k = 0; k < 7; k++)
                        C[i][k] += muestras[j][k];
                    contador[i] += 1;
                }
        for (i = 0; i < 2; i++)
            for (k = 0; k < 7; k++)
                C[i][k] = (C[i][k] / contador[i]);
        // Calculo de centroides finalizado
        // Calcular las distancias euclidianas de cada muestra a su centroide
        for (j = 0; j < 7200; j++)
        {
            double distancia1 = 0, distancia2 = 0;
            for (k = 0; k < 7; k++)
                distancia1 += pow(C[0][k] - muestras[j][k], 2);
            for (k = 0; k < 7; k++)
                distancia2 += pow(C[1][k] - muestras[j][k], 2);
            if (distancia1 < distancia2)
            {
                if (!(solucionInicial[j] == 0))
                {
                    solucionInicial[j] = 0;
                }
            }
            else
            {
                if (!(solucionInicial[j] == 1))
                {
                    solucionInicial[j] = 1;
                }
            }
        }
    }

    FILE *resultados;
    resultados = fopen("resultados.dat", "a");
    fprintf(resultados, "\n\nLa solucion K-medias para empresas de clase media en %d iteraciones es:\n\n", a);
    for (i = 0; i < 7200; i++)
    {
        if (solucionInicial[i] == 0)
        {
            muestrasCero++;
        }
        if (solucionInicial[i] == 1)
        {
            muestrasUno++;
        }
        fprintf(resultados, "Muestra %d: %d %d %d %d %d %d %d asignada al cluster %d\n", (i + 1), muestras[i][0], muestras[i][1], muestras[i][2], muestras[i][3], muestras[i][4], muestras[i][5], muestras[i][6], solucionInicial[i]);
    }

    fprintf(resultados, "\n\n\nTotal de muestras en el cluster 0: %d\n", muestrasCero);
    fprintf(resultados, "\nTotal de muestas en el cluster 1: %d\n", muestrasUno);
    fclose(resultados);
}

void k_medias_ejemplo_semana3()
{
    // generando solucion inicial aleatoria
    int sol[4], i, j, k;
    for (i = 0; i < 4; i++)
    {
        int random = rand() % 10;
        if (random < 5)
            sol[i] = 0;
        else
            sol[i] = 1;
    }
    int muestras[4][2]; // Tabla de 2 columnas y 3 datos en clase
    muestras[0][0] = 6;
    muestras[0][1] = -5;
    muestras[1][0] = 2;
    muestras[1][1] = 3;
    muestras[2][0] = 6;
    muestras[2][1] = -2;
    muestras[3][0] = -2;
    muestras[3][1] = 4;

    int cambio = 1, a = 0;
    while (cambio != 0)
    {
        a++;
        double C[2][2];
        for (i = 0; i < 2; i++)
            for (j = 0; j < 2; j++)
                C[i][j] = 0;
        int contador[2] = {0, 0};
        for (i = 0; i < 2; i++)
            for (j = 0; j < 4; j++)
                if (sol[j] == i)
                {
                    for (k = 0; k < 2; k++)
                        C[i][k] += muestras[j][k];
                    contador[i] += i;
                }
        for (i = 0; i < 2; i++)
            for (k = 0; k < 2; k++)
            {
                C[i][k] = (C[i][k] / contador[i]);
            }
        // Calculo de centroides
        cambio = 0;
        for (j = 0; j < 4; j++)
        {
            double distancia1 = 0, distancia2 = 0;
            for (k = 0; k < 2; k++)
                distancia1 += pow(C[0][k] - muestras[j][k], 2);
            for (k = 0; k < 2; k++)
                distancia2 += pow(C[1][k] - muestras[j][k], 2);
            if (distancia1 < distancia2)
            {
                if (!(sol[j] == 0))
                {
                    cambio = 1;
                    sol[j] = 0;
                }
                else
                {
                    if (!(sol[j] == 1))
                    {
                        cambio = 1;
                        sol[j] = 1;
                    }
                }
            }
        }
    }
    remove("resultados.dat");
    int clusterA = 0, clusterB = 0;
    FILE *resultados;
    resultados = fopen("resultados.dat", "a");
    fprintf(resultados, "\nLa solucion obtenida de K-Medias hasta que no hubo cambios(se ocuparon %d iteraciones) para el elemento de la semana 3 es:\n\n", a);
    for (i = 0; i < 4; i++)
    {
        if (sol[i] == 0)
            clusterA++;
        if (sol[i] == 1)
            clusterB++;
        fprintf(resultados, "Muestra %d: %d %d asignada al cluster %d\n", (i + 1), muestras[i][0], muestras[i][1], sol[i]);
    }
    fprintf(resultados, "\nTotal de muestras en el cluster A: %d\n", clusterA);
    fprintf(resultados, "\nTotal de muestras en el cluster B: %d\n", clusterB);
    fclose(resultados);
}

void k_medias_IRIS()
{
    // generando solucion inicial aleatoria
    int solucioninicial[150], i, j, k, a = 0;
    for (i = 0; i < 150; i++)
    {
        int a = rand() % 10;
        if (a < 5)
            solucioninicial[i] = 0;
        else if (a < 7)
            solucioninicial[i] = 1;
        else
            solucioninicial[i] = 2;
    }

    // Obtenermos muestras del archivo IRIS.csv y las guardamos en una matriz

    FILE *archivo;
    int numLinea = 0;
    char *linea;
    float muestras[150][4];
    linea = (char *)malloc(sizeof(char) * 50);
    archivo = fopen("IRIS.csv", "r");
    while (!foef(archivo))
    {
        fgets(linea, 100, archivo);
        i = 0;
        char *token = strtok(linea, "7");
        while (token)
        {
            muestras[numLinea][i] = atoi(token);
            token = strtok(NULL, "7");
            i++;
        }
        numLinea++;
    }
}
