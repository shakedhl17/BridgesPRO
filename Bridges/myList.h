#ifndef _MY_LIST_H
#define _MY_LIST_H

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev; // New member for the previous node

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;

    LinkedList() : head(nullptr), tail(nullptr) {}

    void pushFront(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        newNode->prev = nullptr; // New node is the head, so no previous node
        if (head) {
            head->prev = newNode;
        }
        else {
            tail = newNode; // If the list was empty, the new node becomes the tail
        }
        head = newNode;
    }

    void pushBack(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = nullptr; // New node is the tail, so no next node
        newNode->prev = tail;
        if (tail) {
            tail->next = newNode;
        }
        else {
            head = newNode; // If the list was empty, the new node becomes the head
        }
        tail = newNode;
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    bool remove(Node* nodeToRemove) {
        if (!nodeToRemove) {
            return false; // Cannot remove nullptr
        }

        Node* current = head;
        while (current != nullptr) {
            if (current == nodeToRemove) {
                if (current->prev) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }

                if (current->next) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = current->prev;
                }

                delete current;
                return true; // Successfully removed the node
            }
            current = current->next;
        }

        return false; // Node not found in the list
    }

    bool remove(const T& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }

                if (current->next) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = current->prev;
                }

                delete current;
                return true; // Successfully removed the value
            }
            current = current->next;
        }

        return false; // Value not found in the list
    }

    Node* getHead() const {
        return head;
    }

    Node* getTail() const {
        return tail;
    }
};
#endif