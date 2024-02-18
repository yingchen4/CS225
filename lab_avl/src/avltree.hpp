/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    std::cout << "t: " << t << std::endl;
    Node * r = t->right;
    std::cout << "r:" << r << std::endl;
    t->right = r->left;
    r->left = t;
    t=r;

    t->height = std::max(heightOrNeg1(t->left),heightOrNeg1(t->right)) + 1;
    r->left->height = std::max(heightOrNeg1(r->left->left),heightOrNeg1(r->left->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node * root = t->left;
    t->left = root->right;
    root->right = t;
    t=root;

    t->height = std::max(heightOrNeg1(t->left),heightOrNeg1(t->right)) + 1;
    t->right->height = std::max(heightOrNeg1(root->right->left),heightOrNeg1(root->right->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{   
    if (subtree == NULL) {
        return;
    }
    std::cout << "value" <<subtree->key << std::endl;
    std::cout << "subtree: " << heightOrNeg1(subtree) << std::endl;
    std::cout << "left: " << heightOrNeg1(subtree->left) << std::endl;
    std::cout << "right: " << heightOrNeg1(subtree->right) << std::endl;
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if ( balance == -2 ) {
        int l_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if ( l_balance == -1 ) { 
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }    
    } else if ( balance == 2 ) {
        int r_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (r_balance == 1) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    }
    int leftHeight = heightOrNeg1(subtree->left);
    int rightHeight = heightOrNeg1(subtree->right);
    //balance = leftHeight - rightHeight;
    if (leftHeight > rightHeight) {
        subtree->height = leftHeight + 1;
    } else {
        subtree->height = rightHeight + 1;
    }
    // your code here

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL) {
        subtree = new Node{key,value};
    } else if (key < subtree->key) {
        insert(subtree->left,key,value);
    } else {
        insert(subtree->right,key,value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL) {
        return;
    }
    if (key < subtree->key) {
        remove(subtree->left,key);
    } else if (key > subtree->key) {
        remove(subtree->right,key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node * temp = subtree->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            swap(subtree, temp);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            if (subtree->left != NULL) {
                Node * temp = subtree->left;
                delete subtree;
                subtree = temp;
            } else {
                Node * temp = subtree->right;
                delete subtree;
                subtree = temp;
            }
            // your code here
        }
    }
    rebalance(subtree);
}
