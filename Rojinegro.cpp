#include <iostream>
#include <stdio.h>
#include <ctime>
#include <chrono>
#include <bits/stdc++.h>
#include <queue>

using namespace std::chrono;
using namespace std;

enum COLOR { RED, BLACK };

template <class T>
class Node {
public:
T val;
COLOR color;
Node<T> *left, *right, *parent;


Node<T>(T val) : val(val) {
	parent = left = right = NULL;


	color = RED;
}


Node<T> *uncle() {
	if (parent == NULL or parent->parent == NULL)
	return NULL;

	if (parent->isOnLeft())
	return parent->parent->right;
	else
	return parent->parent->left;
}

bool isOnLeft() { return this == parent->left; }

Node *sibling() {
	if (parent == NULL)
	return NULL;

	if (isOnLeft())
	return parent->right;

	return parent->left;
}

void moveDown(Node<T> *nParent) {
	if (parent != NULL) {
	if (isOnLeft()) {
		parent->left = nParent;
	} else {
		parent->right = nParent;
	}
	}
	nParent->parent = parent;
	parent = nParent;
}

bool hasRedChild() {
	return (left != NULL and left->color == RED) or
		(right != NULL and right->color == RED);
}
};

template <class T>
class RBTree {
Node<T> *root;

void leftRotate(Node<T> *x) {
	Node<T> *nParent = x->right;

	if (x == root)
	root = nParent;

	x->moveDown(nParent);

	x->right = nParent->left;
	if (nParent->left != NULL)
	nParent->left->parent = x;

	nParent->left = x;
}


void rightRotate(Node<T> *x) {
	Node<T> *nParent = x->left;

	if (x == root)
	root = nParent;

	x->moveDown(nParent);

	x->left = nParent->right;

	if (nParent->right != NULL)
	nParent->right->parent = x;

	nParent->right = x;
}


void swapColors(Node<T> *x1, Node<T> *x2) {
	COLOR temp;
	temp = x1->color;
	x1->color = x2->color;
	x2->color = temp;
}


void swapValues(Node<T> *u, Node<T> *v) {
	int temp;
	temp = u->val;
	u->val = v->val;
	v->val = temp;
}

void fixRedRed(Node<T> *x) {
	if (x == root) {
	x->color = BLACK;
	return;
	}

	Node<T> *parent = x->parent, *grandparent = parent->parent,
		*uncle = x->uncle();

	if (parent->color != BLACK) {
	if (uncle != NULL && uncle->color == RED) {
		parent->color = BLACK;
		uncle->color = BLACK;
		grandparent->color = RED;
		fixRedRed(grandparent);
	} else {
		if (parent->isOnLeft()) {
		if (x->isOnLeft()) {
			swapColors(parent, grandparent);
		} else {
			leftRotate(parent);
			swapColors(x, grandparent);
		}
		rightRotate(grandparent);
		} else {
		if (x->isOnLeft()) {
			rightRotate(parent);
			swapColors(x, grandparent);
		} else {
			swapColors(parent, grandparent);
		}

		leftRotate(grandparent);
		}
	}
	}
}

Node<T> *successor(Node<T> *x) {
	Node<T> *temp = x;

	while (temp->left != NULL)
	temp = temp->left;

	return temp;
}

Node<T> *BSTreplace(Node<T> *x) {
	if (x->left != NULL and x->right != NULL)
	return successor(x->right);

	if (x->left == NULL and x->right == NULL)
	return NULL;

	if (x->left != NULL)
	return x->left;
	else
	return x->right;
}

void deleteNode(Node<T> *v) {
	Node<T> *u = BSTreplace(v);

	bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
	Node<T> *parent = v->parent;

	if (u == NULL) {
	if (v == root) {
		root = NULL;
	} else {
		if (uvBlack) {

		fixDoubleBlack(v);
		} else {
		if (v->sibling() != NULL)
			v->sibling()->color = RED;
		}

		if (v->isOnLeft()) {
		parent->left = NULL;
		} else {
		parent->right = NULL;
		}
	}
	delete v;
	return;
	}

	if (v->left == NULL or v->right == NULL) {
	if (v == root) {
		v->val = u->val;
		v->left = v->right = NULL;
		delete u;
	} else {
		if (v->isOnLeft()) {
		parent->left = u;
		} else {
		parent->right = u;
		}
		delete v;
		u->parent = parent;
		if (uvBlack) {
		fixDoubleBlack(u);
		} else {
		u->color = BLACK;
		}
	}
	return;
	}

	swapValues(u, v);
	deleteNode(u);
}

void fixDoubleBlack(Node<T> *x) {
	if (x == root)
	return;

	Node<T> *sibling = x->sibling(), *parent = x->parent;
	if (sibling == NULL) {
	fixDoubleBlack(parent);
	} else {
	if (sibling->color == RED) {
		parent->color = RED;
		sibling->color = BLACK;
		if (sibling->isOnLeft()) {
		rightRotate(parent);
		} else {
		leftRotate(parent);
		}
		fixDoubleBlack(x);
	} else {
		if (sibling->hasRedChild()) {
		if (sibling->left != NULL and sibling->left->color == RED) {
			if (sibling->isOnLeft()) {
			sibling->left->color = sibling->color;
			sibling->color = parent->color;
			rightRotate(parent);
			} else {
			sibling->left->color = parent->color;
			rightRotate(sibling);
			leftRotate(parent);
			}
		} else {
			if (sibling->isOnLeft()) {
			sibling->right->color = parent->color;
			leftRotate(sibling);
			rightRotate(parent);
			} else {
			sibling->right->color = sibling->color;
			sibling->color = parent->color;
			leftRotate(parent);
			}
		}
		parent->color = BLACK;
		} else {
		sibling->color = RED;
		if (parent->color == BLACK)
			fixDoubleBlack(parent);
		else
			parent->color = BLACK;
		}
	}
	}
}

void levelOrder(Node<T> *x) {
	if (x == NULL)
	return;

	queue<Node<T> *> q;
	Node<T> *curr;

	q.push(x);

	while (!q.empty()) {
	curr = q.front();
	q.pop();

	cout << curr->val << " ";

	if (curr->left != NULL)
		q.push(curr->left);
	if (curr->right != NULL)
		q.push(curr->right);
	}
}

void inorder(Node<T> *x) {
	if (x == NULL)
	return;
	inorder(x->left);
	cout << x->val << " ";
	inorder(x->right);
}



public:

RBTree() { root = NULL; }

Node<T> *getRoot() { return root; }

Node<T> *search(int n) {
	Node<T> *temp = root;
	while (temp != NULL) {
	if (n < temp->val) {
		if (temp->left == NULL)
		break;
		else
		temp = temp->left;
	} else if (n == temp->val) {
		break;
	} else {
		if (temp->right == NULL)
		break;
		else
		temp = temp->right;
	}
	}

	return temp;
}

void insert(T n) {
	Node<T> *newNode = new Node<T>(n);
	if (root == NULL) {

	newNode->color = BLACK;
	root = newNode;
	} else {
	Node<T> *temp = search(n);

	if (temp->val == n) {
		return;
	}


	newNode->parent = temp;

	if (n < temp->val)
		temp->left = newNode;
	else
		temp->right = newNode;


	fixRedRed(newNode);
	}
}

void deleteByVal(T n) {
	if (root == NULL)
	return;

	Node<T> *v = search(n), *u;

	if (v->val != n) {
	cout << "No node found to delete with value:" << n << endl;
	return;
	}

	deleteNode(v);
}

void printInOrder() {
	cout << "Inorder: " << endl;
	if (root == NULL)
	cout << "Tree is empty" << endl;
	else
	inorder(root);
	cout << endl;
}

void printLevelOrder() {
	cout << "Level order: " << endl;
	if (root == NULL)
	cout << "Tree is empty" << endl;
	else
	levelOrder(root);
	cout << endl;
}

int heightHelper(Node<T> * n) const{
        if ( n == NULL ){
            return -1;
        }
        else{
            return max(heightHelper(n->left), heightHelper(n->right)) + 1;
        }
    }

int max(int x, int y) const{
    if (x >= y){
        return x;
    }
    else{
        return y;
    }
}


};



template <class T>
void Ascendente(T arr[], T tamArreglo){

	sort(arr, arr+tamArreglo);

	cout << "El arreglo en orden ascendente es " << endl;

	for (int i = 0; i < tamArreglo; ++i){
        cout << arr[i] << " ";
		}

		cout << "\n";

};

template <class T>
void Descendente(T arr[], T tamArreglo){

	sort(arr, arr+tamArreglo);

	cout << "El arreglo en orden descendente es " << endl;

	for (int i = tamArreglo; i > 0; --i){
        cout << arr[i] << " ";
		}

		cout << "\n";

};

template <class T>
void Buscar(T arr[], T tamArreglo, T n){
	sort(arr, arr+tamArreglo);

	bool res=false;
	int i=0;
	while(i<tamArreglo && res!=true){
		if(arr[i]==n){
			res=true;
		}
		else{
			i++;
		}
	}

	if(arr[i]==n){
		cout<<"El valor si está en el arbol"<<" ";
	}
	else{
		cout<<"El valor no se encuentra en el arbol"<<" ";
	}
		cout << "\n";
};

template<class T>
int obtenerProfundidad(Node<T>* node, T val, T profundidad){

    if ((val == node->val) || (node->right == NULL && node->left == NULL)){
        if(val==node->val){
            cout<<"La profundidad del árbol es: "<<profundidad<<endl;
            return profundidad;
        }
        else{
            cout<<"El nodo no se encuentra en el árbol"<<endl;
            return -1;
        }
    }

    if (val < node->val)
        obtenerProfundidad(node->left, val, profundidad +1);
    else {
        obtenerProfundidad(node->right, val, profundidad + 1);
    }
}





int main() {

	RBTree<int> tree;
	Node<int> *root=NULL;
	int tamArreglo, delVal, cant, newVal, tamRand, opcion, buscado;
		int profundidad;
		//profundidad=obtenerProfundidad(root, 25, 0);
		tree.heightHelper(root);

		tamRand = 1000000;
		tamArreglo = 100000;

		tamArreglo = tamArreglo * 2;

		int arr[tamArreglo];

		//srand((unsigned)time(0));

		for (int cont = 0; cont < tamArreglo; cont++) {

			arr[cont] = (rand()%tamRand);
		}

		int n = sizeof(arr)/sizeof(arr[0]);

		for (size_t i = 0; i < tamArreglo; i++) {
			tree.insert(arr[i++]);
		}

		tree.printInOrder();
		tree.printLevelOrder();

		cout << "Inserta un valor" << '\n';
		cin >> newVal;
		cout << "\n";

		tree.insert(newVal);


		cout << "Inserta el valor que se va a borrar" << '\n';
		cin >> delVal;
		cout << "\n";
		tree.deleteByVal(delVal);


		cout << "Que valor desea buscar?" << '\n';

			cin >> buscado;

			cout << '\n';
			auto start = high_resolution_clock::now();

			Buscar(arr, tamArreglo, buscado);


			auto stop = high_resolution_clock::now();

			auto durationMilli = duration_cast<milliseconds>(stop-start);

			cout << "\n";

			cout << "Le tomo " << durationMilli.count() << " milisegundos\n";

			cout << "\n";
			//Ascendente(arr, tamArreglo);
			//Descendente(arr, tamArreglo);

	return 0;

}

//Algunos metodos fueron obtenidos de https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
