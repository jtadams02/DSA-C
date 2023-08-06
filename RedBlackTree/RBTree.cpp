#include <iostream>
#include <cmath> // I need this library to calculate log2()
/* RBTree implementation
*  Learning what RBTree's are and their specifics as I go along building this
*
*  Rules of RBTrees: 
*  1. Every node must be either red of black (nodes must now have an extra variable depicting which color they are)
*  2. The root must be black
*  3. Every leaf node (NIL) must be black
*  4. If a node is red, then both its children are black
*  5. For each node, all simple paths from the node to decendent leaves contain the same number of black nodes ()
*  
*/

using namespace std;


template<typename keytype,typename valuetype>
class RBTree{
private: // Yes

    /* TODO
    *  Figure out how the null pointers will work
    */
    struct node {
        bool color; // false = black, true = red
        keytype key; // holds the key
        node *right; // pointer to right child
        node *left; // pointer to left child
        node *parent; // pointer to the parent
        valuetype value;
        int sz=0;
    };
   /*
    struct node { // This will be the structure for all nodes in the RBTree. 
        bool color; // Determine whether or not the node is red/black. 0 = black while 1 = red
        keytype key;
        valuetype value;
        node *right; // this points to the right of the node
        node *left; // this points to the left of the node
        node *parent; // parent pointer of the node 

        // Can structs use constructors?
        node(keytype k, valuetype v, node* l, node* r, node* p, bool rcol) :
            key(k), value(v), left(l), right(r), parent(p), color(rcol) {}

        node(keytype k, valuetype v){
            color = true; // Has color, red. Will be changed later
            key = k;
            value = v;

            left = right = parent = nullptr; // Does not point to anything yet, will be assigned later
        }
    };
    */
 
    node *root; // This creates the parent root node using the above struct. By defualt it is empty
    int nodes = 0; // Number of nodes in the tree!
    node *TNIL; // This should be what leaf nodes point to, i think?

    // HELPER FUNCTIONS

    // Helper function for destructor
    void destroy_tree(node* n) {
        if (n != TNIL) {
            destroy_tree(n->left);
            destroy_tree(n->right);
            delete n;
        }
    }

   // Helper function for inserting into tree
   // The ampersand is all important here!
   // Without passing the root (or sub-root in recursion) by reference then the root's child pointers would remain unchanged!
  void ins(node* &t,keytype k, valuetype v)
   {
        // node t is root node at first, then the children of root node
        // We need to assign parent ptr, so I'm going to make this in my own form

        if(t!=nullptr) // Checks if t is root, but shouldn't matter in this scope
        {
            // If it is not null, lets compare keys
            if(k<t->key) // if our new k is less than t, look at left child
            {
                if(t->left==nullptr) // If t-> is a null ptr, lets set it to the new node because this is where the new node would go
                {
                    node* new_node = new node(k, v, nullptr, nullptr, t, true);
                    t->left = new_node; // This sets the currentNodes left child to the new node. The new node now has a pointer back up to it's parent
                    cout << "Trying to fix insertion on left insert" << endl;
                    // fixInsertion(new_node); // This wil fix the newnode

                    /*
                    // This stuff is just debugging
                    cout << "Inserted new leaf with key of " << t->left->key << " and value of " << t->left->value << endl;
                    cout << "It has a parent with key of " << new_node->parent->key << " and a parent value of " << new_node->parent->value << endl;
                    inorder();
                   // */

                    return;
                } else { // If the left child is not a nulltpr, then that means there is a value in that child. So let's recurse
                    ins(t->left,k,v);
                }
            } else if(t->key==k){ // If the keys are the same, just change value
                t->value = v;
                cout << "Duplicate key: " << k << endl;
                return;
            } else { // For everything else, this means specifically if k > t->key
                if(t->right==nullptr) // if t->right is a nullptr, set it to the newnode and assign the parent as t
                {
                    node* new_node = new node(k, v, nullptr, nullptr, t, true);
                    t->right = new_node;
                    cout << "Trying to fix insertion" << endl;
                    //fixInsertion(new_node);

                    /*
                    // This stuff is just debugging
                    cout << "Inserted new leaf with key of " << t->right->key << " and value of " << t->right->value << endl;
                    cout << "It has a parent with key of " << new_node->parent->key << " and a parent value of " << new_node->parent->value << endl;
                    inorder();
                    */

                    return;
                } else{ // If the right child is not a null ptr, then move down the tree on the right
                    ins(t->right,k,v);
                }
            }
        } else { // If it is null, idk
            cout << "Somehow the root is null!" << endl;
        }
   } 

    // THIS WILL BE HUGE - CONTROL ALL CASES FOR INSERTION AHHHHHH
   void fixInsertion(node* n)
   {
        // When fixing insertion, there are a few cases we need to consider
        // Let N=Current Node, P=Parent of N, U=Uncle of N, S=Sibling of N, G=Grandparent of N
        // Case 1: Tree is Empty; This is taken care of with our first insertion
        // Case 2: P of N is black.
            // If N's Parent Node is Black, Then there is no violation and nothing needs to be done
        // Case 3: P of N is red
            // If N's Parent Node is Red, it violates property 4. P and N are both red, but that is not possible in a red black tree
            // To fix this, we need to see if N's Uncle, U, is red or black
            // Case 3.1: P of N is red, and U of N is red too
                // In this case, we flip the color of nodes P,U, and G. That means that P becomes black, U becomes black, and G becomes red. 
                // IF G is root, DO NOT RECOLOR
            // Case 3.2: P of N is red and U of N is black (Or NULL)
                // If the Uncle U is black, we need single or double rotations depending on whether N is a left or right child of p
                // Case 3.2.1: P is a right child of G, and N is a right child of P
                    // First perform a left rotation at G, that makes G the new sibling of S of N. Next change the color S to Red and P to black
                // Case 3.2.2: P is the right child of G and N is the left child of P
                    // Perform a right rotation at P, this reduces it to case 3.2.1
                // Case  3.2.3: P is left child of G, and N is left Child of P
                    // Mirror Case to 3.2.1 
                    // Right Rotation on G, swaps G with P. G is now S of N. Set P to black, and change G to red
                // Case 3.2.4
                    // Mirror Case to 3.2.2
                    // Left Rotation on G, Swaps G with P. G is now left child of P and S of N. Set P to black and G to red. 
            node* uncle;
        while(n->parent->color==true)
        {
            //cout << "In While loop" << endl;
            if(n->parent==n->parent->parent->right) // Checks if P is the right child of G
            {
                
                uncle = n->parent->parent->left; // Uncle, could be nullptr?
              //  cout << "Parent is right child of Grandparent" << endl;

                if(uncle->color==1) // Makes sure that the uncle is a red node, if it is a nullptr then it is black
                {
                   // cout << "Case 3.1" << endl;
                    // CASE 3.1
                    uncle->color=0;
                    n->parent->color = 0;
                    n->parent->parent->color = 1;
                    n = n->parent->parent; // Set N to G
                } else {
                    if(n==n->parent->left) // Case 3.2.1 and 3.2.2 - Checks if N is left child of its parent
                    {
                        // Case 3.2.2
                     //   cout << "Case 3.2.2" << endl;
                        n = n->parent; // Sets n to parent
                     //   cout << "Trying to right rotate" << endl;
                        rightRotate(n); // Rotate Left on P
                        //cout << "right rotated successfully" << endl;
                    } 
                    // Case 3.2.1
                  //  cout << "Case 3.2.1" << endl;
                    n->parent->color = 0;
                    n->parent->parent->color = 1;
                 //   cout << "Trying to left rotate" << endl;
                    leftRotate(n->parent->parent);
                }
            } else{
                uncle = n->parent->parent->right; // Uncle is set to the right child of G
               // cout << "Parent is left child of Grandparent" << endl;
                if(uncle->color==1) // If Uncle is red
                { 
                    uncle->color = 0;
                    n->parent->color = 0;
                    n->parent->parent->color = 1;
                    n = n->parent->parent;
                } else {
                    if(n==n->parent->right){
                        // mirror case of 3.2.2
                        n=n->parent;
                        leftRotate(n);
                    }
                    // Mirror case 3.2.1
                    n->parent->color = 0;
                    n->parent->parent->color = 1;
                    rightRotate(n->parent->parent);
                }
            }
            if(n==root){break;}
        }
        root->color = 0;
   }

    // I really hope I know what I'm doing here
   void leftRotate(node* n)
   {
       // cout << "In the left rotate" << endl;
        node *y = n->right;
       // cout << "Init y to n.right" << endl;
        n->right = y->left;
       // cout << "In the left rotate, n.right = y.left" << endl;
        if(y->left!=TNIL){
            y->left->parent = n;
        }
        y->parent = n->parent;
        if(n->parent==nullptr){
            this->root = y;
        } else if(n==n->parent->left){
            n->parent->left = y;
        } else {
            n->parent->right = y;
        }
        y->left = n;
        n->parent = y;
        y->sz = n->sz;
        n->sz = n->left->sz+n->right->sz + 1;  
   }

   void rightRotate(node* n)
   {
        node* y = n->left;
      //  cout << "Rotating Right, y=n.left" << endl;
        n->left = y->right;
     //   cout << "n.left = y.right" << endl;
        if(y->right!=TNIL){
            y->right->parent = n;
        }
        y->parent = n->parent;
        if(n->parent==nullptr){
            this->root = y;
        } else if(n==n->parent->right){
            n->parent->right = y;
        } else {
            n->parent->left = y;
        }
        y->right = n;
        n->parent = y;
        y->sz = n->sz;
        n->sz = n->left->sz+n->right->sz + 1;
   }

   void RBDelete(node* n)
   {
        // Big ole Deletio n function, which we will try to do special cases for!
        node *y = n;
        node *x;
        bool yOriginalColor = y->color;

        if(n->left==TNIL)
        {
            updateSize(y); // Decrements the size of each of the parents
            x = n->right;
            RBTransplant(n,n->right);
        } else if(n->right==TNIL){
            updateSize(y); // Decrements the size of each of the parents
            x = n->left;
            RBTransplant(n,n->left);
        } else {
            y = max(n->left); // Set node to replace n to be its largest node on its left
            yOriginalColor = y->color; // Save original color of y
            x = y->left; // Set x to left child of y, x is set to y.left because there is nothing in y.right
            updateSize(y);// Update the size of every node above y
            if(y->parent==n){ // Checks if y is a child of n
                x->parent = y; // If y is a child of n, x's parent is set to y, because x is taking y's place
            } else { // if y is not a child of n
                RBTransplant(y,y->left); // Transplant y and its left child
                y->left = n->left; // set y.left to what was n.left
                y->left->parent = y; // set the parent of y.left = y?
            }

            // Honestly im not sure what this stuff below does 
            // so I just swapped left and right becasue yeah
            // It works so :)

            RBTransplant(n,y); // n and y
            y->right = n->right; // Set y.right = y.right
            y->right->parent = y;
            y->color = n->color;

            y->sz = n->sz; // TEST

            delete n;
        }
        // ? delete n; 
        if(!yOriginalColor){
            deletionFix(x);
        }
   }

   void RBTransplant(node *u, node *v)
   {
        if(u->parent==nullptr){ // check if parent of u is nullptr or root
            this->root = v; // Then sets it to root
        } else if (u==u->parent->left){ // if u is not root, and u is a left child
            u->parent->left  = v; // set u's parent's left child to v
        } else {
            u->parent->right = v; // otherwise set u's parent's right child to v;
        }
        v->parent = u->parent; // v's parent is now u's parent
   }

   void deletionFix(node *n)
   {
        node *w;
        while(n!=this->root&&n->color==0)
        {
            if(n==n->parent->left){
                w = n->parent->right;
                if(w->color){
                    w->color = false;
                    n->parent->color = true;
                    leftRotate(n->parent);
                    w = n->parent->right;
                }
                if(!w->left->color&&!w->right->color){
                    w->color = true;
                    n = n->parent;
                } else {
                    if(!w->right->color){
                        w->left->color = false;
                        w->color = true;
                        rightRotate(w);
                        w = n->parent->right;
                    }
                    w->color = n->parent->color;
                    n->parent->color = false;
                    w->right->color = false;
                    leftRotate(n->parent);
                    n = root;
                }

            } else {
                w = n->parent->left;
                if(w->color){
                    w->color = false;
                    n->parent->color = true;
                    rightRotate(n->parent);
                    w = n->parent->left;
                }
                if(!w->right->color&&!w->left->color){
                    w->color = true;
                    n = n->parent;
                } else {
                    if(!w->left->color){
                        w->right->color = false;
                        w->color = true;
                        leftRotate(w);
                        w = n->parent->left;
                    }
                    w->color = n->parent->color;
                    n->parent->color = false;
                    w->left->color = false;
                    rightRotate(n->parent);
                    n = root;
                }
            }
            
        }
        n->color = false; // Root set
   }

   valuetype recursiveSearch(keytype k, node *temp)
   {
        if(k==temp->key){return temp->value;}
        if(k<temp->key){ // if key is smaller than node k, go left
            return recursiveSearch(k,temp->left);
        } else{
            return recursiveSearch(k,temp->right);
        }
   }

   bool colorSearch(keytype k, node *temp)
   {
        if(k==temp->key){return temp->color;}
        if(k<temp->key){
            return colorSearch(k,temp->left);
        } else {
            return colorSearch(k,temp->right);
        }
   }


    // Printing inOrder Traversal
    void printInorder(node* n)
    {
        if (n == TNIL)
            return;
    
        /* first recur on left child */
        printInorder(n->left);
    
        /* then print the data of node */
        cout << n->key << " ";
    
        /* now recur on right child */
        printInorder(n->right);
    }

    // Printing preOrder traversal
    /*
    * Algorithm Preorder(tree)
    * Visit the root.
    * Traverse the left subtree, i.e., call Preorder(left->subtree)
    * Traverse the right subtree, i.e., call Preorder(right->subtree)
    */
    void printPreorder(node *n)
    {
        if (n == TNIL)
        return;
 
        /* first print data of node */
        cout << n->key << " ";
    
        /* then recur on left subtree */
        printPreorder(n->left);
    
        /* now recur on right subtree */
        printPreorder(n->right);
    }

    // Printing PostOrder trabersal
    /*
    * Algorithm Postorder(tree)
    * Traverse the left subtree, i.e., call Postorder(left->subtree)
    * Traverse the right subtree, i.e., call Postorder(right->subtree)
    * Visit the root
    */
    void printPostorder(struct node *n)
    {
        if (n == TNIL)
        return;
 
        // first recur on left subtree
        printPostorder(n->left);
    
        // then recur on right subtree
        printPostorder(n->right);
    
        // now deal with the node
        cout << n->key << " ";
    }

    keytype treeMin(node* n)
    {
        while(n->left!=TNIL)
        {
            n = n->left;
        }
        return n->key;
    }

    keytype treeMax(node *n)
    {
        while(n->right!=TNIL)
        {
            n = n->right;
        }
        return n->key;
    }

    node* min(node* n)
    {
        while(n->left!=TNIL)
        {
            n = n->left;
        }
        return n;
    }

    node* max(node *n)
    {
        while(n->right!=TNIL)
        {
            // n->sz--;
            n = n->right;
        }
        return n;
    }

    node* selectNode(keytype k, node* n)
    {
        if(k==n->key){return n;}
        else if(k<n->key)
        {
           return selectNode(k,n->left);
        } else if(k>n->key)
        {
            return selectNode(k,n->right);
        } else {return nullptr;}
    }


    

    node* deleteSelect(keytype k, node* n)
    {
        //cout << "Looking for key " << k << " at node that has key of " << n->key << endl;
        if(n==TNIL){return nullptr;}
        if(k==n->key){return n;}
        else if(k<n->key)
        {
         //   cout << "Key smaller, going left" << endl;
            // n->sz--;
           return deleteSelect(k,n->left);
        } else if(k>n->key)
        {
         //   cout << "Key bigger, going right" << endl;
           // n->sz--;
            return deleteSelect(k,n->right);
        }
        return nullptr;
    }

    int rankHelper(keytype k, node* n)
    {

        int r = n->left->sz+1;
        node* y = n;

        while (y!=root){
            if(y == y->parent->right)
            {
                r = r + y->parent->left->sz +1;
            }
            y = y->parent;
        }
        return r;
    }

    keytype selectHelper(int pos, node *n)
    {
        int r = n->left->sz + 1;
        if(pos==r){
            return n->key;
        }else if(pos<r){
            return selectHelper(pos,n->left);
        } else if(pos>r){
            return selectHelper(pos-r,n->right);
        } else {
            return NULL;
        }
    }

    void updateSize(node *n)
    {
        node *x = n;
        while(x!=root)
        {
            x->parent->sz--;
           // cout << "Decremented size, moving up" << endl;
            x = x->parent;
        }
        // cout << "All sizes decremented" << endl;
    }

    int nSize(node* n) {
		if (n == TNIL) {
			return 0;
		}

		return n->sz;
	}

    node* copy(node* curr) { // copy the tree
		node* newnode;
        newnode->key = curr->key;
        newnode->value = curr->value;
        newnode->color = curr->color;
		if (curr->left != NULL) {
			newnode->left = copy(curr->left);
		}

		if (curr->right != NULL) {
			newnode->right = copy(curr->right);
		}

		newnode->sz = curr->sz;
		return newnode;
	}

    node* copyTree(node *n)
    {
        // cout << "Copy Tree" << endl;
        node *x = new node();
        
        x->key = n->key;
        // cout << "The current key is " << x->key << endl;
        x->value = n->value;
        x->color = n->color;
        x->sz = n->sz;
        x->left = TNIL;
        x->right = TNIL;

       // if(x->parent==nullptr){cout<<"copied the root"<<endl;}

       // cout << "Recursion Time" << endl;
        // if(n->right==TNULL&&n->left==TNULL){ return x;}

        if (n->left!=TNIL) {
           // cout << "Recursing left" << endl;
            //cout << "Going left to node with key: " << n->left->key << endl;           
			x->left = copyTree(n->left);
            x->left->parent = x;
            //cout << "Node with key " << x->key << " now has left child with key " << x->left->key << endl;
            //cout << "The parent of that right child is node: " << x->left->parent->key << endl;

		}
      //  cout << "Left child is done for node with key: " << x->key << endl;
		if (n->right!=TNIL) {
           // cout << "Recursing right" << endl;
           //cout << "Going right to node with key: " << n->right->key << endl;
			x->right = copyTree(n->right);
            x->right->parent = x;
            //cout << "Node with key " << x->key << " now has right child with key " << x->right->key << endl;
          //  cout << "The parent of that right child is node: " << x->right->parent->key << endl;
		}
       // cout << "right child is done for node with key: " << x->key << endl;
        //cout << "Node with key: " << x->key << " should be complete" << endl;
        // printChildClose(x);
        x->parent = nullptr;
        return x;

    }

    // Max height will be the last level. It will remain the same.
    // If current height = max height, the node will be colored red
    node* specialConstructor(keytype k[], valuetype v[],node *n,int s,int maxHeight, int currentHeight)
    {

            int m = s/2;
            if(s==1||s==2){m=0;} // maybe?

            node* newRoot = new node();
            newRoot->key = k[m];
            newRoot->value = v[m];
            newRoot->left = TNIL;
            newRoot->right = TNIL;
            newRoot->parent = n;
            newRoot->sz = 1;
            if(maxHeight==currentHeight){newRoot->color = true;} // If this is the final level, the node will be red
            else{newRoot->color = false;}
            if(s==1){return newRoot;}
            if(s==2){
                node *rightChil = new node();
                rightChil->key = k[1];
                rightChil->value = v[1];
                rightChil->left = TNIL;
                rightChil->right = TNIL;
                rightChil->parent = newRoot;
                rightChil->sz = 1;
                newRoot->right = rightChil;
                newRoot->sz++;
                return newRoot;

            }

            int leftSize = (s/2);
            if(s>2){
                keytype leftKeys[(s/2)];
                valuetype leftVals[(s/2)];

                // Now we need to populate the left array
                //cout << "Assigning left keys on level " << currentHeight << endl;
                for(int i=0;i<(s/2);i++)
                {
                    leftKeys[i] = k[i];
                    //cout << leftKeys[i] << " ";
                    leftVals[i] = v[i];
                }
                //cout << endl;
                newRoot->left = specialConstructor(leftKeys,leftVals,newRoot,leftSize,maxHeight,currentHeight+1);
                newRoot->sz += newRoot->left->sz;
            }
            int rightedSize = (s/2);
            if(s>1)
            {
                if(s%2==0){
                    int rightSize = (s/2)-1;
                    keytype rightKeys[rightSize];
                    valuetype rightVals[rightSize];

                    int counter = 0; // We need this variable to input correctly into right variables
                    for(int i=(s/2)+1;i<s;i++)
                    {
                        rightKeys[counter] = k[i];
                        rightVals[counter] = v[i];
                        counter++;
                    }

                    newRoot->right= specialConstructor(rightKeys,rightVals,newRoot,rightSize,maxHeight,currentHeight+1);

                } else {
                    int rightSize = (s/2);
                    keytype rightKeys[rightSize];
                    valuetype rightVals[rightSize];
                    int counter = 0; // We need this variable to input correctly into right variables
                    for(int i=(s/2)+1;i<s;i++)
                    {
                        rightKeys[counter] = k[i];
                        rightVals[counter] = v[i];
                        counter++;
                    }

                    newRoot->right= specialConstructor(rightKeys,rightVals,newRoot,rightSize,maxHeight,currentHeight+1);
                }
            }


        return newRoot;
        
    }

public:
    // Empty default constructor
    RBTree(){
        TNIL = new node;
		TNIL->color = 0;
		TNIL->left = nullptr;
		TNIL->right = nullptr;
        TNIL->sz = 0;
		root=TNIL;
    } // Just sets root to nothing lol

    /* RBTree(keytype k[], valuetype v[],int s) - Constructor
    *  For this constructor the tree should be built using the arrays K and V containing s items of keytype and valuetype.  
    *  If the keytype array is order then the tree should be built in O(s) time as described later.  
    *  If the items are not in order, the tree should be built using repeated insertion. 
    */
    RBTree(keytype k[], valuetype v[],int s){
        // Check if keytype is in order!
        TNIL = new node;
		TNIL->color = 0;
		TNIL->left = nullptr;
		TNIL->right = nullptr;
        TNIL->parent = nullptr;
        TNIL->sz = 0;
		root=TNIL;
        if(s<=0){return;} // Edge case: Empty value
        if(s==1) // Edge case: if the size is 1
        {
            nodes = s;
            node *newRoot = new node();
            newRoot->key = k[0];
            newRoot->value = v[0];
            newRoot->color = false; // Roots black
            newRoot->parent = nullptr;
            newRoot->left = TNIL;
            newRoot->right = TNIL;
            root = newRoot;
            return; 
        }
        int c=0;
        int cc=0;
        bool inOrder = true;
        while(c<s-1){if(k[c]>k[c+1]){inOrder = false;break;}c++;}// check if keys are in order
        c++;
        // inOrder=false;
        if(inOrder){
            // Edge Case: if the size is 2 but is inorder
            if(s==2)
            {
                nodes = s;
                node *newRoot = new node();
                newRoot->key = k[0];
                newRoot->value = v[0];
                newRoot->color = false; // Roots black
                newRoot->parent = nullptr;
                newRoot->left = TNIL;
                newRoot->right = TNIL;
                root = newRoot;

                node *rightChild = new node();
                rightChild->key = k[1];
                rightChild->value = v[1];
                rightChild->color = true; // RED
                rightChild->parent = root;
                rightChild->sz = 1;
                rightChild->right = TNIL;
                rightChild->left = TNIL;
                
                root->right = rightChild;
                root->sz = root->right->sz + 1;
                return;

            }
            bool isPerf = !(s & (s - 1)); // Checks if s is a power of 2?
            int ceiling = (int)log2(s);
            //cout << "Ceiling: " << ceiling << endl;

            // TODO - Specific way to build. Maybe lets try helper function?
            // cout << "Keys are in order!" << endl;

            // I feel like this could be done in a while loop maybe?

            // Setup Root Node            
            int m = s/2;
            node* newRoot = new node();
            newRoot->key = k[m];
            newRoot->value = v[m];
            newRoot->color = false;
            newRoot->left = TNIL;
            newRoot->right = TNIL;
            newRoot->parent = nullptr;
            newRoot->sz = 1;
            root = newRoot;
            //cout << "Root assigned" << endl;
            // Now lets create subarrays!
            // I am assuming that there is enough room for these subarrays
                // When S is even, the subarrays will not be the same size.
                // The left subarray will be smaller since we take (s/2)
                // ex: 0,1,2,3,4,5 s = 6. s/2 = 3, and the 4th element (S[3] would be the 4th element) 3 will be the median and 0,1,2 will make up the first sub array while 4,5 will make up the second sub array
                // so, the right subarray will have size (s/2)-1 and the right sub array will have size (s/2)
                // FORGET EVERYTHING ABOVE IT DOES NOT MATTER!
                int leftSize = (s/2);
                keytype leftKeys[leftSize];
                valuetype leftVals[leftSize];

                // Now we need to populate the left array
                for(int i=0;i<(s/2);i++)
                {
                    leftKeys[i] = k[i];
                    leftVals[i] = v[i];
                }
                root->left = specialConstructor(leftKeys,leftVals,root,leftSize,ceiling,1);

                if(s%2==0){
                    int rightSize = (s/2)-1;
                    keytype rightKeys[rightSize];
                    valuetype rightVals[rightSize];

                    int counter = 0; // We need this variable to input correctly into right variables
                    for(int i=(s/2)+1;i<s;i++)
                    {
                        rightKeys[counter] = k[i];
                        rightVals[counter] = v[i];
                        counter++;
                    }

                    root->right= specialConstructor(rightKeys,rightVals,root,rightSize,ceiling,1);

                } else {
                    int rightSize = (s/2);
                    keytype rightKeys[(s/2)];
                    valuetype rightVals[(s/2)];
                    int counter = 0; // We need this variable to input correctly into right variables
                    for(int i=(s/2)+1;i<s;i++)
                    {
                        rightKeys[counter] = k[i];
                        rightVals[counter] = v[i];
                        counter++;
                    }

                    root->right= specialConstructor(rightKeys,rightVals,root,rightSize,ceiling,1);
                }
                //Now arrays should be populated 
            // Call recurisve functions, they will be at height 1

            

            
            
        }else {
            // If keytype is not inorder, loop until size while inserting each key
           // cout << "Keys are not in order!" << endl;
            for(int i=0;i<s;i++){
                insert(k[i],v[i]);
            }
        }
    }
    // Destructor that loops through the tree, freeing each node
    ~RBTree(){
        destroy_tree(root);
        delete TNIL;
    }

    RBTree(const RBTree& other) { // copy constructor

        this->TNIL = other.TNIL;
        this->nodes = other.nodes;
        root = copyTree(other.root);
        //this->inorder();
        //root = copyTree(other.root,other.TNIL);
	}

	RBTree& operator=(const RBTree& other) { // assignment operator
        this->TNIL = other.TNIL;
        this->nodes = other.nodes;
        // cout << "Attempting to copy tree" << endl;
		this->root = copyTree(other.root);
        // this->size = other.sizes
		return *this;
	}
    

    /* valuetype *search(keytype k)
    * Traditional search. Should return a pointer to the valuetype stored with the key. 
    * If the key is not stored in the tree then the function should return NULL. 
    */
    valuetype *search(keytype k){
        
        // Call recursive helper func
        valuetype x = recursiveSearch(k,root);
        valuetype *p = &x;
        return p;
    }
    
    /* void insert(keytype k, valuetype v); 
    * Inserts the node with key k and value v into the tree. 
    * When inserting, we will need to check to makesure it is a valid RBTree, probably need helper function
    */
    void insert(keytype k, valuetype v){
        // First, lets check if root is empty. If so, call helper function to 
        // insert when root is null
         // Create temp node
        // Ordinary Binary Search Insertion
        
		node* n = new node;
		n->parent = nullptr;
		n->key = k;
        n->value = v;
		n->left = TNIL;
		n->right = TNIL;
		n->color = 1; // new node must be red
        n->sz = 1;

		node* y = nullptr;
		node* x = this->root;

		while (x != TNIL) {
            x->sz++;
			y = x;
            if(n->key == x->key){ // Handles duplicates, no need to fix anything just update value
                x->value = n->value;
                // cout << "Duplicate key: " << n->key << endl;
                return;
            }
			if (n->key < x->key) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		// y is parent of x
		n->parent = y;
		if (y == nullptr) {
			root = n;
		} else if (n->key < y->key) {
			y->left = n;
		} else {
			y->right = n;
		}

		// if new node is a root node, simply return
		if (n->parent == nullptr){
			n->color = 0;
            nodes++;
			return;
		}

		// if the grandparent is null, simply return
		if (n->parent->parent == nullptr) {
            nodes++;
			return;
		}

		// Fix the tree
        nodes++;
		fixInsertion(n);
        
        /*if(root==nullptr){
            cout << "Root is empty" << endl;
            node* new_node = new node(k, v, nullptr, nullptr, nullptr, true);
            new_node->color = 0; // Set new_node to color black
            root = new_node; // Set root to new node
            nodes++;
            return; // exit
        } else {
        // Otherwise, insert normally
            ins(this->root,k,v);
        }*/
    }


    int remove(keytype k)
    {
        node* nodeToDelete;
        nodeToDelete = deleteSelect(k,root);
        if(nodeToDelete==nullptr||nodeToDelete==TNIL){return 0;}
        //updateSize(nodeToDelete);
       // cout << "You've selected to delete node with key: " << nodeToDelete->key << endl;
        RBDelete(nodeToDelete);
        // cout << "Removed: " << k << endl;
        nodes--;
        return 1;
    }



    int rank(keytype k)
    {
       // cout << "Ranking time" << endl;
        node *x = selectNode(k,root);
        
        if(x==nullptr){return 0;}
        return rankHelper(k,x);
    }


    keytype select(int pos)
    {
        node *n = root;
        keytype x =  selectHelper(pos,root);
        //if(x==NULL){cout<<"Not in tree?"<<endl;return NULL;}
        return x;
    }


    keytype *successor(keytype k)
    {
        node* temp = selectNode(k,root);
        if(temp==nullptr){return NULL;}

        if(temp->right!=TNIL)
        {
            keytype x = treeMin(temp->right);
            keytype *p = new keytype();
            *p = x;
            return p;
        }
        node* y = temp->parent;
        while(y!=nullptr&&temp==y->right)
        {
            temp = y;
            y = y->parent;
        }
        if(y==nullptr&&temp->key<k){return NULL;}
        keytype x = y->key;
        keytype *p = new keytype();
        *p = x;
        return p;

       
    }


    keytype *predecessor(keytype k)
    {

        node* temp = root;
        temp = selectNode(k,temp);
        if(temp==nullptr){return NULL;}
        if(temp->left!=TNIL)
        {
            // cout << "Node DOES have a left subtree" << endl;
            keytype x = treeMax(temp->left);
            keytype *r = new keytype();
            *r = x;
            return r;
        }
       // cout << "Node does not have a left subtree" << endl;
        node* y = temp->parent;
        int counter = 0;
        while(y!=nullptr&& temp == y->left){
            temp = y;
            y = y->parent;
        }
        // cout << "Broken the loop" << endl;
        if(y==nullptr&&temp->key>k){return NULL;}

        keytype x = y->key;
        keytype *r = new keytype();
        *r = x;
        return r;
        // node* temp = root;
        // cout << "trying to select node" << endl;
        // temp = selectNode(k,temp);
        // cout << "SELECTED!" << endl;
        // if(temp==nullptr){cout<<"nullptr, trying to return null" << endl; NULL;}
        // if(temp->left!=TNIL)
        // {
        //     keytype x = treeMax(temp->left);
        //     cout << "Maxed it" << endl;
        //     keytype *p = new keytype();
        //     *p = x;
        //     return p;
        // }
        // cout << "Left is empty" << endl;
        // node *y = temp->parent;
        // if(y==TNIL){return NULL;}
        // cout << "While Loop time" << endl;
        // while((y!=TNIL)&&temp==y->left)
        // {
        //     temp = y;
        //     y = y->parent;
        // }
        // keytype x = y->key;
        // keytype *p = new keytype();
        // *p = x;
        // return p;
        
    }


    int size(){return nodes;}


    /* Preorder Traversal of Tree
    *  
    */
    void preorder(){
        if(root==TNIL){return;} // Handles an empty tree
        node *n = root;
        printPreorder(n);
        cout << endl;
    }

    /* Inorder Traversal of Tree
    * Traverse the left subtree, i.e., call Inorder(left->subtree)
    * Visit the root.
    * Traverse the right subtree, i.e., call Inorder(right->subtree)
    */
    void inorder(){
        if(root==TNIL){return;} // Handles an empty tree
        node *n = root;
        printInorder(n);
        cout << endl;
    }

    /* Postorder Traversal of Tree
    * 
    */
    void postorder(){
        if(root==TNIL){return;} // Handles an empty tree
        node *n = root;
        printPostorder(n);
        cout << endl;
    }

    void test(){

    }
    void colorOf(keytype k) // Find K and return it's color
    {
        node *temp = root;
        bool x = colorSearch(k,temp);
        if(x){
            cout << "Key " << k << " is colored: RED" << endl;
        } else {
            cout << "Key " << k << " is colored: BLACK" << endl;
        }
    }

    void printRoot(){
        if(this->root->color==0){
            cout << "The root has a key of: " << this->root->key << ", and is colored: BLACK" << endl;
        } else {
            cout << "The root has a key of: " << this->root->key << ", and is colored: RED" << endl;
        }
    }


    int colored(node *n)
    {
        if(n->color==1){return 1;} else {return 0;}
    }

    int rootSize()
    {
        return root->sz;
    }

    void printk(keytype k)
    {
        node* n = selectNode(k,root);
        if(n->parent==nullptr){cout<<"This is the root, with key of " << n->key << " and value " << n->value<<endl; return;}
        cout << "Value of key: " << k << " is value: " << n->value << " and size is " << n->sz << ". It has parent: " << n->parent->key << endl;
    }

    void printChild(keytype k)
    {
        node *n = selectNode(k,root);
        if(n->left==TNIL&&n->right==TNIL)
        {
            cout << "The children of node with key " << k << " are NIL" << endl;
        }else if(n->left==TNIL){
            cout << "The children of node with key " << k <<" are left: NIL and right: " << n->right->key << endl;
        } else if (n->right==TNIL){
            cout << "The children of node with key " << k <<" are left: " <<n->left->key << " and right: NIL" << endl;
        } else {
             cout << "The children of node with key " << k <<" are left: " <<n->left->key << " and right: " << n->right->key << endl;
        }
    }

      void printChildClose(node* n)
    {
        if(n->left==TNIL&&n->right==TNIL)
        {
            cout << "The children of node with key " << n->key << " are NIL" << endl;
        }else if(n->left==TNIL){
            cout << "The children of node with key " << n->key <<" are left: NIL and right: " << n->right->key << endl;
        } else if (n->right==TNIL){
            cout << "The children of node with key " << n->key <<" are left: " <<n->left->key << " and right: NIL" << endl;
        } else {
             cout << "The children of node with key " << n->key <<" are left: " <<n->left->key << " and right: " << n->right->key << endl;
        }
    }
};