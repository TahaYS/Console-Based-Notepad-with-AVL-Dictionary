#include <iostream>
#include <ncurses.h>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

void init_ncurses() {
    // Initialize ncurses
    initscr();            // Start ncurses mode
    raw();                // Disable line buffering (for immediate input)
    keypad(stdscr, TRUE); // Enable special keys (e.g., arrow keys)
    noecho();             // Don't display user input
    curs_set(0);          // Hide cursor
}

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

void manageInputWindow() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);

    // Clear the screen to remove artifacts
    clear();
    refresh();

    // Create a larger window
    int height = 20, width = 70, start_y = 5, start_x = 5; // Bigger rectangle
    WINDOW* win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);
    wrefresh(win);

    // Instructions
    mvprintw(0, 0, "Type below. Press ESC to exit. Ctrl+L to load file and Ctrl+S to save file.");
    refresh();

    char buffer[1024];    // Buffer for the text being typed
    int cur_x = 1, cur_y = 1; // Cursor position within the window
    int index = 0;        // Position in the buffer
    memset(buffer, 0, sizeof(buffer)); // Initialize buffer

    while (true) {
        int ch = wgetch(win); // Get input from the user

        if (ch == 27) { // ESC key to exit
            break;
        } else if (ch == KEY_BACKSPACE || ch == 127) { // Handle backspace
            if (index > 0) {
                index--;
                buffer[index] = '\0';

                if (cur_x > 1) {
                    cur_x--;
                } else if (cur_y > 1) {
                    cur_y--;
                    cur_x = width - 2; // Move to the end of the previous line
                    // Adjust cursor to the position of the last character on the previous line
                    while (cur_x > 1 && mvwinch(win, cur_y, cur_x - 1) == ' ') {
                        cur_x--;
                    }
                }
                mvwaddch(win, cur_y, cur_x, ' '); // Clear character
                wmove(win, cur_y, cur_x);
            }
        } else if (ch == '\n') { // Handle Enter key
            if (cur_y < height - 2) {
                cur_y++;
                cur_x = 1;
            }
        } else if (ch == 12) { // Ctrl+L (ASCII code for Ctrl+L is 12)
            // Leave functionality empty for user implementation
        } else if (ch == 19) { // Ctrl+S (ASCII code for Ctrl+S is 19)
            // Leave functionality empty for user implementation
        } else { // Regular characters
            if (index < sizeof(buffer) - 1) { // Prevent buffer overflow
                // Handle word wrapping
                if (cur_x >= width - 2) { // If at the right edge of the window
                    // Find the start of the current word in the buffer
                    int word_start = index - 1;
                    while (word_start >= 0 && buffer[word_start] != ' ') {
                        word_start--;
                    }
                    word_start++; // Adjust to the first character of the word

                    if (word_start < index) { // If a word exists to move
                        // Clear the word from the current line
                        for (int i = word_start; i < index; i++) {
                            mvwaddch(win, cur_y, cur_x - (index - i), ' ');
                        }
                        // Move cursor and word to the next line
                        cur_y++;
                        cur_x = 1;

                        // Redraw the word on the new line
                        for (int i = word_start; i < index; i++) {
                            mvwaddch(win, cur_y, cur_x++, buffer[i]);
                        }
                    } else { // If the word doesn't fit, wrap normally
                        cur_y++;
                        cur_x = 1;
                    }
                }

                buffer[index++] = ch;
                buffer[index] = '\0';
                mvwaddch(win, cur_y, cur_x, ch); // Add character to the window
                if (cur_x < width - 2) {
                    cur_x++;
                }
            }
        }
        wrefresh(win);
    }

    // End ncurses mode
    delwin(win);
    endwin();
}

int main(){
    Dictionary dict;
    dict.makeDict();
    manageInputWindow();
    
    
}


