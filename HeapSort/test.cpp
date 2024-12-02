/********************************
 * 堆排序的测试程序
 * 
 * 采用 std::chrono 来计时
 * 
 * 采用 std::mt19937 生成随机数
 * 
 * 由于 1e6 的范围效率差别很小，我将范围开到了 3e6。
 * 
 */




#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "HeapSort.h"
using namespace std;
using namespace chrono;


constexpr size_t SIZE = 3e6;
constexpr int MAX = 1e8;

template<typename Comparable>
bool isSorted(const vector<Comparable> &arr) {
    for(size_t i = 1; i < arr.size(); ++i)
        if(arr[i - 1] > arr[i])
            return false;
    return true;
}

using tick = microseconds;
const string tickname = "microseconds";

ostream& operator<<(ostream &out, const tick time) {
    out << time.count() << ' ' << tickname;
    return out;
}
void printArray(const vector<int> arr) {
    for(const auto &x : arr)
        cout << x << ' ';
    cout << endl;
}

void print(const string& testName, const string& sortType, tick duration, bool isCorrect) {
    cout << "Sorting " << testName << " with " << sortType << " : "
         << (isCorrect ? "Correct" : "Incorrect") << " with time cost " << duration << endl;
}

tick testCustomHeapSort(const string& testName, vector<int> array) {
    auto start = high_resolution_clock::now();
    HeapSort<int>::sort(array);
    auto end = high_resolution_clock::now();
    print(testName, "Custom HeapSort", duration_cast<tick>(end - start), isSorted(array));
    return duration_cast<tick>(end - start);
}
tick testStdHeapSort(const string& testName, vector<int> array) {
    auto start = high_resolution_clock::now();
    make_heap(array.begin(), array.end());
    sort_heap(array.begin(), array.end());
    auto end = high_resolution_clock::now();
    print(testName, "std::sort_heap", duration_cast<tick>(end - start), isSorted(array));
    return duration_cast<tick>(end - start);
}

//生成随机数列
vector<int> generateRandomArray() {
    vector<int> arr(SIZE);

    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(1, MAX);

    for(size_t i = 0; i < SIZE; ++i)
        arr[i] = dist(gen);
    
    return arr;
}

// 生成有序数列
vector<int> generateOrderedArray() {
    vector<int> arr(SIZE);

    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(1, 10);
    arr[0] = dist(gen);
    for(size_t i = 1; i < SIZE; ++i)
        arr[i] = arr[i - 1] + dist(gen);

    return arr;
}

// 生成反序数列
vector<int> generateReversedArray() {
    vector<int> arr(SIZE);

    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(1, 10);
    arr[0] = 1e8 - dist(gen);
    for(size_t i = 1; i < SIZE; ++i)
        arr[i] = arr[i - 1] - dist(gen);
    
    return arr;
}

// 生成 单个元素重复出现70%及以上的数列
constexpr double DUP_COE = 0.7;
vector<int> generateSingleRepetitiveArray() {
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(0, MAX);

    vector<int> arr(SIZE);
    static size_t pos[SIZE];
    for(size_t i = 0; i < SIZE; ++i)
        pos[i] = i;
    shuffle(pos, pos + SIZE, gen);
    
    size_t DupNum = SIZE * DUP_COE;
    for(size_t i = 0; i < DupNum; ++i)
        arr[pos[i]] = MAX >> 1;
    
    for(size_t i = DupNum; i < SIZE; ++i)
        arr[pos[i]] = dist(gen);
    return arr;
}

// 生成 出现次数多于1的元素的总数多于70%的数列
vector<int> generateMultiRepetitiveArray() {
    size_t DupNum = SIZE * DUP_COE;
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist_val(0, MAX), dis_dup(2, DupNum / 2);

    vector<int> arr(SIZE);
    static size_t pos[SIZE];
    for(size_t i = 0; i < SIZE; ++i)
        pos[i] = i;
    shuffle(pos, pos + SIZE, gen);
    
    for(size_t i = 0; i < DupNum; ) {
        size_t cnt = dis_dup(gen);
        int val = dist_val(gen);
        for(size_t j = i; j < i + cnt && j < DupNum; ++j)
            arr[pos[j]] = val;
        i += cnt;
    }
    
    for(size_t i = DupNum; i < SIZE; ++i)
        arr[pos[i]] = dist_val(gen);
    return arr;
}

constexpr int REP = 5;
constexpr tick Zero = duration(duration_values<tick>::zero());

// 对随机序列的测试
void testRandomArray() {
    const string testName = "Random Array";
    cout << "---------- " << testName << " ----------" << endl;

    tick customTimeCost = Zero, stdTimeCost = Zero;
    for(int i = 1; i <= REP; ++i) {
        vector<int> arr(generateRandomArray());
        customTimeCost += testCustomHeapSort(testName, arr);
        stdTimeCost += testStdHeapSort(testName, arr);
    }
    // printArray(arr);
    cout << "For " << testName << " tests, the average time cost are as follows: \nCustom heapsort : " << customTimeCost / REP
         << "\nStd Heapsort : " << stdTimeCost / REP << endl;
}

// 对有序序列的测试
void testOrderedArray() {
    const string testName = "Ordered Array";
    cout << "---------- " << testName << " ----------" << endl;

    tick customTimeCost = Zero, stdTimeCost = Zero;
    for(int i = 1; i <= REP; ++i) {
        vector<int> arr(generateOrderedArray());
        customTimeCost += testCustomHeapSort(testName, arr);
        stdTimeCost += testStdHeapSort(testName, arr);
    }
    cout << "For " << testName << " tests, the average time costs are as follows: \nCustom heapsort : " << customTimeCost / REP
         << "\nStd Heapsort : " << stdTimeCost / REP << endl;
}

// 对反序序列的测试
void testReversedArray() {
    const string testName = "Reversed Array";
    cout << "---------- " << testName << " ----------" << endl;

    tick customTimeCost = Zero, stdTimeCost = Zero;
    for(int i = 1; i <= REP; ++i) {
        vector<int> arr(generateReversedArray());
        customTimeCost += testCustomHeapSort(testName, arr);
        stdTimeCost += testStdHeapSort(testName, arr);
    }
    cout << "For " << testName << " tests, the average time costs are as follows: \nCustom heapsort : " << customTimeCost / REP
         << "\nStd Heapsort : " << stdTimeCost / REP << endl;
}

// 对单个元素重复出现70%及以上的数列的测试
void testSingleRepetitiveArray() {
    const string testName = "SingleRepetitiveArray";
    cout << "---------- " << testName << " ----------" << endl;

    tick customTimeCost = Zero, stdTimeCost = Zero;
    for(int i = 1; i <= REP; ++i) {
        vector<int> arr(generateSingleRepetitiveArray());
        customTimeCost += testCustomHeapSort(testName, arr);
        stdTimeCost += testStdHeapSort(testName, arr);
    }
    cout << "For " << testName << " tests, the average time costs are as follows: \nCustom heapsort : " << customTimeCost / REP
         << "\nStd Heapsort : " << stdTimeCost / REP << endl;
}

//对于 出现次数多于1的元素的总数多于70%的数列 的测试
void testMultiRepetitiveArray() {
    const string testName = "MultiRepetitiveArray";
    cout << "---------- " << testName << " ----------" << endl;

    tick customTimeCost = Zero, stdTimeCost = Zero;
    for(int i = 1; i <= REP; ++i) {
        vector<int> arr(generateMultiRepetitiveArray());
        customTimeCost += testCustomHeapSort(testName, arr);
        stdTimeCost += testStdHeapSort(testName, arr);
    }
    cout << "For " << testName << " tests, the average time costs are as follows: \nCustom heapsort : " << customTimeCost / REP
         << "\nStd Heapsort : " << stdTimeCost / REP << endl;
}

int main() {
    freopen("test.out", "w", stdout);
    cout << "Comparison Between Custom Heapsort and std::sort_heap with Size = " << SIZE << endl;
    testRandomArray();
    testOrderedArray();
    testReversedArray();
    testSingleRepetitiveArray();
    testMultiRepetitiveArray();
    return 0;
}