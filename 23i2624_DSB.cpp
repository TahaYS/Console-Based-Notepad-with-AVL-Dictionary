#include <iostream>
#include <ncurses.h>
#include <fstream>
using namespace std;

int len(string str){
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
        count++;
    return count;
}

int max(int a, int b){
    if(a > b)
        return a;
    else    
        return b;
}

class AvlNode{
    public:
        string data;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(string data = "", int height = 0, 
            AvlNode *left = NULL, AvlNode *right = NULL)
        {
                this -> data = data;
                this -> height = height;
                this -> left = left;
                this -> right = right;
        }
};

class Dictionary{
    private:
        AvlNode *root;
    public:
        Dictionary(){
            this -> root = NULL;
        }

        int Height(AvlNode *node){
            if(node == NULL)
                return -1;
            return node -> height;
        }

        AvlNode* RotateLeft(AvlNode* node) {
            AvlNode* temp1 = node;
            AvlNode* temp2 = temp1 -> right;
            
            temp1 -> right = temp2 -> left;
            temp2 -> left = temp1;
             
            temp1 -> height = max(Height(temp1 -> left), Height(temp1 -> right)) + 1;
            temp2 -> height = max(Height(temp2 -> right), temp1 -> height) + 1;
            
            return temp2; 
        }


        AvlNode* RotateRight(AvlNode* node) {
            AvlNode* temp1 = node;
            AvlNode* temp2 = temp1 -> left;
            
            temp1 -> left = temp2 -> right;
            temp2 -> right = temp1;
            
            temp1 -> height = max(Height(temp1 -> left), Height(temp1 -> right)) + 1;
            temp2 -> height = max(Height(temp2 -> left), temp1 -> height) + 1;
            
            return temp2; 
        }


        AvlNode* RotateLeftRight(AvlNode* node) {
            node -> left = RotateLeft(node -> left);
            return RotateRight(node);
        }

        AvlNode* RotateRightLeft(AvlNode* node){
            node -> right = RotateRight(node -> right);
            return RotateLeft(node);
        }

        void insert(string data){

        }
};

int main(){
    string str = "HELLO";
    int size = len(str);
    cout<< size;
}


// AvlTree Insert( ElementType X, AvlTree T ){
//     if ( T == NULL ){ /* Create and return a one-node tree */

//     T = new AvlNode;

//     T->Element = X;

//     T->left = T->right = NULL;

//     }

//     else{
//         if( X < T->Element ){
//             T->left = Insert( X, T->left );

//             if( Height( T->left ) - Height( T->right ) == 2 )

//             if( X < T->left->Element )

//             T = Rotateright( T );

//             else
//                 T = Rotateleftright( T );

//         }
//         else if(X > T -> Element){
//             T->right = Insert( X, T->right );

//             if(Height( T->left ) - Height( T->right ) == -2 )

//             if( X > T->right->Element )

//             T = Rotateleft( T );

//             else
//                 T = Rotaterightleft( T );
//         }
//         /* Else X is in the tree already; we'll do nothing */
//         T->Height = Max( Height( T->left ), Height( T->right ) ) + 1;
//         return T;
//     }
// }
