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
std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{
    os << "Node->    address: " << &node << "    value: " << node.value << "    left child address: " << node.left << "    right child address: " << node.right << std::endl;
    return os;
}
BST::Node*& BST::get_root()
{
    return root;
}
void BST::bfs(std::function<void(BST::Node*& node)> func)
{
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
