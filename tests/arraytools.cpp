#include "catch/catch.hpp"

#include <arraytools.hpp>


TEMPLATE_TEST_CASE("basics", "", char, int, double)
{
  const int len = 3;
  
  TestType *a, *b;
  arraytools::alloc(len, &a);
  arraytools::alloc(len, &b);
  
  REQUIRE_NOTHROW( arraytools::check_allocs(a, b) );
  
  TestType *c = NULL;
  REQUIRE_THROWS_AS( arraytools::check_allocs(a, b, c), std::bad_alloc );
}



TEMPLATE_TEST_CASE("x", "", char, int, double)
{
  const int len = 3;
  
  TestType *x;
  arraytools::zero_alloc(len, &x);
  
  REQUIRE( x[0] == 0 );
  
  arraytools::free(x);
}



TEMPLATE_TEST_CASE("realloc", "", char, int, double)
{
  int len = 2;
  
  TestType *x;
  arraytools::zero_alloc(len, &x);
  
  len = 3;
  arraytools::realloc(len, &x);
  arraytools::zero(len, x);
  
  REQUIRE( x[len-1] == 0 );
  x[len-1] = 1;
  REQUIRE( x[len-1] == 1);
  
  arraytools::free(x);
}



template <typename T, typename S>
struct TypeRecoverer
{
  T x;
  S y;
};

TEMPLATE_PRODUCT_TEST_CASE("asdf", "",
  TypeRecoverer, ((int, char), (float, int), (double, double)))
{
  TestType a;
  using T = decltype(+a.x);
  using S = decltype(+a.y);
  
  const int len = 5;
  T *x;
  S *y;
  arraytools::alloc(len, &x);
  arraytools::alloc(len, &y);
  
  for (int i=0; i<len; i++)
    x[i] = (T) i;
  
  arraytools::copy(len, x, y);
  
  for (int i=0; i<len; i++)
    REQUIRE( y[i] == (S) i );
  
  arraytools::free(x);
  arraytools::free(y);
}
