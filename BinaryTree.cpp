//
// Algorithm Practice - Binary Tree
//
// Author: Mingjie Li (limingjie0719@gmail.com)
// Date  : Mar 11, 2014
//
// Compiled successfully on:
// 1. MinGW g++ 4.8.1
// 2. VS Express 2013
//

#include <iostream>
#include <stack> // inOrderTraverseStack
#include <queue> // breadthTraverseQueue

template<typename T>
class treeNode
{
public:
    treeNode(T t) { key = t; }
    treeNode<T> *left;
    treeNode<T> *right;
    T key;
};

template <typename T>
void visitNode(treeNode<int> *node)
{
    std::cout << node->key << ' ';
}

template <typename T>
void inOrderTraverseRecursive(treeNode<T> *node)
{
    if (node != NULL)
    {
        inOrderTraverseRecursive(node->left);
        visitNode<T>(node);
        inOrderTraverseRecursive(node->right);
    }
}

template <typename T>
void inOrderTraverseStack(treeNode<T> *tree)
{
    std::stack<treeNode<T> *> stack;
    treeNode<T> *current = tree;

    while (true)
    {
        if (current != NULL)
        {
            stack.push(current);
            current = current->left;
        }
        else
        {
            if (!stack.empty())
            {
                current = stack.top();
                stack.pop();

                visitNode<T>(current);

                current = current->right;
            }
            else
            {
                break;
            }
        }
    }
}

template <typename T>
void breadthTraverseQueue(treeNode<T> *tree)
{
    std::queue<treeNode<T> *> queue;
    treeNode<T> *node;

    queue.push(tree);
    while (!queue.empty())
    {
        node = queue.front();
        queue.pop();
        visitNode<T>(node);

        if (node->left != NULL) queue.push(node->left);
        if (node->right != NULL) queue.push(node->right);
    }
}

template <typename T>
treeNode<T> *buildHelper(T key, treeNode<T> *left, treeNode<T> *right)
{
    treeNode<T> *node = new treeNode<T>(key);
    node->left = left;
    node->right = right;

    return node;
}

// Build Tree
//        64
//      /    \
//    32      96
//   /  \    /
//  16  48  80
//     /  \   \
//    40  56  88
//   /          \
//  36          92
treeNode<int> *buildTree()
{
    treeNode<int> *k = buildHelper<int>(92, NULL, NULL);
    treeNode<int> *j = buildHelper<int>(88, NULL, k);
    treeNode<int> *i = buildHelper<int>(80, NULL, j);
    treeNode<int> *h = buildHelper<int>(36, NULL, NULL);
    treeNode<int> *g = buildHelper<int>(56, NULL, NULL);
    treeNode<int> *f = buildHelper<int>(40, h, NULL);
    treeNode<int> *e = buildHelper<int>(48, f, g);
    treeNode<int> *d = buildHelper<int>(16, NULL, NULL);
    treeNode<int> *c = buildHelper<int>(96, i, NULL);
    treeNode<int> *b = buildHelper<int>(32, d, e);
    treeNode<int> *a = buildHelper<int>(64, b, c);

    std::cout << "== Initialize Tree ==\n"
        << "      64\n    /    \\\n  32      96\n /  \\    /\n16  48  80\n"
        << "   /  \\   \\\n  40  56  88\n /          \\\n36          92"
        << std::endl;
    
    return a;
}

int main()
{
    treeNode<int> *tree = buildTree();

    std::cout << "== Traverse Tree In-order Recusively ==\n";
    inOrderTraverseRecursive<int>(tree);
    std::cout << std::endl;

    std::cout << "== Traverse Tree In-order by Stack ==\n";
    inOrderTraverseStack<int>(tree);
    std::cout << std::endl;

    std::cout << "== Traverse Tree Breadth First ==\n";
    breadthTraverseQueue<int>(tree);
    std::cout << std::endl;

    std::cout << "Press any key to exit." << std::endl;
    std::cin.get();

    return 0;
}
