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
	return *this *= divide;
}

Rational::Rational(){
	numerator = 0L;
	denominator = 1UL;
	isRational = true;
}

Rational::Rational (long l){
	numerator = l;
	denominator = 1;
	isRational = true;
}

Rational::Rational(long n, unsigned long d){
	unsigned temp = n < 0 ? -n : n;  //czy to dobra konwersja int to unsigned?
	numerator = n / gcd(temp, d);
	denominator = d / gcd(temp, d);
	isRational = (denominator != 0UL);
}

Rational::Rational(const Rational& r){
	numerator = r.numerator;
	denominator = r.denominator;
	isRational = r.isRational;
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
  if (r.isNumber()){
	  os << r.numerator /r.denominator << " " << "/" << r.denominator;
  } else
	  os << "NaN";
  return os;
}

int main() {}
