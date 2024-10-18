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
        if (!head) { //if list is empty, set head and tail to the new node
            head = tail = newNode;
            return;
        }

        Node* temp = head; //start from head
        for (int i = 0; i < position && temp; ++i) //iterate to desired position
            temp = temp->next;

        if (!temp) { //if the position exceeds the list size, deallocate the memory
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        //new node, after found desired position
        newNode->next = temp->next; //link newNode to node after temp
        newNode->prev = temp; //link newNode to current temp node
        if (temp->next) //if temp is not the last node, then modify the pointer of the next node
            temp->next->prev = newNode;
        else //if temp is the last node, update tail
            tail = newNode;
        temp->next = newNode; //modify the current node's next pointer to new node
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

        if (temp->next) //if temp is not the last node, then modify the pointer of the next node
            temp->next->prev = temp->prev;
        else //if temp is the last node, update tail
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

    //insert a node at the end of the list
    void push_back(int v) {
        Node* newNode = new Node(v); //new node
        if (!tail) //if list is empty, set head and tail to the new node
            head = tail = newNode;
        else { 
            tail->next = newNode; //set the current tail's next pointer to new node
            newNode->prev = tail; //set the new node's previous pointer to current tail
            tail = newNode; //tail is now new node
        }
    }
    
    //insert a node at the beginning of the list
    void push_front(int v) {
        Node* newNode = new Node(v); //new node
        if (!head) //if list is empty, set head and tail to the new node
            head = tail = newNode;
        else {
            newNode->next = head; //link new node to current head
            head->prev = newNode; //link current head back to new node
            head = newNode; //update head to new node
        }
    }
    
    //remove the first node of the list
    void pop_front() {

        if (!head) { //if list is empty, then return
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head; //store current head node

        if (head->next) { //if the list has more than one node, move the head pointer to the next node
            head = head->next;
            head->prev = nullptr; //set the new head's previous pointer to nullptr
        }
        else
            head = tail = nullptr; //if there is only one node, set head and tail to nullptr
        delete temp; //deallocate the memory of the removed node
    }

    //remove the last node of the list
    void pop_back() {
        if (!tail) { //if the list is empty, return
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail; //store current tail node

        if (tail->prev) { //if the list has more than one node, move the tail pointer to the previous node
            tail = tail->prev;
            tail->next = nullptr; //set the new tail's previous pointer to nullptr
        }
        else
            head = tail = nullptr; //if there is only one node, set head and tail to nullptr
        delete temp; //deallocate the memory of the removed node
    }

    //destructor
    ~DoublyLinkedList() {
        while (head) { //iterate through list
            Node* temp = head; //store current head node
            head = head->next; //move the head pointer to next node
            delete temp; //deallocate the memory of the removed node
        }
    }

    //print the list from head to tail
    void print() {
        Node* current = head; //start from head
        if (!current) { //if list is empty, return
            cout << "List is empty." << endl;
            return;
        }
        while (current) { //iterate the list
            cout << current->data << " "; //print the data of the current node
            current = current->next; //move to next node
        }
        cout << endl;
    }

    //print the list from tail to head
    void print_reverse() {
        Node* current = tail; //start from head
        if (!current) { //if list is empty, return
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " "; //print the data of the current node
            current = current->prev; //move to previous node
        }
        cout << endl;
    }

    //print every other element
    void every_other_element(){
        Node* current = head; //start from head
        if(!current){ //if the list is empty, return
            cout << "List is empty." << endl;
            return;
        }

        while(current){ //iterate the list
            cout << current->data << " "; //print the data of the current nnode
            if(current->next) //move to the node after the next
                current = current->next->next;
            else
                break; //stop if no next node
        }
        cout << endl;
    }
};

int main() {
    DoublyLinkedList list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);

    cout << "Original List: ";
    list.print();

    cout << "Every Other Element: ";
    list.every_other_element();
    
    return 0;
}