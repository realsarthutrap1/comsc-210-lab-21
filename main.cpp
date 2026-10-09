// COMSC-210 | Lab 21 | Sarthak Pani
// adapted from the instructor doubly linked list demo

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class Goat {
private:
    int age;
    string name;
    string color;
    // ai-generated names and colors
    string names[15] = {
        "Clover", "Biscuit", "Maple", "Pebble", "Juniper",
        "Pickles", "Waffles", "Acorn", "Sprout", "Hazel",
        "Nugget", "Pippin", "Willow", "Mochi", "Bramble"
    };
    string colors[15] = {
        "White", "Black", "Brown", "Gray", "Cream",
        "Tan", "Gold", "Silver", "Copper", "Chestnut",
        "Caramel", "Ivory", "Beige", "Chocolate", "Rust"
    };

public:
    Goat();
    Goat(int age, string name, string color);
    int get_age() const;
    string get_name() const;
    string get_color() const;
};

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
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
            tail = newNode; // inserting at the end
        temp->next = newNode;
    }

    void delete_node(int value) {
        if (!head) return; // empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// driver program
int main() {
    srand(time(0));
    DoublyLinkedList list;
    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    return 0;
}

Goat::Goat() {
    age = rand() % 20 + 1;
    name = names[rand() % 15];
    color = colors[rand() % 15];
}

Goat::Goat(int age, string name, string color)
    : age(age), name(name), color(color) {}

int Goat::get_age() const {
    return age;
}

string Goat::get_name() const {
    return name;
}

string Goat::get_color() const {
    return color;
}
