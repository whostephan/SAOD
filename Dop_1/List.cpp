#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <iterator>
#include <numeric>

template <typename T>
class LList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value = T()) : data(value), next(nullptr) {}
    };

    Node* head;       // Указатель на первый служебный узел
    Node* tail;       // Указатель на последний служебный узел
    size_t list_size; // Количество узлов в списке, исключая служебные узлы

    void copy(const LList& other) {
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    void move(LList&& other) {
        head = other.head;
        tail = other.tail;
        list_size = other.list_size;
        other.head = other.tail = nullptr;
        other.list_size = 0;
    }

public:
    LList() : head(new Node()), tail(new Node()), list_size(0) {
        head->next = tail;
    }
    
    ~LList() { clear(); delete head; delete tail; }
    
    LList(const LList& other) : head(new Node()), tail(new Node()), list_size(0) {
        head->next = tail;
        copy(other);
    }

    LList(LList&& other) noexcept : head(new Node()), tail(new Node()), list_size(0) {
        move(std::move(other));
    }

    LList& operator=(const LList& other) {
        if (this != &other) {
            clear();
            copy(other);
        }
        return *this;
    }

    LList& operator=(LList&& other) noexcept {
        if (this != &other) {
            clear();
            move(std::move(other));
        }
        return *this;
    }

    LList(std::initializer_list<T> init_list) : LList() {
        for (const T& value : init_list) {
            push_back(value);
        }
    }

    // Добавление в конец
    void push_back(const T& value) {
        Node* new_node = new Node(value);
        Node* last = tail;
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        current->next = new_node;
        new_node->next = tail;
        ++list_size;
    }
    // Добавление в начало
    void push_front(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head->next;
        head->next = new_node;
        ++list_size;
    }
    // Вставка по индексу
    void insert(size_t idx, const T& value) {
        if (idx > list_size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (size_t i = 0; i < idx; ++i) {
            current = current->next;
        }
        Node* new_node = new Node(value);
        new_node->next = current->next;
        current->next = new_node;
        ++list_size;
    }
    // Удаление последнего элемента
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        Node* current = head;
        while (current->next->next != tail) {
            current = current->next;
        }
        delete current->next;
        current->next = tail;
        --list_size;
    }
    // Удаление первого элемента
    void pop_front() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        Node* old_head = head->next;
        head->next = old_head->next;
        delete old_head;
        --list_size;
    }
    // Удаление элемента по индексу
    void remove_at(size_t index) {
        if (index >= list_size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        Node* to_delete = current->next;
        current->next = to_delete->next;
        delete to_delete;
        --list_size;
    }
    // Доступ к элементу по индексу
    T& operator[](const size_t index) {
        if (index >= list_size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head->next;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    T const& operator[](const size_t index) const {
        if (index >= list_size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head->next;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    // Размер списка
    size_t size() const {
        return list_size;
    }
    // Проверка на пустоту
    bool empty() const {
        return list_size == 0;
    }
    // Очистка
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
    // Возвращение первого и последнего элементов
    T front() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->next->data;
    }

    T back() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        return current->data;
    }

    // Итератор
    class ListIterator {
    private:
        Node* current;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        ListIterator(Node* node) : current(node) {}

        reference operator*() const { return current->data; }
        pointer operator->() { return &current->data; }

        ListIterator& operator++() {
            current = current->next;
            return *this;
        }

        ListIterator operator++(int) {
            ListIterator temp = *this;
            ++(*this);
            return temp;
        }

        friend bool operator==(const ListIterator& a, const ListIterator& b) {
            return a.current == b.current;
        }

        friend bool operator!=(const ListIterator& a, const ListIterator& b) {
            return a.current != b.current;
        }
    };

    ListIterator begin() const {
        return ListIterator(head->next);
    }

    ListIterator end() const {
        return ListIterator(tail);
    }
};

// Вспомогательная функция для печати списка
template <typename T>
void print_lst(const LList<T>& l) {
    for (size_t i = 0; i < l.size(); ++i) {
        std::cout << l[i];
        if (i != l.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

// Тестирование
int main() {
    LList<char> lst;
    std::cout << std::boolalpha << lst.empty() << std::endl;

    for (int i = 0; i < 5; ++i)
        lst.push_back(char('a' + i));

    print_lst(lst);

    for (int i = 0; i < 5; ++i)
        lst.insert(0, char('z' - i));

    print_lst(lst);

    for (size_t i = 0; i != lst.size(); ++i)
        lst[i] = char('a' + i);

    print_lst(lst);

    lst.pop_back();
    lst.pop_front();

    print_lst(lst);

    lst.remove_at(5);
    lst.insert(3, 'o');

    print_lst(lst);

    lst.clear();

    lst.push_back('q');
    lst.push_back('w');

    std::cout << lst.size() << ' ' << std::boolalpha << lst.empty() << std::endl;

    return 0;
}

