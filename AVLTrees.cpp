#include<iostream>
using namespace std;
struct Node{
    int data;
    int height;
    Node*left;
    Node*right;
};
//Creating node
Node* CreateNode(int val){
Node*temp =(Node* )malloc(sizeof(Node));
temp->data = val;
temp->height = 1;
temp->left = NULL;
temp->right = NULL;
return temp;
}
//Height of Node
int height (Node*n) {
    if(n==NULL){
        return 0;
    }
    return n->height;
}
//Balance Factor 
int getBalance(Node* n){
    if(n==NULL){
        return 0;
    }
    return height(n->left) - height(n->right); //BF = left - right
}
//To update the height
void UpdateHeight(Node *n){
    if(n==NULL) {
        return;
    }
    int lh = height(n->left);
    int rh = height(n->right);
    n->height = 1 + (lh > rh ? lh : rh); // height = 1 + max(left height, right height)
}
// For LL imbalance 
Node* RightRotate(Node*z){
    // BF > 1 -> Left heavy (LL or LR case)
    Node* a = z->left;
    Node* T3= a->right;
    a->right = z;
    z->left = T3;
    UpdateHeight(z);
    UpdateHeight(T3);
    return a;
}
// For RR imbalance 
Node* LeftRotate(Node*z){
    //BF < -1 -> right heavy (RR or RL case)
    Node*b = z->right;
    Node*T2 = b->left;
    b->left = z;
    z->right = T2;
    UpdateHeight(z);
    UpdateHeight(T2);
    return b;
}
// Now for inserting the values (by recursion method)
Node* insert(Node* node, int val){
    //Simply inserting as BST
    if(node == NULL){
        return CreateNode(val); // Base Case 
    }
    if(val < node->data){
        node->left = insert(node->left, val);
    }
    else if(val > node->data){
        node->right = insert(node->right, val);
    }
    else {
        return node; // do nothing
    }
    // Now for balance and update:
    UpdateHeight(node);
    int bf = getBalance(node);

    // Now For LL Case (BF > 1): 
    // LL case: val < node->left->data, then-> right rotate (the node)
    if (bf > 1 && val < node->left->data ){
        return RightRotate(node);
    }

    // For RR Case (BF < -1):
   // RR case: val > node->right->data, then-> Left rotate (the node)
   if(bf < -1 && val > node->right->data){
    return LeftRotate(node);
   }

   // For LR Case (BF > 1):
   // LR case : val > node->left->data -> left rotate (the left child), then-> right rotate (the current node)
   // Left heavy but new node went right of left child
   if(bf > 1 & val > node->left->data ){
    node-> left = LeftRotate(node->left);
    return RightRotate(node); // current node
   }

   // For RL Case (BF < -1 ):
   // RL case: val < node->right->data -> Right rotate (the right child), then-> left rotate (the current node)
   // Right heavy but the new node went to left of right node
   if(bf < -1 & val < node->right->data){
    node->right = RightRotate(node->right);
    return LeftRotate(node); // current node
   }
   return node;
}
   
   // For inorder successor
   // find the left most node in the right subtree, it is the smallest value that is still greater than the deleted node
   //making it a safe BST replacement
   Node* minValue(Node* node){
    Node* curr = node;
    while (curr->left != NULL){
        curr = curr->left;
    }
    return curr;
   }

   // For Deletation:
   // Step 1: Standard BST delete
   // Step 2: Re balance the tree

// Step 1: Standard BST delete
Node*DeleteNode(Node*root, int val){
    Node* temp;
    if(root== NULL){
        cout<< "Value " << val << " not found in the tree";
        return NULL;
    }
    if(val < root->data ){
        root->left = DeleteNode(root->left, val); //go left
    }
    else if (val > root->data) {
        root->right = DeleteNode(root->right, val); // go right
    }
    else{
        // find the node to delete
        if(root->left== NULL || root->right == NULL){
        temp = (root->left != NULL)? root->left : root->right;
        
    // Case 1 : A leaf node - just delete it
    if(temp ==NULL){
        free(root);
        return NULL;
    }
    //Case 2: One child - replace current with the child
    else {
    *root = *temp; // copying child's data into current node
    delete temp;
    }
}
    // Case 3: Two children - find inorder successor
    else {
        Node* successor = minValue(root->right);
        // Now copy successor value in current node
        root->data = successor->data;
        // Now delete the successor from right subtree
        root->right = DeleteNode(root->right, successor->data);
    }
}
// Step 2: Rebalancing the tree
UpdateHeight(root);
int bf = getBalance(root);

//For LL
if(bf > 1 && getBalance(root->left)>= 0){
    return RightRotate(root);
}

// For LR
if(bf > 1 && getBalance(root->left) <0){
    root->left = LeftRotate(root->left);
}

// For RR
if(bf < -1 && getBalance(root->right)<= 0){
    return LeftRotate(root);
}

//For RL
if(bf< -1 && getBalance(root->right)> 0){
    root->right = RightRotate(root->right);
    return LeftRotate(root);
}
return root;
}

// For Search
void Search (Node*root, int val){
    if(root == NULL){
        return;
    }
    if(val > root->data)
    return Search(root->right, val);
    else 
    return Search(root->left, val);
}
 
// For Display 
//Inorder Transversal
void inorder(Node*root){
    if(root==NULL){
        cout<< "Root not found";
        return;
    }
    cout<< "\n InOrder Transversal: "<<endl;
    inorder(root->left);
    cout<< root->data << " ";
    inorder(root->right);
}
// PreOrder Transversal
void preorder(Node*root){
    if(root== NULL){
    cout<< "\n Root not found";
    return;
    }
    cout<< "\n PreOrder Transversal: "<< endl;
    cout<< root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
//PostOrder Transversal
void postorder(Node*root){
    if(root==NULL){
        cout<<"Root not found";
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<< " ";
}
int main() {
    Node* root = NULL;
    int choice , val;
    cout<< "AVL Trees Operations: "<<endl;
    while(true){
        cout<<"\n1. Insert";
        cout<<"\n2.Search";
        cout<<"\n3.Delete";
        cout<<"\n4.InOrder Display";
        cout<<"\n5.PreOrder Display";
        cout<<"\n6.PostOrder Display";
        cout<<"\n Enter your choice: ";
        cin>> choice;
    
    switch(choice){
        //Insert
        case 1:
        cout<<"\nEnter the value to insert: ";
        cin>> val;
        root = insert(root, val);
        cout<<"\n Value: "<< val << " inserted successfully";
        break;

       // Search
        case 2: 
        cout<<"\nEnter the value to search: ";
        cin>>val;
        Search(root, val);
        if(val == root->data){
            cout<<"\nValue found";
        }
        else{
            cout<<"\nValue not found";
        }
        break;
    //Delete
    case 3:
    cout<<"\n Enter the value to delete: ";
    cin>> val;
    if(val != root->data){
        cout<< val << " not found in the tree.";
        break;
    }
    else {
        root = DeleteNode(root, val);
        cout<< val << " deleted succesfully ";
    }
    break;
    // InOrder Display
    case 4:
    cout<<"InOrder: ";
    inorder(root);
    break;
    //PreOrder Display
    case 5:
    cout<<"PreOrder: " ;
    preorder(root);
    break;
    //Post Order Display
    case 6:
    cout<<"PostOrder: ";
    postorder(root);
    break;
    default: 
    cout<<"\nInvalid data";
}
    }
return 0;
}






