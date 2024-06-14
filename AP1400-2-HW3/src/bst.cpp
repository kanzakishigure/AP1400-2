#include "bst.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

BST::Node::Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}

BST::Node::Node() : value(0), left(nullptr), right(nullptr) {}

BST::Node::Node(const Node& node) : value(node.value), left(node.left), right(node.right) {}

BST::BST(std::initializer_list<int> list)
:root(nullptr)
{
    
    for(auto value : list)
    {
        add_node(value);
    }
}
BST::BST(const BST& other) 
:root(nullptr)
{
    root  = nullptr;
    std::vector<int> values;
    other.bfs([&values](BST::Node*& node){values.push_back(node->value);});
    for(auto value : values)
    {
        add_node(value);
        std::cout<< value <<" ";
    }
    std::cout<<std::endl;
}
BST::BST(BST&& other) noexcept
{
    root = std::move(other.root);
    other.root = nullptr;
    
    
}
BST::~BST()
{
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
    for (auto& node : nodes)
        delete node;
}
void BST::operator=(const BST& other)
{
    std::vector<int> values;
    other.bfs([&values](BST::Node*& node){values.push_back(node->value);});
    for(auto value : values)
    {
        add_node(value);
    }
}
void BST::operator=(BST&& other)
{
    root = std::move(other.root);
    other.root = nullptr;
}

BST& BST::operator++()
{
    bfs([](BST::Node*& node){node->value++;});
    return *this;
}
BST BST::operator++(int)
{
    BST ret = *this;
    bfs([](BST::Node*& node){node->value++;});
    return ret;
}
BST::Node*& BST::get_root() { return this->root; }

std::size_t BST::length() { return get_node_length(root); }
std::size_t BST::length() const 
{
    Node* croot = root;
    return get_node_length(croot); 
}

std::size_t BST::get_node_length(Node* node)
{
    const Node* cnode = node;
    return get_node_length(cnode);
}
std::size_t BST::get_node_length(const Node* node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    int length = 1;
    if (node->left != nullptr)
    {
        length += get_node_length(node->left);
    }
    if (node->right != nullptr)
    {
        length += get_node_length(node->right);
    }
    return length;
}
bool BST::add_node(int value)
{
    if (root == nullptr)
    {
        root = new Node(value, nullptr, nullptr);
        return true;
    }
    Node* node = root;
    while (true)
    {
        if ((*node) == value)
        {
            return false;
        }
        if ((*node) > value)
        {
            if (node->left == nullptr)
            {
                node->left = new Node(value, nullptr, nullptr);
                return true;
            }
            node = node->left;
            continue;
        }
        if ((*node) < value)
        {
            if (node->right == nullptr)
            {
                node->right = new Node(value, nullptr, nullptr);
                return true;
            }
            node = node->right;
            continue;
        }
    }
    return false;
}
// what a crazy Node**?
BST::Node** BST::find_node(int value)
{

    std::function<Node**(Node*)> funcit = [&](Node* node) -> Node** {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->value == value)
        {
            Node** res = new Node*(node);
            return res;
        }
        if (node->right != nullptr && value > node->value)
        {
            return funcit(node->right);
        }
        if (node->left != nullptr && value < node->value)
        {
            return funcit(node->left);
        }
        return nullptr;
    };
    return funcit(root);
}
BST::Node** BST::find_parrent(int value)
{
    BST::Node** childnode = find_node(value);
    if (childnode != nullptr)
    {
        if (*childnode == get_root())
        {
            return nullptr;
        }
        std::function<Node**(Node*)> funcit = [&](Node* node) -> Node** {
            if (node == nullptr)
            {
                return nullptr;
            }
            Node** res = nullptr;
            if (node->right == *childnode||node->left == *childnode)
            {
                Node** parent = new Node*(node);
                return parent;
            }
            
            if (node->left != nullptr)
            {
                res = funcit(node->left);
                if (res != nullptr)
                {
                    return res;
                }
            }
            if (node->right != nullptr)
            {
                res = funcit(node->right);
                if (res != nullptr)
                {
                    return res;
                }
            }
            return nullptr;
        };
        return funcit(get_root());
    }
    return nullptr;
}

void BST::bfs(std::function<void(Node*& node)> func)
{
    std::function<void(Node*)> bstit = [&](Node* node) {
        if (node == nullptr)
        {
            return;
        }
        func(node);
        if (node->left != nullptr)
        {
            bstit(node->left);
        }
        if (node->right != nullptr)
        {
            bstit(node->right);
        }
        return;
    };
    bstit(get_root());
}
void BST::bfs(std::function<void(Node*& node)> func) const
{
     std::function<void(Node*)> bstit = [&](Node* node) {
        if (node == nullptr)
        {
            return;
        }
        func(node);
        if (node->left != nullptr)
        {
            bstit(node->left);
        }
        if (node->right != nullptr)
        {
            bstit(node->right);
        }
        return;
    };
    bstit(root);
    return;
}
BST::Node** BST::find_successor(int value) 
{ 
    BST::Node** node  = find_node(value);
    if(node==nullptr)
    {
        return nullptr;
    }
    if((*node)->left==nullptr)
    {
        return nullptr;
    }
    std::function<Node**(Node*)> find_successor_reversive = [&](Node* node){
        if(node->right!=nullptr)
        {
            return find_successor_reversive(node->right);
        }
        return new Node*(node);
    };
    
    return find_successor_reversive((*node)->left); 
}


bool        BST::delete_node(int value)
{
    Node** node = find_node(value);
    if (node == nullptr)
    {
        return false;
    }

    Node** parrent = find_parrent(value);
    //check if the node is end node

    if ((*node)->left == nullptr&&(*node)->right == nullptr)
    {
        if (parrent != nullptr)
        {
            if ((*parrent)->left == (*node))
            {
                (*parrent)->left = nullptr;
            }
            else if ((*parrent)->right == (*node))
            {
                (*parrent)->right = nullptr;
            }
        }
        else
        {
            root = nullptr;
        }
        delete (*node);
        return true;
    }
    // check if the node have left
    if ((*node)->left != nullptr&&(*node)->right == nullptr)
    {
        if (parrent != nullptr)
        {
            if ((*parrent)->left == (*node))
            {
                (*parrent)->left = (*node)->left;
            }
            else if ((*parrent)->right == (*node))
            {
                (*parrent)->right = (*node)->left;
            }
        }
        else
        {
            root = (*node)->left;
        }
        delete (*node);
        return true;
    }
    // check if the node have right
    if ((*node)->right != nullptr&&(*node)->left==nullptr)
    {
        if (parrent != nullptr)
        {
            if ((*parrent)->left == (*node))
            {
                (*parrent)->left = (*node)->right;
            }
            else if ((*parrent)->right == (*node))
            {
                (*parrent)->right = (*node)->right;
            }
        }
        else
        {
            root = (*node)->right;
        }
        delete (*node);
        return true;
    }
    // if the node is have left and right ,rebuild bst
    if((*node)->right != nullptr&&(*node)->left!=nullptr)
    {

        Node** successor = find_successor((*node)->value);
        Node** successor_parrent = find_parrent((*successor)->value);
        if((*successor_parrent)->left==(*successor))
        {
            (*successor_parrent)->left = nullptr;
        }
        if((*successor_parrent)->right==(*successor))
        {
            (*successor_parrent)->right = nullptr;
        }
        (*successor)->right = (*node)->right;
        if((*node)->left==(*successor))
        {
            (*successor)->left = nullptr;
        }
        else
        {
            (*successor)->left = (*node)->left;
        }
        
        if (parrent != nullptr)
        {
            if ((*parrent)->left == (*node))
            {
                (*parrent)->left = (*successor);
            }
            else if ((*parrent)->right == (*node))
            {
                (*parrent)->right = (*successor);
            }
        } 
        else
        {
            root = (*successor);
        }  
        
        delete (*node);
        return true;
    }
    
    return false;
}

void BST::rebuild_tree(Node* node,std::vector<int>& values)
{
    if(node!=nullptr)
    {
        values.push_back(node->value);
    }
    if(node->left!=nullptr)
    {
        rebuild_tree(node->left,values);
    }
    if(node->right!=nullptr)
    {
        rebuild_tree(node->right, values);
    }
    delete  node;
}
int BST::get_depth() const
{
    std::function<int(Node*,int)> get_depth_func = [&](Node* node ,int deep) {
        
        if(node->left==nullptr&&node->right==nullptr)
        {
            return deep;
        }
        int maxd = 0;
        if (node->left != nullptr)
        {
          maxd = std::max(maxd,get_depth_func(node->left,deep +1)) ;
        }
        if (node->right != nullptr)
        {
            maxd = std::max(maxd,get_depth_func(node->right,deep +1)) ;
        }
        
        return maxd;
    };
    return get_depth_func(root,0);
}
