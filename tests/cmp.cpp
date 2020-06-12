#include "catch/catch.hpp"

#include <arraytools.hpp>
#include "type_recoverer.hpp"


TEMPLATE_PRODUCT_TEST_CASE("cmp", "[arraytools]",
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
  
  arraytools::zero(len, x);
  arraytools::zero(len, y);
  
  REQUIRE( arraytools::cmp(len, x, y) );
  REQUIRE( arraytools::cmp_firstmiss(len, x, y) == len );
  
  for (int i=0; i<len; i++)
  {
    x[i] = (T) i;
    y[i] = (S) i;
  }
  
  REQUIRE( arraytools::cmp(len, x, y) );
  REQUIRE( arraytools::cmp_firstmiss(len, x, y) == len );
  
  x[len-1] = (T) 999;
  REQUIRE( !arraytools::cmp(len, x, y) );
  REQUIRE( arraytools::cmp_firstmiss(len, x, y) == len-1 );
  
  arraytools::free(x);
  arraytools::free(y);
}
