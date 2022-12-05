#include <stdbool.h>
#include <stdio.h>

// Global Vertices
#define V 5

// Printar solução;
void printSolution(int path[]) {
  printf("Solução Existe, caminho seguido: \n");
  for (int i = 0; i < V; i++) {
    printf(" %d ", path[i]);
  }

  printf(" %d ", path[0]);
  printf("\n");
}

bool isSafe(int iVer, bool graph[V][V], int path[], int pos) {

  // Verifica se o vertice é adjacente ao adicionado anteriormente;
  if (graph[path[pos - 1]][iVer] == 0) {
    return false;
  }

  // Verifica se o vertice ja foi usado;
  for (int i = 0; i < pos; i++) {
    if (path[i] == iVer) {
      return false;
    }
  }
  return true;
}

bool hamCycleUtil(bool graph[V][V], int path[], int pos) {

  // Caso todos ja tenham adicionados;
  if (pos == V) {
    if (graph[path[pos - 1]][path[0]] == 1)
      return true;
    else
      return false;
  }

  for (int iVer = 1; iVer < V; iVer++) {

    // Checa se pode adicionar o vertice;
    if (isSafe(iVer, graph, path, pos)) {
      path[pos] = iVer;

      // Chama recursivamente para o proximo vertice;
      if (hamCycleUtil(graph, path, pos + 1) == true) {
        return true;
      }
    }
  }

  // Se nenhum vertice conseguiu ser adicionado;
  return false;
}

bool hamCycle(bool graph[V][V]) {
  int path[V];

  // Primeiro vertice 0;
  path[0] = 0;

  if (hamCycleUtil(graph, path, 1) == false) {
    printf("\n Solução não existe");
    return false;
  }

  printSolution(path);
  return true;
}

int main() {
  /* (0)--(1)--(2)
      |   / \   |
      |  /   \  |
      | /     \ |
     (3)-------(4)    */

  bool graph1[V][V] = {
      {0, 1, 0, 1, 0}, {1, 0, 1, 1, 1}, {0, 1, 0, 0, 1},
      {1, 1, 0, 0, 1}, {0, 1, 1, 1, 0},
  };

  hamCycle(graph1);

  /* (0)--(1)--(2)
      |   / \   |
      |  /   \  |
      | /     \ |
     (3)       (4)    */
  bool graph2[V][V] = {
      {0, 1, 0, 1, 0}, {1, 0, 1, 1, 1}, {0, 1, 0, 0, 1},
      {1, 1, 0, 0, 0}, {0, 1, 1, 0, 0},
  };

  hamCycle(graph2);

  return 0;
}