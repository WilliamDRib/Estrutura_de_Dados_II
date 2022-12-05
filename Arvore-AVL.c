#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *right, *left;
  int data;
  int height;
} Node;

Node *new_node(int x) {
  Node *node = (Node *)malloc(sizeof(Node));

  node->data = x;
  node->left = NULL; // Inicializando o node;
  node->right = NULL;
  node->height = 0;

  return node;
}

int max(int a, int b) {
  if (a > b) {
    return a;
  } else { // Maior valor;
    return b;
  }
}

int height(Node *node) {
  if (node == NULL) {
    return 0;
  } // Função para descobrir o tamanho da arvore;

  return 1 + max(height(node->left), height(node->right));
}

/*
Realizando rotação a direita (horário);

    10                   8
   /                    / \
  8        --->       5    10
 /
5
*/
Node *rightRotate(Node *node) {
  Node *aux = node->left;
  Node *temp = aux->right;

  aux->right = node;
  node->left = temp;

  node->height = height(node);
  aux->height = height(aux);

  return aux;
}

/*
Realizando rotação a esquerda (anti-horário);

    5                    8
     \                  / \
      8     --->       5   10
       \
       10

*/
Node *leftRotate(Node *node) {
  Node *aux = node->right;
  Node *temp = aux->left;

  aux->left = node;
  node->right = temp;

  node->height = height(node);
  aux->height = height(aux);

  return aux;
}

int getBalance(Node *node) {
  if (node == NULL) {
    return 0;
  }
  return height(node->left) - height(node->right);
}

// Procurando por valor na arvore e o retornando;
Node *search(Node *node, int value) {
  if (node == NULL || node->data == value) {
    return node;
  } else if (value > node->data) {
    return search(node->right, value);
  } else {
    return search(node->left, value);
  }
}

// Procurando o menor valor, indo a esquerda;
Node *find_minimum(Node *node) {
  if (node == NULL) {
    return NULL;
  } else if (node->right != NULL) {
    return find_minimum(node->right);
  }

  return node;
}

Node *insert(Node *node, int value) {
  if (node == NULL) {
    return new_node(value);
  } else {
    if (value > node->data) {
      node->right = insert(node->right, value);
    } else if (value <= node->data) {
      node->left = insert(node->left, value);
    }
  }

  node->height = height(node);

  int balance = getBalance(node);

  // Se for maior que 1 está "pesado a esquerda"
  if (balance > 1) {
    if (value < node->left->data) {
      return rightRotate(node);
    }

    else if (value > node->left->data) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }

  // Se for menor que -1 está "pesado a direita"
  if (balance < -1) {
    if (value > node->right->data) {
      return leftRotate(node);
    }

    else if (value < node->right->data) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }

  return node;
}

Node *deleteNode(Node *node, int value) {

  if (node == NULL) {
    return NULL;
  }

  if (value > node->data) {
    node->right = deleteNode(node->right, value);
  } else if (value < node->data) { // Procura pelo node;
    node->left = deleteNode(node->left, value);
  } else {
    // Caso tenha achado;

    // Sem filhos;
    if (node->left == NULL && node->right == NULL) {
      free(node);
      return NULL;
    }

    // Possue somente 1 filho;
    else if (node->left == NULL || node->right == NULL) {
      Node *temp;
      if (node->left == NULL) {
        temp = node->right;
      } else {
        temp = node->left;
      }
      free(node);
      return temp;
    }

    // Possue os 2 filhos;
    else {
      Node *temp = find_minimum(node->left);
      node->data = temp->data;
      node->left = deleteNode(node->left, temp->data);
    }
  }
  return node;
}

void in_order(Node *node) {
  if (node != NULL) {
    in_order(node->left);
    printf(" %i ", node->data);
    in_order(node->right);
  }
}

void pre_order(Node *node) {
  if (node != NULL) {
    printf(" %i, ", node->data);
    pre_order(node->left);
    pre_order(node->right);
  }
}

void pos_order(Node *node) {
  if (node != NULL) {
    pos_order(node->left);
    pos_order(node->right);
    printf(" %i, ", node->data);
  }
}

void print2D(Node *node, int alt) {
  if (node == NULL)
    return;

  alt += 1;

  print2D(node->right, alt);

  for (int i = 0; i < alt; i++) {
    printf("	");
  }
  printf("%d\n", node->data);

  print2D(node->left, alt);
}
int main() {
  Node *top = NULL;

  top = insert(top, 15);
  top = insert(top, 25);
  top = insert(top, 35);
  top = insert(top, 45);
  top = insert(top, 65);
  top = insert(top, 55);
  top = insert(top, 44);
  top = insert(top, 34);
  top = insert(top, 24);
  top = insert(top, 10);
  top = insert(top, 15);

  top = deleteNode(top, 25);
  top = deleteNode(top, 35);
  top = deleteNode(top, 15);

  top = insert(top, 42);
  top = insert(top, 40);
  top = insert(top, 43);

  top = deleteNode(top, 44);

  top = insert(top, 60);
  top = insert(top, 70);
  top = insert(top, 50);
  top = insert(top, 67);
  top = insert(top, 64);

  top = deleteNode(top, 65);

  printf("\n\n");
  printf("Tree: \n");
  print2D(top, 0);

  printf("\n\n");
	
  printf("Pre-order: \n");
  pre_order(top);
  printf("\n\n");

  return 0;
}