#include "catch/catch.hpp"

#include <arraytools.hpp>


TEMPLATE_TEST_CASE("set", "[arraytools]", char, int, float, double)
{
  const int len = 3;
  
  TestType *x;
  arraytools::alloc(len, &x);
  
  TestType v = (TestType)1;
  arraytools::set(v, len, x);
  REQUIRE( x[0] == v );
  REQUIRE( x[len-1] == v );
  
  arraytools::free(x);
}
