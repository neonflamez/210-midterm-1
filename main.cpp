// COMSC 210 || Midterm 1 || Shayan Khan

#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; //constants for minimum and maximum values

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev; //pointer to the previous node
        Node* next; //pointer to the next node
        //constructor
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; //set the data value
            prev = p; //set the previous node pointer
            next = n; //set the next node pointer
        }
    };

    Node* head; //pointer to the first node
    Node* tail; //pointer to the last node

public:
    //constructor initializes the head and tail to nullptr
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //insert a new node
    void insert_after(int value, int position) {
        if (position < 0) { //if position is <0, invalid position, return
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value); //new node with given value
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }
    
    //delete a node by its value
    void delete_val(int value) {
        if (!head) return; //list is empty, then return

        Node* temp = head; //start from the head
        
        while (temp && temp->data != value) //iterate through the list to find the given value
            temp = temp->next;

        if (!temp) return; //if value is not found, then return

        if (temp->prev) //if temp is not the first node, then modify the pointer of the previous node
            temp->prev->next = temp->next;
        else //if temp is the first node, update head
            head = temp->next; 

        if (temp->next) //if temp is not the first node, then modify the pointer of the next node
            temp->next->prev = temp->prev;
        else //if temp is the first node, update tail
            tail = temp->prev; 

        delete temp; //deallocate the memory of the deleted node
    }

    // delete a node at a given position
    void delete_pos(int pos) {
        if (!head) { // if list is empty, return
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) { //if the position is the first node, use pop_front to remove the first node
            pop_front();
            return;
        }
    
        Node* temp = head; //start from head
    
        for (int i = 1; i < pos; i++){ //iterate until you get to the desired position
            if (!temp) { //if position doesn't exist, return 
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) { //if position doesn't exist, return 
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) { //if the position is the last node, use pop_back to remove the last node
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next; //link the previous note to the next node
        temp->next->prev = tempPrev; //link the next note to the previous node
        delete temp; //deallocate the memory of the deleted node
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}