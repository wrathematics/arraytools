#include "catch/catch.hpp"

#include <arraytools.hpp>


TEMPLATE_TEST_CASE("lenprod", "[arraytools]", char, int, float, double)
{
  size_t test, truth;
  
  test = arraytools::lenprod(3);
  truth = ((size_t) 3);
  REQUIRE( test == truth );
  
  test = arraytools::lenprod(3, 2);
  truth = ((size_t) 3) * ((size_t) 2);
  REQUIRE( test == truth );
  
  test = arraytools::lenprod(3, 2, sizeof(float));
  truth = ((size_t) 3) * ((size_t) 2) * sizeof(float);
  REQUIRE( test == truth );
}
