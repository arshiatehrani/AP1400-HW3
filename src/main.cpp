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
        std::cout << bst.get_root() << std::endl;
        bst.add_node(25);
        bst.add_node(10);
        bst.add_node(50);
        bst.add_node(65);
        bst.add_node(5);
        bst.add_node(20);
        bst.add_node(22);
        BST bst2 { bst++ };
        std::cout << bst << std::endl;
        std::cout << bst2 << std::endl;

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