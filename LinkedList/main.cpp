#include <iostream>
#include "LinkedList.h" 


int main() {
    SingleLinkedList<int> list_1{1, 2, 3, 4, 5}, list_3;
    SingleLinkedList<int> list_2(list_1);
    list_3 = list_3 = list_2;

    std::cout << "List 1 : " << std::endl;
    list_1.printList(); // Initialization Test

    std::cout << "List 3 : " << std::endl;
    list_3.printList(); // Self-assertion Test

    /*Part 1*/

    if(list_1.find(3)) {
        std::cout << "Found 3" << std::endl;
        std::cout << list_1.getCurrentVal() << std::endl; // getCurrentVal Test
        list_1.setCurrentVal(5);
        std::cout << list_1.getCurrentVal() << std::endl;
        list_1.printList(); // setCurrentVal Test
    }

    /*Part 2*/
    std::cout << "List 2 : " << std::endl;
    list_2.printList(); // Deep Copy Test

    if(list_2.find(3)) {
        list_2.insert(8);
        list_2.printList(); // Insertion Test
        list_2.insert(7);
        list_2.insert(6); // Continuous Insertion Test
        list_2.printList();
        list_2.find(5);
        list_2.insert(9); // Insertion at the tail Test
        list_2.printList();
    }

    /*Part 3*/
    std::cout << "List 3 : " << std::endl;
    list_3.printList();
    if(list_3.find(4)) {
        list_3.remove();
        list_3.printList();
        std::cout << "After removing 4, the pointer is now at the position of " << list_3.getCurrentVal() << std::endl; // Removal Test
        list_3.find(2);
        list_3.remove();
        list_3.remove();
        list_3.printList();
        std::cout << "After removing 2 and 3 continuously, the pointer is now at the position of " << list_3.getCurrentVal() << std::endl; // Continuous removal Test
        list_3.find(1);
        list_3.remove();
        list_3.printList(); // Removal at the head Test
    }

    SingleLinkedList<double> dlist;

    // dlist.setCurrentVal(); 
    // dlist.getCurrentVal(); // Invalid operation test
    
    dlist.insert(1.0);
    dlist.insert(3.0);
    dlist.insert(2.0);
    dlist.insert(4.0);
    dlist.find(3.0);
    dlist.remove();
    dlist.setCurrentVal(5.0);
    dlist.insert(6.0);
    dlist.remove();
    dlist.printList();
    dlist.find(2.0);
    dlist.setCurrentVal(8.1);
    dlist.printList();


    return 0;
}

/*Expected Output :
List 1 :
1       2       3       4       5
List 3 :
1       2       3       4       5
Found 3
3
5
1       2       5       4       5
List 2 :
1       2       3       4       5
1       2       3       8       4       5
1       2       3       8       7       6       4       5
1       2       3       8       7       6       4       5       9
List 3 :
1       2       3       4       5
1       2       3       5
After removing 4, the pointer is now at the position of 5
1       5
After removing 2 and 3 continuously, the pointer is now at the position of 5
5
1       5       4
1       5       8.1
*/