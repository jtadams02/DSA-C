#include <iostream>

using namespace std; // namespace std;

template <class elmtype> // Fixed name from just T to elmtype to match with directions better :)

// Logic: (Front+Index)%cap will return the correct placement of variables

/* TODO LIST
* CircularDynamicArray(); - Y
* CircularDynamicArray(int s); - Y
* ~CircularDynamicArray(); - Y
* elmtype& operator[](int i); - Y
* void addEnd(elmtype v); - Y
* void addFront(elmtype v); - Y
* void delEnd(); -Y
* void delFront(); - Y
* int length(); -Y
* int capacity(); - Y
* void clear(); -Y
* Elmtype QuickSelect(int k); - 
* void stableSort(); - Y
* int linearSearch(elmtype e) - Y
* int binSearch(elmtype e) - Y
* void reverse() - Y
* CircularDynamicArray& operator=(const CircularDynamicArray& old) - Y
* CircularDynamicArray(const CircularDynamicArray &old) - Y
*/

// What about (front+index+cap)%cap
class CircularDynamicArray
{
    private:
        elmtype* array;
        bool isReversed; // Tracks whether or not array is reversed, will cause functions to change 
        int cap; // Maximum size of the array, will determine when to grow (Can't name it capacity lol)
        int size; // Current size in use, if size <= 25% this will cause it to shrink
        int front; // Front of the array, duh
        int back; // Back of the array, where the next value will go
        elmtype errorHandler; // Error variable, will be thrown :P

        /*
        * void grow()
        * This function will grow the array by double the previous capacity, and copy everything over, resetting the front to 0
        * Helper Function 
        */
        void grow()
        {
            // Initialize new array wiith size cap*2, do not change cap's value because
            elmtype* temp = new elmtype[cap*2];

            // Now copy all elements from the old array to the new one
            for(int i=0;i<size;i++){
                if(!isReversed){
                temp[i] = array[(front+i+cap)%cap];
                } else {
                    temp[i] = array[(back-i+cap)%cap];
                }
            }
            // Back variable should stay unchanged
            // But front variable can be reset

            delete[] array; // Delete the old array from memory
            isReversed = false; // Resets
            array = temp;
            front = 0; // Resets
            back = size-1;
            cap *= 2;
            

        }

        /*
        * void shrink()
        * This function will shrink the array by half the previous capacity, and copy everything over, resetting the front to 0
        * Helper Function 
        */
        void shrink()
        {
            // Initialize new array wiith size cap/2, do not change cap's value because we will need it
            elmtype* temp = new elmtype[cap/2];
            for(int i = 0;i<size;i++)
            {
                if(!isReversed){
                    temp[i] = array[(front+i+cap)%cap];
                } else {
                    temp[i] = array[(back-i+cap)%cap];
                }
            }

            delete[] array;
            isReversed = false;
            array = temp;
            front = 0;
            back = size - 1;
            cap = cap / 2;
        }

        // The Real implementation of quick select that won't ruin the array lol!
        elmtype realQuickSelect(CircularDynamicArray<elmtype> arr, int k)
        {

            int r = rand();
            int piv = (r%(arr.length())); // RNG BABY

            elmtype pivot = arr[piv];

            // Now we need to make the 3 empty lists L, E, G
            // L=Less Than, E=Equal Too, G=Greater Than. All according to the pivot
            CircularDynamicArray<elmtype> ll; // Spells leg lol
            CircularDynamicArray<elmtype> ee;
            CircularDynamicArray<elmtype> gg;

            for(int i=0;i<arr.length();i++)
            {
                if(arr[i]<pivot){ // if (x<pivot) add x to L;
                    ll.addEnd(arr[i]);
                } else if(arr[i]==pivot){ // else if (x==pivot) add x to E
                    ee.addEnd(arr[i]);
                } else{ // else /* (x>pivot) */ add x to G;
                    gg.addEnd(arr[i]);
                }
            }

            if(k <= ll.length()){ 
                /*if (k <= L.size)
                return Select (L, k);*/
                return realQuickSelect(ll,k);
            } else if(k<=(ll.length()+ee.length())){
                /*else if (k <= L.size + E.size)
                return pivot;*/
                return pivot;
            } else {
                //else return Select (G, k – L.size – E.size);
                return realQuickSelect(gg,k-ll.length()-ee.length());
            }


        }

        void mergeSort(int low, int high)
        {
            if(low>=high){
                return; // Returns recursively
            }


            int mid = low + ((high-low) / 2); // THIS MATH MIGHT NEED TO BE FIXED
            // The math did indeed need to be fixed lol


            mergeSort(low,mid);
            mergeSort(mid+1,high);
            // It's merging time
            merge(low,mid,high);

        }

       void merge(int left, int mid, int right)
        {
            int subArrayOne = mid - left +1;
            int subArrayTwo = right - mid;

            // Create these temp arrays for 
            elmtype *leftArray = new elmtype[subArrayOne];
            elmtype *rightArray = new elmtype[subArrayTwo];

            // Copy data to temp arrays leftArray[] and rightArray[]
            for(auto i=0;i<subArrayOne;i++)
            {
                leftArray[i] = array[revIndex(left+i)];
            }

            for(auto j=0;j<subArrayTwo;j++)
            {   
                rightArray[j] = array[revIndex(mid+1+j)];
            }

            auto indexOfSubArrayOne = 0; //Initial index of the first sub array
            auto indexOfSubArrayTwo = 0; // Initial index of the second sub array
            int indexOfMergedArray = left;

            // Merge the temp arrays back into array[left..right]
            while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
                if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
                        array[revIndex(indexOfMergedArray)] = leftArray[indexOfSubArrayOne];
                        indexOfSubArrayOne++;
                    }
                    else {
                        array[revIndex(indexOfMergedArray)] = rightArray[indexOfSubArrayTwo];
                        indexOfSubArrayTwo++;
                    }
                    indexOfMergedArray++;
                }

            // Copy the remaining elements of
            // left[], if there are any
            while (indexOfSubArrayOne < subArrayOne) {
                array[revIndex(indexOfMergedArray)] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
                indexOfMergedArray++;
            }

            // Copy the remaining elements of
            // right[], if there are any
            while (indexOfSubArrayTwo < subArrayTwo) {
                array[revIndex(indexOfMergedArray)] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
                indexOfMergedArray++;
            }
            delete[] leftArray;
            delete[] rightArray;            
        }

    public:
        /*
        Default Constructer, initializes array with capacity of 2, and size of 0
        */
        CircularDynamicArray(){
            cap = 2;
            size = 0;
            front = -1; // Honestly idk why this is neg 1 but oh well
            back = -1; // Since arr will be empty, set back to -1
            isReversed = false;
            array = new elmtype[cap]; // Constructs array with size of 2, or capacity
        }
        /*
        Constructor(int s), s = capacity of array. Array will be empty but will have the capacity of s. 
        */
        CircularDynamicArray(int s){

            cap = s;
            size = s;
            front = 0;
            back = s-1;
            isReversed = false;
            array = new elmtype[cap]; // Constructs array with size of capacity

        }

        ~CircularDynamicArray(){
            delete[] array;
        }
        /*
        * elmtype& operator[](int i)
        * Selects an element from the array at the index i which is from the user-view
        */
        elmtype& operator[](int i)
        {
            // TODO Make this work when reversed

            if ((i<0)||i>=size){ // Make sure that the selected index is valid!
                cout << "Index does not exist!" << endl;
                return errorHandler;
            } else{ // For reverse, would we just swap back with front?
                if(!isReversed){return array[(front+i+cap)%cap];} // Normal return
                else{return array[(back-i+cap)%cap];}
            }
        }

        /*
        * Copy Constructor
        * Just copies the argument to this
        */
        CircularDynamicArray(const CircularDynamicArray &prev){
            cap = prev.cap;
            size = prev.size;
            front = prev.front;
            back = prev.back;

            // Now we need to handle the new array
            array = new elmtype[cap];
            for(int i=0;i<size;i++)
            {
                array[(front+i+cap)%cap] = prev.array[(front+i+cap)%cap];
            }

            // Also maybe reverse?
            isReversed = prev.isReversed;
        }

        /*
        * operator=
        * Just another copier, essentially the same but this one will require memory changes
        */
        CircularDynamicArray& operator=(const CircularDynamicArray& prev)
        {
            cap = prev.cap;
            size = prev.size;
            front = prev.front;
            back = prev.back;

            // Now we need to make a new array?
            delete[] array;
            array = new elmtype[cap];

            for(int i=0;i<size;i++){
                array[(front+i+cap)%cap] = prev.array[(front+i+cap)%cap];
            }

            // Reverse again ig?
            isReversed = prev.isReversed;

            return *this;
        }


        /*
        * void addEnd(elmtype v)
        * This will add an element to the end of the array, it should also increase the back pointer and possibly resize
        * 
        */
        void addEnd(elmtype v)
        {
            if(size==cap){grow();} // Resize array when the size of the array reaches the cap 

            if(isReversed){ // This code will run when class is reversed 
                if(front==-1){ // If arr is empty, front will be -1 so we need to take care of this
                    array[0] = v; 
                    size++; // Increase size counter 

                    // Start pointers
                    front = 0;
                    back = 0; 
                } else { // For when the array is normal and initalized 
                    array[(front-1+cap)%cap] = v; // the Extra cap is added for padding so no negatives?? idk thats what google said
                    size++; // Increase size 
                    front = (front-1+cap)%cap; // Set back = the new value's index
                    // THIS WAS MY BUG OMG
                }
            } else { // Normal Function
                if(front==-1){ // If arr is empty, front will be -1 so we need to take care of this
                    array[0] = v; 
                    size++; // Increase size counter 
                    // Start pointers
                    front = 0;
                    back = 0; 
                } else { // For when the array is normal and initalized 
                    array[(back+1+cap)%cap] = v; // the Extra cap is added for padding so no negatives?? idk thats what google said
                    size++; // Increase size 
                    back = (back+1+cap)%cap; // Set back = the new value's index
                }
            }
        }

        /*
        * void delEnd()
        * This will "pop" the last index off the array and allow it to be overwritten by future add ends
        */
        void delEnd()
        {
            if(isReversed){ // When Reversed
                front = (front + 1 + cap) % cap;
                size--;
            }
            else{ // When normal
                back = (back - 1 + cap) % cap; 
                size--; // This essentially just pops off the back
            }
            if(((double)size)/((double)cap) <= .25){ // Shrinks array when it is a quarter full
                shrink();
                // cout << "Shrunk" << endl;
            }
        }

        /*
        * void addFront(elmtype v)
        * Adds an element to the "front" of the array, this will set the front = to the index that is placed in here
        */
       void addFront(elmtype v)
       {
            if(size==cap){grow();}

            if(isReversed){ // Run when class is reversed
                if(front==-1){ // Rare case IF array is reversed before being edited
                    array[0] = v;
                    size++;
                    back = 0;
                    front=0; // Set the pointers to 0
                } else { // I don't think the above if will ever be called but whatevs
                    array[(back+cap+1)%cap] = v;
                    size++;
                    back = (back+cap+1)%cap;
                    // I screwed up this for both im so stupid this should be BACK
                }

            } else {
                if(front==-1){ // Remember that basic arrays are declared with a negative front and back
                    array[0] = v;
                    size++;
                    back = 0;front=0; // Set the pointers to 0
                } else {
                    array[(front+cap-1)%cap] = v;
                    size++;
                    front = (front-1+cap)%cap;
                }
            }
       }

        /*
        * void delFront()
        * "Deletes" the front element of the array, moves the front index down one, reduces size
        */

        void delFront(){
            if(isReversed){ // Run when reversed
                back = (back - 1 + cap) % cap;
                size--;
            }
            else{ // Run when normal
                front = (front + 1 + cap) % cap;
                size--;
            }
            if(((double)size)/((double)cap) <= .25){
                shrink();
            }
        }

        // SEARCHES/SORTINGS 


        /*
        * int linearSearch(elmtype e)
        * Basic O(n) search function
        */
        int linearSearch(elmtype e)
        {
            // This will not work because it needs the first index from the user's pov :(
            /*int index = 0;
            for(elmtype i : array)
            {
                if(i==e){return index;}
                index++;
            }*/

            for(int i=0;i<size;i++)
            {
                if(!isReversed){ // Normal
                    if(array[(front+i+cap)%cap]==e){return i;}
                } else {
                    if(array[(back-i+cap)%cap]==e){return i;}
                }
            }
            return -1;
        }

        /*
        * int binSearch(elmtype e)
        * Binary search looking for item e
        * Will return index where e is found, otherwise will return -1 if not found
        * Thank you geeks for geeks
        */

       int binSearch(elmtype e)
       {
            int low = 0;
            int high = size-1;
            
            // Now we loop, this will not be recursive because that was a headache
            // IDK if it matters whether or not this is reversed but whatever
            if(!isReversed||isReversed){ 
                while(low<=high)
                {
                    int mid = (low+high)/2; // Maybe need to fix math?
                    // The math did need to be fixed
                    // I had (high-1) instead of just high and the -1 was not needed

                    // Check if e is the middle
                    if(array[revIndex(mid)]==e){return mid;}

                    // If e > mid, ignore left half
                    if(array[revIndex(mid)]<e){low=mid+1;}
                    // If e is smaller, ignore right
                    else{
                        high = mid-1;
                    }
                }
                // If nothing has been found, return -1
                return -1;
            } else { // TODO Add reverse part 

            }
            return -1;
       }

        /* Stable Sort
        * This will legit just call merge sort because thats the best N-LogN sort
        * Geeks for Geeks coming CLUTCH
        */
       void stableSort()
       {
            // For Merge sort I do not think it matters what front or back is lol
            mergeSort(0,size-1);
       }

        /* QuickSelect
        * elmtype QuickSelect(int k); 
        * returns the kth smallest element in the array using the quickselect algorithm. This method should choose a  pivot element at random. 
        */
       elmtype QuickSelect(int k)
       {
            // I think we'll need a temp array, quickSelect looks like it'll ruin my array
            CircularDynamicArray<elmtype> temp; // Create temporary array 
            // We'll need to make this array an exact copy 
            for(int i=0;i<size;i++)
            {
                temp.addEnd(operator[](i));
            }
            return realQuickSelect(temp,k);
       }

        /*
        int length()
            Returns the size of the array (how many indices are in use)
        */
        int length(){
            return size;
        }
        /*
        int capacity()
            Returns the capacity of the array (Maximum # of values the array can use)
        */
        int capacity(){
            return cap;
        }
        
        /*
        * void clear()
        * This essentially just resets the default constructor lol
        */
        void clear(){
            cap = 2;
            size = 0;
            front = -1; // Honestly idk why this is neg 1 but oh well
            back = -1; // Since arr will be empty, set back to -1
            isReversed = false;
            delete[] array;
            array = new elmtype[cap]; // Constructs array with size of 2, or capacity
        }

        /*
        * void reverse()
        *   Changes the value of the isReversed variable in the object - This will effect almost all operations
        */
        void reverse(){
            // We need to make it so isReversed will switch back and forth
            if(!isReversed){isReversed=true;} // If object is not reversed,, Reverse it
            else{isReversed=false;} // Else, the object is reversed and we unreverse it!
        }

        void print(){
            for(int i=0;i<size;i++)
            {
                if(!isReversed){
                    cout << array[(front+i+cap)%cap] << " ";
                } else {
                    cout << array[(back-i+cap)%cap] << " ";
                }
            }
        }

        // I am tired for writing out the stupid math so im just gonna use a damn helper function
        int revIndex(int i)
        {
            if(isReversed){ // WHEN ARRAY IS REVERSED
                return ((back-i+cap)%cap);
            } else { // When Array is NORMAL
                return ((front+i+cap)%cap);
            }
        }


};
