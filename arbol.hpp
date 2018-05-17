#include <stdio.h>
#include <iostream>
using namespace std;

class colisiones {
	int col;
public:
	void set (int n) {
		col = n;
	}
	int get () {
		return col;
	}
	
	colisiones (){col = 0;}
};

template <class T>
class nodoAVL{
public:
	nodoAVL <T>* left;
	nodoAVL <T>* right;
	nodoAVL <T>* padre;
	int balance;
	colisiones col;
	T dato;

	void actualizar (bool& desequilibrio = false, int& mayor = 0) {
		int may1, may2;
		if (left == NULL)
			may1 = 0;
		else
			left -> actualizar(desequilibrio, may1);

		if (right == NULL)
			may2 = 0;
		else
			right -> actualizar(desequilibrio, may2);

		mayor = (may1 > may2 ? may1 : may2) + 1;
		
		balance = may1 - may2;
		if ((balance > 1) || (balance < -1)) desequilibrio = true;
	}

	void printall () {
		bool haymas = true;
		int n = 0;
		while (haymas) {
			cout << "Nivel " << n << ": ";
			haymas = print (n);
			cout << endl;
			n++;
		}
		cout << "Nivel " << n << ": ";
		print (n);
		cout << endl;
	}

	bool print (int distancia) {
		if (distancia == 0) {
			cout << dato << " ";
			if ((right != NULL) || (left != NULL))
				return (true);
			else
				return (false);
		} else if (distancia > 0){
			bool haymas = false;
			if (left == NULL){
				if (distancia == 1) {
					cout << "[.] ";
				}
			} else {
				haymas = left -> print (distancia - 1);
			}
			if (right == NULL) {
				if (distancia == 1) {
					cout << "[.] ";
				}
			} else {
				haymas = ((haymas) || (right -> print (distancia - 1)));
			}
			return (haymas);
		}
	}

	nodoAVL (T d){
		left = right = padre = NULL;
		dato = d;
		balance = 0;
		col.set (0);
	}
	nodoAVL (){left = right = padre = NULL; balance = 0; col.set (0);}
};

template <class T>
class AVL{
public:
	int comp;
	nodoAVL <T>* abuelo;

	AVL (){abuelo = NULL;}

	void print () {
		if (abuelo != NULL)
			abuelo -> printall();
		else
			cout << "Nivel 0: [.]" << endl;
	}

	nodoAVL <T>* buscarn (T valor){
		comp = 0;
		nodoAVL <T>* n = abuelo;
		while (n != NULL){
			comp++;
			if (valor == n -> dato)
				return (n);
			else if (valor < n -> dato)
				n = n -> left;
			else
				n = n -> right;
		}
		return (NULL);
	}

	bool buscar (T valor) {
		if (buscarn (valor) != NULL)
			return (true);
		else
			return (false);
	}

	void insertar (T valor) {
		comp = 0;
		if (abuelo == NULL) {
			comp++;
			abuelo = new nodoAVL <T> (valor);
		} 
		else {
			nodoAVL<T>* nuevo;
			nodoAVL<T>* prenuevo;
			nuevo = prenuevo = abuelo;
			while (nuevo != NULL){
				comp++;
				prenuevo = nuevo;
				if (valor == nuevo -> dato) {
					nuevo -> col.set (nuevo -> col.get() + 1);
					return;
				}
				if (valor < nuevo -> dato)
					nuevo = nuevo -> left;
				else
					nuevo = nuevo -> right;
			}
			nuevo = new nodoAVL <T> (valor);
			if (valor > prenuevo -> dato) {
				prenuevo -> right = nuevo;
				prenuevo -> right -> padre = prenuevo;
			} else {
				prenuevo -> left = nuevo;
				prenuevo -> left -> padre = prenuevo;
			}
		}
		equilibrar(abuelo);
	}

	void eliminar (T valor){if (buscar (valor)){
		nodoAVL <T>* n = buscarn (valor);

		if (n != abuelo) {
			bool eszurdo;
			if (n -> padre -> left == n){
				n -> padre -> left = NULL;
				eszurdo = true;
			} else {
				n -> padre -> right = NULL;
				eszurdo = false;
			}

			if (n -> left != NULL) {
				if (eszurdo)
					n -> padre -> left = n -> left;
				else
					n -> padre -> right = n -> left;
				redist (n -> right);
			} else {
				if (eszurdo)
					n -> padre -> left = n -> right;
				else
					n -> padre -> right = n -> right;
			}
			delete n;
		} else {
			if (n -> left != NULL) {
				abuelo = n -> left;
				n -> left -> padre = NULL;
				redist (n -> right);
			} else {
				if (n -> right != NULL) n -> right -> padre = NULL;
				abuelo = n -> right;
			}
			delete n;
		}
		bool desequilibrio;
		do {
			equilibrar (abuelo);
			int k = 0;
			abuelo -> actualizar (desequilibrio, k);
		} while (desequilibrio);
	}}

	void redist (nodoAVL <T>* n) {if (n != NULL) {
		nodoAVL <T>* nodotemp;
		while ((n -> left != NULL) || (n -> right != NULL)){
			nodotemp = n;
			while ((nodotemp -> left != NULL) || (nodotemp -> right != NULL)){
				if (nodotemp -> left != NULL)
					nodotemp = nodotemp -> left;
				else
					nodotemp = nodotemp -> right;
			}
			if (nodotemp -> padre -> left == nodotemp)
				nodotemp -> padre -> left = NULL;
			else
				nodotemp -> padre -> right = NULL;
			insertar (nodotemp -> dato);
			delete nodotemp;
		}
		insertar (n -> dato);
		delete n;
	}}

	void equilibrar (nodoAVL <T>* n) {if (n != NULL){
		if (n -> left != NULL)
			equilibrar(n -> left);
		if (n -> right != NULL)
			equilibrar(n -> right);
		bool k1 = false;
		int k2 = 0;
		(*n).actualizar(k1,k2);
		
		nodoAVL <T>* &donde = (n==abuelo)? abuelo : ((*(*n).padre).left==n)? (*(*n).padre).left : (*(*n).padre).right;
		nodoAVL <T>* predonde = (n==abuelo)? NULL : (*n).padre;
		
		if (n -> balance <= -2) {
			switch (n -> right -> balance){
			case -1:
				donde = n -> right;
				donde -> padre = predonde;
				n -> right = donde -> left;
				if (n -> right != NULL)
					n -> right -> padre = n;
				donde -> left = n;
				n -> padre = donde;
				break;
			case 0:
				donde = n -> right;
				donde -> padre = predonde;
				n -> right = donde -> left;
				if (n -> right != NULL)
					n -> right -> padre = n;
				donde -> left = n;
				n -> padre = donde;
				break;
			case 1:
				donde = n -> right -> left;
				donde -> padre = predonde;
				n -> right -> left = donde -> right;
				if (n -> right -> left != NULL)
					n -> right -> left -> padre = n -> right;
				donde -> right = n -> right;
				donde -> right -> padre = donde;
				n -> right = donde -> left;
				if (n -> right != NULL)
					n -> right -> padre = n;
				donde -> left = n;
				n -> padre = donde;
				break;
			}
		} else if (n -> balance >= 2) {
			switch (n -> left -> balance){
			case -1:
				donde = n -> left -> right;
				donde -> padre = predonde;
				n -> left -> right = donde -> left;
				if (n -> left -> right != NULL)
					n -> left -> right -> padre = n -> left;
				donde -> left = n -> left;
				donde -> left -> padre = donde;
				n -> left = donde -> right;
				if (n -> left != NULL)
					n -> left -> padre = n;
				donde -> right = n;
				n -> padre = donde;
				break;
			case 0:
				donde = n -> left;
				donde -> padre = predonde;
				n -> left = donde -> right;
				if (n -> left != NULL)
					n -> left -> padre = n;
				donde -> right = n;
				n -> padre = donde;
				break;
			case 1:
				donde = n -> left;
				donde -> padre = predonde;
				n -> left = donde -> right;
				if (n -> left != NULL)
					n -> left -> padre = n;
				donde -> right = n;
				n -> padre = donde;
				break;

			}
		}
	}}
};
