#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transfo(int, char **, int*);                                                                       //Prototipo de funcion

int main(){
    int total=0;
    FILE *gen = fopen("BD_ASCII.dat","wt");
    printf("*##################################################################################################################\n");
    printf("\tTRANSFORMACIóN DE LA BASE DE DATOS DE EMPRESAS DE CLASE MEDIA\n\n");

    int *costumbres_int = (int *) malloc(5*sizeof(int ));
    char **costumbres = (char **) malloc(5* sizeof(char *));
    costumbres[0] = "Simbolico";
    costumbres[1] = "Ritual";
    costumbres[2] = "Ceremonial";
    costumbres[3] = "Relatos";
    costumbres[4] = "Modelos";
    printf("\tLa transformacion de los atributos de Costumbres Sociales son:\n");
    transfo(5,costumbres,costumbres_int);

    int *estatus_int = (int *)malloc(3 * sizeof(int));
    char **estatus = (char **)malloc(3 * sizeof(char *));
    estatus[0] = "Trascendencia";
    estatus[1] = "Prestigio";
    estatus[2] = "Rango";
    printf("\tLa transformacion de los atributos de Estatus son:\n");
    transfo(3, estatus, estatus_int);

    int *cooperacion_int =(int *)malloc(2*sizeof(int));
    char **cooperacion = (char **)malloc(2*sizeof(char*));
    cooperacion[0] = "Imitacion";
    cooperacion[1] = "Seguridad";
    printf("\tLa transformación de los atritutos de Cooperación son:\n");
    transfo(2,cooperacion,cooperacion_int);

    int *psicologicos_int = (int *)malloc(6*sizeof(int));
    char **psicologicos = (char **)malloc(6*sizeof(char *));
    psicologicos[0] = "Egoismo";
    psicologicos[1] = "Confianza";
    psicologicos[2] = "Indiferencia";
    psicologicos[3] = "Precaución";
    psicologicos[4] = "Premonicion";
    psicologicos[5] = "Fe";
    printf("\tLa transformación de los atritutos Psicológicos son:\n");
    transfo(6, psicologicos,psicologicos_int);

    int *viscerales_int = (int *)malloc(4*sizeof(int));
    char **viscerales = (char **)malloc(4*sizeof(char *));
    viscerales[0] = "Dolor";
    viscerales[1] = "Hambre";
    viscerales[2] = "Sueño";
    viscerales[3] = "Agotamiento";
    printf("\tLa transformación de los atritutos Viscerales son:\n");
    transfo(4, viscerales, viscerales_int);

    int *emociones_int = (int *)malloc(2*sizeof(int));
    char **emociones = (char **)malloc(2*sizeof(char *));
    emociones[0] = "Positivas";
    emociones[1] = "Negativas";
    printf("\tLa transformación de los atritutos de Emociones son:\n");
    transfo(2, emociones, emociones_int);

    int *conocimientos_int = (int *) malloc(5*sizeof(int));
    char **conocimientos = (char **) malloc(5*sizeof(char *));
    conocimientos[0] = "Habituales";
    conocimientos[1] = "Destrezas";
    conocimientos[2] = "Limitados";
    conocimientos[3] = "Trucos";
    conocimientos[4] = "Engaños";
    printf("\tLa transformación de los atributos de Conocimientos son:\n");
    transfo(5, conocimientos, conocimientos_int);

    for(int i1=0;i1<5;i1++){
        for(int i2=0;i2<3;i2++){
            for(int i3=0;i3<2;i3++){
                for(int i4=0;i4<6;i4++){
                    for(int i5=0;i5<4;i5++){
                        for(int i6=0;i6<2;i6++){
                            for(int i7=0;i7<5;i7++){
                                fprintf(gen, "%d,%d,%d,%d,%d,%d,%d\n", costumbres_int[i1], estatus_int[i2], cooperacion_int[i3],psicologicos_int[i4],viscerales_int[i5],emociones_int[i6],conocimientos_int[i5]);
                                total++;
                            }
                        }

                    }
                }


            }
        }
    }

    printf("\n\tArchivo BD_ASCII.dat generado con exito\n");
    printf("\tSe generaron %d registros\n",total);
    printf("\tGENERACION DE LA BASE DE DATOS FINALIZADA\n");
    fclose(gen);
}

void transfo(int tam_vect, char **vect_palabra, int *vect_ascii_int)
{
    int ascii, tam;
    for (int i = 0; i < tam_vect; i++)
    {
        ascii = 0;
        tam = strlen(vect_palabra[i]);
        printf("\t\tEl codigo ASCII de %s es: ", vect_palabra[i]);
        for (int ii = 0; ii < tam; ii++)
        {
                if(vect_palabra[i][ii]=='ñ'){
                        ascii += 164;
                }else{
                    ascii += vect_palabra[i][ii];
                }
        }
        vect_ascii_int[i] = ascii;
        printf("%d\n", ascii);
    }
}