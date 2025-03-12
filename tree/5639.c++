#include <iostream>

using namespace std;

struct Node{
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
        root->left = insert(root, value);
    }
    else
    {
        root->right = insert(root, value);
    }

    return root;
}

void postorder(Node* root)
{
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->value << '\n'; 
}

int main()
{

    int nodeIdx;
    Node* tree = nullptr;

    while(cin >> nodeIdx)
    {
        tree = insert(tree, nodeIdx);
    }

    postorder(tree);

    return 0;
}