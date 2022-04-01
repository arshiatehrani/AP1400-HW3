#ifndef BST_H
#define BST_H

#include <compare>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

class BST {
public:
    class Node;

    // Constructors and the destructor
    BST(std::initializer_list<int>); // constructor
    BST() = default; // default constructor
    BST(const BST& bst); // copy constructor
    BST(BST&& bst); // move constructor
    ~BST(); // destructor

    // Methods
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    friend std::ostream& operator<<(std::ostream& os, BST& bst);

    // Operators
    const BST& operator++() const;
    const BST operator++(int) const;
    BST& operator=(const BST& bst); // BST operator = copy version
    BST& operator=(BST&& bst); // BST operator = move version

private:
    Node* root;
};

class BST::Node {
public:
    // Constructors:
    Node(int value, Node* left = nullptr, Node* right = nullptr); // Constructor
    Node() = default; // default constructor
    Node(const Node& node); // copy constructor

    // Operators:
    std::partial_ordering operator<=>(const int& _value) const { return value <=> _value; }
    bool operator==(const int& _value) const { return value == _value; }
    // Node& operator=(const Node& node); // Node operator = copy version
    // Node& operator=(Node&& node); // Node operator = move version

    friend std::ostream& operator<<(std::ostream& os, const BST::Node& node);

    // Public member variables:
    int value;
    Node* left;
    Node* right;
};

#endif // BST_H