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
  // NOTE check_allocs() throwing here will automatically call free() on a, b, c
  REQUIRE_THROWS_AS( arraytools::check_allocs(a, b, c, d), std::bad_alloc );
}
