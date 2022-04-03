#include "bst.h"

BST::Node::Node(int _value, Node* _left, Node* _right)
    : value { _value }
    , left { _left }
    , right { _right }
{
}

BST::Node::Node(const Node& node)
    : value { node.value }
    , left { node.left }
    , right { node.right }
{
}

// BST::Node& BST::Node::operator=(const Node& node)
// {
//     node.left;
//     std::cout << "Node operator = copy version" << std::endl;
//     if (this == &node)
//         return *this;
//     value = node.value;
//     delete left, right;
//     left = new BST::Node(*node.left);
//     right = new BST::Node(*node.right);
//     return *this;
// }

// BST::Node& BST::Node::operator=(Node&& node)
// {
//     std::cout << "Node operator = move version" << std::endl;
//     value = node.value;
//     left = node.left;
//     right = node.right;
//     node.left = nullptr;
//     node.right = nullptr;
//     return *this;
// }

BST::BST(std::initializer_list<int> node)
    : root { nullptr }
{
    for (const int* node_iterator_ptr { node.begin() }; node_iterator_ptr != node.end(); node_iterator_ptr++)
        this->add_node(*node_iterator_ptr);
}

BST::BST(const BST& bst)
    : root { nullptr }
{
    std::queue<BST::Node*> queue;
    bst.bfs([&queue](BST::Node*& node) { queue.push(node); });

    while (!queue.empty()) {
        this->add_node(queue.front()->value);
        queue.pop();
    }
}

BST::BST(BST&& bst)
    : root { bst.get_root() }
{
    bst.root = nullptr;
}

BST::~BST()
{
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });

    for (auto& node : nodes)
        delete node;
}

BST::Node*& BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(BST::Node*& node)> func) const
{
    // Check if the tree exists:
    if (root == nullptr)
        return;

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

size_t BST::length() const
{
    size_t len {};
    this->bfs([&len](BST::Node*& node) { len++; });
    return len;
}

bool BST::add_node(int _value)
{
    std::queue<Node*> tree;
    BST::Node* node { new BST::Node(_value) };

    if (root == nullptr) {
        root = node;
        return true;
    }

    tree.push(root);

    while (!tree.empty()) {

        if (tree.front()->value == _value)
            return false;

        if (_value > tree.front()->value) {
            if (tree.front()->right == nullptr) {
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
    os << &node << "\t=> value:" << node.value << "\t   ";
    os << "left:" << std::left;
    os.width(12);
    os << node.left << std::right;
    os.width(12);
    os << "right:" << std::left;
    os << node.right;

    return os;
}

std::ostream& operator<<(std::ostream& os, BST& bst)
{
    os << std::string(80, '*') << std::endl;
    std::queue<BST::Node*> nodes;

    // Using lambda function
    bst.bfs([&nodes](BST::Node*& node) { nodes.push(node); });

    while (!nodes.empty()) {
        os << *nodes.front() << std::endl;
        nodes.pop();
    }
    os << "Binary Search tree size: " << bst.length() << std::endl;
    os << std::string(80, '*') << std::endl;

    return os;
}

BST::Node** BST::find_node(int _value)
{
    BST::Node* node_ptr { root };

    while (true) {

        if (_value == node_ptr->value)
            break;

        if (_value > node_ptr->value) {
            if (node_ptr->right != nullptr)
                node_ptr = node_ptr->right;
            else
                return nullptr;
        }

        if (_value < node_ptr->value) {
            if (node_ptr->left != nullptr)
                node_ptr = node_ptr->left;
            else
                return nullptr;
        }
    }
    BST::Node** ptr_ret { new BST::Node*(node_ptr) };
    return ptr_ret;
}

BST::Node** BST::find_parrent(int _value)
{
    BST::Node* node_ptr { root };

    while (true) {

        if (_value == node_ptr->value)
            break;

        if (_value > node_ptr->value) {
            if (node_ptr->right != nullptr) {
                if (_value == node_ptr->right->value)
                    break;

                node_ptr = node_ptr->right;
            } else {
                return nullptr;
            }
        }

        if (_value < node_ptr->value) {
            if (node_ptr->left != nullptr) {
                if (_value == node_ptr->left->value)
                    break;
                node_ptr = node_ptr->left;
            } else {
                return nullptr;
            }
        }
    }
    BST::Node** ptr_ret { new BST::Node*(node_ptr) };
    return ptr_ret;
}

BST::Node** BST::find_successor(int _value)
{
    BST::Node* node_ptr { root };
    bool flag { false };

    while (true) {

        if (flag) {

            if (node_ptr->left == nullptr)
                break;
            else
                node_ptr = node_ptr->left;

            if (node_ptr->right == nullptr)
                break;
            else {
                while (node_ptr->right != nullptr)
                    node_ptr = node_ptr->right;
            }
        }

        if (_value == node_ptr->value && flag == false)
            flag = true;

        if (_value > node_ptr->value && flag == false) {
            if (node_ptr->right != nullptr)
                node_ptr = node_ptr->right;
            else
                return nullptr;
        }

        if (_value < node_ptr->value && flag == false) {
            if (node_ptr->left != nullptr)
                node_ptr = node_ptr->left;
            else
                return nullptr;
        }
    }
    BST::Node** ptr_ret { new BST::Node*(node_ptr) };
    return ptr_ret;
}

bool BST::delete_node(int _value)
{
    BST::Node* node_ptr { root };
    bool flag { false };
    size_t num_child {};

    while (true) {

        if (flag) {

            BST::Node** node_ptr_parent { new BST::Node*(*(this->find_parrent(node_ptr->value))) };

            // Leaf
            if (node_ptr->right == nullptr && node_ptr->left == nullptr) {

                if ((*node_ptr_parent)->right == node_ptr)
                    (*node_ptr_parent)->right = nullptr;

                if ((*node_ptr_parent)->left == node_ptr)
                    (*node_ptr_parent)->left = nullptr;

                delete node_ptr;
                return true;
            }

            // 1 right child
            if (node_ptr->right != nullptr && node_ptr->left == nullptr) {

                if ((*node_ptr_parent)->right == node_ptr)
                    (*node_ptr_parent)->right = node_ptr->right;

                if ((*node_ptr_parent)->left == node_ptr)
                    (*node_ptr_parent)->left = node_ptr->right;

                return true;
            }

            // 1 left child
            if (node_ptr->right == nullptr && node_ptr->left != nullptr) {

                if ((*node_ptr_parent)->right == node_ptr)
                    (*node_ptr_parent)->right = node_ptr->left;

                if ((*node_ptr_parent)->left == node_ptr)
                    (*node_ptr_parent)->left = node_ptr->left;

                return true;
            }

            // 2 children
            if (node_ptr->right != nullptr && node_ptr->left != nullptr) {

                BST::Node** node_ptr_successor { new BST::Node*(*(this->find_successor(node_ptr->value))) };
                BST::Node** node_ptr_successor_parent { new BST::Node*(*(this->find_parrent((*node_ptr_successor)->value))) };
                bool root_check { true };

                if ((*node_ptr_parent)->right == node_ptr) {
                    root_check = false;
                    (*node_ptr_parent)->right->value = (*node_ptr_successor)->value;
                }

                if ((*node_ptr_parent)->left == node_ptr) {
                    root_check = false;
                    (*node_ptr_parent)->left->value = (*node_ptr_successor)->value;
                }

                // if the node is root
                if (root_check == true)
                    root->value = (*node_ptr_successor)->value;

                if ((*node_ptr_successor_parent)->right == *node_ptr_successor)
                    (*node_ptr_successor_parent)->right = nullptr;

                if ((*node_ptr_successor_parent)->left == *node_ptr_successor)
                    (*node_ptr_successor_parent)->left = nullptr;

                delete node_ptr_successor;
                return true;
            }
        }

        if (_value == node_ptr->value && flag == false)
            flag = true;

        if (_value > node_ptr->value && flag == false) {

            if (node_ptr->right != nullptr)
                node_ptr = node_ptr->right;
            else
                return false;
        }

        if (_value < node_ptr->value && flag == false) {
            if (node_ptr->left != nullptr)
                node_ptr = node_ptr->left;
            else
                return false;
        }
    }
    BST::Node** ptr_ret { new BST::Node*(node_ptr) };
    return true;
}

const BST& BST::operator++() const
{
    // Check if the tree exists:
    if (root == nullptr)
        return *this;

    std::queue<Node*> queue;
    root->value++;
    queue.push(root);

    // To the end of the tree:
    while (!queue.empty()) {

        // The left child:
        if (queue.front()->left != nullptr) {
            queue.front()->left->value++;
            queue.push(queue.front()->left);
        }

        // The right child:
        if (queue.front()->right != nullptr) {
            queue.front()->right->value++;
            queue.push(queue.front()->right);
        }
        queue.pop();
    }
    return *this;
}

const BST BST::operator++(int) const
{
    BST _bst { *this };
    ++*this;
    return _bst;
}

BST& BST::operator=(const BST& bst)
{
    if (this == &bst)
        return *this;

    delete root;
    root = nullptr;

    std::queue<BST::Node*> queue;
    bst.bfs([&queue](BST::Node*& node) { queue.push(node); });

    while (!queue.empty()) {
        this->add_node(queue.front()->value);
        queue.pop();
    }
    return *this;
}

BST& BST::operator=(BST&& bst)
{
    root = bst.root;
    bst.root = nullptr;
    return *this;
}