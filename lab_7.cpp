#include <iostream>
#include <vector>

using namespace std;
struct Node {
    int data;
    Node* next;
    Node* prev;
};

class LinkedList {
public:
    LinkedList();
    LinkedList(int data);
    LinkedList(std::vector<int> data);
    bool add_element(int data);
    bool delete_element(int data);
    bool find_element(int data);
    bool find_pos(int pos);
    bool insert(int data, int pos);
    void print_list();
    void sort_list();
    ~LinkedList();

private:
    Node* first;
    Node* last;
};

LinkedList::LinkedList() {
    first = nullptr;
    last = nullptr;
}

LinkedList::LinkedList(int data) {
    Node* nd = new Node{ data, nullptr, nullptr };
    first = nd;
    last = nd;
    last->next = nullptr;
}

LinkedList::LinkedList(std::vector<int> data) {
    first = nullptr;
    last = nullptr;
    for (int element : data) {
        add_element(element);
    }
}

bool LinkedList::add_element(int data) {
    Node* newNode = new Node{ data, nullptr, nullptr };
    if (first == nullptr) {
        first = newNode;
        last = newNode;
    }
    else {
        newNode->prev = last;
        last->next = newNode;
        last = newNode;
    }
    newNode->next = nullptr;
    return true;
}

bool LinkedList::delete_element(int data) {
    if (last != nullptr) {
        Node* current = first;
        Node* previous = nullptr;
        while (current != nullptr) {
            if (current->data == data) {
                if (current == first) {
                    first = first->next;
                    delete current;
                    current = first;
                    continue;
                }
                else if (current == last) {
                    last = previous;
                    last->next = nullptr;
                    delete current;
                    break;
                }
                previous->next = current->next;
                delete current;
                current = previous->next;
                continue;
            }
            previous = current;
            current = current->next;
        }
        return true;
    }
    return false;
}


bool LinkedList::find_element(int data) {
    if (first == nullptr) {
        return 0;
    }
    Node* current = first;
    while (current != nullptr) {
        if (current->data == data) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

bool LinkedList::find_pos(int pos) {
    Node* current = first;
    int counter = 0;
    while (current != nullptr) {
        ++counter;
        if (counter == pos) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

bool LinkedList::insert(int data, int pos) {
    if (!this->find_pos(pos)) {
        return false;
    }
    Node* nd = new Node{ data, nullptr, nullptr };
    if (pos == 1) {
        nd->next = first;
        first = nd;
    }
    else {
        Node* current = first;
        for (int i = 1; i < pos - 1; ++i) {
            current = current->next;
        }
        nd->next = current->next;
        nd->prev = current;
        current->next = nd;
    }
    return true;
}

void LinkedList::print_list() {
    if (first == nullptr) {
        return;
    }
    Node* current = first;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void LinkedList::sort_list() {
    Node* nd = new Node;
    Node* left = first;
    Node* right = first->next;
    while (left->next) {
        while (right) {
            if ((left->data) > (right->data)) {
                nd->data = left->data;
                left->data = right->data;
                right->data = nd->data;
            }
            right = right->next;
        }
        left = left->next;
        right = left->next;
    }
    return;
}

LinkedList::~LinkedList() {
    Node* current = first;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

int main() {
    int a, b, c, d, n;
    setlocale(LC_ALL, "Russian");

    LinkedList LIST;
    cout << "Введите длину списка: ";
    cin >> n;
    cout << endl;
    for (int i = n; i > 0; --i) {
        LIST.add_element(i);
    }
    cout << "Начальный список: ";
    LIST.print_list();
    cout << endl;

    cout << "Введите элемент, который хотите найти: ";
    cin >> c;
    cout << endl;
    if (LIST.find_element(c) == 1) {
        cout << "Элемент " << c << " найден" << endl;
    }
    else {
        cout << "Элемент " << c << " не найден" << endl;
    }

    cout << "Введите в строчку номер, на который хотите поставить элемент, и сам элемент: ";
    cin >> a >> b;
    cout << endl;
    LIST.insert(b, a);
    LIST.print_list();
    cout << endl;
    cout << "Отсортированный список: ";
    LIST.sort_list();
    LIST.print_list();
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Введите элемент, который хотите удалить: ";
        cin >> d;
        cout << endl;
        LIST.delete_element(d);
        LIST.print_list();
        cout << endl;
    }
    return 0;
}