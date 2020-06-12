#include "catch/catch.hpp"

#include <arraytools.hpp>
#include "type_recoverer.hpp"


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
