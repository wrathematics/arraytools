#include "catch/catch.hpp"

#include <arraytools.hpp>
#include "type_recoverer.hpp"


TEMPLATE_TEST_CASE("alloc", "[arraytools]", char, int, float, double)
{
  const int len = 3;
  
  TestType *x;
  arraytools::zero_alloc(len, &x);
  
  REQUIRE_NOTHROW( arraytools::check_allocs(x) );
  
  arraytools::free(x);
}



TEMPLATE_TEST_CASE("zero_alloc", "[arraytools]", char, int, float, double)
{
  const int len = 3;
  
  TestType *x;
  arraytools::zero_alloc(len, &x);
  
  REQUIRE_NOTHROW( arraytools::check_allocs(x) );
  REQUIRE( x[0] == 0 );
  
  arraytools::free(x);
}



TEMPLATE_TEST_CASE("realloc", "[arraytools]", char, int, float, double)
{
  int len = 2;
  
  TestType *x;
  arraytools::zero_alloc(len, &x);
  
  REQUIRE_NOTHROW( arraytools::check_allocs(x) );
  
  len = 3;
  arraytools::realloc(len, &x);
  REQUIRE_NOTHROW( arraytools::check_allocs(x) );
  
  arraytools::zero(len, x);
  REQUIRE( x[len-1] == 0 );
  
  x[len-1] = 1;
  REQUIRE( x[len-1] == 1);
  
  arraytools::free(x);
}


TEMPLATE_TEST_CASE("check_allocs", "[arraytools]", char, int, float, double)
{
  const int len = 3;
  
  TestType *a, *b, *c;
  arraytools::alloc(len, &a);
  arraytools::alloc(len, &b);
  arraytools::alloc(len, &c);
  
  REQUIRE_NOTHROW( arraytools::check_allocs(a) );
  REQUIRE_NOTHROW( arraytools::check_allocs(a, b) );
  REQUIRE_NOTHROW( arraytools::check_allocs(a, b, c) );
  
  TestType *d = NULL;
  REQUIRE_THROWS_AS( arraytools::check_allocs(a, b, c, d), std::bad_alloc );
  // NOTE check_allocs() throwing here will automatically call free() on a, b, c
}



TEMPLATE_PRODUCT_TEST_CASE("copy", "[arraytools]",
  TypeRecoverer, (
    (char, char), (int, int), (float, float), (double, double),
    (char, int), (int, char), (int, double), (double, int), (float, double), (double, float)
  )
)
{
  TestType a;
  using T = decltype(+a.x);
  using S = decltype(+a.y);
  
  const int len = 3;
  T *x;
  S *y;
  arraytools::alloc(len, &x);
  arraytools::alloc(len, &y);
  REQUIRE_NOTHROW( arraytools::check_allocs(x, y) );
  
  for (int i=0; i<len; i++)
    x[i] = (T) i;
  
  arraytools::copy(len, x, y);
  
  for (int i=0; i<len; i++)
    REQUIRE( y[i] == (S) i );
  
  arraytools::free(x);
  arraytools::free(y);
}
