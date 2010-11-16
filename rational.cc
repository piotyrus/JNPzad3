/*
 * rational.cc
 *
 *  Created on: 2010-11-14
 *      Author: piotr
 */
#include <ostream>
#include "rational.h"

using namespace std;

/*class MyInt
    : boost::operators<Rational>
{
    bool operator<(const Rational& x) const;
    bool operator==(const Rational& x) const;
    Rational& operator+=(const Rational& x);
    Rational& operator-=(const Rational& x);
    Rational& operator*=(const Rational& x);
    Rational& operator/=(const Rational& x);
    Rational& operator%=(const Rational& x);
    Rational& operator^=(const Rational& x);
    Rational& operator++();
    Rational& operator--();
};*/

static Rational NaN(0L, 0UL);


int gcd(unsigned long a, unsigned long b){
	if(b == 0L)
		return a;
	else
		return gcd(b, a % b);
}

void Rational::opposite(){
	numerator = -numerator;

	return;
} // safe even for NaN since it doesn't change denominator

void Rational::reciprocal(){
	long temp;
	if (numerator == 0 || denominator == 0)
		this = NaN;
	else {
		temp = numerator;
		numerator = temp >= 0 ? denominator : -denominator;	//what about this conversion and sign?
		denominator = temp >= 0? temp : -temp;
	}
	return;
}

Rational& Rational::operator+=(const Rational& x){
						//check later for Nan additon!!
	if (!x.isNumber()){
		*this = NaN;
		return *this;
	}
	long lcm = (numerator * x.numerator)/gcd(numerator, x.numerator);
		//least common multiple
	numerator = (numerator * x.denominator + x.numerator * denominator)
			/gcd(numerator, x.numerator);
	denominator = lcm;
	return *this;
}

Rational& Rational::operator -=(const Rational& x){
						//check later for Nan additon!!
	Rational minus(x);
	minus.opposite();
	return *this += minus;
}

Rational& Rational::operator *=(const Rational& x){
	numerator *= x.numerator /gcd(denominator, x.numerator); //what about minus?
	denominator *= x.denominator /gcd(numerator, x.denominator);
	return *this;
}

Rational& Rational::operator /=(const Rational& x){
	Rational divide(x);
	*this *= divide.reciprocal();
	return *this;
}

Rational::Rational(){
	numerator = 0;
	denominator = 1;
}

Rational::Rational (long l){
	numerator = l;
	denominator = 1;
}

Rational::Rational(long n, unsigned long d){
	unsigned temp = n < 0 ? -n : n;  //czy to dobra konwersja int to unsigned?
	numerator = n / gcd(temp, d);
	denominator = d / gcd(temp, d);
}

Rational::Rational(const Rational& r){
	numerator = r.numerator;
	denominator = r.denominator;
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
	return denominator != 0;
}

ostream& operator<<(ostream& os, const Rational& r) {
  if (r.isNumber()){
	  os << r.numerator /r.denominator << " " << "/" << r.denominator;
  } else
	  os << "NaN";
  return os;
}

int main() {}
