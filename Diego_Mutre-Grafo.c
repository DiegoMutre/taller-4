#include <stdio.h>
#include <stdlib.h>

typedef struct Grafo
{
  int numVertices;
  int **matrizAdyacencia;
} Grafo;

Grafo *crearGrafo(int numVertices)
{
  Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
  grafo->numVertices = numVertices;

  grafo->matrizAdyacencia = (int **)malloc(numVertices * sizeof(int *));
  for (int i = 0; i < numVertices; i++)
  {
    grafo->matrizAdyacencia[i] = (int *)malloc(numVertices * sizeof(int));
    for (int j = 0; j < numVertices; j++)
    {
      grafo->matrizAdyacencia[i][j] = 0;
    }
  }

  return grafo;
}

void agregarArista(Grafo *grafo, int origen, int destino)
{
  if (origen >= 0 && origen < grafo->numVertices && destino >= 0 && destino < grafo->numVertices)
  {
    grafo->matrizAdyacencia[origen][destino] = 1;
  }
}

void imprimirMatrizAdyacencia(Grafo *grafo)
{
  printf("Matriz de Adyacencia:\n");
  for (int i = 0; i < grafo->numVertices; i++)
  {
    for (int j = 0; j < grafo->numVertices; j++)
    {
      printf("%d ", grafo->matrizAdyacencia[i][j]);
    }
    printf("\n");
  }
}

void crearListaAdyacencia(Grafo *grafo)
{
  printf("Lista de Adyacencia:\n");
  for (int i = 0; i < grafo->numVertices; i++)
  {
    printf("%d: ", i);
    for (int j = 0; j < grafo->numVertices; j++)
    {
      if (grafo->matrizAdyacencia[i][j] == 1)
      {
        printf("%d ", j);
      }
    }
    printf("\n");
  }
}

int main()
{
  int numVertices = 5;
  Grafo *grafo = crearGrafo(numVertices);

  int aristas[][2] = {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3}, {3, 4}, {4, 0}, {4, 1}};
  int aristas_length = sizeof(aristas) / sizeof(aristas[0]);

  // Crear las aristas en el grafo
  for (int i = 0; i < aristas_length; i++)
  {
    agregarArista(grafo, aristas[i][0], aristas[i][1]);
  }

  // Imprimir el grafo
  imprimirMatrizAdyacencia(grafo);
  crearListaAdyacencia(grafo);

  // Vaciar el grafo
  for (int i = 0; i < numVertices; i++)
  {
    free(grafo->matrizAdyacencia[i]);
  }
  free(grafo->matrizAdyacencia);
  free(grafo);

  return 0;
}
