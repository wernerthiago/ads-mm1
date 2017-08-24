/*
 * MetodoCongruente.h
 *
 *  Created on: 21 de ago de 2017
 *      Author: root
 */

#ifndef METODOCONGRUENTE_H_
#define METODOCONGRUENTE_H_

class MetodoCongruente {
public:
	MetodoCongruente(int a, int c, unsigned int m, unsigned int z0);
	~MetodoCongruente();

	int GeraNumeroAleatorio();

protected:
    int _a, _c;
    unsigned int _m, _seed;
};

#endif /* METODOCONGRUENTE_H_ */
