#include <iostream>
#include "LinkedList.h" // 假设您的链表类保存在这个头文件中

void testSingleLinkedList() {
    SingleLinkedList<int> list;

    // 1. 在空链表中插入元素
    std::cout << "Inserting into empty list:" << std::endl;
    list.insert(10);
    list.printList(); // 输出: 10

    // 2. 在链表中插入多个元素
    std::cout << "Inserting more elements:" << std::endl;
    list.insert(20);
    list.insert(30);
    list.printList(); // 输出: 10 20 30

    // 3. 删除头节点
    std::cout << "Removing head node:" << std::endl;
    list.find(10);
    list.remove();
    list.printList(); // 输出: 20 30

    // 4. 删除尾节点
    std::cout << "Removing tail node:" << std::endl;
    list.find(30);
    list.remove();
    list.printList(); // 输出: 20

    // 5. 删除中间节点
    std::cout << "Inserting more elements:" << std::endl;
    list.insert(30);
    list.insert(40);
    list.printList(); // 输出: 20 30 40

    std::cout << "Removing middle node:" << std::endl;
    list.find(30);
    list.remove();
    list.printList(); // 输出: 20 40

    // 6. 查找元素
    std::cout << "Finding element 40:" << std::endl;
    if (list.find(40)) {
        std::cout << "Found 40!" << std::endl;
    } else {
        std::cout << "40 not found!" << std::endl;
    }

    // 7. 设置当前节点的值
    std::cout << "Setting current value to 25:" << std::endl;
    list.setCurrentVal(25);
    list.printList(); // 输出: 20 25

    // 8. 删除当前节点后，链表为空的情况
    std::cout << "Removing current node (20):" << std::endl;
    list.remove();
    list.printList(); // 输出: 25

    std::cout << "Removing current node (25):" << std::endl;
    list.remove();
    list.printList(); // 输出: (空链表)

    // 9. 尝试从空链表获取当前值
    try {
        std::cout << "Trying to get current value from empty list:" << std::endl;
        list.getCurrentVal();
    } catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl; // 输出异常信息
    }
}

int main() {
    testSingleLinkedList();
    return 0;
}
