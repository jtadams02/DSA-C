#include "BHeap.cpp"
#include "Heap.cpp"
#include <string>
#include <random>
#include <iostream>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <stdexcept>
using namespace std;

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

char ABCrandom() {
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char tmp_s;

    tmp_s = alphanum[rand() % (sizeof(alphanum) - 1)];
    
    return tmp_s;
}


int randomInt(int low, int high)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(low,high); 
    // distribution in range [low, high] (I got frustrated with C++ rng so I looked up a better way. I understand none of this)
    return dist6(rng);
}

std::string randomString(int maxLength)
{
    int length = randomInt(1, maxLength);
    return gen_random(length);
}
void basicHeapTest()
{
      // Test Heap constructor
  Heap<int> h;
  std::cout << "Default Constructor Test:\n\tEmpty Heap built" << std::endl;

  // Test Heap constructor with array
  int arr[] = {3, 6, 8, 1, 4, 7};
  int arrSize = sizeof(arr)/sizeof(arr[0]);
  Heap<int> h2(arr, arrSize);
  std::cout << "Default Constructor Test:\n\tBuilt Heap of size " << arrSize << std::endl;

  // Test peekKey
  std::cout << "peekKey Test:\n\tExpected: 1\n\tReceived: " << h2.peekKey() << std::endl;

  // Test extractMin
  int minKey = h2.extractMin();
  std::cout << "extractMin Test:\n\tExpected: 1\n\tReceived: " << minKey << std::endl;

  // Test insert
  h2.insert(0);
  std::cout << "inserting 0...\nRunning peekKey:\n\tExpected: 0\n\tReceived: " << h2.peekKey() << std::endl;

  // Test printKey
  std::cout << "printKey Test:\n\tExpected: 0 4 3 6 8 7\n\tReceived: ";
  h2.printKey();
  std::cout << "Note: If your output is 0 3 1 6 4 8 7, extractMin is probably not properly removing" << std::endl;
  std::cout << std::endl;

  // Test destructor
  Heap<int>* h3 = new Heap<int>();
  delete h3;
  std::cout << "Destructor test passed" << std::endl;
}

void basicBHeapTest()
{
  // Test BHeap constructor
  BHeap<int> h;
  std::cout << "Default Constructor Test:\n\tEmpty BHeap built" << std::endl;

  // Test BHeap constructor with array
  int arr[] = {3, 6, 8, 1, 4};
  int arr2[] = {1, 2, 5, 9, 10, 11, 7, 14, 24, 17, 12};
  int arrSize = sizeof(arr)/sizeof(arr[0]);
  int arr2Size = sizeof(arr2)/sizeof(arr2[0]);
  BHeap<int> h2(arr, arrSize);
  std::cout << "Array Constructor Test:\n\tBuilt Heap of size " << arrSize << std::endl;

  // Test peekKey
  std::cout << "peekKey Test:\n\tExpected: 1\n\tReceived: " << h2.peekKey() << std::endl;

  // Test extractMin
  int minKey = h2.extractMin();
  std::cout << "extractMin Test:\n\tExpected: 1\n\tReceived: " << minKey << std::endl;

  // Test insert
  h2.insert(0);
  std::cout << "inserting 0...\nRunning peekKey:\n\tExpected: 0\n\tReceived: " << h2.peekKey() << std::endl;

  // Test merge
  BHeap<int> h3(arr2, arr2Size);
  h2.merge(h3);
  std::cout << "Testing Merge..." << std::endl;

  // Test printKey
  std::cout << "printKey Test:\nExpected:\nB4\n0 1 7 10 11 14 5 9 2 3 4 8 6 17 24 12\n\nReceived:" << std::endl;
  h2.printKey();

  // Test destructor
  BHeap<int>* h4 = new BHeap<int>();
  delete h4;
  std::cout << "Destructor test passed" << std::endl;
}

void bHeapRubricPrintTest()
{
    std::cout << "Rubric Tree with default constructor and insertion:" << std::endl;
    BHeap<int> test;
    //make the B3
    test.insert(25);
    test.insert(50);
    test.insert(10);
    test.insert(12);
    test.insert(4);
    test.insert(8);
    test.insert(3);
    test.insert(20);
    //make the B2
    test.insert(2);
    test.insert(15);
    test.insert(1);
    test.insert(9);
    //make the B1
    test.insert(6);
    //print em
    std::cout << "Expected output: \nB0\n6\n\nB2\n1 2 15 9\n\nB3\n3 10 25 50 12 4 8 20\n\n" << std::endl;
    std::cout << "Your output: " << std::endl;
    test.printKey();

    //now do it with an array
    std::cout << "Rubric Tree with array constructor:" << std::endl;
    int k[] = {25, 50, 10, 12, 4, 8, 3, 20, 2, 15, 1, 9, 6};
    BHeap<int> test2(k, 13);
    std::cout << "Expected output: \nB0\n6\n\nB2\n1 2 15 9\n\nB3\n3 10 25 50 12 4 8 20\n\n" << std::endl;
    std::cout << "Your output: " << std::endl;
    test2.printKey();
}

void veryLargeHeapInt()
{
    const int BIG_SIZE = 1000000;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,BIG_SIZE * 3); //randomness stuff
    cout << "Generating Big Heap..." << endl;
    Heap<int> heap;
    for (int i = 0; i < BIG_SIZE; i++) {
        int num = dist6(rng);
        heap.insert(num);
    }
    heap.printKey();
    cout << "Min value: " << heap.peekKey() << endl;
    cout << "Extracting min..." << endl;
    int minVal = heap.extractMin();
    cout << "Extracted min value: " << minVal << endl;
    cout << "Min value after extraction: " << heap.peekKey() << endl;
    cout << "Testing copy constructor..." << endl;
    Heap<int> copyHeap(heap);
    cout << "Min value in copy: " << copyHeap.peekKey() << endl;
    cout << "Testing assignment operator..." << endl;
    Heap<int> assignHeap;
    assignHeap = heap;
    cout << "Min value in assigned heap: " << assignHeap.peekKey() << endl;
}

void veryLargeHeapString()
{
    cout << "Generating Big Heap..." << endl;
    const int BIG_SIZE = 1000000;
    Heap<std::string> heap;
    for (int i = 0; i < BIG_SIZE; i++) {
        string toInsert = gen_random(5);
        heap.insert(toInsert);
    }
    heap.printKey();
    cout << "Min value: " << heap.peekKey() << endl;
    cout << "Extracting min..." << endl;
    string minVal = heap.extractMin();
    cout << "Extracted min value: " << minVal << endl;
    cout << "Min value after extraction: " << heap.peekKey() << endl;
    cout << "Testing copy constructor..." << endl;
    Heap<std::string> copyHeap(heap);
    cout << "Min value in copy: " << copyHeap.peekKey() << endl;
    cout << "Testing assignment operator..." << endl;
    Heap<std::string> assignHeap;
    assignHeap = heap;
    cout << "Min value in assigned heap: " << assignHeap.peekKey() << endl;
}

void veryLargeBHeapInt()
{
    const int BIG_SIZE = 1000;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,BIG_SIZE * 3); //randomness stuff
    cout << "Generating Big BHeap..." << endl;
    BHeap<int> heap;
    for (int i = 0; i < BIG_SIZE; i++) {
        int num = dist6(rng);
        heap.insert(num);
    }
    heap.printKey();
    cout << "Min value: " << heap.peekKey() << endl;
    cout << "Extracting min..." << endl;
    int minVal = heap.extractMin();
    cout << "Extracted min value: " << minVal << endl;
    cout << "Min value after extraction: " << heap.peekKey() << endl;
    cout << "Testing copy constructor..." << endl;
    BHeap<int> copyHeap(heap);
    cout << "Min value in copy: " << copyHeap.peekKey() << endl;
    cout << "Testing assignment operator..." << endl;
    BHeap<int> assignHeap;
    assignHeap = heap;
    cout << "Min value in assigned heap: " << assignHeap.peekKey() << endl;
}

void veryLargeBHeapString()
{
    const int BIG_SIZE = 1000;
    cout << "Generating Big BHeap..." << endl;
    BHeap<std::string> heap;
    for (int i = 0; i < BIG_SIZE; i++) {
        string toInsert = gen_random(5);
        heap.insert(toInsert);
    }
    heap.printKey();
    cout << "Min value: " << heap.peekKey() << endl;
    cout << "Extracting min..." << endl;
    std::string minVal = heap.extractMin();
    cout << "Extracted min value: " << minVal << endl;
    cout << "Min value after extraction: " << heap.peekKey() << endl;
    cout << "Testing copy constructor..." << endl;
    BHeap<std::string> copyHeap(heap);
    cout << "Min value in copy: " << copyHeap.peekKey() << endl;
    cout << "Testing assignment operator..." << endl;
    BHeap<std::string> assignHeap;
    assignHeap = heap;
    cout << "Min value in assigned heap: " << assignHeap.peekKey() << endl;
}

void hugeMerge()
{
    const int BIG_SIZE = 1000;
    cout << "Generating Big BHeap..." << endl;
    BHeap<std::string> heap;
    for (int i = 0; i < BIG_SIZE; i++) {
        string toInsert = gen_random(6);
        heap.insert(toInsert);
    }
    cout << "Generating Another Big BHeap..." << endl;
    BHeap<std::string> heap2;
    for (int i = 0; i < BIG_SIZE; i++) {
        string toInsert = gen_random(6);
        heap2.insert(toInsert);
    }
    cout << "Merging Them" << endl;
    heap.merge(heap2);
    heap.printKey();
    cout << "Min value: " << heap.peekKey() << endl;


}

void randomBullshitHeap()
{
    const int STARTING_SIZE = 15;
    char arr[STARTING_SIZE];
    for (int i = 0; i < STARTING_SIZE; i++)
    {
        arr[i] = ABCrandom();
    }
    Heap<char>* heap = new Heap(arr, STARTING_SIZE);
    heap->printKey();
    const int RANDOM_CYCLES = 100;
    int dice;
    for (int i = 0; i < RANDOM_CYCLES; i++)
    {
        dice = randomInt(1, 9);
        char query = ABCrandom();
        switch (dice)
        {
            case 1: case 2:
            {
                std::cout << "Inserting " << query << "..." << std::endl;
                heap->insert(query);
                break;
            }
            case 3: case 4:
            {
                std::cout << "Extracting Min..." << std::endl;
                std::cout << "Extract yields " << heap->extractMin() << std::endl; 
                break;
            }
            case 5: case 6:
            {
                std::cout << "Peeking Key..." << std::endl;
                std::cout << "Peek yields " << heap->peekKey() << std::endl; 
            }
            case 7: 
            {
                std::cout << "Deleting Heap..." << std::endl;
                delete heap;
                std::cout << "Default Constructing Heap..." << std::endl;
                heap = new Heap<char>();
                for (int i = 0; i < STARTING_SIZE; i++)
                {
                    heap->insert(ABCrandom());
                }
                break;
            }
            case 8:
            {
                std::cout << "Testing CopyCon..." << std::endl;
                Heap<char> copyHeap(*heap);
                std::cout << "printKey of copied Heap:" << std::endl;
                copyHeap.printKey();
                break;
            }
            case 9:
            {
                std::cout << "Testing Copy=..." << std::endl;
                Heap<char> copyHeap;
                copyHeap = *heap;
                std::cout << "printKey of copied Heap:" << std::endl;
                copyHeap.printKey();
                break;
            }
            default:
                break;
        }
        heap->printKey();
    }
}

void randomBullshitBHeap()
{
    const int STARTING_SIZE = 15;
    char arr[STARTING_SIZE];
    for (int i = 0; i < STARTING_SIZE; i++)
    {
        arr[i] = ABCrandom();
    }
    BHeap<char>* heap = new BHeap<char>(arr, STARTING_SIZE);
    heap->printKey();
    const int RANDOM_CYCLES = 100;
    int dice;
    for (int i = 0; i < RANDOM_CYCLES; i++)
    {
        dice = randomInt(1, 10);
        char query = ABCrandom();
        switch (dice)
        {
            case 1: case 2:
            {
                std::cout << "Inserting " << query << "..." << std::endl;
                heap->insert(query);
                break;
            }
            case 3: case 4:
            {
                std::cout << "Extracting Min..." << std::endl;
                std::cout << "Extract yields " << heap->extractMin() << std::endl; 
                break;
            }
            case 5: case 6:
            {
                std::cout << "Peeking Key..." << std::endl;
                std::cout << "Peek yields " << heap->peekKey() << std::endl; 
            }
            case 7: 
            {
                std::cout << "Deleting Heap..." << std::endl;
                delete heap;
                std::cout << "Default Constructing Heap..." << std::endl;
                heap = new BHeap<char>();
                for (int i = 0; i < STARTING_SIZE; i++)
                {
                    heap->insert(ABCrandom());
                }
                break;
            }
            case 8:
            {
                std::cout << "Testing CopyCon..." << std::endl;
                BHeap<char> copyHeap(*heap);
                std::cout << "printKey of copied Heap:" << std::endl;
                copyHeap.printKey();
                break;
            }
            case 9: 
            {
                std::cout << "Testing Copy=..." << std::endl;
                BHeap<char> copyHeap;
                copyHeap = *heap;
                std::cout << "printKey of copied Heap:" << std::endl;
                copyHeap.printKey();
                break;
            }
            case 10: 
            {
                std::cout << "Testing Merge..." << std::endl;
                BHeap<char>* mergeHeap = new BHeap<char>();
                for (int i = 0; i < STARTING_SIZE; i++)
                {
                    mergeHeap->insert(ABCrandom());
                }
                std::cout << "printKey of Heap to merge:" << std::endl;
                mergeHeap->printKey();
                heap->merge(*mergeHeap);
                std::cout << "Heaps merged!\nprintKey of consumed Heap (should be an empty line):" << std::endl;
                mergeHeap->printKey();
                std::cout << std::endl;
                std::cout << "--- Merge Complete ---" << std::endl;
                break;
            }
            default:
                break;
        }
        heap->printKey();
    }
}




void printMenu()
{
    std::cout << "OPTIONS:\n\n-2: Stop\n-1: Menu\n0: All\n1: Basic Heap Tester\n2: Lots of random ints in a Heap\n3: Lots of random strings in a Heap\n4: RandomBullShitGo for a Heap" << std::endl;
    std::cout << "5: Basic BHeap Tester\n6: Tester for BHeap print that creates the exact tree drawn in the rubric\n7: Lots of random ints in a BHeap\n8: Lots of random strings in a BHeap" << std::endl;
    std::cout << "9: A merge of two massive string BHeaps\n10: RandomBullShitGo for a BHeap" << std::endl;

    std::cout << "\nNOTES:\n" << std::endl;
    std::cout << "- Please tweak the BIG_SIZE values in the methods with big datasets, higher for better stress tests and lower for better readablity" << std::endl;
    std::cout << "- RandomBullShit can segfault sometimes if you get really unlucky and it tries to ExtractMin from an empty heap (both kinds). This seems unavoidable since we aren't required a size() method" << std::endl;
    std::cout << "- Hope this tester helps! :) Please let me (Robert Powell) know on groupme if you have any issues !" << std::endl;
    /*
    1 basicHeapTest();
    2 veryLargeHeapInt();
    3 veryLargeHeapString();
    4 randomBullshitHeap();
    5 basicBHeapTest();
    6 bHeapRubricPrintTest();
    7 veryLargeBHeapInt();
    8 veryLargeBHeapString();
    9 hugeMerge();
    10 randomBullshitBHeap();
    */
}

int main()
{
    const int METHOD_COUNT = 10;
    bool done = false;
    while (!done)
    {
        std::cout << "Enter a number to select a tester, -1 for the Menu" << std::endl;
        int methodNum;
        std::string input;
        std::cin >> input;
        try{
            methodNum = std::stoi(input);
            if (!(-2 <= methodNum && methodNum <= METHOD_COUNT)) throw std::out_of_range("no");
        }
        catch(std::invalid_argument)
        {
            cout << "\nPlease enter an integer value.\n";
            std::cin.clear();
            continue;
        }
        catch(std::out_of_range)
        {
            cout << "\nPlease enter an value from -2 - " << METHOD_COUNT << "\n";
            methodNum = -3;
            std::cin.clear();
            continue;
        }
        switch (methodNum)
        {
        case -2:
            done = true;
            break;
        case -1:
            printMenu();
            break;
        case 0:
            basicHeapTest();
            veryLargeHeapInt();
            veryLargeHeapString();
            randomBullshitHeap();
            basicBHeapTest();
            bHeapRubricPrintTest();
            veryLargeBHeapInt();
            veryLargeBHeapString();
            hugeMerge();
            randomBullshitBHeap();
            break;
        case 1:
            basicHeapTest();
            break;
        case 2:
            veryLargeHeapInt();
            break;
        case 3:
            veryLargeHeapString();
            break;
        case 4:
            randomBullshitHeap();
            break;
        case 5:
            basicBHeapTest();
            break;
        case 6:
            bHeapRubricPrintTest();
            break;
        case 7:
            veryLargeBHeapInt();
            break;
        case 8:
            veryLargeBHeapString();
            break;
        case 9:
            hugeMerge();
            break;
        case 10:
            randomBullshitBHeap();
            break;
        default:
            break;
        }
    }
}