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
    std::cout << "BST copy constructor" << std::endl;
    std::queue<BST::Node*> queue;
    bst.bfs([&queue](BST::Node*& node) { queue.push(node); });
    while (!queue.empty()) {
        this->add_node(queue.front()->value);
        std::cout << ")))))))))))))))" << std::endl;
        queue.pop();
    }
    // *root = *bst.root;
}
BST::BST(BST&& bst)
    : root { bst.get_root() }
{
    std::cout << "BST move constructor" << std::endl;
    bst.root = nullptr;
}
// BST::BST()
//     : root { nullptr }
// {
//     std::cout << "default constructor" << std::endl;
// }
BST::~BST()
{
    std::cout << "BST destructor" << std::endl;
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
    std::cout << "***" << std::endl;
    // Check if the tree exists:
    if (root == nullptr)
        // throw std::underflow_error("Nothing to search!");
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
std::ostream& operator<<(std::ostream& os, BST& bst)
{
    os << "********************************************************************************" << std::endl;
    // Check if the tree exists:
    if (bst.get_root() == nullptr)
        throw std::underflow_error("Nothing to show!");

    std::queue<BST::Node*> queue;
    queue.push(bst.get_root());
    // To the end of the tree:
    while (!queue.empty()) {
        os.width(80);
        os << std::left << std::setw(16) << queue.front() << "=> Value:" << queue.front()->value << std::right << std::setw(20) << "left:" << queue.front()->left << std::setw(13) << "Right:" << queue.front()->right << std::endl;

        // Enqueue the left child:
        if (queue.front()->left != nullptr)
            queue.push(queue.front()->left);

        // Enqueue the right child:
        if (queue.front()->right != nullptr)
            queue.push(queue.front()->right);

        queue.pop();
    }
    os << "binary search tree size: " << bst.length() << std::endl;
    os << "********************************************************************************" << std::endl;
    return os;
}
BST::Node** BST::find_node(int _value)
{
    BST::Node* node_ptr { root };
    std::cout << node_ptr->value << ", " << root->value << std::endl;
    while (true) {
        std::cout << "test-1 --------- *****************" << std::endl;
        if (_value == node_ptr->value) {
            std::cout << "test-1-== --------- *****************" << std::endl;
            std::cout << node_ptr->value << std::endl;
            // BST::Node** ptr_ret = new Node*(node_ptr);
            // return ptr_ret;
            break;
        }
        if (_value > node_ptr->value) {
            std::cout << "test-1-right --------- *****************" << std::endl;
            if (node_ptr->right != nullptr) {
                // node_ptr = nullptr;
                node_ptr = node_ptr->right;
                // break;
            } else {
                return nullptr;
            }
        }
        if (_value < node_ptr->value) {
            std::cout << "test-1-left --------- *****************" << std::endl;
            if (node_ptr->left != nullptr) {
                // node_ptr = nullptr;
                node_ptr = node_ptr->left;
                // break;
            } else {
                std::cout << "test-1-left-else --------- *****************" << std::endl;
                return nullptr;
            }
        }
    }
    BST::Node** ptr_ret { new BST::Node*(node_ptr) };
    return ptr_ret;
}
BST::Node** BST::find_parrent(int _value)
{
    BST::Node* node_ptr { root };
    std::cout << node_ptr->value << ", " << root->value << std::endl;
    while (true) {
        std::cout << "test-1 --------- *****************" << std::endl;
        if (_value == node_ptr->value) {
            std::cout << "test-1-== --------- *****************" << std::endl;
            std::cout << node_ptr->value << std::endl;
            // BST::Node** ptr_ret = new Node*(node_ptr);
            // return ptr_ret;
            break;
        }
        if (_value > node_ptr->value) {
            std::cout << "test-1-right --------- *****************" << std::endl;
            if (node_ptr->right != nullptr) {
                if (_value == node_ptr->right->value)
                    break;
                // node_ptr = nullptr;
                node_ptr = node_ptr->right;
                // break;
            } else {
                return nullptr;
            }
        }
        if (_value < node_ptr->value) {
            std::cout << "test-1-left --------- *****************" << std::endl;
            if (node_ptr->left != nullptr) {
                if (_value == node_ptr->left->value)
                    break;
                // node_ptr = nullptr;
                node_ptr = node_ptr->left;
                // break;
            } else {
                std::cout << "test-1-left-else --------- *****************" << std::endl;
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
    std::cout << node_ptr->value << ", " << root->value << std::endl;
    bool flag { false };
    while (true) {
        std::cout << "test-1 --------- *****************" << std::endl;
        if (flag) {
            if (node_ptr->left == nullptr)
                break;
            else {
                node_ptr = node_ptr->left;
            }
            if (node_ptr->right == nullptr)
                break;
            else {
                while (node_ptr->right != nullptr) {
                    node_ptr = node_ptr->right;
                }
            }
        }
        if (_value == node_ptr->value && flag == false) {
            std::cout << "test-1-== --------- *****************" << std::endl;
            std::cout << node_ptr->value << std::endl;
            // BST::Node** ptr_ret = new Node*(node_ptr);
            // return ptr_ret;
            flag = true;
            // break;
        }
        if (_value > node_ptr->value && flag == false) {
            std::cout << "test-1-right --------- *****************" << std::endl;
            if (node_ptr->right != nullptr) {
                // node_ptr = nullptr;
                node_ptr = node_ptr->right;
                // break;
            } else {
                return nullptr;
            }
        }
        if (_value < node_ptr->value && flag == false) {
            std::cout << "test-1-left --------- *****************" << std::endl;
            if (node_ptr->left != nullptr) {
                // node_ptr = nullptr;
                node_ptr = node_ptr->left;
                // break;
            } else {
                std::cout << "test-1-left-else --------- *****************" << std::endl;
                return nullptr;
            }
        }
    }
    BST::Node** ptr_ret { new BST::Node*(node_ptr) };
    return ptr_ret;
}
bool BST::delete_node(int _value)
{
    BST::Node* node_ptr { root };
    std::cout << node_ptr->value << ", " << root->value << std::endl;
    bool flag { false };
    size_t num_child {};
    while (true) {
        std::cout << "test-1 --------- *****************" << std::endl;
        if (flag) {
            BST::Node** node_ptr_parent { new BST::Node*(*(this->find_parrent(node_ptr->value))) };
            // std::cout << "Parent value" << (*node_ptr_parent)->value << std::endl;
            if (node_ptr->right == nullptr && node_ptr->left == nullptr) {
                std::cout << "**********Leaf**********" << std::endl;
                if ((*node_ptr_parent)->right == node_ptr)
                    (*node_ptr_parent)->right = nullptr;
                // break;
                if ((*node_ptr_parent)->left == node_ptr)
                    (*node_ptr_parent)->left = nullptr;
                // break;
                // node_ptr = nullptr;
                delete node_ptr;
                return true;
            }
            if (node_ptr->right != nullptr && node_ptr->left == nullptr) {
                std::cout << "**********right**********" << std::endl;
                if ((*node_ptr_parent)->right == node_ptr)
                    (*node_ptr_parent)->right = node_ptr->right;
                // break;
                if ((*node_ptr_parent)->left == node_ptr)
                    (*node_ptr_parent)->left = node_ptr->right;
                // (*node_ptr_parent)->right = node_ptr->right;
                // node_ptr = nullptr;
                return true;
            }
            if (node_ptr->right == nullptr && node_ptr->left != nullptr) {
                std::cout << "**********left**********" << std::endl;
                if ((*node_ptr_parent)->right == node_ptr)
                    (*node_ptr_parent)->right = node_ptr->left;
                // break;
                if ((*node_ptr_parent)->left == node_ptr)
                    (*node_ptr_parent)->left = node_ptr->left;
                // (*node_ptr_parent)->left = node_ptr->left;
                // node_ptr = nullptr;
                return true;
            }
            if (node_ptr->right != nullptr && node_ptr->left != nullptr) {
                std::cout << "**********2 child**********" << std::endl;
                BST::Node** node_ptr_successor { new BST::Node*(*(this->find_successor(node_ptr->value))) };
                BST::Node** node_ptr_successor_parent { new BST::Node*(*(this->find_parrent((*node_ptr_successor)->value))) };
                bool root_check { true };
                if ((*node_ptr_parent)->right == node_ptr) {
                    std::cout << "node is right side of its parent" << std::endl;
                    root_check = false;
                    (*node_ptr_parent)->right->value = (*node_ptr_successor)->value;
                }
                // break;
                if ((*node_ptr_parent)->left == node_ptr) {
                    std::cout << "node is left side of its parent" << std::endl;
                    root_check = false;
                    (*node_ptr_parent)->left->value = (*node_ptr_successor)->value;
                }
                if (root_check == true) {
                    std::cout << "node is the root" << std::endl;
                    root->value = (*node_ptr_successor)->value;
                }

                if ((*node_ptr_successor_parent)->right == *node_ptr_successor) {
                    std::cout << "node_successor is right side of its parent" << std::endl;
                    std::cout << (*node_ptr_successor)->value << std::endl;
                    (*node_ptr_successor_parent)->right = nullptr;
                }
                // break;
                if ((*node_ptr_successor_parent)->left == *node_ptr_successor) {
                    std::cout << "node_successor is left side of its parent" << std::endl;
                    (*node_ptr_successor_parent)->left = nullptr;
                }
                // node_ptr->value = (*node_ptr_successor)->value;
                delete node_ptr_successor;
                // node_ptr_successor = nullptr;
                return true;
            }
        }
        if (_value == node_ptr->value && flag == false) {
            std::cout << "test-1-== --------- *****************" << std::endl;
            std::cout << node_ptr->value << std::endl;
            // BST::Node** ptr_ret = new Node*(node_ptr);
            // return ptr_ret;
            flag = true;
            // break;
        }
        if (_value > node_ptr->value && flag == false) {
            std::cout << "test-1-right --------- *****************" << std::endl;
            if (node_ptr->right != nullptr) {
                // node_ptr = nullptr;
                node_ptr = node_ptr->right;
                // break;
            } else {
                return false;
            }
        }
        if (_value < node_ptr->value && flag == false) {
            std::cout << "test-1-left --------- *****************" << std::endl;
            if (node_ptr->left != nullptr) {
                // node_ptr = nullptr;
                node_ptr = node_ptr->left;
                // break;
            } else {
                std::cout << "test-1-left-else --------- *****************" << std::endl;
                return false;
            }
        }
    }
    // node_ptr = nullptr;
    // return true;
    BST::Node** ptr_ret { new BST::Node*(node_ptr) };
    return true;
}
const BST& BST::operator++() const
{
    std::cout << "Operator ++ left" << std::endl;
    // Check if the tree exists:
    if (root == nullptr)
        return *this;

    std::queue<Node*> queue;
    root->value++;
    queue.push(root);
    // To the end of the tree:
    while (!queue.empty()) {

        // Enqueue the left child:
        if (queue.front()->left != nullptr) {
            queue.front()->left->value++;
            queue.push(queue.front()->left);
        }

        // Enqueue the right child:
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
    std::cout << "Operator ++ right" << std::endl;
    BST _bst { *this };
    ++*this;
    return _bst;
}
BST& BST::operator=(const BST& bst)
{
    std::cout << this->length() << std::endl;
    std::cout << bst.length() << std::endl;
    std::cout << "BST operator = copy version" << std::endl;
    if (this == &bst)
        return *this;
    std::cout << this->root->value << std::endl;
    // std::cout << bst.root << std::endl;
    delete root;
    std::cout << this->root->value << std::endl;
    // std::cout << this->get_root() << std::endl;
    root = nullptr;
    // std::cout << this->root->value << std::endl;
    std::queue<BST::Node*> queue;
    bst.bfs([&queue](BST::Node*& node) { queue.push(node); });
    while (!queue.empty()) {
        this->add_node(queue.front()->value);
        std::cout << "(((((((((((((((((((((" << std::endl;
        queue.pop();
    }
    std::cout << this->root->value << std::endl;
    return *this;
}
BST& BST::operator=(BST&& bst)
{
    std::cout << "BST operator = move version" << std::endl;
    root = bst.root;
    bst.root = nullptr;
    return *this;
}