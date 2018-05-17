#include "dni.hpp"
#include "arbol.hpp"
#include <iostream>
using namespace std;

void limite (int &num, int min, int max) {
	cin >> num;
	while ((num < min) || (num > max)) {
		cout << "Introduce un numero valido";
		cin >> num;
	}
}

int main (void) {
	int demo;
	cout << "Introduce [0] para demostracion o [1] para entrar en el modo estadistica.\n";
	limite (demo, 0, 1);
	if (demo == 0) {
		AVL <int> arbol;
		cout << "Introduce el numero de la opcion elegida:\n\t[0] Salir\n\t[1] Insertar clave\n\t[2] Eliminar clave\n(AVISO no se volveran a mostrar (memorizalas))\n";
		int opt;
		limite (opt, 0, 2);
		while (opt != 0) {
			switch (opt){
				case 1:
					cout << "Insertar: ";
					cin >> opt;
					cout << endl;
					arbol.insertar (opt);
					break;
				case 2:
					cout << "Eliminar: ";
					cin >> opt;
					cout << endl;
					arbol.eliminar (opt);
					break;
			}
			arbol.print();
			limite (opt, 0, 2);
		}
	} else {
		int seguir = 1;
		while (seguir == 1){
			int tam, pruebas;
			cout << "\n\tIntroduce el tamaño de arbol: ";
			limite (tam, 0, 1000000000);
			cout << "\n\tIntroduce el numero de pruebas a realizar: ";
			limite (pruebas, 0, 1000000000);
			dni* banco = new dni [tam * 2];
			AVL <dni> arbol;
			for (int a = 0; a < tam; a++){
				arbol.insertar (banco [a]);
			}
			int min, max, acum;
			arbol.buscar (banco [rand()%tam]);
			min = max = acum = arbol.comp;
			for (int a = 0; a < (pruebas - 1); a++){
				arbol.buscar (banco [rand()%tam]);
				acum += arbol.comp;
				if (arbol.comp > max)
					max = arbol.comp;
				if (arbol.comp < min)
					min = arbol.comp;
			}

			cout << "\t\t\t\tNumero de comparaciones\n\t\tTamano\tPruebas\tMinimo\tMedio\tMaximo\n";
			cout << "Busqueda\t" << tam <<"\t"<< pruebas <<"\t"<< min <<"\t"<< acum/pruebas <<"\t"<< max;

			arbol.insertar (banco [tam + rand()%tam]);
			min = max = acum = arbol.comp;
			for (int a = 0; a < (pruebas - 1); a++){
				arbol.insertar (banco [tam + rand()%tam]);
				acum += arbol.comp;
				if (arbol.comp > max)
					max = arbol.comp;
				if (arbol.comp < min)
					min = arbol.comp;
			}
			cout << "\nInsercion\t" << tam <<"\t"<< pruebas <<"\t"<< min <<"\t"<< acum/pruebas <<"\t"<< max << endl;
			cout << "\nSi desea continuar introduzca 1 o si no, cualquier otro valor: ";
			cin >> seguir;
		}
	}
}
