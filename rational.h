/*
 * rational.h
 *
 *  Created on: 2010-11-14
 *      Author: piotr
 */
#include <ostream>


class Rational {
  public:
	Rational();
	Rational(long);
	Rational(long, unsigned long);
	Rational(const Rational&);

        Rational& operator+=(const Rational& x);
	Rational& operator-=(const Rational& x);
	Rational& operator*=(const Rational& x);
	Rational& operator/=(const Rational& x);

	bool operator<=(const Rational& x);
	bool operator<(const Rational& x);
	bool operator==(const Rational& x);

	bool isNumber() const;

	friend std::ostream& operator<<(std::ostream& os, const Rational& r);
  private:
    long numerator;
    unsigned long denominator; //denominator == 0 <=> NaN!

    void opposite();
    void reciprocal();

};

const Rational& operator+(const Rational& a, const Rational& b);
const Rational& operator-(const Rational& a, const Rational& b);
const Rational& operator*(const Rational& a, const Rational& b);
const Rational& operator/(const Rational& a, const Rational& b);
