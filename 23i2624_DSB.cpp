#include <iostream>
#include <ncurses.h>
#include <string>
#include <cstring>
#include <termios.h>
#include <unistd.h>
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

void disableFlowControl() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_iflag &= ~(IXON | IXOFF | IXANY);  // Disable flow control
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
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

class Linklist {
    Node *head;
    Node *tail;

    public:
        Linklist() {
            head = NULL;
            tail = NULL;
        }

        void insert(char value) {
            Node *newNode = new Node;
            newNode->data = value;

            if (head == NULL) { // If list is empty
                head = tail = newNode;
                head->prev = head;
                head->next = head; // Circular links
            } else { // If list is not empty
                newNode->next = head;  // New node points to head
                newNode->prev = tail;  // New node points to tail
                tail->next = newNode;  // Tail points to new node
                head->prev = newNode;  // Head points back to new node
                tail = newNode;        // Update tail to the new node
            }
        }

        void deleteAtEnd() {
            if (head == NULL) // If list is empty
                return;

            if (head == tail) { // If only one node in the list
                delete head;
                head = tail = NULL;
                return;
            }

            Node *temp = tail;
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
            delete temp;
        }

        void emptyList() {
            while (head != NULL)
                deleteAtEnd();
        }

        string wholeList() {
            Node *temp = head;
            string value = "";

            if (head != NULL) {
                do {
                    value += temp->data; // Collect data from each node
                    temp = temp->next;
                } while (temp != head); // Stop when we circle back to head
            }

            return value;
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

        bool isEmpty(){
            if(front == NULL)
                return true;
            else
                return false;
        }

        char dequeueAtEnd(){
            Node *temp = front;
            if(front == NULL)
                return '\0';

            if(front == rear){
                char value = rear -> data;
                delete rear;
                front = rear = NULL;
                return value;
            }

            while(temp -> next != rear)
                temp = temp -> next;
            char value = rear -> data;
            delete rear;
            rear = temp;
            rear -> next = NULL;

            return value;
        }

        void clearQueue(){

            while(front != NULL)
                dequeue();
        }

};

void manageInputWindow(Linklist &list, Queue &queue) {
    // Initialize ncurses
    disableFlowControl();
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

                // Delete the last character from Linklist and Queue
                list.deleteAtEnd();
                queue.dequeueAtEnd();

                if (cur_x > 1) {
                    cur_x--;
                } else if (cur_y > 1) {
                    cur_y--;
                    cur_x = width - 2; // Move to the end of the previous line
                    // Adjust cursor to the position in front of the last character on the previous line
                    while (cur_x > 1 && mvwinch(win, cur_y, cur_x - 1) == ' ') {
                        cur_x--;
                    }
                }
                mvwaddch(win, cur_y, cur_x, ' '); // Clear character
                wmove(win, cur_y, cur_x);
            }
        } else if (ch == '\n') { // Handle Enter key
            list.insert(ch);
            if (cur_y < height - 2) {
                cur_y++;
                cur_x = 1;
            }
        } 
        else if (ch == 12) { // Ctrl+L (ASCII code for Ctrl+L is 12)
            // Empty both the linked list and the queue
            list.emptyList();
            queue.clearQueue();

            // Prompt for the filename
            char filename[256];
            mvprintw(7, 7, "Enter file name: ");
            refresh();

            echo();  // Enable echo to show typed characters
            getstr(filename);  // Get the file name input
            noecho();  // Disable echo again

            clear(); // Clear the screen

            // Create a new window to display the file content inside the rectangle
            int height = 20, width = 70, start_y = 5, start_x = 5;
            WINDOW* win = newwin(height, width, start_y, start_x);
            box(win, 0, 0); // Draw the border
            wrefresh(win);

            // Open the file
            ifstream file(filename);

            if (!file) {
                mvwprintw(win, 1, 1, "File not found");
                wrefresh(win);
            } else {
                // Read the file line by line
                string line;
                int temp_y = 1; // Start on the first line (row 1)
                
                while (getline(file, line)) {
                    int temp_x = 1; // Reset horizontal cursor position at the beginning of each line
                    
                    // Insert each character of the line into the linked list and queue
                    for (char file_char : line) {
                        list.insert(file_char);
                        //queue.enqueue(file_char); // Uncomment this line if you want to enqueue as well
                        
                        // Display character on the ncurses window
                        mvwaddch(win, temp_y, temp_x, file_char);
                        temp_x++; // Move cursor to the next column
                    }

                    // After each line, move to the next row and leave a line space
                    temp_y++;
                    if (temp_y >= height - 1) { // Prevent overflow of the window
                        break;
                    }
                }

                // Refresh the window to show the file content
                wrefresh(win);
            }
            file.close();
            // Clear the prompt and any other displayed message
            move(7, 7);
            clrtoeol();
        }
 
        else if (ch == 19) { // Ctrl+S (ASCII code for Ctrl+S is 19)
            // Get the content from the linked list
            string content = list.wholeList();

            // Debug: Display the content on the console (for debugging purposes)
            //mvprintw(height + 2, 0, "DEBUG: Content to save: %s", content.c_str());
            refresh();

            // Prompt for the filename
            char filename[256];
            mvprintw(7, 7, "Enter file name to save: ");
            refresh();

            echo();  // Enable echo to show typed characters
            getstr(filename);  // Get the file name input
            noecho();  // Disable echo again

            // Open the file for writing, create the file if it doesn't exist
            ofstream file(filename, ios::out | ios::trunc); // `ios::trunc` to create or overwrite the file

            if (!file) {
                mvprintw(9, 7, "Error opening file for writing.");
                refresh();
            } else {
                // Write the content to the file
                file << content;

                mvprintw(9, 7, "File saved successfully.");
                refresh();
            }

            // Clear the prompt message
            move(7, 7);
            clrtoeol();
        }
        
        else if (ch == ' ') { // Space key
            string word = "";
            list.insert(ch);
            // Collect the word from the queue
            while (!queue.isEmpty()) {
                word += queue.dequeue(); 
            }

            // Display the word below the window (but not interfering with it)
            move(height + 1, 0);
            clrtoeol();

            // Display the last word
            mvprintw(start_y + height + 1, start_x, "Last word: %s", word.c_str());
            refresh(); // Refresh the main screen

            // After displaying the word, empty the word and queue
            // Now the queue is empty, so next word will be collected separately

            // Add a space to the buffer
            if (index < sizeof(buffer) - 1) {
                buffer[index++] = ch;
                buffer[index] = '\0';
                mvwaddch(win, cur_y, cur_x, ch);
                if (cur_x < width - 2) {
                    cur_x++;
                } else {
                    cur_y++;
                    cur_x = 1;
                }
            }

            // Redraw the rectangle to prevent it from disappearing
            wrefresh(win);
        }
 
        // Insert regular character
        else if (isprint(ch)) {
            // Add character to buffer and linked list
            if (index < sizeof(buffer) - 1) {
                buffer[index++] = ch;
                buffer[index] = '\0';
                list.insert(ch);
                queue.enqueue(ch);

                // Insert the character in the ncurses window
                mvwaddch(win, cur_y, cur_x, ch);

                // Update cursor position
                if (cur_x < width - 2) {
                    cur_x++;
                } else {
                    // Handle word wrapping to next line
                    cur_y++;
                    cur_x = 1;
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
    Linklist list;
    Queue queue;
    dict.makeDict();
    manageInputWindow(list, queue);
    
}


