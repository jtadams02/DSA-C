#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "BHeap.cpp"
#include "Heap.cpp"

using namespace std;

#define BIG_SIZE 100000 // Change me for smaller/larger heaps.
#define STRING_SIZE 10  // Change me for shorter/longer strings.
#define CHARS "abcdefghijklmnopqrstuvwxyz"

void randomize(int &i) {
    i = rand();
}

void randomize(string &s) {
    s = string(STRING_SIZE, 0);
    for (int i = 0; i < STRING_SIZE; i++) 
        s[i] = CHARS[rand() % (sizeof(CHARS) - 1)];
}

template<typename T, template<typename> class HeapType>
void testBigHeap() {
    T min, *arr = new T[BIG_SIZE];
    for (int i = 0; i < BIG_SIZE; i++)
        randomize(arr[i]);

    HeapType<T> heap(arr, BIG_SIZE);

    // Sort array, then extract min from the heap until empty.
    // If an i'th extract min is not equal to the i'th element of
    // the array, then something went wrong.
    sort(arr, arr + BIG_SIZE);
    for (int i = 0; i < BIG_SIZE; i++) {
        min = heap.extractMin();
        if(i==34464){
            heap.print();
        }
        if (min != arr[i]) {
            stringstream ss;
            ss << "Failed at i = " << i << "!\n";
            ss << "   Expected: " << arr[i] << '\n';
            ss << "   Got: " << min;            
            throw logic_error(ss.str());
        }
    }
    
    delete[] arr;
}

int main(int argc, char* argv[]) {   
    try {
        if (argc < 2) throw invalid_argument("argc < 2");
        srand(stoi(argv[1]));
    } catch (const invalid_argument &e) {
        cout << "Invalid/No seed given. Using 0." << endl;
        srand(0);
    }

    /**
     * Comment out tests if you only want to test certain ones.
     * 
     * IMPORTANT: Skipping certain tests will mess with randomness, even
     * if you pass the same seed. In other words, if you fail a test, 
     * then comment out the other tests to isolate the one that failed,
     * the behavior will not be the same.
     * 
     * If you want to test with a type other than int or string,
     * you must also overload the randomize() your type.
    */
    
    // cout << "Testing with Heap<int>... " << flush;
    // testBigHeap<int, Heap>();
    // cout << "Success!" << endl;

    // cout << "Testing with Heap<string>... " << flush;
    // testBigHeap<string, Heap>();
    // cout << "Success!" << endl;

    cout << "Testing with BHeap<int>... " << flush;
    testBigHeap<int, BHeap>();
    cout << "Success!" << endl;

    cout << "Testing with BHeap<string>... " << flush;
    testBigHeap<string, BHeap>();
    cout << "Success!" << endl;

    return 0;
}
