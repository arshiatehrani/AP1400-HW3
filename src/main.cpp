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
        bst.add_node(20);
        bst.add_node(5);
        EXPECT_EQ(bst.get_root()->value, 10);
        std::cout << "root: " << bst.get_root()->value << std::endl;
        EXPECT_EQ(bst.get_root()->left->value, 5);
        EXPECT_EQ(bst.get_root()->right->value, 20);
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