//
//  Tree.cpp
//  Binary_Tree
//
//  Created by Jeme Jbareen on 3/18/19.
//  Copyright © 2019 Jeme Jbareen. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp

#include <stdio.h>
namespace ariel{
    struct Node{
        int val;
        Node *left;
        Node *right;
        Node *parent;
    };
    class Tree{
    public:
        Tree();
        ~Tree();
        void insert(int val);
        bool remove(int val);
        int left(int val);
        int right(int val);
        int parent(int val);
        int root();
        int size();
        bool contains(int val);
        void print();
    private:
        bool containsHelp(int key, Node *leaf);
        void insertHelp(int key,Node *leaf);
        void printHelp(Node *root,int size, int space);
        Node* findHelp(int key, Node *leaf);
        Node* Root();
        Node* find(int val);
        void rmAll(Node *root);
        Node *FindNextNum(int num);
        Node *FindNextNode(Node *curr);
        Node *_Root;
        int Size;
    };
}
#endif /* Tree_hpp */
