/*
 * rational.h
 *
 *  Created on: 2010-11-14
 *      Author: piotr
 */
#include <boost/operators.hpp>

class safe_bool_base {
	public:
		typedef void (safe_bool_base::*bool_type)() const;
		void this_type_does_not_support_comparisons() const {}

		safe_bool_base() {}
		safe_bool_base(const safe_bool_base&) {}
		safe_bool_base& operator=(const safe_bool_base&) {return *this;}
		~safe_bool_base() {}
};

template <typename T=void>
class safe_bool : public safe_bool_base {
	public:
		operator bool_type() const {
		return (static_cast<const T*>(this))->boolean_test()
		? &safe_bool_base::this_type_does_not_support_comparisons : 0;
		}
	protected:
		~safe_bool() {}
};

template<>
class safe_bool<void> : public safe_bool_base {
	public:
		operator bool_type() const {
			return boolean_test()==true ?
					&safe_bool_base::this_type_does_not_support_comparisons : 0;
		}
	protected:
		virtual bool boolean_test() const=0;
		virtual ~safe_bool() {}
};

template <typename T, typename U>
	void operator==(const safe_bool<T>& lhs,const safe_bool<U>& rhs) {
	lhs.this_type_does_not_support_comparisons();
	return false;
}

template <typename T,typename U>
	void operator!=(const safe_bool<T>& lhs,const safe_bool<U>& rhs) {
	lhs.this_type_does_not_support_comparisons();
	return false;
}



class Rational
    : boost::addable< Rational >
    , boost::subtractable< Rational >
    , boost::dividable< Rational >
    , boost::multipliable< Rational >
    , public safe_bool<Rational>
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

	bool boolean_test() const;

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
