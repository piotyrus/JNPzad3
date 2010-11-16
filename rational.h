/*
 * rational.h
 *
 *  Created on: 2010-11-14
 *      Author: piotr
 */
#include <boost/operators.hpp>


class Rational
    : boost::addable< Rational >
    , boost::subtractable< Rational >
    , boost::dividable< Rational >
    , boost::multipliable< Rational >
{
  public:
	Rational();
	Rational(long);
	Rational(long, unsigned long);
	Rational(const Rational&);

    Rational& operator+=(const Rational& x);
	Rational& operator-=(const Rational& x);
	Rational& operator*=(const Rational& x);
	Rational& operator/=(const Rational& x);

	const Rational& operator-();

	const bool operator<=(const Rational& x) const;
	const bool operator>=(const Rational& x) const;
	const bool operator<(const Rational& x) const;
	const bool operator>(const Rational& x) const;
	const bool operator==(const Rational& x) const;
	const bool operator!=(const Rational& x) const;

	bool isNumber() const;

	static const Rational One();
	static const Rational Zero();

	friend std::ostream& operator<<(std::ostream& os, const Rational& r);
  private:
    long numerator;
    unsigned long denominator;
    bool isRational;

    void opposite();
    void reciprocal();
};

const bool operator <=(const long& l, const Rational& r);
const bool operator >=(const long& l, const Rational& r);
const bool operator<(const long& l, const Rational& r);
const bool operator>(const long& l, const Rational& r);
const bool operator ==(const long& l, const Rational& r);
const bool operator !=(const long& l, const Rational& r);
