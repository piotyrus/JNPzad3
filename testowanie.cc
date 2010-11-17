/*
 * testowanie.cc
 *
 *  Created on: 2010-11-17
 *      Author: piotr
 *
 *
 *      	void wypisz() const; do metod public Rational
 */
#include <iostream>
#include <cstdio>
#include <cassert>
#include "rational.h"
/*void writeValues(Rational a, Rational b, Rational c,
		Rational d, Rational e, Rational f, Rational g){
	cout << "testing values of numbers:" << endl;
	cout << "a = "<< a << endl;
	cout << "b = "<< b << endl;
	cout << "c = "<< c << endl;
	cout << "d = "<< d << endl;
	cout << "e = "<< e << endl;
	cout << "f = "<< f  << endl;
	cout << "g = "<< g << endl << endl;
}

void Rational::wypisz() const{
	cout<< "numerator = " << numerator << " denominator = " << denominator
			<< " a this = " << *this << endl;
}*/
using namespace std;

int main() {
	/* testing constructors */
	Rational a;
	assert(a == Zero());
	Rational b(a);
	assert(b == a);
	Rational c(-5L);
	assert(5 == -c);
	assert(One() != c);
	Rational d(8, 2);
	assert(d == 4);
	Rational e(5, 5);
	assert(e == One());
	Rational f(5, 0);
	Rational g(0, 5);
	assert ((f != c) == false);
	assert ((f == c) == false);
	assert (!a);
	assert (!f);
	assert (!g);
	assert (d);

	/* now testing assign operator */
	b = e;
	assert(b != a);
	b = Rational();
	b = Rational(1);
	b = Rational(5, 2);
	b = Rational(b);
	assert (b == Rational(5, 2));
	b = 1/b;
	assert (Rational(2, 5) == b);

	/* testing other comparision operators
	 * g = 0, f = NaN, e = 1, d = 4, c = -5, b = 2,5, a = 0
	 */
	//writeValues(a, b, c, d, e, f, g);

	assert(Zero() < One());
	g += 5;
	assert(-5 == -g);
	assert(-g == -g);
	a -= g;
	assert (a < 10L);
	assert (g > 0);
	assert (a < g);
	assert(g > 0);
	assert(-g <= 0);
	assert(0 < g);
	assert(g > Zero());
	assert(6 >= Rational(6));
	a = c / d;
	assert(a == Rational(-5, 4));
	b = g / d;
	assert(b == Rational(5, 4));
	assert (a == -b);
	f += a + c;
	assert(f.isNumber() == false);
	f = c / d;
	assert (f == Rational(-5, 4));
	//f += c;
	//assert(f.isNumber());
	//assert(f == Rational(-25, 4));

	/* Testing other arithmetic operators
	 * g = 5, f = -1-1/4, e = 1, d = 4, c = -5, b = 1+1/4, a = -1-1/4
	 */
	//writeValues(a,b,c,d,e,f,g);
	a += b;
	assert(a == Zero());
	f -= g;
	assert (f < -6);
	assert (-6 > f);
	assert (b < 5);
	assert (b <= 5);
	//assert (b > 5);
	//assert (b >= 5);
	d *=  b;
	assert(d >= 5);
	assert(d <= 5);
	assert(d == 5);
	cout << d;

	//writeValues(a,b,c,d,e,f,g);

}

