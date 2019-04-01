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
void Tree::rmAll(Node* root){
    if(root==NULL)return;
    rmAll(root->left);
    rmAll(root->right);
    if(root->val==_Root->val){
        delete _Root->parent;
        _Root->parent=NULL;
    }
    delete root;
    root=NULL;
}
Tree::~Tree(){
    rmAll(_Root);
}
Node* Tree::Root(){return _Root;}
bool Tree::containsHelp(int key, Node *leaf){
    if(leaf!=NULL){
        if(key==leaf->val)
            return true;
        if(key<leaf->val)
            return containsHelp(key, leaf->left);
        else
            return containsHelp(key, leaf->right);
    }
    else return false;
}
bool Tree::contains(int val){
    return containsHelp(val, _Root);
}
void Tree::insertHelp(int key,Node *leaf){
    if(key< leaf->val){
        if(leaf->left!=NULL)
            insertHelp(key, leaf->left);
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
            insertHelp(key, leaf->right);
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
        insertHelp(val,_Root);
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
Node *ariel::Tree::FindNextNum(int num) // Find the next number after num using number
{
    Node *curr = find(num);
    return FindNextNode(curr);
}

Node *ariel::Tree::FindNextNode(Node *curr) // Find the next number after num using current node
{
    Node *next = curr->right;
    while (next->left != NULL)
    {
        next = next->left;
    }
    return next;
}
bool ariel::Tree::remove(int num)
{
    Node *rm = find(num);
    if (rm == NULL)
        throw "invalid value!";
    if (rm->left == NULL && rm->right == NULL){
        if (rm->parent != NULL){
            if (rm->parent->right == rm)
                rm->parent->right = NULL;
            else
                rm->parent->left = NULL;
        }
        else{
            _Root = NULL;
        }
        delete rm;
        Size--;
        return true;
    }
    else if (rm->left == NULL || rm->right == NULL){
        Node *temp = NULL;
        if (rm->left == NULL)
            temp = rm->right;
        if (rm->right == NULL)
            temp = rm->left;
        
        if (rm->parent != NULL)
        {
            temp->parent = rm->parent;
            if (rm->parent->right == rm)
                rm->parent->right = temp;
            else
                rm->parent->left = temp;
        }
        else{
            _Root = temp;
            temp->parent = NULL;
        }
        
        delete rm;
        Size--;
        return true;
    }
    else if (rm->left != NULL && rm->right != NULL){
        Node *next = FindNextNode(rm);
        int temp = next->val;
        remove(temp);
        rm->val = temp;
        return true;
    }
    return false;
}

int Tree::size(){return Tree::Size;}
int Tree::root(){
    if(_Root==NULL)
        throw "there is no root!";
    return _Root->val;
}
Node* Tree::findHelp(int key, Node *leaf){
    if(leaf!=NULL){
        if(key==leaf->val)
            return leaf;
        if(key<leaf->val)
            return findHelp(key, leaf->left);
        else
            return findHelp(key, leaf->right);
    }
    else return NULL;
}
Node* Tree::find(int val){
    return findHelp(val, _Root);
}
int Tree::parent(int val){
    Node *a=find(val);
    if(a!=NULL&&a->parent!=NULL)
        return a->parent->val;
    throw "invalid parent!";
}
int Tree::left(int val){
    Node* a=find(val);
    if(a!=NULL&&a->left!=NULL)
        return a->left->val;
    throw "there is no left to this value!";
}
int Tree::right(int val){
    Node* a=find(val);
    if(a!=NULL&&a->right!=NULL)
        return a->right->val;
    throw "there is no right to this value!";
}
//https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void Tree::printHelp(Node *root,int size, int space){
    if (root == NULL)
        return;
    space += size;
    printHelp(root->right,size, space);
    cout<<endl;
    for (int i = size; i < space; i++)
        cout<<" ";
    cout<<root->val<<"\n";
    printHelp(root->left,size, space);
}
void Tree::print(){printHelp(_Root,Size,0);}
