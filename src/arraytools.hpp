// This file is part of arraytools which is released under the Boost Software
// License, Version 1.0. See accompanying file LICENSE or copy at
// https://www.boost.org/LICENSE_1_0.txt

#ifndef SPVEC_ARRAYTOOLS_H
#define SPVEC_ARRAYTOOLS_H
#pragma once


#include <cstdlib>
#include <cstring>
#include <stdexcept>


namespace arraytools
{
  template <typename T>
  static inline void copy(const size_t len, const T *src, T *dst)
  {
    std::memcpy(dst, src, len*sizeof(*src));
  }
  
  template <typename SRC, typename DST>
  static inline void copy(const size_t len, const SRC *src, DST *dst)
  {
    #pragma omp for simd
    for (size_t i=0; i<len; i++)
      dst[i] = (DST) src[i];
  }
  
  
  
  template <typename T>
  static inline void zero(const size_t len, T *x)
  {
    std::memset(x, 0, len*sizeof(*x));
  }
  
  
  
  template <typename T>
  static inline void alloc(const size_t len, T **x)
  {
    *x = (T*) std::malloc(len*sizeof(T));
  }
  
  
  
  template <typename T>
  static inline void zero_alloc(const size_t len, T **x)
  {
    *x = (T*) std::calloc(len, sizeof(T));
  }
  
  
  
  template <typename T>
  static inline void realloc(const size_t len, T **x)
  {
    void *realloc_ptr = std::realloc(*x, len*sizeof(T));
    if (realloc_ptr == NULL)
      std::free(*x);
    
    *x = (T*) realloc_ptr;
  }
  
  
  
  template <typename T>
  static inline void free(T *x)
  {
    if (x)
      std::free(x);
  }
  
  
  
  namespace
  {
    static const int ALLOC_FAILED = -1;
    static const int ALLOC_OK = 0;
    
    template <typename T>
    static inline int check_alloc(T *x)
    {
      if (x == NULL)
        return ALLOC_FAILED;
      else
        return ALLOC_OK;
    }
    
    template <typename T, typename S>
    static inline int check_alloc(T *x, S *y)
    {
      return arraytools::check_alloc(x) + arraytools::check_alloc(y);
    }
    
    template <typename T, typename S>
    static inline void free(T *x, S *y)
    {
      arraytools::free(x);
      arraytools::free(y);
    }
  }
  
  template <typename T>
  static inline void check_allocs(T *x)
  {
    int check = check_alloc(x);
    
    if (check != ALLOC_OK)
    {
      arraytools::free(x);
      
      throw std::bad_alloc();
    }
  }
  
  template <typename T, typename... VAT>
  static inline void check_allocs(T *x, VAT... vax)
  {
    int check = check_alloc(x) + check_alloc(vax...);
    
    if (check != ALLOC_OK)
    {
      arraytools::free(x);
      free(vax...);
      
      throw std::bad_alloc();
    }
  }
}


#endif
