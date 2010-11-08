// Przeanalizuj poniższy kod. Odpowiedz na pytania.
// W jakich sytuacjach wywoływane są poszczególne konstruktory?
// Kiedy wywoływane są operatory przypisania i konwersji?
// W jakiej kolejności wywoływane są konstruktory obiektów składowych klasy?
// W jakiej kolejności wywoływane są destruktory?
// Kiedy konstruowane są wartości tymczasowe?
// Czym rożni się przekazywanie argumentów przez wartość i przez referencję?
// Jak funkcja zwraca wartość będącą obiektem?
// Co sie dzieje, gdy stała jest przekazywana przez const&?
// Dlaczego operator konwersji jest const, a operator przypisania nie?
// Dlaczego operator przypisania zwraca wartość typu Integer&, a nie const Integer&?
// Dlaczego funkcja operator* zwraca wartość typu const Rational, a nie Rational?
#include <iostream>
using namespace std;

template<class T>
class Integer {
  public:
    Integer() : internal(0) {
      cout << *this << "::konstruktor_bezparametrowy()" << endl;
    }
    Integer(const Integer<T>& that) : internal(that.internal) {
      cout << *this << "::konstruktor_kopiujacy(" << that << ")" << endl;
    }
    // Zobacz, co sie stanie, gdy ponizszy konstruktor zostanie zadeklarowany tak:
    // explicit Integer(T i) : internal(i) {
    Integer(T i) : internal(i) {
      cout << *this << "::konstruktor_konwertujacy(" << i << ")" << endl;
    }
    ~Integer() {
      cout << *this << "::destruktor()" << endl;
    }
    Integer& operator=(const Integer& that) {
      cout << *this << "::operator=(" << that << ")" << endl;
      internal = that.internal;
      return *this;
    }
    operator int() const {
      cout << *this << "::operator int()" << endl;
      return internal;
    }
    Integer& operator*=(const Integer& that) {
      internal *= that.internal;
      return *this;
    }
    template<class T1>
    friend ostream& operator<<(ostream&, const Integer<T1>&);
  private:
    T internal;
};

template<class T>
ostream& operator<<(ostream& os, const Integer<T>& i) {
  os << "{" << typeid(i).name() << "(" << i.internal << ")@" << static_cast<const void*>(&i) << "}";
  return os;
}

typedef Integer<int> Int;
typedef Integer<unsigned> Unsigned;

class Rational {
  public:
    Rational(Int n, Unsigned d) : numerator(n), denominator(d) {}
    Rational& operator*=(const Rational& that) {
      // To jest badziewie, trzeba skracac przez NWD.
      numerator *= that.numerator;
      denominator *= that.denominator;
      return *this;
    }
  private:
    Int numerator;
    Unsigned denominator;
};

const Rational operator*(const Rational& a, const Rational& b) {
  Rational c(a);
  return c *= b;
}

Int foo(Int i) {
  return i;
}

void foo(const Int& i, const Int& j) {
  cout << "wywolano foo(" << i << ", " << j << ")" << endl;
}

Int foo(void) {
  return Int();
}

int main() {
  {
    cout << "\nWykonuje sie konstruktor bezparametrowy i kopiujący." << endl;
    Int i, j(i);
    cout << "\nPrzy opuszczaniu zasiegu wykonuja sie destruktory." << endl;
  }
  {
    cout << "\nWykonuje sie konwersja typu." << endl;
    Int i('3');
    cout << "\nTu tez wykonuje sie konwersja typu." << endl;
    Int j = 4;
    cout << "\nA tu wykonuje sie operator przypisania." << endl;
    i = j;
    cout << "\nWykonuje sie ponowna konwersja typu." << endl;
    int k = j;
    cout << "\nPrzekazywanie wartosci wywoluje konstruktor kopiujacy (i potem destruktor)." << endl;
    foo(j);
    cout << "\nPrzekazywanie argumentów przez referencje." << endl;
    foo(i, j);
    cout << "\nZwracanie wartosci przez funkcje." << endl;
    i = foo();
    cout << "\nPrzy opuszczaniu zasiegu wykonuja sie destruktory." << endl;
  }
  {
    cout << "\nI wszystko na raz." << endl;
    Int i;
    int j = i = foo(7);
  }
  {
    cout << "\nTworzymy ulamki 2/3 i 5/7." << endl;
    Rational a(2, 3), b(5, 7);
    cout << "\nMnozymy je." << endl;
    a *= b;
    cout << "\nA teraz znow mnozymy, ale wynik w nowym obiekcie." << endl;
    Rational c = a * b;
    cout << "\nOperator przypisania dla ulamkow." << endl;
    a = c;
    cout << "\nI znow destrukcja." << endl;
  }
}

