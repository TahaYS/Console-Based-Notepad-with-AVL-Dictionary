#include <iostream>
#include <ncurses.h>
#include <string>
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
                return 0;
            return node -> height;
        }

        AvlNode* RotateLeft(AvlNode *node) {
            AvlNode* temp1 = node;
            AvlNode* temp2 = temp1 -> right;
            
            temp1 -> right = temp2 -> left;
            temp2 -> left = temp1;
             
            temp1 -> height = max(Height(temp1 -> left), Height(temp1 -> right)) + 1;
            temp2 -> height = max(Height(temp2 -> right), temp1 -> height) + 1;
            
            return temp2; 
        }


        AvlNode* RotateRight(AvlNode *node) {
            AvlNode* temp1 = node;
            AvlNode* temp2 = temp1 -> left;
            
            temp1 -> left = temp2 -> right;
            temp2 -> right = temp1;
            
            temp1 -> height = max(Height(temp1 -> left), Height(temp1 -> right)) + 1;
            temp2 -> height = max(Height(temp2 -> left), temp1 -> height) + 1;
            
            return temp2; 
        }


        AvlNode* RotateLeftRight(AvlNode *node) {
            node -> left = RotateLeft(node -> left);
            return RotateRight(node);
        }

        AvlNode* RotateRightLeft(AvlNode *node){
            node -> right = RotateRight(node -> right);
            return RotateLeft(node);
        }

        void insert(string value, AvlNode *&node){
            if ( node == NULL ){ 
                node = new AvlNode;
                node -> data = value;
                //node -> left = node -> right = NULL;
                node -> height = 1;
                return;
            }

            if(value < node -> data){
                
                insert(value, node -> left);

                if(Height(node -> left) - Height(node -> right) == 2){
                    if(value < (node -> left -> data))
                        node = RotateRight(node);
                    else
                        node = RotateLeftRight(node);
                }

            }

            else if(value > node -> data){
                insert(value, node -> right);

                if(Height(node -> left) - Height(node -> right) == -2){
                    //cout<<"HELLO\n";
                    if(value > (node -> right -> data)){
                        //cout<<"HELLO\n";
                        node = RotateLeft(node);

                    }
                    else{
                        
                        node = RotateRightLeft(node);
                    }
                }
            }

            else if(value == node -> data){
                return;
            }
            
            node -> height = max(Height(node -> left), Height(node -> right)) + 1;
        }

        void inOrderTraversal(AvlNode* node) {
            if (node == NULL) 
                return;
            
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }

        void insertByValue(string value){
            insert(value, root);
        }

        void printDict(){
            inOrderTraversal(root);
        }
};

int main(){
    Dictionary dict;
    // Test Case 1: Insert a sequence of words
    cout << "Test Case 1: Insert a sequence of words:" << endl;
    dict.insertByValue("apple");
    dict.insertByValue("banana");
    dict.insertByValue("cherry");
    dict.insertByValue("date");
    dict.printDict(); // Expected output: apple banana cherry date

    // // Test Case 2: Insert words with varying lengths
    cout << "\n\nTest Case 2: Insert words with varying lengths:" << endl;
    dict.insertByValue("pear");
    dict.insertByValue("kiwi");
    dict.insertByValue("grape");
    dict.printDict(); // Expected output: apple banana cherry date grape kiwi pear

    // // // Test Case 3: Insert words in lexicographical order
    cout << "\n\nTest Case 3: Insert words in lexicographical order:" << endl;
    dict.insertByValue("apple");
    dict.insertByValue("banana");
    dict.insertByValue("cherry");
    dict.insertByValue("date");
    dict.printDict(); // Expected output: apple banana cherry date

    // // Test Case 4: Insert words in reverse lexicographical order
    cout << "Test Case 4: Insert words in reverse lexicographical order:" << endl;
    dict.insertByValue("date");
    dict.insertByValue("cherry");
    dict.insertByValue("banana");
    dict.insertByValue("apple");
    dict.printDict(); // Expected output: apple banana cherry date

    // return 0;
}


