#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>

int fact_ram;
int TAM_COLA = 0;

struct nodo_BFS
{
    int dato;
    //Doble apuntador es para un arreglo generico
    struct nodo_BFS **hijos;
    struct nodo_BFS *padre;
    struct nodo_BFS *sig;
};

typedef struct nodo_BFS Nodo_BFS;
Nodo_BFS *arbol;

struct nodo_Cola
{
    Nodo_BFS *info;
    struct nodo_cola *sig;
};

typedef struct nodo_Cola Nodo_Cola;

Nodo_Cola *Cola = NULL;
Nodo_Cola *E_A = NULL;

Nodo_BFS *creanodo_arbol(int elem);
Nodo_BFS *Desencolar(Nodo_Cola **);
Nodo_Cola *creanodo_cola(Nodo_BFS *nodo);
Nodo_BFS *set_hijos(Nodo_BFS *Hijos[fact_ram], Nodo_BFS *n);
void Encolar(Nodo_Cola **Cola, int elem, int b);

int main(int args, char *argv[])
{
    int niveles, nivel;
    int i, j, k, valores;
    srand(time(NULL));
    nivel = 0;
    printf("\nProporciona el factor de ramificacion del arbol:\n");
    scanf("%d", &fact_ram);

    printf("\nCuantos niveles del arbol quieres generar??\n");
    scanf("%d", &niveles);

    Nodo_BFS *nodo_inicial;
    Nodo_BFS *nodo;
    Nodo_BFS **Hijos = (Nodo_BFS **)malloc(fact_ram * sizeof(Nodo_BFS *));
    for (i = 0; i < fact_ram; i++)
    {
        Hijos[i] = (Nodo_BFS *)malloc(fact_ram * sizeof(Nodo_BFS));
    }

    valores = rand() % 101;
    nodo_inicial = creanodo_arbol(valores);
    arbol = nodo_inicial;

    Encolar(&Cola, nodo_inicial, 1);
    Encolar(&E_A, nodo_inicial, 0);
    nivel++;
    int exp = 0;
    while (TAM_COLA != 0)
    {
        for (k = 0; k < pow(fact_ram, exp); k++)
        {
            nodo = Desencolar(&Cola);
            if (nivel <= niveles)
            {
                for (i = 0; i < fact_ram; i++)
                {
                    valores = rand() % 101;
                    Hijos[i] = creanodo_arbol(valores);
                    Encolar(&Cola, Hijos[i], 1);
                    Encolar(&E_A, Hijos[i], 0);
                }
                nodo = set_hijos(Hijos, nodo);
            }
        }
        exp++;
        nivel++;
    }
    j = 0;

    for (i = 0; i <= niveles; i++)
    {
        if (i == 0)
        {
            printf("Los datos del arbol con sus respectivos datos son los siguientes\n");
            printf("Padre\n\tDato=%d\n\t", E_A->info->dato);
            printf("Direccion de Memoria del Padre= %p\n\t", E_A->info);
            printf("Direccion de Memoria del arreglo de Hijos=%p\n", E_A->info->hijos);
            E_A = E_A->sig;
            j++;
        }
        else
        {
            printf("\n\nLos hijos del nivel %d con su respectiva padre son:\n", i);
            printf("\tDireccion de Memoria del arreglo de los Hijos=%p\n", E_A->info->hijos);
            k = 0;
            while (k < pow(fact_ram, j))
            {
                printf("\n\tHijo[%d][%d]\n\tDato=%d\n", i, k + 1, E_A->info->dato);
                printf("\tDireccion de Memoria del Hijo[%d][%d]=%p\n", i, k + 1, E_A->info);
                printf("\tDireccion de Memoria de su Padre=%p\n", E_A->info->padre);
                E_A = E_A->sig;
                k++;
            }
            j++;
        }
    }

    return 0;
}
Nodo_BFS *creanodo_arbol(int elem)
{
    Nodo_BFS *aux;
    aux = (Nodo_BFS *)malloc(sizeof(Nodo_BFS));
    aux->dato = elem;
    aux->sig = NULL;
    return (aux);
}
Nodo_BFS *Desencolar(Nodo_Cola **Cola)
{
    Nodo_Cola *aux1;
    Nodo_Cola *aux2;
    aux1 = *Cola;
    if (aux1 != NULL)
    {
        aux2 = aux2->info;
        aux1 = aux1->sig;
        *Cola = aux1;
        TAM_COLA--;
        return aux2;
    }
    else
    {
        return NULL;
    }
}
Nodo_Cola *creanodo_cola(Nodo_BFS *nodo)
{
    Nodo_Cola *aux;
    aux = (Nodo_Cola *)malloc(sizeof(Nodo_Cola));
    aux->info = nodo;
    aux->sig = NULL;
    return (aux);
}
Nodo_BFS *set_hijos(Nodo_BFS *Hijos[fact_ram], Nodo_BFS *n)
{
    int i;
    n->hijos = Hijos;
    if (n->hijos != NULL)
    {
        for (i = 0; i < fact_ram; i++)
        {
            Hijos[i]->padre = n;
        }
    }
    return n;
}
void Encolar(Nodo_Cola **C, int elem, int b)
{
    Nodo_Cola *nuevo, *aux1, *aux2;
    aux1 = *C;
    nuevo = creanodo_cola(elem);
    while (aux1 != NULL)
    {
        aux2 = aux1;
        aux1 = aux1->sig;
    }
    if (*C == NULL)
    {
        *C = nuevo;
        if (b)
        {
            TAM_COLA++;
        }
    }
    else
    {
        aux2->sig = nuevo;
        if (b)
        {
            TAM_COLA++;
        }
    }
}