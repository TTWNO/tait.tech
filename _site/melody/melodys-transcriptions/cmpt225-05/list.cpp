#include <utility> // not in original, needed for compilation

template <typename Object>
class List
{
  private:
    // the basic doubly linked list node
    // Nested inside a list, can be public
    // because the node itself is private
    struct Node
    {
      Object data; // (annotation: list element)
      Node *prev; // (annotation: pointer to next node)
      Node *next; // (annotation: pointer to previous node)

      Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr)
        : data{d}, prev{p}, next{n} {}

      Node(Object&& d, Node* p = nullptr, Node* n = nullptr)
        : data{std::move(d)}, prev{p}, next{n} {}
    };
}; // not in original, needed for compilation
