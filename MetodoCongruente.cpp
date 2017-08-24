/*
 * MetodoCongruente.cpp
 *
 *  Created on: 21 de ago de 2017
 *      Author: root
 */

#include "MetodoCongruente.h"

MetodoCongruente::MetodoCongruente(int a, int c, unsigned int m, unsigned int z0) {
	// TODO Auto-generated constructor stub
	_a = a;
	_c = c;
	_m = m;
	_seed = z0;

}

MetodoCongruente::~MetodoCongruente() {
	// TODO Auto-generated destructor stub
}

int MetodoCongruente::GeraNumeroAleatorio(){
	this->_seed = ((_a * _seed + _c) % _m);
	return _seed;
}
