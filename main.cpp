#include "tree.h"
#include <cassert>
using bintree::TNode;

int main() {
    auto node = TNode<int>::createLeaf(1);

    assert(!node->getLeft());
    assert(!node->getRight());
    assert(node->getParent() == nullptr);

    const auto node2 = node;
    assert(!node2->getLeft());
    assert(!node2->getRight());

    node->replaceLeftWithLeaf(5);

    assert(node->getLeft()->getValue() == 5);
    assert(node->getLeft()->getParent() == node.get()); // Compare raw pointers instead of shared.

    node->replaceRightWithLeaf(518);

    assert(node->getLeft()->getValue() == 5);
    assert(node->getLeft()->getParent() == node.get());
    assert(node->getRight()->getValue() == 518);
    assert(node->getRight()->getParent() == node.get());

    auto leaf = TNode<int>::createLeaf(4);
    auto node3 = TNode<int>::fork(0, node, leaf); // Set child nodes ad shared pointers.

    assert(node3->getValue() == 0);
    assert(node3->getLeft()->getValue() == 1);
    assert(node3->getLeft()->getLeft()->getValue() == 5);
    assert(node3->getLeft()->getRight()->getValue() == 518);
    assert(node3->getRight()->getValue() == 4);

    assert(node3->getLeft()->getParent() == node3.get());
}
