#ifndef BST_H
#define BST_H
#include <compare>
#include <functional>
#include <iostream>
#include <queue>
class BST {

public:
    class Node;
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

private:
    Node* root;
};
class BST::Node {
public:
    // Constructors:
    Node(int value, Node* left = nullptr, Node* right = nullptr);
    Node() = default;

    // Copy Constructors:
    Node(const Node& node);

    // Inequality functions with int:
    std::partial_ordering operator<=>(const int& _value) const { return value <=> _value; }
    bool operator==(const int& _value) const { return value == _value; }

    // Public member variables:
    int value;
    Node* left;
    Node* right;
};
std::ostream& operator<<(std::ostream& os, const BST::Node& node);
#endif // BST_H