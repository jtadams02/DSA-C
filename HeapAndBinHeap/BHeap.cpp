#include <iostream>

using namespace std;

template<class keytype>
class BHeap{
    private:
    // Node struct
    struct BNode {
        keytype key;
        int degree; // # of children, IDK if this is needed
        BNode *parent;
        BNode *child; // Points to the left most child
        BNode *sibling; // Points to the right sibling of the child
    };

   // BHeap *head; // Points to the first BHeap
   // BHeap *sibling; // Points to next BHeap

    BNode *minNode; // This will point to the smallest node
    BNode *headNode; // IDK what we need yet so this should point to the Bnode that is the head? idk
    
    int treeSize;

    // Helper Functions
    void destroy_tree(BHeap n) {
    }

    void printHeap(){

    }
    
    BNode* makeBinomialHeap(){
        BNode *x = new BNode();
        return x;

    }

    BNode* binomialHeapMinimum(BHeap *H){
        BNode *y;

        BNode *x = H->headNode;

        keytype min = x->key;
        if(x->sibling==nullptr){
            // This ensures an output if there's only 1 tree in the heap
            y=x;
        }
        while(x!=nullptr){
            if(x->key<min){
                min = x->key;
                y = x;
            }
            x = x->sibling;
        }
        return y;
    }

    // Who knows if this actually works
    void binomialLink(BNode *y, BNode *z){
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree = z->degree+1;
    }

    BNode* bHeapMerge(BHeap* H1, BHeap* H2){
        BNode *final = new BNode();
        final = nullptr;
        BNode *placeholder;
        BNode *node1 = H1->headNode;
        BNode *node2 = H2->headNode;

        while(node1!=nullptr || node2!=nullptr){
            // if(final!=nullptr) {cout << "Final currently has a key of: " << final->key << endl;}
            if(node1==nullptr){
                //cout << "Node1 is a nullptr!" << endl;
                // This handles the case where node1 is a nullptr
                if(final==nullptr){
                    // If the final Node is also a nullptr, then set final node to node2 and incrememnt node 2
                    final = node2;
                    node2 = node2->sibling;
                    // final->sibling = nullptr;
                    placeholder = final;
                }else{
                    // If the final node is not a nullptr, then just set the sibling to node2 and increment both final to its sibiling and node to its sibling
                    placeholder->sibling = node2;
                    placeholder = placeholder->sibling;
                    node2 = node2->sibling;
                }
            }else if(node2==nullptr)
            {
                //cout << "Node2 is a nullptr!" << endl;
                // If Node2 is the one thats a nullptr
                if(final==nullptr){
                    // If the final node is a nullptr (nothing has been inserted), then set the final node to node 1 and increment node1
                    //cout << "final is a nullptr still" << endl;
                    final = node1;
                    node1 = node1->sibling;
                    // final->sibling = nullptr;
                    placeholder = final;
                } else{
                    //cout << "Final is not a nullptr, lets add node 1" << endl;
                    placeholder->sibling = node1;
                    placeholder = placeholder->sibling;
                    node1 = node1->sibling;
                    // This inserts node1 into the new rootlist of the placeholder Bheap
                }

            } else{
                // This is when neither node1 or node2 is a nullptr
                //cout << "No Null ptrs here" << endl;
                if(node1->degree<node2->degree){
                    // If the degree of ndoe1 is less tahn the degree of node 2, throw node1 in next
                    if(final==nullptr){
                        // If the final node is a nullptr (nothing has been inserted), then set the final node to node 1 and increment node1
                        final = node1;
                        node1 = node1->sibling;
                        // This inserts node1 into the new rootlist of the final Bheap
                        placeholder = final;
                    } else {
                        placeholder->sibling = node1;
                        placeholder = placeholder->sibling;
                        node1 = node1->sibling;
                        // This inserts node1 into the new rootlist of the final Bheap
                    }
                } else if(node2->degree<node1->degree){
                    if(final==nullptr){
                        final = node2;
                        node2 = node2->sibling;
                        placeholder = final;
                    } else {
                        placeholder->sibling = node2;
                        placeholder = placeholder->sibling;
                        node2 = node2->sibling;
                    }

                } else {
                    // When the degrees are the same, I think we'll just select node2
                    //cout << "The degrees are equal ugh" << endl;
                    if(final==nullptr){
                            // If the final node is a nullptr (nothing has been inserted), then set the final node to node 1 and increment node1
                            final = node2;
                            node2 = node2->sibling;
                            // final->sibling = nullptr;
                            placeholder = final;
                    } else {
                        placeholder->sibling = node2;
                        placeholder = placeholder->sibling;
                        node2 = node2->sibling;
                    }
                    /*
                    if(node1->key<node2->key){
                        if(final==nullptr){
                            // If the final node is a nullptr (nothing has been inserted), then set the final node to node 1 and increment node1
                            final = node1;
                            node1 = node1->sibling;
                            // final->sibling = nullptr;
                            placeholder = final;
                        } else{
                            placeholder->sibling = node1;
                            placeholder = placeholder->sibling;
                            node1 = node1->sibling;
                            // This inserts node1 into the new rootlist of the final Bheap
                        }
                    } else {
                        //cout << "Node 2 is <= Node 1" << endl;
                        if(final==nullptr){
                            //cout << "Looks like final is a nullptr" << endl;
                            final = node2;
                            node2 = node2->sibling;
                            placeholder = final;
                        } else {
                            placeholder->sibling = node2;
                            placeholder = placeholder->sibling;
                            node2 = node2->sibling;
                        }
                    } */

                }
            }
        }
        return final;
    }


    BNode* bUnion(BHeap* H1, BHeap* H2){
        // I'm scard
        // cout << "This two heads are H1: " << H1->headNode->key << " and H2: " << H2->headNode->key << endl;
        BNode* newHead = bHeapMerge(H1,H2);

        delete H2;
        //debugPrint(newHead);
        if(newHead==nullptr){
            return newHead;
        }
        BNode *x;
        x = newHead;
        BNode *prev_x = nullptr;
        BNode *next_x;
        next_x = x->sibling;
        // We need to keep track of the minNode here
        BNode *mini;
        mini = x;
        
        while(next_x!=nullptr){
            if(next_x->key<mini->key){mini=next_x;}
            if(x->degree!=next_x->degree||(next_x->sibling!=nullptr&&next_x->sibling->degree==x->degree)){
                // cout << "Stuck in the loop" << endl;
                prev_x = x;
                x = next_x;
                // I guess we dont increase next x?
            } else {
                if(x->key<=next_x->key){
                    x->sibling = next_x->sibling;
                    binomialLink(next_x,x);
                    // cout << "here" << endl;
                } else {
                    if(prev_x==nullptr){
                    newHead = next_x;
                    //cout << "there" << endl;
                    } else {
                        prev_x->sibling = next_x;
                        // cout << "else" << endl;
                    }
                    binomialLink(x,next_x);
                    x = next_x;
                }
            }
            next_x = x->sibling;
        }
        // this->headNode = mergedHeap->headNode;
        // That should merge the two of them, which will only create a large linked list of the two heaps

        // delete H1;
        if(x->key<mini->key){mini=x;}
        minNode = mini;

        return newHead;
    }

    void bHeapInsert(BHeap *H,BNode *x){
        BHeap<keytype> *newHeap = new BHeap();
        newHeap->headNode = x;
    }



    void insertRoot(BNode* newRoot){
        addNode(newRoot);

        if(newRoot->key < minNode->key){
            minNode = newRoot;
        }
    }

    void printRoots(){
        BNode* it = this->headNode;
        while(it!=nullptr){
            cout << "key: " << it->key << " degree: " << it->degree << " ---- ";
            it = it->sibling;
        }
        cout << endl;
    }

    void debugPrint(BNode *tester){
        BNode* it = tester;
        while(it!=nullptr){
            cout << "key: " << it->key << " degree: " << it->degree << " ---- ";
            it = it->sibling;
        }
        cout << endl;
    }

    BNode* extractMinHelper(){
        if(headNode==nullptr){return nullptr;}
        BNode* extractor = headNode;
        BNode* prevNode = nullptr;
        if(extractor==nullptr){return extractor;}

        while(extractor!=minNode){
            prevNode = extractor;
            extractor = extractor->sibling;
        }
        // Now extractor should be the minNode
        // Lets remove minNode from the list
        if(extractor->sibling==nullptr){
            // If the minnode is the last element, we cahnge prevNode to point to a null
            if(prevNode==nullptr){
                headNode==nullptr;
            }else {

                prevNode->sibling=nullptr;
            }
        } else {
            // If the minNode is not the last element, remove it
            if(prevNode==nullptr){
                headNode=extractor->sibling;
            } else {
                prevNode->sibling = extractor->sibling;
            }

        }

        if(extractor->child!=nullptr){      
            BNode* reversedList = nullptr;
            BNode* curr = extractor->child;
            BNode* temp = nullptr;
            //debugPrint(curr);

            while(curr!=nullptr){
                    // this code loops while current is not a null ptr
                BNode* nextSibling = curr->sibling;
                BNode* revHolder = reversedList;
                curr->parent=nullptr;
                reversedList = curr;
                
                reversedList->sibling = revHolder;
                curr = nextSibling;
            }

            if(headNode==nullptr){
                headNode=reversedList;

            } else {
                BHeap<keytype> *HNew = new BHeap();
                HNew->headNode = reversedList;
                //debugPrint(HNew->headNode);
                headNode = bUnion(this,HNew);

            }
            // debugPrint(HNew->headNode);
            // childPrint(HNew->headNode->sibling->sibling);
            // cout << "Trying to unionize" << endl;

        } else {
            // We need to find a new minNode or else this whole thing will segfault
            BNode *iterator = headNode;
            BNode *newMinNode = headNode;
            iterator=iterator->sibling;
            while(iterator!=nullptr){
                if(iterator->key<newMinNode->key){
                    newMinNode = iterator;
                }
                iterator = iterator->sibling;
            }
            minNode = newMinNode;
        }


        return extractor;

    }

    void printTree(BNode *stuff){

        cout << stuff->key << " ";
        if(stuff->child!=nullptr){
            // If the node has a child, lets check it out
            printTree(stuff->child);
        }
        if(stuff->parent!=nullptr){
            // If the node is a child
            if(stuff->sibling!=nullptr){
                // If the node has siblings
                printTree(stuff->sibling);
            }
        }

    }

    void deleteHeap(BNode *stuff){
       // cout << stuff->key << " ";
        if(stuff->child!=nullptr){
            // If the node has a child, lets check it out
            deleteHeap(stuff->child);
        }
        if(stuff->parent!=nullptr){
            // If the node is a child
            if(stuff->sibling!=nullptr){
                // If the node has siblings
                deleteHeap(stuff->sibling);
            }
        }
        delete stuff;
    }

    void childPrint(BNode* x){
        if(x->child!=nullptr){
            BNode* son = x->child;
            while(son!=nullptr){
                cout << "Key: " << son->key << endl;
                son = son->sibling;
            }
        }
    }

    void destroy(BNode* node){
        if (node != nullptr) {
            destroy(node->child);
            destroy(node->sibling);
            delete node;
        }
        headNode = nullptr;
        minNode = nullptr;
    }

    BNode* copyNodes(BNode* node, BNode* parent) {
        if (node == nullptr) {
            return nullptr;
        }
        BNode* newNode = new BNode();
        newNode->key = node->key;
        newNode->degree = node->degree;
        if(parent!=nullptr){
            newNode->parent = parent;
        }
        newNode->child = copyNodes(node->child, newNode);
        newNode->sibling = copyNodes(node->sibling, parent);
        return newNode;
    }

    BNode* findMinNode(BNode* node){
            BNode* minNode = node;
            BNode* currentNode = node->sibling;

            while (currentNode != nullptr) {
                if (currentNode->key < minNode->key) {
                    minNode = currentNode;
                }
                currentNode = currentNode->sibling;
            }

            return minNode;
    }



    public:
        BHeap(){
           headNode  = nullptr;
           minNode = nullptr;
           // cout << "We made a heap" << endl;
        }

        BHeap(keytype k){
            // This constructor will be called only when inserting I think
            BNode *temp = new BNode();
            temp->key = k;
            temp->degree = 0;
            temp->parent = nullptr;
            temp->child = nullptr;
            temp->sibling = nullptr;
        }

        BHeap(keytype k[], int s){
            headNode  = nullptr;
            minNode = nullptr;
            // cout << "We made a heap with the array constructor" << endl;
            for(int i=0;i<s;i++){
                this->insert(k[i]);
            }

        }

    ~BHeap(){
        // Destructor
        // destroy(headNode);
    }   

    BHeap(const BHeap& other) { // copy constructor
        headNode = copyNodes(other.headNode,other.headNode->parent);
        minNode = findMinNode(headNode);
	}

	BHeap& operator=(const BHeap& other) { // assignment operator
        if (this != &other) { // check for self-assignment
            // clear the current heap
            destroy(headNode);

            // create a new heap and copy the data from the other heap
             headNode = copyNodes(other.headNode,other.headNode->parent);
             minNode = findMinNode(headNode);
        }
    return *this;
	}
    //Returns the minimum key in the heap without modifiying the heap.
    keytype peekKey(){
        if(minNode==nullptr){
        } else {
            return minNode->key;
        }


    }

    //Removes the minimum key in the heap and returns the key.
    keytype extractMin(){
        
        BNode *mini = extractMinHelper();
        if(mini==nullptr){
            return 0;
        }
        return mini->key;

    }

    // Inserts the key k into the heap
    void insert(keytype k){
        // New Node to insert
            BNode *newNode = new BNode();
            newNode->degree = 0;
            newNode->key = k;

        if(headNode==nullptr){
            headNode = newNode;
            // cout << "No head?" << endl;
        } else{
            BHeap *newHeap = new BHeap();
            newHeap->headNode = newNode;
           // cout << "Unionizing H1 and new H2 with key " << newHeap->headNode->key << endl;
            this->headNode = bUnion(this,newHeap);
        }



        // Testing
        /*
        BNode *treeClimber = headNode;
        BNode *prev = headNode;
        if(treeClimber==nullptr){
            headNode = newNode;
            //cout << "Set the head" << endl;
        } else {
            treeClimber = treeClimber->sibling;
            while(treeClimber!=nullptr){
                prev = treeClimber;
                treeClimber = treeClimber->sibling;
            }
            treeClimber = newNode;
            prev->sibling = treeClimber;
        }
        */


    }

    // Merges the heap H2 into the current heap. Consumes H2, H2 should be empty after.
    // So I should probably delete H2
    void merge(BHeap<keytype> &H2){

        BHeap<keytype> *newH = new BHeap();

        newH->headNode = H2.headNode;
        newH->minNode = H2.minNode;

        this->headNode = bUnion(this,newH);

        H2.mergeDestroy();

    }

    // Writes the keys stored in the heap, printing the smallest binomial tree first. When printing a binomial tree, print the size of tree first and then use a modified preorder traversal of the tree.
    void printKey(){
        //rintHeap(head);
        if(headNode!=nullptr){
            // We can output stuff if the head node isn't a null ptr
            BNode* iter = headNode;
            while(iter!=nullptr){
                cout<<"B"<<iter->degree<<endl;
                printTree(iter);
                cout << endl;
                cout << endl;
                iter = iter->sibling;
            }
        }
    } 

    void print(){
        printRoots();
    }

    void headGrabber(){
        cout << "head: " << headNode->key << endl;
        if(headNode->sibling!=nullptr){
            cout << "it has a sibiling: " << headNode->sibling->key << endl;
        }
    }

    void test(){
        cout << "The min node of this heap is: " << minNode->key << endl;
    }

    void mergeDestroy(){
        headNode = nullptr;
        minNode = nullptr;
    }
};