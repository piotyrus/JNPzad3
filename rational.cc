/*
 * rational.cc
 *
 *  Created on: 2010-11-14
 *      Author: piotr
 */
#include <iostream>
#include <cstdio>
#include <cassert>
#include "rational.h"

using namespace std;


/*	this is the greatest common divisor function
 *  that takes two nonnegative arguments
 *  so unsigned...
 */
long gcd(unsigned long a, unsigned long b){
	if(b == 0UL)
		return a;
	else
		return gcd(b, a % b);
}

/* Global function which creates Rational constant
 * 0 and returns adress to it
 */
const Rational& Zero(){
	static const Rational zero = Rational(0L);
	return zero;
}

/* Global function which creates Rational constant
 * 1 and returns adress to it
 */
const Rational& One(){
	static const Rational one = Rational(1L);
	return one;
}

/* Series of constructors: without any argument,
 * with one long (long conversion), with long and
 * unsigned (true rational) and a copy constructor
 */

Rational::Rational(){
	numerator = 0L;
	denominator = 1UL;
	isRational = true;
}

Rational::Rational (long l){
	//cout << "constructor rational (long), l = " << l << endl;
	numerator = l;
	denominator = 1UL;
	isRational = true;
}

Rational::Rational(long n, unsigned long d){
	numerator =  n / gcd(abs(n), d);
	denominator = d / gcd(abs(n), d);
	isRational = (denominator != 0UL);
}

Rational::Rational(const Rational& r){
	numerator = r.numerator;
	denominator = r.denominator;
	isRational = r.isRational;
}

/* This function changes the sign of Rational
 * object. Changing the sign does not have
 * any impact on if it's still Rational,
 * or is it NaN
 */

void Rational::opposite(){
	numerator = -numerator;

	return;
}

/* This function swaps numerator and denominator
 * of Rational object. While swaping, it's essential
 * to check if the object became NaN and
 * set isRational value. This situation is only
 * when denominator became 0.
 */

void Rational::reciprocal(){
	long temp = numerator;

	numerator = temp >= 0 ? denominator : -denominator;
	denominator = abs(temp);
	/* swapped values properly, now
	 *  check if it is still proper number
	 */
	if (denominator == 0)
		isRational = false;

	return;
}

/* Series of operators: +=, -=, *=, /=.
 * Operation that involves NaN on rvalue
 * results in changing lvalue into NaN.
 *
 */

Rational& Rational::operator+=(const Rational& x){

	if (!x.isRational){
		isRational = false;
	}
	unsigned long lcm = (denominator * x.denominator)
			/gcd(denominator, x.denominator);
		/* lcm = least common multiple
		 * It's working since lcm(a, b) * gcd(a, b) = a*b
		 */
	numerator = (numerator * (long)x.denominator + x.numerator *(long) denominator)
			/gcd(denominator, x.denominator);
	/* casting here is unavoidable since long (operator) unsigned is
	 * converted to unsigned
	 */
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
	cout << endl << "testowanie *=" << endl;
	cout << "numerator = " << numerator << " denominator = " << denominator <<endl;
	cout << "x.numerator = " << numerator << " x.denominator = " << x.denominator <<endl;
	numerator = numerator * x.numerator /gcd(denominator, abs(x.numerator));
	denominator = denominator * x.denominator /gcd(abs(numerator), x.denominator);
	cout << "wynik: numerator = " << numerator << " denominator = " << denominator <<endl;
	//cout << numerator << "/" << denominator << endl;;
	return *this;
}

Rational& Rational::operator /=(const Rational& x){
	Rational divide(x);
	divide.reciprocal();
	*this *= divide;
	return *this;
}

/* Series of boolean operator for Rational arguments <= >= < > == !=.
 * If any number is NaN, false value should be returned
 */

const bool operator <=(const Rational& x, const Rational& y){
	long long a = x.numerator;
	a *= y.denominator;
	long long b = y.numerator;
	b *=  x.denominator;
	return y.isRational && x.isRational
	&& a <= b;
}

const bool operator >=(const Rational& x, const Rational& y){
	return y.isRational && x.isRational
	&& x <= y;
}

const bool operator <(const Rational& x, const Rational& y){
	long long a = x.numerator;
	a *= y.denominator;
	long long b = y.numerator;
	b *=  x.denominator;
	return y.isRational && x.isRational
	&& a < b;
}

const bool operator >(const Rational& x, const Rational& y){
	return y.isRational && x.isRational
	&& y < x;
}

const bool operator ==(const Rational& x, const Rational& y) {
	long long a = x.numerator;
	a *= y.denominator;
	long long b = y.numerator;
	b *=  x.denominator;
	return y.isRational && x.isRational
	&& a == b;
}

const bool operator !=(const Rational& x, const Rational& y){
	return y.isRational && x.isRational
	&& !(y == x);
}


/* This is object's method to test if it's a proper
 * Rational Number away from class
 */
bool Rational::isNumber() const{
	return isRational;
}

/* This is an operator that changes sign
 * of the Rational Object that casted this method.
 */

const Rational Rational::operator-() const{
	Rational minus(*this);
	minus.opposite();
	return minus;
}

/* Operator responsible for writing Rational number
 * into stream in proper format. If it's NaN, "NaN" should
 * be written, else there should be sign involved. + should
 * be skipped if possible. Dividing and Moduling should be
 * commited only on nonnegative values of numerator!
 */

ostream& operator<<(ostream& os, const Rational& r) {
  if (r.isRational){
	  /* first writting integer part */
	  if (abs(r.numerator) / r.denominator > 0){
		  /* Numerator should be written*/
		  if (r.numerator < 0)
			  os << "-";	/* write a sign */
		  os << abs(r.numerator) /r.denominator;
		  if (abs(r.numerator) % r.denominator > 0 && r.numerator > 0)
			  os << "+";
		  /* for positive Rational with both integer and rational part,
		   * we need to write it's addition sign
		   */
	  } else /* it might be just 0 */
		  if (abs(r.numerator) % r.denominator == 0){
			  os << 0L;
		  }
	  /* now writting rational part */
	  if (abs(r.numerator) % r.denominator > 0){
		  if (r.numerator < 0)
			  os << "-";
		  os << abs(r.numerator) % r.denominator << "/" <<r.denominator;
	  }

  } else	/* it's not proper Rational number */
	  os << "NaN";
  return os;
}

bool Rational::boolean_test() const{
	return isRational && numerator != Zero();
}

void writeValues(Rational a, Rational b, Rational c,
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
	writeValues(a,b,c,d,e,f,g);
	a += b;
	assert(a == Zero());
	f -= g;
	assert (f < -6);
	assert (-6 > f);
	cout << "b = " << b << " a d= " << d <<endl;
	b *=  d;
	cout << "b = " << b << endl;
	assert(b >= 5);
	assert(b <= 5);
	cout << "b = " << b << " a 5 = " << Rational(5) <<endl;
	assert(b == 5);
}
