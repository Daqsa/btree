#include "binary_search_tree.hpp"
#include <iostream>

using namespace Tree;

void testBST() {
    BinarySearchTree<int, int> tree;

    Entry<int, int> n1 = {1, 1};
    Entry<int, int> n2 = {2, 2};
    Entry<int, int> n3 = {3, 3};
    Entry<int, int> n4 = {4, 4};
    Entry<int, int> n5 = {5, 5};
    Entry<int, int> n6 = {6, 6};
    Entry<int, int> n7 = {7, 7};
    tree.Insert(n4);
    tree.Insert(n2);
    tree.Insert(n3);
    tree.Insert(n1);
    tree.Insert(n5);
    tree.Insert(n6);
    tree.Insert(n7);


    int x { 0 };
    int& val = x;
    if (tree.Lookup(6, val)) {
        std::cout << val << std::endl;
    }

    Entry<int, int> n7_2 = {7, 70};
    tree.Update(n7_2);

    tree.Delete(2);
    tree.Delete(6);
    tree.Delete(7);
    tree.Delete(4);

    tree.Print2D();
}

int main() {
    testBST();
}