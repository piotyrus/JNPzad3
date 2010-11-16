/*
 * rational.cc
 *
 *  Created on: 2010-11-14
 *      Author: piotr
 */
#include <iostream>
#include <cstdio>
#include "rational.h"

using namespace std;


/*	this is the greatest common divisor function
 */
long gcd(unsigned long a, unsigned long b){
	if(b == 0UL)
		return a;
	else
		return gcd(b, a % b);
}

unsigned long abs(long a){
	return a >= 0 ? a : -a;
}

Rational::Rational(){
	numerator = 0L;
	denominator = 1UL;
	isRational = true;
}

Rational::Rational (long l){
	numerator = l;
	denominator = 1UL;
	isRational = true;
}

Rational::Rational(long n, unsigned long d){
	numerator = n;
	denominator = d;
	if (numerator != 0 && denominator != 0){
		numerator /= gcd(abs(n), d);
		denominator /= gcd(abs(n), d);
	}
	//cout << numerator << "/" << denominator << endl;
	isRational = (denominator != 0UL);
}

Rational::Rational(const Rational& r){
	numerator = r.numerator;
	denominator = r.denominator;
	isRational = r.isRational;
}

void Rational::opposite(){
	numerator = -numerator;

	return;
}

void Rational::reciprocal(){
	long temp;

	temp = numerator;
	numerator = temp >= 0 ? denominator : -denominator;	//what about this conversion and sign?
	denominator = temp >= 0? temp : -temp;
	/* swap values, check if it is still proper number */
	if (denominator == 0)
		isRational = false;

	return;
}

Rational& Rational::operator+=(const Rational& x){
						//check later for Nan additon!!
	if (!x.isRational){
		isRational = false;
	}
	long lcm = (denominator * x.denominator)/gcd(denominator, x.denominator);
		//least common multiple
	numerator = (numerator * x.denominator + x.numerator * denominator)
			/gcd(numerator, x.numerator);
	denominator = lcm;
	return *this;
}

Rational& Rational::operator -=(const Rational& x){
	Rational minus(x);
	minus.opposite();
	*this += minus;
	return *this;
}

Rational& Rational::operator *=(const Rational& x){
	if (!x.isRational){
		isRational = false;
	}
	numerator *= x.numerator /gcd(denominator, x.numerator); //what about minus?
	denominator *= x.denominator /gcd(numerator, x.denominator);
	return *this;
}

Rational& Rational::operator /=(const Rational& x){
	Rational divide(x);
	divide.reciprocal();
	*this *= divide;
	return *this;
}


const Rational& operator+(const Rational& a, const Rational& b){
  Rational c(a);
  return c += b;
}

const Rational& operator-(const Rational& a, const Rational& b){
  Rational c(a);
  return c -= b;
}

const Rational& operator*(const Rational& a, const Rational& b) {
  Rational c(a);
  return c *= b;
}

const Rational& operator/(const Rational& a, const Rational& b){
  Rational c(a);
  return c /= b;
}

/*const Rational& operator>(const Rational& a, const Rational& b){
  return b <= a;		//?? co jak zwroci false ze wzgledu na NaN  ??
}*/

bool Rational::isNumber() const{
	return isRational;
}

ostream& operator<<(ostream& os, const Rational& r) {
  if (r.isRational){
	  if (abs(r.numerator) / r.denominator > 0){
		  if (r.numerator < 0)
			  os << "-";
		  os << abs(r.numerator) /r.denominator;
		  if (abs(r.numerator) % r.denominator > 0 && r.numerator > 0)
			  os << "+";
	  } else if (abs(r.numerator) % r.denominator == 0){
			  os << 0L;
		  }
	  if (abs(r.numerator) % r.denominator > 0){
		  if (r.numerator < 0)
			  os << "-";
		  os << abs(r.numerator) % r.denominator << "/" <<r.denominator;
	  }

  } else
	  os << "NaN";
  return os;
}

int main() {
	Rational a;
	cout << a << endl;
	Rational b(a);
	cout << b << endl;
	Rational c(1L);
	cout << c << endl;
	Rational d(8L, 5UL);
	cout << d << endl;
	c /= d;
	cout << c << endl;
}
