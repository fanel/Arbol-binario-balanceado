#include <iostream>
using namespace std;
#include <stdlib.h>
#pragma once

class dni {
public:
	int id;
	char letra;

	bool operator == (dni x){
		return ((id == x.id) && (letra == x.letra));
	}

	bool operator <= (dni x){
		if (id != x.id)
			return (id < x.id);
		else
			return ((int)letra <= (int)x.letra);
	}

	bool operator >= (dni x){
		if (id != x.id)
			return (id > x.id);
		else
			return ((int)letra >= (int)x.letra);
	}

	bool operator > (dni x){
		if (id != x.id)
			return (id > x.id);
		else
			return ((int)letra > (int)x.letra);
	}

	bool operator < (dni x){
		if (id != x.id)
			return (id < x.id);
		else
			return ((int)letra < (int)x.letra);
	}

	bool operator = (dni x){
		id = x.id;
		letra = x.letra;
	}

	operator int (){
		return (id);
	}

	dni (){
		id = rand()%100000000;
		letra = (char) (65 + rand()%26);
	}
};
