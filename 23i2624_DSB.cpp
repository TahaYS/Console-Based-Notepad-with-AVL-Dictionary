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

        void makeDict(){
            ifstream a1("dictionary.txt");

            if(!a1){
                cout<<"File not found\n";
                return;
            }
            
            else{
                string word;
                while(a1 >> word){
                    insertByValue(word);
                }
            }

            a1.close();
        }

        void insertByValue(string value){
            insert(value, root);
        }

        void printDict(){
            inOrderTraversal(root);
        }
};

struct Node{
    char data;
    Node *next;
    Node *prev;

    Node(char data = '-', Node *next = NULL, Node *prev = NULL){
        this -> data = data;
        this -> next = next;
        this -> prev = prev;
    }
};

class Linklist{
    Node *head;
    Node *tail;
    public:
        Linklist(){
            head = NULL;
            tail = NULL;
        }

        void insert(char value){
            
            Node *newNode = new Node;
            newNode -> data = value;
            
            if(head == NULL){
                tail = newNode;
                tail -> prev = newNode;
                tail -> next = newNode;
                return;
            }
            
            else{
                newNode -> next = tail -> next;
                newNode -> prev = tail;
                tail -> next -> prev = newNode;
                tail -> next = newNode;
                tail = newNode;
            }
        }

        void deleteAtEnd(){
            if(head == NULL)
                return;

            if(head == tail){
                delete head;
                head = tail = NULL;
                return;
            }

            Node *temp = tail;
            tail = tail -> prev;
            tail -> next = head;
            head -> prev = tail;
            
            delete temp;
        }
};

class Queue{
    private:
        Node *front;
        Node *rear;
    public:
        Queue(){
            this ->front = NULL;
            this ->rear = NULL;
        }

        void enqueue(char value){
            Node *newNode = new Node;
            newNode -> data = value;
            if(front == NULL){
                front = rear = newNode;
                return;
            }

            else{
                rear -> next = newNode;
                rear = newNode;
            }
        }

        char dequeue(){
            char value;
            if(front == NULL)
                return '\0';
            
            else{
                Node *temp = front;
                front = front -> next;
                value = temp -> data;
                delete temp;
            }
            return value;
        }
};

int main(){
    // Dictionary dict;
    // dict.makeDict();
    Queue  obj1;
    obj1.enqueue('a');
    obj1.enqueue('b');
    obj1.enqueue('c');
    cout<<obj1.dequeue();
    cout<<obj1.dequeue();
    cout<<obj1.dequeue();
    
}


