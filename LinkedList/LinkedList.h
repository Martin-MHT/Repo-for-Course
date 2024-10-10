#include <initializer_list>
#include <iostream>

template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val){data = _val;}

        friend class SingleLinkedList<T>;
    };
    Node* head = nullptr;
    int size = 0;
    Node* currentPos = nullptr;
    Node* prePos = nullptr;
    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);
public:
    /// 返回当前位置的值
    T getCurrentVal() const;
    /// 设置当前位置的值
    void setCurrentVal(const T &_val);
    /// 如果链表为空，返回 true；否则返回 false
    bool isEmpty() const;

    int getSize() const;
    void emptyList();
    SingleLinkedList(){};
    ~SingleLinkedList(); 
    SingleLinkedList(std::initializer_list<T> _l);
    void printList() const;
    SingleLinkedList(const SingleLinkedList<T> &_l);
    SingleLinkedList<T>& operator=(const SingleLinkedList<T> &_l);

    /// 在 currentPos 后面插入一个元素，数据为 _val
    void insert(const T &_val); 
    /// 如果找到，返回 ture, currentPos 停留在第一个 _val 的位置。
    /// 否则返回 false, currentPos 不动。
    bool find(const T &_val) ;  
    /// 删除 currentPos 后面的元素 //经过改进，现在直接删除对应位置上面的元素
    void remove();       
};

template<typename T>
bool SingleLinkedList<T>::find(const T &_val) {
    Node *p = head, *pre = nullptr;
    while (p != nullptr) {
        if (p->data == _val) {
            prePos = pre;
            currentPos = p;
            return true;
        }
        pre = p;
        p = p->next;
    }
    return false;
}

template<typename T>
int SingleLinkedList<T>::getSize() const {
    return size;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l) {
    for (auto i = _l.begin(); i != _l.end(); ++i) {
        Node* newNode = new Node(*i);
        if (head == nullptr) {
            head = newNode;
            currentPos = head;
        }
        else {
            currentPos->next = newNode;
            prePos = currentPos;
            currentPos = newNode;
        }
        ++size;
    }
}

template <typename T>
void SingleLinkedList<T>::_emptyList() {
    Node* p = head;
    while (p != nullptr) {
        Node* t = p;
        p = p->next;
        delete t;
    }
    head = nullptr;
    currentPos = nullptr;
    prePos = nullptr;
    size = 0;
}

template <typename T>
void SingleLinkedList<T>::printList() const {
    Node* p = head;
    while (p != nullptr) {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList() {
    _emptyList();
};

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l) {
    _copy(_l);
}

template<typename T>
void SingleLinkedList<T>::emptyList() {
    _emptyList();
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l) {
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template <typename T>
bool SingleLinkedList<T>::isEmpty() const {
    return head == nullptr;
}

template <typename T>
void SingleLinkedList<T>::setCurrentVal(const T &val) {
    if(currentPos == nullptr)
        throw std::runtime_error("Empty current position! Can't set value!");
    else
        currentPos->data = val;
}


template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l) {
    Node *p = _l.head;
    while (p != nullptr) {
        Node* newNode = new Node(p->data);
        if (head == nullptr) {
            head = newNode;
            currentPos = head;
        }
        else {
            currentPos->next = newNode;
            prePos = currentPos;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
}


template <typename T>
void SingleLinkedList<T>::insert(const T &val) {
    Node* newNode = new Node(val);
    if(head == nullptr)
        currentPos = head = newNode, prePos = nullptr;
    else {
        newNode->next = currentPos->next;
        prePos = currentPos;
        currentPos = prePos->next = newNode;
    }
    ++size;
}

template <typename T>
void SingleLinkedList<T>::remove() {
    // if(currentPos == nullptr)   return;
    // else if(size == 1)   _emptyList();
    // else if(currentPos->next == nullptr)    return;
    // else {
    //     Node* p = currentPos->next;
    //     currentPos->next = p->next;
    //     delete p;
    //     --size;
    // }
    if(currentPos == nullptr)   return;
    if(currentPos == head) {
        head = head->next;
        delete currentPos;
        currentPos = head;
        prePos = nullptr;
    } else if(currentPos->next == nullptr) {
        
    } else {
        prePos->next = currentPos->next;
        delete currentPos;
        currentPos = prePos->next;
    }
    --size;
}

template <typename T>
T SingleLinkedList<T>::getCurrentVal() const {
    if(currentPos == nullptr)
        throw std::runtime_error("Empty current position! Can't get value!");
    else return currentPos->data;
}


// 1. Whenever _emptyList is called, 'size', pointer 'head' and 'currentPos' should be cleared. Thus the work was moved into _emptylist.