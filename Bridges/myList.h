#ifndef _MY_LIST_H
#define _MY_LIST_H

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {};
    };
    
    Node* head;

    LinkedList() : head(nullptr) {};

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    };

    void pushFront(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    };

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    };

    bool remove(Node* nodeToRemove) {
        if (!nodeToRemove) {
            return false; // Cannot remove nullptr
        }

        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current == nodeToRemove) {
                if (prev == nullptr) {
                    // If the node to remove is the head
                    head = current->next;
                }
                else {
                    prev->next = current->next;
                }

                delete current;
                return true; // Successfully removed the node
            }

            prev = current;
            current = current->next;
        }

        return false; // Node not found in the list
    };

    bool remove(const T& value) {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->data == value) {
                if (prev == nullptr) {
                    // If the node to remove is the head
                    head = current->next;
                }
                else {
                    prev->next = current->next;
                }

                delete current;
                return true; // Successfully removed the value
            }

            prev = current;
            current = current->next;
        }

        return false; // Value not found in the list
    };

    Node* getHead() const {
        return head;
    };
};
#endif