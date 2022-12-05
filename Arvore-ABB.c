#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *right, *left;
  int data;
} Node;

Node *new_node(int x) {
  Node *node = (Node *)malloc(sizeof(Node));

  node->data = x;
  node->left = NULL; // Inicializando o node;
  node->right = NULL;

  return node;
}

Node *search(Node *node, int value) {
  if (node == NULL || node->data == value) {
    return node;
  } else if (value > node->data) {
    return search(node->right, value);
  } else {
    return search(node->left, value);
  }
}

Node *find_minimum(Node *node) {
  if (node == NULL) {
    return NULL; // Procurando o menor valor, indo a esquerda;
  } else if (node->left != NULL) {
    return find_minimum(node->left);
  }

  return node;
}

Node *insert(Node *node, int value) {
  if (node == NULL) {
    return new_node(value);
  } else if (value > node->data) {
    node->right = insert(node->right, value);
  } else {
    node->left = insert(node->left, value);
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
    if (node->left == NULL && node->right == NULL) {
      free(node); // Sem filhos;
      return NULL;
    }

    else if (node->left == NULL || node->right == NULL) {
      Node *temp;
      if (node->left == NULL) {
        temp = node->right; // Possue somente 1 filho;
      } else {
        temp = node->left;
      }
      free(node);
      return temp;
    }

    else {
      Node *temp = find_minimum(node->right);
      node->data = temp->data; // Possue os 2 filhos;
      node->right = deleteNode(node->right, temp->data);
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

  top = insert(top, 10);
  top = insert(top, 20);
  top = insert(top, 30);
  top = insert(top, 40);
  top = insert(top, 50);
  top = insert(top, 60);
  top = insert(top, 70);
  top = insert(top, 80);
  top = insert(top, 90);

  /*
      10
            \
                 20
           \
            30
              \
               40
                 \
                  50
                    \
                    ...
  */

  printf("Tree: \n");
  print2D(top, 0);

  top = deleteNode(top, 40);
  top = deleteNode(top, 50);

  printf("\n\n");
  printf("Tree: \n");
  print2D(top, 0);

  top = insert(top, 40);
  top = insert(top, 50);

  printf("\n\n");
  printf("Tree: \n");
  print2D(top, 0);

  printf("\n\n");
  printf("In order: ");
  in_order(top);

  return 0;
}