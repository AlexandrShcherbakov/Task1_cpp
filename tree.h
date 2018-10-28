#pragma once

#include <memory>

namespace bintree {
    template <typename T>
    struct TNode {
        using TNodePtr = std::shared_ptr<TNode<T>>;
        using TNodeConstPtr = std::shared_ptr<const TNode<T>>;
        // Types for pointer to parent node.
        using TNodeParentPtr = TNode<T>*; 
        using TNodeParentConstPtr = const TNode<T>*;

        bool hasLeft() const {
            return bool(left);
        }

        bool hasRight() const {
            return bool(right);
        }

        bool hasParent() const {
            return bool(parent);
        }

        T& getValue() {
            return value;
        }

        const T& getValue() const {
            return value;
        }

        TNodePtr getLeft() {
            return left;
        }

        TNodeConstPtr getLeft() const {
            return left;
        }

        TNodePtr getRight() {
            return right;
        }

        TNodeConstPtr getRight() const {
            return right;
        }

        TNodeParentPtr getParent() {
            return parent;
        }

        TNodeParentConstPtr getParent() const {
            return parent;
        }

        static TNodePtr createLeaf(T v) {
            return std::shared_ptr<TNode>(new TNode(v)); // Create node in class and put raw pointer to shared_ptr constructor
        }

        static TNodePtr fork(T v, TNodePtr left, TNodePtr right) {
            TNodePtr ptr = std::shared_ptr<TNode>(new TNode(v, left, right)); // Create node in class and put raw pointer to shared_ptr constructor
            setParent(ptr->getLeft(), ptr);
            setParent(ptr->getRight(), ptr);
            return ptr;
        }

        TNodePtr replaceLeft(TNodePtr l) {
            setParent(l, this);
            setParent(left, nullptr);
            std::swap(l, left);
            return l;
        }

        TNodePtr replaceRight(TNodePtr r) {
            setParent(r, this);
            setParent(right, nullptr);
            std::swap(r, right);
            return r;
        }

        TNodePtr replaceRightWithLeaf(T v) {
            return replaceRight(createLeaf(v));
        }

        TNodePtr replaceLeftWithLeaf(T v) {
            return replaceLeft(createLeaf(v));
        }

        TNodePtr removeLeft() {
            return replaceLeft(nullptr);
        }
        TNodePtr removeRight() {
            return replaceRight(nullptr);
        }

    private:
        T value;
        TNodePtr left = nullptr;
        TNodePtr right = nullptr;
        TNodeParentPtr parent; // Save parent as raw pointer

        TNode(T v)
            : value(v)
        {
        }
        TNode(T v, TNodePtr left, TNodePtr right)
            : value(v)
            , left(left)
            , right(right)
        {
        }

        static void setParent(TNodePtr node, TNodePtr parent) {
            if (node)
                node->parent = parent.get();
        }

        static void setParent(TNodePtr node, TNodeParentPtr parent) {
            if (node)
                node->parent = parent;
        }
    };
}
