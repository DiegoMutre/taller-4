#include <stdio.h>
#include <stdlib.h>

typedef struct tiponodo
{
  int clave;
  double valor;
  int peso;
  int nivel;
  struct tiponodo *s;
  struct tiponodo *a;
} NODO;

typedef struct arbol
{
  NODO *raiz;
  int nelementos;
} arbolBinario;

NODO *crearNodo(int clave, double valor)
{
  NODO *h = NULL;

  h = (NODO *)malloc(sizeof(NODO));

  if (h != NULL)
  {
    h->clave = clave;
    h->valor = valor;
    h->peso = 0;
    h->nivel = 0;
    h->a = NULL;
    h->s = NULL;
  }

  return h;
}

NODO *agregar(NODO *r, int clave, double valor, int *n)
{
  NODO *h = NULL;
  int peso = 0;
  int nivel = 0;

  h = crearNodo(clave, valor);

  if (h != NULL)
  {
    if (r == NULL)
    {
      r = h;
      *n = *n + 1;
    }
    else
    {
      if (clave < r->clave)
      {
        r->a = agregar(r->a, clave, valor, n);
      }
      else
      {
        r->s = agregar(r->s, clave, valor, n);
      }

      if (r->a != NULL)
      {
        nivel = r->a->nivel;
        peso = -nivel - 1;
      }

      if (r->s != NULL)
      {
        peso = peso + r->s->nivel + 1;
        if (r->s->nivel > nivel)
        {
          nivel = r->s->nivel;
        }
      }

      r->nivel = nivel + 1;
      r->peso = peso;
    }
  }
  return r;
}

arbolBinario *agregarNodo(arbolBinario *a, int clave, double valor)
{
  if (a != NULL)
  {
    a->raiz = agregar(a->raiz, clave, valor, &a->nelementos);
  }

  return a;
}

arbolBinario *crearArbolBinario()
{
  arbolBinario *a = (arbolBinario *)malloc(sizeof(arbolBinario));

  if (a != NULL)
  {
    a->raiz = NULL;
    a->nelementos = 0;
  }

  return a;
}

void imprimirNodo(int clave, double valor, int nivel, int peso)
{
  printf(" {\"clave\": \"%d\", \"valor\": \"%lf\", \"nivel\": \"%d\", \"peso\": \"%d\"} ", clave, valor, nivel, peso);
}

void imprimir(NODO *nodo, int modo)
{
  if (nodo != NULL)
  {
    if (modo == -1)
    {
      imprimirNodo(nodo->clave, nodo->valor, nodo->nivel, nodo->peso);
    }

    if (nodo->a != NULL)
    {
      imprimir(nodo->a, modo);
    }

    if (modo == 0)
    {
      imprimirNodo(nodo->clave, nodo->valor, nodo->nivel, nodo->peso);
    }

    if (nodo->s != NULL)
    {
      imprimir(nodo->s, modo);
    }

    if (modo == 1)
    {
      imprimirNodo(nodo->clave, nodo->valor, nodo->nivel, nodo->peso);
    }
  }
}

void imprimirArbol(arbolBinario *a, int modo)
{
  if (a != NULL)
  {
    printf("{\"tipo\": \"arbol\", \"nelementos\": \"%d\", \"raiz\":[", a->nelementos);
    imprimir(a->raiz, modo);
    printf("]}");
  }
}

NODO *vaciar(NODO *nodo)
{

  if (nodo != NULL)
  {
    if (nodo->a != NULL)
      vaciar(nodo->a);
    if (nodo->s != NULL)
      vaciar(nodo->s);
    free(nodo);
    nodo = NULL;
  }

  return nodo;
}

arbolBinario *eliminarArbolBinario(arbolBinario *arbol)
{
  if (arbol != NULL)
  {

    arbol->raiz = vaciar(arbol->raiz);
    free(arbol);
    arbol = NULL;
  }

  return arbol;
}

NODO *buscar(NODO *r, int clave)
{
  if (r == NULL)
  {
    return NULL;
  }

  NODO *nodo = NULL;

  if (r->clave == clave)
  {
    nodo = r;
  }

  if (clave < r->clave)
  {
    nodo = buscar(r->a, clave);
  }
  else if (clave > r->clave)
  {
    nodo = buscar(r->s, clave);
  }

  return nodo;
}

void buscarNodo(arbolBinario *arbol, int clave)
{
  if (arbol != NULL && arbol->raiz != NULL)
  {
    NODO *nodo = buscar(arbol->raiz, clave);

    if (nodo != NULL)
    {
      printf("\nNODO \"%d\" ENCONTRADO!\n", clave);
      imprimirNodo(nodo->clave, nodo->valor, nodo->nivel, nodo->peso);
    }
    else
    {
      printf("\nNODO \"%d\" NO ENCONTRADO\n", clave);
    }
  }
  else
  {
    printf("El arbol esta vacio");
  }
}

int main()
{
  arbolBinario *arbol = crearArbolBinario();
  double datos[] = {22, 2, 47, 72, 88, 35};

  // Obtener la longitud del array de datos
  int datos_length = sizeof(datos) / sizeof(datos[0]);

  printf("\n\n=============================AGREGAR DATOS AL ARBOL BINARIO=============================\n\n");

  // Agregar los datos al arbol binario
  for (int i = 0; i < datos_length; i++)
  {
    printf("\nAgregando: %.f\n", datos[i]);

    agregarNodo(arbol, datos[i], datos[i]);
    imprimirArbol(arbol, 0);

    printf("\n");
  }

  printf("\n\n=========================BUSCAR CADA VALOR EN EL ARBOL BINARIO=========================\n\n");

  // Buscar cada NODO en el arbol binario
  for (int i = 0; i < datos_length; i++)
  {
    buscarNodo(arbol, datos[i]);
  }

  printf("\n\n=========================BUSCAR UN VALOR QUE NO ESTA EN EL ARBOL BINARIO=========================\n\n");

  // Buscar un NODO el cual no existe en el arbol binario
  buscarNodo(arbol, 55); // 55 no esta en el arbol binario

  printf("\n\n=========================VACIAR EL ARBOL BINARIO=========================\n\n");

  // Vaciar el arbol binario
  arbol = eliminarArbolBinario(arbol);

  if (arbol == NULL)
    printf("El arbol esta vacio");

  printf("\n\n=========================BUSCAR UN VALOR QUE ANTES ESTABA EN EL ARBOL BINARIO=========================\n\n");

  buscarNodo(arbol, 72);
}