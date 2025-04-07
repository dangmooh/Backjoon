/*
BST 삽입 : O(N log N) 최악의 경우 O(N^2) 최대 N = 10000
*/

#include <iostream>

using namespace std;


struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int value)
{
    if(!root) return new Node(value);

    if(value < root->value)
    {
        root->left = insert(root->left, value);
    }
    else
    {
        root->right = insert(root->right, value);
    }

    return root;
}

void postorder(Node* root)
{
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->value << "\n";
}


int main()
{

    int value;
    Node* root = nullptr;

    while (cin >> value)
    {
        root = insert(root, value);
    }

    postorder(root);
    return 0;
}