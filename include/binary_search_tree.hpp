#pragma once
#include <iostream>

namespace Tree {

    template<typename K, typename V>
    struct Entry {
        K key;
        V value;
    };

    template<typename K, typename V>
    struct Node {
        Entry<K, V> entry;
        Node *leftChild;
        Node *rightChild;
    };

    template<typename K, typename V>
    class BinarySearchTree {

        Node<K, V> *root;

        public:

            BinarySearchTree();

            // inserts the entry in the tree
            void Insert(Entry<K, V> e);

            // updates the first entry with the given key
            void Update(Entry<K, V> e);

            // removes the first entry with the given key
            void Delete(K key);
            
            // returns the value of the entry with the given key
            // returns false if not found
            // returns true if found and stores the data in retrieved_value
            bool Lookup(K key, V& retrieved_value);

            void Print2D();
    };


    template<typename K, typename V>
    BinarySearchTree<K, V>::BinarySearchTree() :root{ nullptr } { }

    template<typename K, typename V>
    void InsertHelper(Node<K, V> *&root, Entry<K, V> e) {
        
        Node<K, V> *node = new Node<K, V>;
        node->entry = e;

        if (root == nullptr) {
            root = node;
            return;
        }

        Node<K, V> *prev;
        Node<K, V> *current = root;

        while (current) {
            if (current->entry.key < e.key) {
                prev = current;
                current = current->rightChild;
            } else if (current->entry.key > e.key) {
                prev = current;
                current = current->leftChild;
            }
        }

        if (prev->entry.key < e.key) {
            prev->rightChild = node;
        } else {
            prev->leftChild = node;
        }
    }

    template<typename K, typename V>
    void BinarySearchTree<K, V>::Insert(Entry<K, V> e) {
        InsertHelper(root, e);
    }


    template<typename K, typename V>
    void BinarySearchTree<K, V>::Update(Entry<K, V> e) {
        Node<K, V> *current = root;

        while (current) {
            if (current->entry.key == e.key) {
                current->entry.value = e.value;
                return;
            } else if (current->entry.key < e.key) {
                current = current->rightChild;
            } else {
                current = current->leftChild;
            }
        }
    }

    template<typename K, typename V>
    Node<K, V> *findBSTMin(Node<K, V> *root) {
        while (root->leftChild)
            root = root->leftChild;
        
        return root;
    }

    // deletes the leftmost node of the given BST, then returns the new root
    template<typename K, typename V>
    Node<K, V> *deleteBSTMin(Node<K, V> *root) {
        if (root == nullptr) 
            return nullptr;
        
        if (root->leftChild == nullptr) {
            Node<K, V> *tmpNode = root->rightChild;
            delete root;
            return tmpNode;
        }

        root->leftChild = deleteBSTMin(root->leftChild);
        return root;
    }

    // deletes the key, searching in the subtree root and returns the new root
    template<typename K, typename V>
    Node<K, V> *DeleteRecursive(Node<K, V> *root, int key) {
        if (root->entry.key < key) {
            root->rightChild = DeleteRecursive(root->rightChild, key);
        } else if (root->entry.key > key) {
            root->leftChild = DeleteRecursive(root->leftChild, key);
        } else {
            if (root->leftChild == nullptr && root->rightChild == nullptr) {
                // case 1 : root is a leaf
                delete root;
                return nullptr;
            } else if (root->leftChild == nullptr && root->rightChild != nullptr) {
                // case 2 : root has a right child
                Node<K, V> *tmpNode = root->rightChild;
                delete root;
                return tmpNode;
            } else if (root->leftChild != nullptr && root->rightChild == nullptr) {
                // case 3 : root has a left child
                Node<K, V> *tmpNode = root->leftChild;
                delete root;
                return tmpNode;
            } else {
                // case 4 : root has two children
                Node<K, V> *tmpNode = findBSTMin(root->rightChild);
                root->entry = tmpNode->entry;
                root->rightChild = deleteBSTMin(root->rightChild);
            }

        }
        return root;
    }

    template<typename K, typename V>
    void BinarySearchTree<K, V>::Delete(K key) {
        Node<K, V> *newRoot = DeleteRecursive(root, key);
        root = newRoot;
    }

    template<typename K, typename V>
    bool BinarySearchTree<K, V>::Lookup(K key, V& retrieved_value) {
        Node<K, V> *current = root;

        if (current == nullptr)
            return false;

        // if current == nullptr, it means we've searched beyond a leaf
        while (current) {
            if (current->entry.key == key) {
                retrieved_value = current->entry.value;
                return true;
            } else if (current->entry.key < key) {
                current = current->rightChild;
            } else {
                current = current->leftChild;
            }
        }

        return false;
    }

    // Function to print binary tree in 2D
    // It does reverse inorder traversal
    template<typename K, typename V>
    void print2DUtil(Node<K, V> *root, int space)
    {    
        int count = 10;
        // Base case
        if (root == nullptr)
            return;
    
        // Increase distance between levels
        space += count;
    
        // Process right child first
        print2DUtil(root->rightChild, space);
    
        // Print current node after space
        // count
        std::cout << std::endl;
        for (int i = count; i < space; i++)
            std::cout << " ";
        std::cout << "(" << root->entry.key << "," << root->entry.value << ")" << "\n";
    
        // Process left child
        print2DUtil(root->leftChild, space);
    }
    
    template<typename K, typename V>
    void BinarySearchTree<K, V>::Print2D()
    {
        // Pass initial space count as 0
        print2DUtil(root, 0);
    }
}