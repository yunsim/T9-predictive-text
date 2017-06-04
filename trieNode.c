/*
 * trieNode.c - implementation of a trie node struct used for contstructing a trie to realize T9 predictive text
 * CSE 374 HW 5, Yunsi Mou
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trieNode.h"

// create an empty trie node
Node_t * CreateTrieNode() {
  Node_t * node = (Node_t *) malloc(sizeof(Node_t));
  node -> word = NULL;
  int i;
  for (i = 0; i < 11; i++) {
    node -> branch[i] = NULL;
  }
  return node;
}

// convert the given character to the corresponding digit in numeric keypads
int getDigit(char letter) {
  char table[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7,
          8, 8, 8, 9, 9, 9, 9};
  int i = letter - 'a';
  return table[i];
}

// translate the given word into its numeric key sequence, then
// build the trie with the word at the end of the path corresponding
// to the digits
void BuildTrie(Node_t * root, char * s) {
  Node_t * current = root;
  // make a copy of the given string
  int length = strlen(s);
  char * text = (char *) malloc(length);
  if (text != NULL) {
    strncpy(text, s, length - 1);
    text[length - 1] = '\0';
  }
  int i = 0;
  while (s[i] != '\n') {
    int digit = getDigit(s[i]);
    if (current -> branch[digit] == NULL) {
      current -> branch[digit] = CreateTrieNode();
    }
    current = current -> branch[digit];
    i++;
  }
  while (current -> branch[10] != NULL) {
    current = current -> branch[10];
  }
  if (current -> word == NULL) {
    current -> word = text;
  } else {
    current -> branch[10] = CreateTrieNode();
    current = current -> branch[10];
    current -> word = text;
  }
}

// traverse and search the trie node according to the given key sequence
Node_t * FindNode(Node_t * root, char * number) {
  Node_t * cur = root;
  int i;
  for (i = 0; i < strlen(number); i++) {
    if (number[i] != '#') {
      if (cur -> branch[(number[i] - '0')] == NULL) {
        return NULL;
      }
      cur = cur -> branch[(number[i] - '0')];
    } else {
      if (cur -> branch[10] == NULL) {
        return NULL;
      }
      cur = cur -> branch[10];
    }
  }
  return cur;
}

// recursively free all the decendent nodes of the root
void malfree(Node_t * root) {
  int i;
  for (i = 0; i < 11; i++) {
    if (root -> branch[i] != NULL) {
      malfree(root -> branch[i]);
      free(root -> branch[i]);
    }
  }
  if (root -> word != NULL) {
    free(root -> word);
  }
}
