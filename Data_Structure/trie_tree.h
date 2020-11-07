/*
 * trie tree header file
 * class: trie_node, trie_tree
 * this trie tree only support 26 lowercase characters
 * for tree: insert, delete, search
*/

#ifndef TRIE_TREE
#define TRIE_TREE

// dependencies
#include<iostream>
#include<memory>
using std::cout;
using std::unique_ptr;

class trie_node{
public:
    trie_node(){ // constructor
        for(int i=0; i<26; i++){
            next[i] = nullptr;
        }
        flag = false;
    } 
private:
    trie_node* next[26];
    bool flag;
};

class trie_tree{
public:
    trie_tree(){ // constructor
        root = unique_ptr<trie_node>();
    }

    // other method
    void print_tree();
    void insert(); // recursion
    void erase();
    bool find();
private:
    unique_ptr<trie_node> root;
};

#endif