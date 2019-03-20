//
//  Tree.cpp
//  Binary_Tree
//
//  Created by Jeme Jbareen on 3/18/19.
//  Copyright © 2019 Jeme Jbareen. All rights reserved.
//

#include<iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include "Tree.hpp"
using std::vector;
using std::string;

using namespace std;
using namespace ariel;
Tree::Tree():Size(0),_Root(NULL){}
Node* Tree::Root(){return _Root;}
bool contains(int key, Node *leaf){
    if(leaf!=NULL){
        if(key==leaf->val)
            return true;
        if(key<leaf->val)
            return contains(key, leaf->left);
        else
            return contains(key, leaf->right);
    }
    else return false;
}
bool Tree::contains(int val){
    return ::contains(val, _Root);
}
void insert(int key,Node *leaf){
    if(key< leaf->val){
        if(leaf->left!=NULL)
            insert(key, leaf->left);
        else{
            leaf->left=new Node;
            leaf->left->val=key;
            leaf->left->left=NULL;
            leaf->left->right=NULL;
            leaf->left->parent=leaf;
        }
    }
    else if(key>=leaf->val){
        if(leaf->right!=NULL)
            insert(key, leaf->right);
        else{
            leaf->right=new Node;
            leaf->right->val=key;
            leaf->right->left=NULL;
            leaf->right->right=NULL;
            leaf->right->parent=leaf;
        }
    }
    
}
void Tree::insert(int val){
    
    if(Root()!=NULL){
        if(contains(val))
            throw "the value is exists!";
        ::insert(val,_Root);
        Size++;
    }
    else{
        _Root=new Node;
        _Root->val=val;
        _Root->left=NULL;
        _Root->right=NULL;
        _Root->parent=NULL;
        Size++;
    }
}
Node* remove(Node* root, int k){
    if (root == NULL)
        return root;
    if (root->val > k) {
        root->left = remove(root->left, k);
        return root;
    }
    else if (root->val < k) {
        root->right = remove(root->right, k);
        return root;
    }
    if (root->left == NULL) {
        Node* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        Node* temp = root->left;
        delete root;
        return temp;
    }
    else {
        Node* succParent = root->right;
        Node *succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }
        succParent->left = succ->right;
        root->val = succ->val;
        delete succ;
        return root;
    }
}
void Tree::remove(int val){
    if(!contains(val))
        throw "you are trying to delete unvalid value!";
    if(_Root!=NULL){
        ::remove(_Root,val);
        Size--;
    }
}
int Tree::size(){return Tree::Size;}
int Tree::root(){return _Root->val;}
Node* find(int key, Node *leaf){
    if(leaf!=NULL){
        if(key==leaf->val)
            return leaf;
        if(key<leaf->val)
            return find(key, leaf->left);
        else
            return find(key, leaf->right);
    }
    else return NULL;
}
Node* Tree::find(int val){
    return ::find(val, _Root);
}
int Tree::parent(int val){
    Node *a=find(val);
    if(a->parent!=NULL)
        return a->parent->val;
    return -9999;
}
int Tree::left(int val){
    Node* a=find(val);
    if(a->left!=NULL)
        return a->left->val;
    return 0;
}
int Tree::right(int val){
    Node* a=find(val);
    if(a->right!=NULL)
        return a->right->val;
    return 0;
}
void print(Node *root,int size, int space){
    if (root == NULL)
        return;
    space += size;
    ::print(root->right,size, space);
    cout<<endl;
    for (int i = size; i < space; i++)
        cout<<" ";
    cout<<root->val<<"\n";
    :: print(root->left,size, space);
}
void Tree::print(){::print(_Root,Size,0);}
