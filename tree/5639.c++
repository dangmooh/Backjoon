<<<<<<< HEAD
/*
BST 삽입 : O(N log N) 최악의 경우 O(N^2) 최대 N = 10000
*/

=======
>>>>>>> 80171284c865a0d10641cf2fa91a6e1b1da7b549
#include <iostream>

using namespace std;

<<<<<<< HEAD

struct Node {
=======
struct Node{
>>>>>>> 80171284c865a0d10641cf2fa91a6e1b1da7b549
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
<<<<<<< HEAD
        root->left = insert(root->left, value);
    }
    else
    {
        root->right = insert(root->right, value);
=======
        root->left = insert(root, value);
    }
    else
    {
        root->right = insert(root, value);
>>>>>>> 80171284c865a0d10641cf2fa91a6e1b1da7b549
    }

    return root;
}

void postorder(Node* root)
{
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
<<<<<<< HEAD
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
=======
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

>>>>>>> 80171284c865a0d10641cf2fa91a6e1b1da7b549
    return 0;
}