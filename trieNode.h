/*
 * trieNode.h - interfece to routine to contstruct a trie to realize T9 predictive text
 * CSE 374 HW 5, Yunsi Mou
 */

#ifndef TRIENODE_H
#define TRIENODE_H

// define the struct trieNode
typedef struct trieNode {
  char * word;
  struct trieNode * branch[11];
} Node_t;

Node_t * CreateTrieNode();
int getDigit(char letter);
void BuildTrie(Node_t * root, char * s);
Node_t * FindNode(Node_t * root, char * number);
void malfree(Node_t * root);

#endif
