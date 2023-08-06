#include <iostream>
#include "CircularDynamicArray.cpp"

using namespace std;

int main(){
    //(front+index)%cap
    CircularDynamicArray<int> s;
    cout << s.capacity() << endl;
    while(1){
        s.print();
        cout << endl;
        cout << "Enter a number: ";
        int x;
        cin >> x; 
        
        if(x==1){
            cout << "Enter a number to add: ";
            int y;
            cin >> y;
            s.addEnd(y);
        }else if(x==2){
            s.delEnd();
        }else if(x==3){
            cout << "Enter a number to add: ";
            int y;
            cin >> y;
            s.addFront(y);
        }else if(x==4){
            s.delFront();
        }else if(x==5){
            cout << "Lets linearly search for a number!" << endl;
            cout << "What number should we search for: ";
            int y;
            cin >> y;
            int index = s.linearSearch(y);
            if(index==-1){cout<<"Sorry, that element was not found :("<<endl;}
            else{cout<<"Number "<<y<<" was found at index: "<<index<<endl;}
        }else if(x==-1){
            s.reverse();
        }else if(x==-5){
            int len = s.length();
            for(int i=len;i<len+50;i++){
                s.addEnd(i);
            }
        }else if(x==10){
            s.stableSort();
            cout << "Sorted!" << endl;
        }else if(x==0){
            // Opps
             cout << "Operator[] Time!" << endl;
             cout << "Please enter the index you would like to edit: ";
             int y;
             cin >> y;
             cout << "\nThe current value of that index is: " << s[y] << "\nWhat would you like to change it too: ";
             int z;
             cin >> z;
             s[y] = z;
             cout <<"\nChanged!";
             cout << endl;
        }else{
            break;
        }
    }

}
