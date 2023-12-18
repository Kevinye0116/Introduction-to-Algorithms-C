//
// Created by Kevin Ye on 12/11/2023.
// Copyright (c) KevinYe on 12/11/2023.

#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

struct Node *InitNode() {
  return NULL;
}

struct Node *Prepend(struct Node *head, int data) {
  struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
  if (newNode == NULL) {
    printf("Memory Allocation Faailed\n");
    exit(EXIT_FAILURE);
  }

  newNode->data = data;
  newNode->next = head;
  head = newNode;

  return head;
}

struct Node *insertAtEnd(struct Node *head, int data) {
  struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
  if (newNode == NULL) {
    printf("Memory Allocation Failed\n");
    exit(EXIT_FAILURE);
  }
  newNode->data = data;
  newNode->next = NULL;

  if (head == NULL) {
    head = newNode;
  } else {
    struct Node *current = head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
  return head;
}

struct Node *insertAtPosition(struct Node *head, int data, int position) {
  struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
  if (newNode == NULL) {
    printf("Memory Allocation Failed\n");
    exit(EXIT_FAILURE);
  }

  newNode->data = data;

  if (position == 1) {
    newNode->next = head;
    head = newNode;
  } else {
    struct Node *current = head;
    int count = 1;

    while (count < position - 1 && current != NULL) {
      current = current->next;
      count++;
    }

    if (current == NULL) {
      printf("Invalid position\n");
      free(newNode);
      return head;
    }

    newNode->next = current->next;
    current->next = newNode;
  }

  return head;
}

struct Node *search(struct Node *head, int key) {
  struct Node *current = head;

  while (current != NULL) {
    if (current->data == key) {
      return current;
    }
    current = current->next;
  }

  return NULL;
}

void printList(struct Node *head) {
  struct Node *current = head;
  printf("List: ");
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

void freeList(struct Node *head) {
  struct Node *current = head;
  struct Node *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

int main(int argc, char *argv[]) {
  struct Node *myList = InitNode();

  myList = Prepend(myList, 1);
  myList = Prepend(myList, 2);
  myList = insertAtEnd(myList, 3);
  myList = insertAtEnd(myList, 4);
  myList = insertAtPosition(myList, 5, 3);

  printList(myList);

  int keyToSearch = 3;
  const struct Node *result = search(myList, keyToSearch);
  if (result != NULL) {
    printf("%d found in the list\n", keyToSearch);
  } else {
    printf("%d not found in the list\n", keyToSearch);
  }

  freeList(myList);

  return 0;
}