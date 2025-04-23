#include <bits/stdc++.h>
using namespace std;

struct Node {
  int data;
  Node *left, *right;
  Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

// Preorder: Root, Left, Right
void preorder(Node *root) {
  if (!root)
    return;
  cout << root->data << " ";
  preorder(root->left);
  preorder(root->right);
}

// Inorder: Left, Root, Right
void inorder(Node *root) {
  if (!root)
    return;
  inorder(root->left);
  cout << root->data << " ";
  inorder(root->right);
}

// Postorder: Left, Right, Root
void postorder(Node *root) {
  if (!root)
    return;
  postorder(root->left);
  postorder(root->right);
  cout << root->data << " ";
}

int main() {
  // Example tree
  Node *root = new Node(1);
  root->left = new Node(2);
  root->right = new Node(3);
  root->left->left = new Node(4);
  root->left->right = new Node(5);

  cout << "Preorder: ";
  preorder(root); // 1 2 4 5 3
  cout << "\nInorder: ";
  inorder(root); // 4 2 5 1 3
  cout << "\nPostorder: ";
  postorder(root); // 4 5 2 3 1
  return 0;
}
