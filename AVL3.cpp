// C++ program to insert a node in AVL tree  
#include<bits/stdc++.h> 
#include<chrono>

using namespace std; 
using namespace std::chrono;

template <class T>
// An AVL tree node  
class Node  
{  
    public: 
    int key;  
    Node *left;  
    Node *right;  
    int height;  
};  

template<class T> 
// A utility function to get maximum 
// of two integers  
int max(int a, int b);  
  

// A utility function to get the  
// height of the tree 
template<class T> 
T height(Node<T> *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
}  
  
// A utility function to get maximum 
// of two integers 
template<class T> 
int max(int a, int b)  
{  
    return (a > b)? a : b;  
}  
  
/* Helper function that allocates a  
   new node with the given key and  
   NULL left and right pointers. */

template <class T>
Node<T>* newNode(T key)  
{  
    Node<T>* node = new Node<T>(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; // new node is initially 
                      // added at leaf  
    return(node);  
}  
  
// A utility function to right 
// rotate subtree rooted with y  
// See the diagram given above.  
template <class T>
Node<T> *rightRotate(Node<T> *y)  
{  
    Node<T> *x = y->left;  
    Node<T> *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = max(height(y->left), 
                    height(y->right)) + 1;  
    x->height = max(height(x->left), 
                    height(x->right)) + 1;  
  
    // Return new root  
    return x;  
}  
  
// A utility function to left  
// rotate subtree rooted with x  
// See the diagram given above.
template <class T>  
Node<T> *leftRotate(Node<T> *x)  
{  
    Node<T> *y = x->right;  
    Node<T> *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height(x->left),     
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
  
// Get Balance factor of node N  
template<class T>
T getBalance(Node<T> *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) - height(N->right);  
}  
  
// Recursive function to insert a key 
// in the subtree rooted with node and 
// returns the new root of the subtree.
template <class T>  
Node<T>* insert(Node<T>* node, T key)  
{  
    /* 1. Perform the normal BST insertion */
    if (node == NULL)  
        return(newNode(key));  
  
    if (key < node->key)  
        node->left = insert(node->left, key);  
    else if (key > node->key)  
        node->right = insert(node->right, key);  
    else // Equal keys are not allowed in BST  
        return node;  
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),  
                        height(node->right));  
  
    /* 3. Get the balance factor of this ancestor  
        node to check whether this node became  
        unbalanced */
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, then  
    // there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && key < node->left->key)  
        return rightRotate(node);  
  
    // Right Right Case  
    if (balance < -1 && key > node->right->key)  
        return leftRotate(node);  
  
    // Left Right Case  
    if (balance > 1 && key > node->left->key)  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && key < node->right->key)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}  

/* Given a non-empty binary search tree,  
return the node with minimum key value  
found in that tree. Note that the entire  
tree does not need to be searched. */
template<class T>
Node<T> * minValueNode(Node<T>* node)  
{  
    Node<T>* current = node;  
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}  

// Recursive function to delete a node  
// with given key from subtree with  
// given root. It returns root of the  
// modified subtree.  
template<class T>
Node<T>* deleteNode(Node<T>* root, int key)  
{  
      
    // STEP 1: PERFORM STANDARD BST DELETE  
    if (root == NULL)  
        return root;  
  
    // If the key to be deleted is smaller  
    // than the root's key, then it lies 
    // in left subtree  
    if ( key < root->key )  
        root->left = deleteNode(root->left, key);  
  
    // If the key to be deleted is greater  
    // than the root's key, then it lies  
    // in right subtree  
    else if( key > root->key )  
        root->right = deleteNode(root->right, key);  
  
    // if key is same as root's key, then  
    // This is the node to be deleted  
    else
    {  
        // node with only one child or no child  
        if( (root->left == NULL) || 
            (root->right == NULL) )  
        {  
            Node<T> *temp = root->left ?  
                         root->left :  
                         root->right;  
  
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else // One child case  
            *root = *temp; // Copy the contents of  
                           // the non-empty child  
            free(temp);  
        }  
        else
        {  
            // node with two children: Get the inorder  
            // successor (smallest in the right subtree)  
            Node<T>* temp = minValueNode(root->right);  
  
            // Copy the inorder successor's  
            // data to this node  
            root->key = temp->key;  
  
            // Delete the inorder successor  
            root->right = deleteNode(root->right,  
                                     temp->key);  
        }  
    }  
  
    // If the tree had only one node 
    // then return  
    if (root == NULL)  
    return root;  
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
    root->height = 1 + max(height(root->left),  
                           height(root->right));  
  
    // STEP 3: GET THE BALANCE FACTOR OF  
    // THIS NODE (to check whether this  
    // node became unbalanced)  
    int balance = getBalance(root);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 &&  
        getBalance(root->left) >= 0)  
        return rightRotate(root);  
  
    // Left Right Case  
    if (balance > 1 &&  
        getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
  
    // Right Right Case  
    if (balance < -1 &&  
        getBalance(root->right) <= 0)  
        return leftRotate(root);  
  
    // Right Left Case  
    if (balance < -1 &&  
        getBalance(root->right) > 0)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    return root;  
}  
template<class T>
int obtenerProfundidad(Node<T>* node, T key, T profundidad){
    //Vars here

    if ((key == node->key) || (node->right == NULL && node->left == NULL)){
        if(key==node->key){
            cout<<"La profundidad del nodo es: "<<profundidad<<endl;
            return profundidad;
        }
        else{
            cout<<"El nodo no se encuentra en el árbol, no se puede dar la profundidad"<<endl;
            return -1;
        }
    }
    
    if (key < node->key)  
        obtenerProfundidad(node->left, key, profundidad +1);  
    else {
        obtenerProfundidad(node->right, key, profundidad + 1); 
    }
}

template<class T>
int search(Node<T>* node, T key){
    //Vars here

    if ((key == node->key) || (node->right == NULL && node->left == NULL)){
        if(key==node->key){
            cout<<"Nodo encontrado"<<endl;
            return 1;
        }
        else{
            cout<<"Nodo NO encontrado"<<endl;
            return -1;
        }
    }

    if (key < node->key)  
        search(node->left, key);  
    else {
        search(node->right, key); 
    }
}

template<class T>
int obtenerAltura(Node<T>* node, T key){
    //Vars here

    if ((key == node->key) || (node->right == NULL && node->left == NULL)){
        if(key==node->key){
            cout<<"La altura del nodo es: "<<height(node)-1<<endl;
            return 1;
        }
        else{
            cout<<"Nodo NO encontrado"<<endl;
            return -1;
        }
    }

    if (key < node->key)  
        obtenerAltura(node->left, key);  
    else {
        obtenerAltura(node->right, key); 
    }
}



// A utility function to print preorder  
// traversal of the tree.  
// The function also prints height  
// of every node  
template<class T>
void preOrder(Node<T> *root)  
{  
    if(root != NULL)  
    {  
        cout << root->key << " ";  
        preOrder(root->left);  
        preOrder(root->right);  
    }  
}  

template <class T>
void inOrder(Node<T> *root)  
{  
    if(root != NULL)  
    {  
        inOrder(root->left);
        cout << root->key << " ";  
        inOrder(root->right);  
    }  
}  

template <class T>
void reverse(Node<T> *root)  
{  
    if(root != NULL)  
    {   
        reverse(root->right); 
        cout << root->key << " ";  
        reverse(root->left);
        
         
    }  
}  
  
// Driver Code 
int main()  
{  
    //Vars here
    Node<int> *root = NULL;  
    int profundidad = 0, k=1000000, buscar=0, numBuscar=0, numEliminar=0, numAgregar=0, numProfundidad=0, numAltura=0;

    //Demostrando todos los métodos

    //Insertando los 100,000 números aleatorios
    srand(time(NULL));

    root=insert(root, 857898);
    root=insert(root, 344154);
    root=insert(root, 127590);
    root=insert(root, 5027);
    root=insert(root, 4925);
    root=insert(root, 880343);
    root=insert(root, 600025);
    root=insert(root, 386632);
    root=insert(root, 486084);
    root=insert(root, 18);

    for(int i=0; i<99991; i++){
        numAgregar = rand()%k;
        root=insert(root, numAgregar);
    }//End of for

    inOrder(root);  
    cout<<endl;

    //Función Buscar
    cout<<"Número a buscar: ";
    cin>>numBuscar;
    cout<<""<<endl;

    auto start = high_resolution_clock::now();
    buscar = search(root, numBuscar);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout<<"Tiempo de búsqueda: "<<duration.count()<<" microsegundos"<<endl; 


    //Impresión ordenada ascendentemente
    inOrder(root);  
    cout<<endl;

    //Borrar
    cout<<"Número a eliminar: ";
    cin>>numEliminar;
    cout<<" "<<endl;
    root = deleteNode(root, numEliminar);

    //Impresión ordenada descendentemente
    reverse(root);
    cout<<""<<endl;
    cout<<""<<endl;

    //Obtener altura -> dirá la altura del nodo que se buscó
    cout<<"Obtener altura de: ";
    cin>>numAltura;
    cout<<""<<endl;
    obtenerAltura(root, numAltura);

    //Obtener profundidad -> dirá la profundidad del nodo que se buscó
    cout<<"Obtener profundidad de: ";
    cin>>numProfundidad;
    cout<<""<<endl;
    obtenerProfundidad(root, numBuscar, 0);

    return 0;  
}  


//Algunas secciones del código AVL fueron obtenidas de https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
