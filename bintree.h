#ifndef BINTREE_H
#define BINTREE_H
#include "Planet.h"
#include "Galaxy.h"
typedef Planet Item;
namespace Tree
{
    struct node
    {
        double route;
        Item key;
        node *left;
        node *right;
        node(Item k, double rou){key = k; route = rou; left = nullptr; right = nullptr;}
    };
    typedef node *link;
    link h = nullptr;

    void insert(Item item, double route) 
    {
        if (h == nullptr) 
        {
            h = new node(item, route);
            return;
        }
        
        link current = h;
        link parent = nullptr;
        
        while (current != nullptr) 
        {
            parent = current;
            if (item < current->key) 
            {
                current = current->left;
            } 
            else if (item > current->key) 
            {
                current = current->right;
            } 
            else 
            {
                return;
            }
        }
        
        link newNode = new node(item, route);
        if (item < parent->key) 
        {
            parent->left = newNode;
        }
        else 
        {
            parent->right = newNode;
        }
    }

    link findMin(link node) 
    {
        while (node != nullptr && node->left != nullptr) 
        {
            node = node->left;
        }
        return node;
    }
    link deleteNode(link node, Item item) 
    {
        if (node == nullptr) return nullptr;
        
        if (item < node->key) 
        {
            node->left = deleteNode(node->left, item);
        }
        else if (item > node->key) 
        {
            node->right = deleteNode(node->right, item);
        }
        else 
        {            
            if (node->left == nullptr) 
            {
                link temp = node->right;
                delete node;
                return temp;
            } 
            else if (node->right == nullptr) 
            {
                link temp = node->left;
                delete node;
                return temp;
            }
            
            link temp = findMin(node->right);
            
            node->key = temp->key;
            
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }
}
#endif