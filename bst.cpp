#ifndef BST
#define BST
#include <iostream>
#include <map>

using namespace std;

template <typename T>
struct Node {
    int key; 
    T value;
    Node * nextLeft;
    Node * nextRight;
};


template <typename T>
Node <T> * createTree(int keys, T value) {
    Node <T> * root;
    root = new Node<T>;
    root->key= keys;
    root->value = value;
    return root;
    
};
template <typename T>
void insertLeft(Node <T> * root, int newKey,  T value){
    root->nextLeft = createTree(newKey, value);
};
template <typename T>
void insertRight(Node <T> * root, int newKey, T value){
    root->nextRight = createTree(newKey, value);
};

template <typename T>
Node <T> * getLeft(Node <T> *root){
    return root->nextLeft;
};

template <typename T>
Node <T> * getRight(Node <T> *root){
    return root->nextRight;
}

template <typename T>
void deleteLeft(Node <T> * root){
    Node <T> * left = root->nextLeft;
    root->nextLeft = NULL;
    free(left);
}

template <typename T>
void deleteRight(Node <T> * root){
    Node <T> * right = root->nextRight;
    root->nextRight = NULL;
    free(right);
}

template <typename T>
class Binary {
    private:

    void traverse(Node <T> * node, Node <T> * newNode){
       // assert(node->key);

        if (node->key > newNode->key){
            if (node->nextLeft){
                traverse(getLeft(node), newNode);
            }
            else {
                node->nextLeft = newNode;
            }
        }

        else if (node->key < newNode->key){
            if (node->nextRight){
                traverse(getRight(node), newNode);
            }
            else {
                node->nextRight = newNode;
            }
        }

    }   

    
     
    T traverseKey(Node <T> * node, int key){
        if (node->key == key){
            return node->value;
        }
        else if (node->key > key){
            if (!node->nextLeft){
                T t; 
                return t;
            }
           return traverseKey(getLeft(node), key);
        }
        else {
            if (!node->nextRight){
                T t; 
                return t;
            }
            return traverseKey(getRight(node), key);
        }

    };

    Node  <T> * returnNodeRight(Node <T> * node){
        Node  <T> *  newNode;
        
        if (node->nextLeft){
            newNode = returnNodeRight(getLeft(node));

            if (!getLeft(newNode)->nextLeft){
                newNode->nextLeft = nullptr;

                delete newNode->nextLeft;
            }

            return newNode;
        }
        else {
            
            return node;
        }
    }

    void show(Node <T> * node){
        cout << node->key << endl;

        if (node->nextLeft){
            show(getLeft(node));
        };
        if (node->nextRight){
            show(getRight(node));
        };
    };

    int caseDetermine(Node<T> * node){
        if (node->nextLeft && node->nextRight){
            // both children
            return 1;
        }
        else if (node->nextLeft){
            // one child left
            return 2;
        }
        else if (node->nextRight){
            // one child right
            return 3;
        }
        else {
            // no children
            return 4;
        }
    }

    void traverseDeleteLeft(int key, Node <T> * node){
        
        
        if (node->nextLeft){
            Node <T> * newNode;
            
            if (getLeft(node)->key == key){
                // Check for case 1, 2, 3
                
                switch (caseDetermine(getLeft(node))){
                    case 1:
                        newNode = returnNodeRight(getRight(node));
                        newNode->nextLeft = getLeft(node);
                        node->nextLeft = newNode;
                        
                        break;
                        
                    case 2:
                        
                        node->nextLeft = getLeft(node->nextLeft);
                        break;
                    case 3:
                        
                        node->nextLeft = getRight(node->nextLeft);
                        break;

                    case 4:
                        node->nextLeft = nullptr;
                        delete node->nextLeft;
                        break;
                }
            }

            else {
                // check for which is larger
                if (getLeft(node)->key > key){
                    traverseDeleteLeft(key, getLeft(node));
                }
                else{
                    traverseDeleteRight(key, getLeft(node));
                }
            }
        }

    }

    void traverseDeleteRight(int key, Node <T> *node){
        
         if (node->nextRight){
              Node <T> * newNode;
              
            if (getRight(node)->key == key){
                
               switch (caseDetermine(getRight(node))){
                    case 1:
                        newNode = returnNodeRight(getRight(node));
                        newNode->nextLeft = getLeft(node);
                        node->nextRight = newNode;
                        break;
                    case 2:
                        node->nextRight = getLeft(node->nextRight);
                        break;
                    case 3:
                        node->nextRight = getRight(node->nextRight);
                        break;

                    case 4:
                        node->nextRight = nullptr;
                        delete node->nextRight;
                        break;
                };
            }
            else {
                // check where to go
                if (getRight(node)->key < key){
                    traverseDeleteRight(key, getRight(node));
                }
                else{
                    traverseDeleteLeft(key, getRight(node));
                }
            }
        }

    }

    public:
    Node <T> * root;
    Binary(int rootKey, T value){
        root = createTree <T>(rootKey, value);
    };

    void addValuePair(int key, T value){
        Node <T> * node = createTree(key, value);
        if (!root){
            root =  node;
        }
        if (root->key > key){
            if (root->nextLeft){
                traverse(getLeft(root), node);
            }
            else {
                insertLeft(root, key, value);
            }
            
            
        }
        else if (root->key < key){
            if (root->nextRight){
                traverse(getRight(root), node);
            }
            else {
                insertRight(root, key, value);
            }   

        }

    }

    void showTree(){
        // We wanna show the keys
        if (!root) {
            cout << "No root" << endl;
        }
        else{
            cout << root->key << endl;
        if (root->nextLeft)
        show(getLeft(root));
        if (root->nextRight)
        show(getRight(root));
        }
        
    
};

    T getValue(int key){
        if (!root){
            T t;
            return t;
        }

        if (root-> key == key){
            return root->value;
        }

        else if (root-> key > key){
            assert(root->nextLeft);
            return traverseKey(getLeft(root), key);
        }
        else {
            assert(root->nextRight);
            return traverseKey(getRight(root), key);
        }
    };

    

    void deleteNode(int key){
        if (root->key == key){
            if (root->nextLeft && root->nextRight){
                
                Node <T> * newRoot = returnNodeRight(getRight(root));
                newRoot->nextLeft = getLeft(root);
                root = newRoot;
            }
            else if (root->nextLeft){
                root = root->nextLeft;
            }
            else if (root->nextRight){
                root = root->nextRight;
            }
            else {
                root = nullptr;
                delete root;
            }

        }
    
        else if (root->key > key){
            
            if (root->nextLeft)
            traverseDeleteLeft(key, root);
        }

        else {
            if (root->nextRight)
            traverseDeleteRight(key, root);
        }

};

};



#endif