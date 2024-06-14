#pragma once
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

class BST
{
public:
    class Node
    {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);

    public:
        int value = 0;
        ;
        Node* left  = nullptr;
        Node* right = nullptr;
    };
    BST() = default;
    BST(std::initializer_list<int> list);
    BST(const BST& other);
    BST(BST&& other) noexcept;
    void operator=(const BST& other);
    void operator=(BST&& other);

    BST& operator++();
    BST  operator++(int);
    ~BST();

public:
    Node*&      get_root();
    void        bfs(std::function<void(Node*& node)> func);
    void        bfs(std::function<void(Node*& node)> func) const;
    std::size_t length();
    std::size_t length() const;
    bool        add_node(int value);
    Node**      find_node(int value);
    Node**      find_parrent(int value);
    Node**      find_successor(int value);
    bool        delete_node(int value);
    int         get_depth() const;

private:
    std::size_t get_node_length(Node* node);
    std::size_t get_node_length(const Node* node) const;
    // for delete_node
    void rebuild_tree(Node* node, std::vector<int>& values);

private:
    Node* root;
};

static bool operator==(int value, const BST::Node& node) { return node.value == value; }

static bool operator!=(int value, const BST::Node& node) { return node.value != value; }

static bool operator<(int value, const BST::Node& node) { return value < node.value; }

static bool operator<=(int value, const BST::Node& node) { return value <= node.value; }

static bool operator>(int value, const BST::Node& node) { return value > node.value; }

static bool operator>=(int value, const BST::Node& node) { return value >= node.value; }

static bool operator==(const BST::Node& node, int value) { return node.value == value; }

static bool operator!=(const BST::Node& node, int value) { return node.value != value; }

static bool operator>(const BST::Node& node, int value) { return node.value > value; }

static bool operator>=(const BST::Node& node, int value) { return node.value >= value; }

static bool operator<(const BST::Node& node, int value) { return node.value < value; }

static bool operator<=(const BST::Node& node, int value) { return node.value <= value; }

static std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{

    os << std::ios::hex << &node << "   =>";
    os << node.value << "      ";
    os << "left: " << std::ios::hex << node.left << std::ios::right << "     ";
    os << "right: " << std::ios::hex << node.right << std::endl;
    return os;
}

static std::ostream& operator<<(std::ostream& os, const BST& bst)
{

    std::vector<int> values;
    bst.bfs([&values, &os](BST::Node*& node) { os << (*node); });

    os << "bst tree length is " << bst.length() << std::endl;
    return os;
}