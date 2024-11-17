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

//     T->Left = T->Right = NULL;

//     }

//     else{
//         if( X < T->Element ){
//             T->Left = Insert( X, T->Left );

//             if( Height( T->Left ) - Height( T->Right ) == 2 )

//             if( X < T->Left->Element )

//             T = RotateRight( T );

//             else
//                 T = RotateLeftRight( T );

//         }
//         else if(X > T -> Element){
//             T->Right = Insert( X, T->Right );

//             if(Height( T->Left ) - Height( T->Right ) == -2 )

//             if( X > T->Right->Element )

//             T = RotateLeft( T );

//             else
//                 T = RotateRightLeft( T );
//         }
//         /* Else X is in the tree already; we'll do nothing */
//         T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
//         return T;
//     }
// }
