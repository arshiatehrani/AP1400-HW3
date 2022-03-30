#include "bst.h"
BST::Node::Node(int _value, Node* _left, Node* _right)
    : value { _value }
    , left { _left }
    , right { _right }
{
    std::cout << "Node constructor!" << std::endl;
}
BST::Node::Node(const Node& node)
    : value { node.value }
    , left { node.left }
    , right { node.right }
{
    std::cout << "Node copy constructor!" << std::endl;
}
BST::Node*& BST::get_root()
{
    return root;
}
void BST::bfs(std::function<void(BST::Node*& node)> func)
{
    // Check if the tree exists:
    if (root == nullptr)
        throw std::underflow_error("Nothing to search!");

    std::queue<Node*> queue;
    queue.push(root);
    // To the end of the tree:
    while (!queue.empty()) {

        // Enqueue the left child:
        if (queue.front()->left != nullptr)
            queue.push(queue.front()->left);

        // Enqueue the right child:
        if (queue.front()->right != nullptr)
            queue.push(queue.front()->right);

        func(queue.front());
        queue.pop();
    }
}
size_t BST::length()
{
    size_t len {};
    // Check if the tree exists:
    if (root == nullptr)
        return len;

    std::queue<Node*> queue;
    queue.push(root);
    len++;
    // To the end of the tree:
    while (!queue.empty()) {

        // Enqueue the left child:
        if (queue.front()->left != nullptr) {
            queue.push(queue.front()->left);
            len++;
        }

        // Enqueue the right child:
        if (queue.front()->right != nullptr) {
            queue.push(queue.front()->right);
            len++;
        }

        queue.pop();
    }
    return len;
}
bool BST::add_node(int _value)
{
    std::queue<Node*> tree;
    BST::Node* node { new BST::Node(_value) };

    if (root == nullptr) {
        std::cout << "1***********" << std::endl;
        root = node;
        return true;
    }

    tree.push(root);
    std::cout << "2***********" << std::endl;
    std::cout << "root: " << tree.front()->value << std::endl;

    while (!tree.empty()) {
        if (tree.front()->value == _value)
            return false;
        std::cout << "3***********" << std::endl;

        if (_value > tree.front()->value) {
            if (tree.front()->right == nullptr) {
                std::cout << "right***********" << std::endl;
                tree.front()->right = node;
                return true;
            } else {
                if (tree.front()->right->value == _value)
                    return false;
            }
            tree.push(tree.front()->right);
        }
        if (_value < tree.front()->value) {
            if (tree.front()->left == nullptr) {
                std::cout << "left***********" << std::endl;
                tree.front()->left = node;
                return true;
            } else {
                if (tree.front()->left->value == _value)
                    return false;
            }
            tree.push(tree.front()->left);
        }
        tree.pop();
    }
    return false;
}
std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{
    os << "Node->    address: " << &node << "    value: " << node.value << "    left child address: " << node.left << "    right child address: " << node.right << std::endl;
    return os;
}