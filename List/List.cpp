#include <iostream>
#include "List.h"  // 假设你的list类在list.h文件中

template<typename Object>
void print(const List<Object> &l) {
    for(auto &x : l)
        std::cout << x << " ";
    std::cout << std::endl;
};
void test_copy() {
    std::cout << "===== Copy Test =====" << std::endl;
    List<int> l1, l2;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    List<int> l3(l1), l4;
    l2 = l1;
    l4 = l4 = l3 = l1;
    std::cout << "Original list contents: \n";
    print(l1);
    std::cout << "\nContents of three copied lists: \n";
    
    print(l2);
    print(l3);
    print(l4);

    l2.push_back(4);
    l3.pop_front();

    std::cout << "After adding 4 to the tail of the 1st list and removing the head of the 2nd list, " << std::endl;

    std::cout << "Original list contents: \n";
    print(l1);
    std::cout << "\nContents of three copied lists: \n";
    print(l2);
    print(l3);
    print(l4);
    std::cout << std::endl;
}

void test_push_back() {
    std::cout << "===== Push to back Test =====" << std::endl;
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    std::cout << "Push back test: \n";
    print(lst);
    std::cout << "Expected:\n1 2 3\n";
    std::cout << std::endl;
}

void test_push_front() {
    std::cout << "===== Push to front Test =====" << std::endl;
    List<int> lst;
    lst.push_front(1);
    lst.push_front(2);
    lst.push_front(3);

    std::cout << "Push front test: \n";
    print(lst);
    std::cout << "Expected:\n3 2 1\n";
    std::cout << std::endl;
}

void test_pop_back() {
    std::cout << "===== Pop from back Test =====" << std::endl;
    List<int> lst{1, 2, 3};
    lst.pop_back();

    std::cout << "Pop back test: \n";
    print(lst);
    std::cout << "Expected:\n1 2\n";
    std::cout << std::endl;
}

void test_pop_front() {
    std::cout << "===== Pop from front Test =====" << std::endl;
    List<int> lst{1, 2, 3};
    lst.pop_front();

    std::cout << "Pop front test: \n";
    print(lst);
    std::cout << "Expected:\n2 3\n";
    std::cout << std::endl;
}
void test_iterator() {
    std::cout << "===== Iterator Test =====" << std::endl;
    List<int> lst{1, 2, 3, 4, 5};

    std::cout << "Iterator test: \n";
    print(lst);
    std::cout << "Expected:\n1 2 3 4 5\n";

    std::cout << "Increment and Decrement operation test: \n";

    auto it = --lst.end();
    std::cout << *(it--) << " ";
    std::cout << *(--it) << " ";

    std::cout << *(it++) << " ";
    std::cout << *(++it) << " ";
    
    std::cout << *------it << " ";
    std::cout << *++++it;

    std::cout << "\nExpected:\n5 3 3 5 2 4\n";
    std::cout << std::endl;
}

void test_insert() {
    std::cout << "===== Insertion Test =====" << std::endl;
    List<int> lst{1, 3};

    List<int>::iterator it = lst.begin();
    ++it;
    it = lst.insert(it, 2);  // 插入2到位置1

    std::cout << "Insert test: \n";
    print(lst);
    std::cout << *it << std::endl;
    std::cout << "Expected:\n1 2 3\n";
    std::cout << std::endl;
}

void test_erase_single() {
    std::cout << "===== Single Erase Test =====" << std::endl;
    List<int> lst{1, 2, 3};

    auto it = lst.begin();
    ++it;
    it = lst.erase(it);  // 删除元素2

    std::cout << "Erase single element test: \n";
    print(lst);
    std::cout << *it << std::endl;
    std::cout << "Expected:\n1 3\n3\n";
    std::cout << std::endl;
}

void test_erase_range() {
    std::cout << "===== Range Erase Test =====" << std::endl;
    List<int> lst{1, 2, 3, 4, 5};

    List<int>::iterator from = lst.begin(), to = lst.begin(), ret;
    ++from; // 指向元素2
    ++to; ++to; ++to; // 指向元素4

    ret = lst.erase(from, to);  // 删除元素2和3

    std::cout << "Erase range test: \n";
    print(lst);
    std::cout << *ret << std::endl;
    std::cout << "Expected:\n1 4 5\n4\n";

    std::cout << std::endl;
}

void test_size_and_empty() {
    std::cout << "===== Size and Empty Test =====" << std::endl;

    List<int> lst;
    std::cout << "For an Initially Empty List:\n";
    std::cout << "Initial size: " << lst.size() << "\nExpected:\n0\n";
    std::cout << "Initial empty: " << (lst.empty() ? "true" : "false") << "\nExpected: true\n";

    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(5);
    lst.push_back(6);
    std::cout << "Size after pushing back: " << lst.size() << "\nExpected: 6\n";
    std::cout << "Empty after pushing back: " << (lst.empty() ? "true" : "false") << "\nExpected: false\n";

    lst.push_front(1);
    std::cout << "Size after pushing front:  " << lst.size() << "\nExpected: 7\n";
    std::cout << "Empty after pushing front:  " << (lst.empty() ? "true" : "false") << "\nExpected: false\n";

    lst.pop_front();
    std::cout << "Size after popping front:  " << lst.size() << "\nExpected: 6\n";
    std::cout << "Empty after popping front:  " << (lst.empty() ? "true" : "false") << "\nExpected: false\n";

    lst.pop_back();
    std::cout << "Size after popping back:  " << lst.size() << "\nExpected: 5\n";
    std::cout << "Empty after popping back:  " << (lst.empty() ? "true" : "false") << "\nExpected: false\n";

    auto it = ++lst.begin();
    lst.erase(it);
    std::cout << "Size after single erase:  " << lst.size() << "\nExpected: 4\n";
    std::cout << "Empty after single erase:  " << (lst.empty() ? "true" : "false") << "\nExpected: false\n";

    auto from = lst.begin(), to = lst.end();
    lst.erase(from, to);
    std::cout << "Size after single erase:  " << lst.size() << "\nExpected: 0\n";
    std::cout << "Empty after single erase:  " << (lst.empty() ? "true" : "false") << "\nExpected: true\n";
    std::cout << std::endl;

    List<int> init_lst{1, 2, 3};
    std::cout << "For a list initialized by an initialiszer_list:\n";
    std::cout << "Initial size: " << init_lst.size() << "\nExpected: 3\n";
    std::cout << "Initial empty: " << (init_lst.empty() ? "true" : "false") << "\nExpected: false\n";

    lst = init_lst;
    std::cout << "For a list that copied from another:\n";
    std::cout << "Size: " << lst.size() << "\nExpected: 3\n";
    std::cout << "Empty: " << (lst.empty() ? "true" : "false") << "\nExpected: false\n";

}

int main() {
    
    test_copy();
    test_push_back();
    test_push_front();
    test_pop_back();
    test_pop_front();
    test_iterator();
    test_insert();
    test_erase_single();
    test_erase_range();
    test_size_and_empty();
    
    return 0;
}
