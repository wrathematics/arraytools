# arraytools

* **Version:** 0.1-0
* **License:** [BSL-1.0](http://opensource.org/licenses/BSL-1.0)
* **Project home**: https://github.com/wrathematics/arraytools
* **Bug reports**: https://github.com/wrathematics/arraytools/issues


arraytools is a small, single file, header-only C++ 17 library that makes some minor improvements to working with arrays. It's very simple and permissively licensed, but you could probably re-create this yourself pretty easily. I'm only putting this here because I am using it across multiple projects. That said, if this looks interesting to you but there's some feature you want and it isn't hilariously out of scope (e.g. "re-implement std::vector"), then feel free to ask and I'll probably do it.

The library solves two major annoyances I have with arrays in C++. For one, unlike in C you have to cast the return of `malloc()`. This is stupid and annoying. Allocation functions in arraytools avoid this by accepting a reference. Also, guarding against a bad `malloc()` is usually verbose and complicated. We handle this with `check_allocs()`, which can detect an allocation failure and then free all passed arrays before throwing `std::bad_alloc()`. The function uses variadic templates, so it's annoying to write but easy to use.

There are some minor improvements as well. First, all length arguments are "number of elements", as opposed to number of bytes. Next, the `malloc()` and `calloc()` equivalents (`arraytools::alloc()` and `arraytools::zero_alloc()`) have a consistent API. Also the `realloc()` wrapper `arraytools::realloc()` automatically handles allocation failure in a simple way. Finally, the `free()` wrapper `arraytools::free()` will only call `std::free()` on a non-`NULL` pointer.



## Dependencies and Tests

There are no external dependencies. Tests use [catch2](https://github.com/catchorg/Catch2), a copy of which is included under `tests/catch`.

To build the tests, modify `tests/make.inc` as appropriate and type `make`.
