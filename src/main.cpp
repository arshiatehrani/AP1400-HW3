#include "bst.h"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char** argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
        std::cout << "Hello Arshia!" << std::endl;
        BST bst {};
        bst.add_node(10);
        bst.add_node(15);
        bst.add_node(20);
        bst.add_node(30);
        bst.add_node(17);
        bst.add_node(6);
        bst.add_node(8);
        bst.add_node(2);
        bst.add_node(1);
        bst.add_node(3);
        bst.add_node(5);
        bst.add_node(4);

        BST::Node** node { bst.find_successor(6) };
        std::cout << "successor 6: " << (*node)->value << std::endl;
        bst.delete_node(6);

        std::cout << "now" << std::endl;
        BST::Node** node1 { bst.find_node(3) };
        std::cout << "node3: " << (*node1)->value << std::endl;
        std::cout << "node3 right: " << (*node1)->right->value << std::endl;
        std::cout << "root's left child: " << bst.get_root()->left->value << std::endl;

        std::cout << "now" << std::endl;
        BST::Node** node2 { bst.find_node(4) };
        std::cout << "node4: " << (*node1)->value << std::endl;
        std::cout << "node4 right: " << (*node2)->right << std::endl;
        std::cout << "node4 left: " << (*node2)->left << std::endl;

        // BST bst2 { bst++ };
        // std::cout << bst << std::endl;
        // std::cout << bst2 << std::endl;

    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret { RUN_ALL_TESTS() };
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}