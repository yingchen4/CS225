/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <vector>
#include <algorithm>
#include <iostream>

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    return find(root, key)->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if (subtree == NULL || subtree->key == key) {
        return subtree;
    }

    if (key < subtree->key) {
        return find(subtree->left, key);
    } else {
        return find(subtree->right, key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{   if (root == NULL) {
        Node* newNode = new Node(key, value);
        root = newNode;
        return;
    }
    if (find(root,key) != NULL) {
        return;
    }
    insert(root,key,value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{   
    
    if (key < subtree->key) {
        if (subtree->left == NULL) {
            Node* newNode = new Node(key, value);
            subtree->left = newNode;
        }
        insert(subtree->left,key,value);

    }
    if (key > subtree->key) {
        if (subtree->right == NULL) {
            Node* newNode = new Node(key, value);
            subtree->right = newNode;
        }
        insert(subtree->right,key,value);
    }
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    if (first == NULL || second == NULL) {
        return;
    }

    std::swap(first->key, second->key);
    std::swap(first->value, second->value);
}

template <class K, class V>
struct BST<K, V>::Node* BST<K, V>::findMinKey(Node* subtree) const {
    while (subtree->left != nullptr) {
        subtree = subtree->left;
    }
    return subtree;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    if (find(root, key) == NULL) {
        return;
    }
    remove(root,key);

}


template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key) {
    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else { //key = subtree->key
        // no child
        if (subtree->left == NULL && subtree->right == NULL) {
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left == nullptr && subtree->right != NULL) {
        // right child
            Node* temp = subtree->right;
            delete subtree;
            subtree = temp;
            return;
        }  else if (subtree->left != nullptr && subtree->right == NULL) {
        // left child
            Node* temp = subtree->left;
            delete subtree;
            subtree = temp;
            return;
        } else {
        //  two children
            // std::cout << __LINE__ << std::endl;
            Node* change = findMinKey(subtree->right);
            swap(change,subtree);
            remove(subtree->right, key);
            return;
        }
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K, V> tree;
    for (auto & pair : inList) {
        tree.insert(pair.first, pair.second);
    }
    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    std::sort(inList.begin(), inList.end());

    std::vector<int> out(inList.size(), 0);

    do {
        BST<K, V> tree = listBuild(inList);
        out[tree.height()]++;
    } while (std::next_permutation(inList.begin(), inList.end()));

    return out;
}