#ifndef HEAP_SORT
#define HEAP_SORT
#include <algorithm>
#include <vector>
using namespace std;


// 形式地维护一个大顶堆，以实现堆排序
template <typename Comparable>
class HeapSort {
    private :

        // 降堆操作，注意 vector 是从 0 开始标号
        static void percolateDown(vector<Comparable> &array, int hole, int size) {
            int child;
            Comparable tmp = std::move(array[hole - 1]);

            for(; (child = hole << 1) <= size; hole = child) {
                if(child != size && array[(child | 1) - 1] > array[child - 1])
                    child |= 1;
                if(array[child - 1] > tmp)
                    array[hole - 1] = std::move(array[child - 1]);
                else break;
            }
            array[hole - 1] = std::move(tmp);
        }
        static void buildHeap(vector<Comparable> &array) {
            for(int i = array.size() >> 1; i; --i)
                percolateDown(array, i, array.size());
        }


    public :

        // 首先建堆，然后依次将最大的放到序列的最后
        static void sort(vector<Comparable> &array) {
            buildHeap(array);

            for(int i = array.size() - 1; i >= 0; --i) {
                std::swap(array[0], array[i]);
                percolateDown(array, 1, i);
            }
        }
};


#endif