#include <iostream>

using namespace std;
// (frontIndex+lastIndex)%cap
// What is this?
// This is our way of relatively sorting our indices in user view
// In reality, the indices are all added to the back of our array, there is no
// O(1) way to add something to the front in the way that we are doing
// So, we need a equation to allow us to output these values in the order that the user wants
// This equation does that, it takes the remainder of the frontIndex and the LastIndex divided by the capacity
// So, if Cap = 5, F=0, and lastIndex = 2, % 5 = 2. So, the number will be placed
// At index 2 when doing add end. If we do add front, Cap=5, F=0, and L=3.%5=3
// The index will be placed in slot 3. But then, how do we get to 
template<typename T>
class CircularDynamicArray 
{ 
    public: 
        bool isReversed; // Easy solution, when reversed, just use a boolean to have functions
        // Do other things. Genius ik. 
        int cap; // Capacity of Array
        int frontIndex; // This sill be the first index, the head
        int lastIndex; // This will denote the next possible empty index, and we can then check if this next index is > cap
        T tp; // Template that will determine type? idk
        T *ap; // Array Pointer
        T error; // Dummy Array to return an error
        

        CircularDynamicArray()
        {
            cap = 2;
            frontIndex=0;
            lastIndex=0;
            ap = new T[cap];
            isReversed = false;
        }

        // Constructor that will actually be used!
        CircularDynamicArray(int i)
        {
            cap = i;
            ap = new T[cap];
            lastIndex = i;
            frontIndex = 0;
            isReversed = false;
        }
        ~CircularDynamicArray()
        {
            delete [] ap;
        }

        //Copy Constructor a
        CircularDynamicArray(const CircularDynamicArray<T>& c1)
        {
            cap = c1.cap;
            frontIndex = c1.frontIndex;
            lastIndex = c1.lastIndex;
            tp = c1.tp;
            error = c1.error;
            isReversed = c1.isReversed;

            ap = new T[cap];
            for(int i=0;i<lastIndex;i++)
            {
                ap[i] = c1.ap[i];
            }   

        }

        //Copy Assignment
        CircularDynamicArray& operator=(const CircularDynamicArray& c1)
        {
            cap = c1.cap;
            lastIndex = c1.lastIndex;
            frontIndex = 0;
            tp=c1.tp;
            error=c1.error;
            isReversed = c1.isReversed;

            ap = new T[cap];
            for(int i=0;i<lastIndex;i++)
            {
                ap[i] = c1.ap[i];
            }   

            return *this;
        }

        T& operator[] (int index)
        {
            if(isReversed)
            {
                // We need to acess the reversed index
                // To find it, we subtract our index from the lastindex-1
                index = (lastIndex-1)-index;
            }

            // check if the index is in the range of the array capacity, if it is print error (NOT FOR PROD)
            if(index>=lastIndex)
            {
                // Error msg
                cout << "Operator access out of bounds" << endl;
                return error;
            } else 
            {
                return ap[(frontIndex+index)%cap];
            }

           /* 
            if(index>lastIndex&&index<cap)
            {
                lastIndex = index + 1;
            }
            return *(ap + index);
            */
        }

        

        // Print Array - Used for testing
        void print()
        {
            if(isReversed)
            {
                if(lastIndex==0){cout<<"Array is empty!"<<endl;return;}
                if(lastIndex==1){cout<<"["<< ap[lastIndex-1]<<"]"<<endl;return;}
                cout << "[";
                for(int i=lastIndex-1;i>0;i--)
                {
                    cout << ap[(frontIndex+i)%cap] <<", ";
                }
                cout << ap[(frontIndex+0)%cap] << "]" << endl;
                return;
            }
            if(lastIndex==0){cout<<"Array is empty!"<<endl;return;}
            if(lastIndex==1){cout<<"["<< ap[lastIndex-1]<<"]"<<endl;return;}
            cout << "[";
            for(int i=0 ;i<lastIndex-1;i++)
            {
                cout << ap[(frontIndex+i)%cap] <<", ";
            }
            cout << ap[(frontIndex+lastIndex-1)%cap] << "]" << endl;
        }

        void addEnd(T t)
        {
            if(isReversed){revAddFront(t);}else{
            // Check if the next index will be in the bounds of the array
            if(lastIndex>=cap)
            {
                // Recap array
                cap = cap*2; // set new cap
                T *np = new T[cap]; // np= new pointer to an array
                
                for(int i=0;i<lastIndex;i++)
                {
                    np[i] = ap[(frontIndex+i)%(cap/2)];
                }
                delete[] ap;
            //    cout<<"Resizing array to cap: " << cap << endl;
                ap = np;
                frontIndex = 0;
           //     cout << "Array recapd" << endl;
            }
            // FrontIndex+LastIndex%cap = How much is left behind when divided by the capacity. ie: With a Head of 0, and 2 elements in the array
            // Last index = 3, 0+3%5 is 0 with 3 remaining
          //  cout <<"Head: "<<frontIndex<<" + End: " << lastIndex << " \%Cap: "<<cap<<" is: "<<(frontIndex+lastIndex)%cap<<endl;
            ap[(frontIndex+lastIndex)%cap] = (T) t;
            lastIndex++;
            }
        }

        void revAddEnd(T t)
        {
            // Check if the next index will be in the bounds of the array
            if(lastIndex>=cap)
            {
                // Recap array
                cap = cap*2; // set new cap
                T *np = new T[cap]; // np= new pointer to an array
                
                for(int i=0;i<lastIndex;i++)
                {
                    np[i] = ap[(frontIndex+i)%(cap/2)];
                }
                delete[] ap;
            //    cout<<"Resizing array to cap: " << cap << endl;
                ap = np;
                frontIndex = 0;
            //    cout << "Array recapd" << endl;
            }
            // FrontIndex+LastIndex%cap = How much is left behind when divided by the capacity. ie: With a Head of 0, and 2 elements in the array
            // Last index = 3, 0+3%5 is 0 with 3 remaining
          //  cout <<"Head: "<<frontIndex<<" + End: " << lastIndex << " \%Cap: "<<cap<<" is: "<<(frontIndex+lastIndex)%cap<<endl;
            ap[(frontIndex+lastIndex)%cap] = (T) t;
            lastIndex++;
        }

        void delEnd()
        {
            if(isReversed){revDelFront();}else{
            int delIndex = lastIndex-1; // Sets the index to be delete the last one with a value
            // I do not think I need to do anything fancy, just knock the index backwards
            // and ignore whatever was there
            lastIndex = delIndex;
            // (head+size-1)%cap = This place, but we don't need that

            //check if array needs to be resized, if it does then resize it
            if(((double)(lastIndex-frontIndex)/(double)cap)<=.25)
            {
                //Shrink the array, shrink to an even number?
                //if(cap%2!=0){cap++;} // Make sure that cap is an even number!
                cap/=2;
                T *np = new T[cap];

                for(int i=frontIndex;i<lastIndex;i++)
                {
                    np[i] = ap[i];
                }
                delete [] ap;
               // cout << "Shrinking array to cap: " << cap << endl;
                ap = np;
               // cout << "Array Shrunk" << endl;
            }
            }
        }

        void revDelEnd()
        {
            int delIndex = lastIndex-1; // Sets the index to be delete the last one with a value
            // I do not think I need to do anything fancy, just knock the index backwards
            // and ignore whatever was there
            lastIndex = delIndex;
            // (head+size-1)%cap = This place, but we don't need that

            //check if array needs to be resized, if it does then resize it
            if(((double)(lastIndex-frontIndex)/(double)cap)<=.25)
            {
                //Shrink the array, shrink to an even number?
                //if(cap%2!=0){cap++;} // Make sure that cap is an even number!
                cap/=2;
                T *np = new T[cap];

                for(int i=frontIndex;i<lastIndex;i++)
                {
                    np[i] = ap[i];
                }
                delete [] ap;
               // cout << "Shrinking array to cap: " << cap << endl;
                ap = np;
               // cout << "Array Shrunk" << endl;
            }
        }

        void delFront()
        {   
            if(isReversed){revDelEnd();}else{
            frontIndex=(frontIndex+1)%cap;
            lastIndex--;

            if(((double)(lastIndex-frontIndex))/cap<=.25)
            {
                if (cap==0) return;
                int nc = cap/2;
                T *np = new T[nc];

                for (int i=0;i<cap;i++) {
                    np[i] = ap[((frontIndex+i)%cap)];
                }
                delete [] ap;
                cap=nc;
               // cout << "Shrinking array to cap: " << cap << endl;
                ap=np;
               // cout << "Array Shrunk" << endl;


               // Reset the front Index 
               frontIndex=0;

            }
            }
        }

        void revDelFront()
        {   
            frontIndex=(frontIndex+1)%cap;
            lastIndex--;

            if(((double)(lastIndex-frontIndex))/cap<=.25)
            {
                if (cap==0) return;
                int nc = cap/2;
                T *np = new T[nc];

                for (int i=0;i<cap;i++) {
                    np[i] = ap[((frontIndex+i)%cap)];
                }
                delete [] ap;
                cap=nc;
               // cout << "Shrinking array to cap: " << cap << endl;
                ap=np;
               // cout << "Array Shrunk" << endl;


               // Reset the front Index 
               frontIndex=0;

            }
        }

        void addFront(T t)
        {
            if(isReversed){revAddEnd(t);}else{
            if(lastIndex>=cap)
            {
                grow();
            }

            frontIndex = (frontIndex+cap-1)%cap;
           // cout << "Front index is: "<< "0" << ", cap-1 is: " << cap-1<< ", and the remainer is:  "<<frontIndex<< endl;
            ap[frontIndex] = (T) t;
            lastIndex++;
            }

        }

        void revAddFront(T t)
        {
            if(lastIndex>=cap)
            {
                grow();
            }

            frontIndex = (frontIndex+cap-1)%cap;
            //cout << "Front index is: "<< "0" << ", cap-1 is: " << cap-1<< ", and the remainer is:  "<<frontIndex<< endl;
            ap[frontIndex] = (T) t;
            lastIndex++;

        }

        void grow()
        {
                // Recap array
                cap = cap*2; // set new cap
                T *np = new T[cap]; // np= new pointer to an array
                
                for(int i=0;i<lastIndex;i++)
                {
                    np[i] = ap[(frontIndex+i)%(cap/2)];
                }
                delete[] ap;
                //cout<<"Resizing array to cap: " << cap << endl;
                ap = np;
                frontIndex = 0;
              //  cout << "Array recapd" << endl;
        }

       
        
        // Reset that damn array
        void clear()
        {
            delete [] ap;
            
            cap = 2;
            ap = new T[cap];
            lastIndex = 0;
            frontIndex = 0;
            isReversed=false;


        }

        // Length and Size 
        int length() //  Size of the Array
        {
            return lastIndex;
        }

        int capacity() // cap
        { 
            return cap;
        }


        // SORTING ALGOS LOL
        /*
        * QuickSelect Algorithm
        * This function will find the k-smallest element in the array
        * I pray this works. Probably will use a copy of the array
        */
       void swap(T arr[],int i,int j)
          {
                  T x;
                  x=arr[i];
                  arr[i]=arr[j];
                  arr[j]=x;
          }

        int partition(T arr[], int low, int high)
        {
            T pivot = arr[high];
            int i = (low - 1);
            for (int j = low; j <= high - 1; j++) {
                if (arr[j] <= pivot) {
                    i++;
                    swap(arr,arr[i], arr[j]);
                }
            }
            swap(arr,arr[i + 1], arr[high]);
            return (i + 1);
        }

        T QuickSelect(int k)
        {
            T *temp = new T[lastIndex];
            temp = ap;

            T output = realQuickSel(temp,0,lastIndex-1,k);
            return output;
            delete [] temp;
            
        }

        T realQuickSel(T a[],int left, int right, int k)
        {
            while (left <= right) {
            
                    // Partition a[left..right] around a pivot
                    // and find the position of the pivot
                    int pivotIndex = partition(a, left, right);
            
                    // If pivot itself is the k-th smallest element
                    if (pivotIndex == k - 1)
                        return a[pivotIndex];
            
                    // If there are more than k-1 elements on
                    // left of pivot, then k-th smallest must be
                    // on left side.
                    else if (pivotIndex > k - 1)
                        right = pivotIndex - 1;
            
                    // Else k-th smallest is on right side.
                    else
                        left = pivotIndex + 1;
                }
                return -1;
        }

        
        /*
        * Merge Sort
        * O(n log n) time
        * 
        */
        void stableSort()
        {
            // after experimentation, turns out this is just gonna be a dummy 
            // function to call another. why? because it works better lol
            realMergeSort(0,lastIndex-1);

        }

        // This is the actual merge sort which will take arguments
        // Arguments represent which indexes to look at in the array
        void realMergeSort(int start, int end)
        {
           if (start < end) {
                // find midpoint
                int m = (start + end) / 2;

                /* recurcive mergesort first
        and second halves */
                realMergeSort(start, m);
                realMergeSort(m + 1, end);

                // merge
                merge(start,m,end);
            }
        }

        // Merging portion of the sort
        void merge(int first, int mid, int last)
        {
                T* temp = new T[last - first + 1];

                int first1 = first;
                int last1 = mid;
                int first2 = mid + 1;
                int last2 = last;
                int i = 0;

                while (first1 <= last1 && first2 <= last2) {
                    if (ap[(frontIndex+first1)%cap] < ap[(frontIndex+first2)%cap]) {
                        temp[i] = ap[(frontIndex+first1)%cap];
                        first1++;
                    }
                    else {
                        temp[i] = ap[(frontIndex+first2)%cap];
                        first2++;
                    }
                    i++;
                }
                
                while (first1 <= last1) {
                    temp[i] = ap[(frontIndex+first1)%cap];
                    first1++;
                    i++;
                }

                while (first2 <= last2) {
                    temp[i] = ap[(frontIndex+first2)%cap];
                    first2++;
                    i++;
                }
                
                for (int k = first; k <= last; k++) {
                    ap[(frontIndex+k)%cap] = temp[k-first];
                }
                delete[] temp;

        }


        // Linear Search
        // O(size) search
        // The most basic type of search function
        // Quite slow when there is a lot of daya
        int linearSearch(T value)
        {
            for(int i=0;i<lastIndex;i++)
            {
                if(value==ap[(frontIndex+i)%cap])
                {
                    return i;
                }
            }
            return -1;
        }

        /*
        *BinSearch
        * Performs a binary search of the array looking for the item e.  
        * Returns the index of the item if found or -1 otherwise.  
        * This method assumes that the array is in increasing order, but there is no guarantee that the sort method has been called.
        * This function will just be a helperfunction to the real binary search
        */
       int binSearch(T value)
       {
            int x = realBinSearch(value,0,lastIndex-1);
            return x;
       }

       int realBinSearch(T x, int low, int high)
       {
            while (low <= high) {
            int mid = low + (high - low) / 2;

            if (ap[mid] == x)
            return mid;

            if (ap[mid] < x)
            low = mid + 1;

            else
            high = mid - 1;
        }

        return -1;
        }



        // Flag the array to be reversed.
       void reverse()
       {
            if(isReversed){isReversed=false;return;}
            if(!isReversed){isReversed=true;return;}
       }


};