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
        Node* Root();
        void insert(int val);
        void remove(int val);
        int left(int val);
        int right(int val);
        int parent(int val);
        int root();
        int size();
        Node* find(int val);
        bool contains(int val);
        void print();
    private:
        Node *_Root;
        int Size;
    };
}
#endif /* Tree_hpp */
