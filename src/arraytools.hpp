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
  /** 
   * Copy one array onto another. Array types can differ. If they are the same, it
   * reduces to a memcpy() call.
   * 
   * @param[in] len Number of elements (not the number of bytes!).
   * @param[in] src Source array.
   * @param[out] dst Destination array.
   */
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
  
  
  
  /**
   * Set an array's values to 0. Wrapper around memset().
   * 
   * @param[in] len Number of elements (not the number of bytes!).
   * @param[inout] x Array to be zeroed.
   */
  template <typename T>
  static inline void zero(const size_t len, T *x)
  {
    std::memset(x, 0, len*sizeof(*x));
  }
  
  
  
  /**
   * Allocate an array. Wrapper around malloc().
   * 
   * @param[in] len Number of elements (not the number of bytes!).
   * @param[out] x Array to be allocated.
   */
  template <typename T>
  static inline void alloc(const size_t len, T **x)
  {
    *x = (T*) std::malloc(len*sizeof(T));
  }
  
  
  
  /**
   * Zero-allocate an array. Wrapper around calloc.
   * 
   * @param[in] len Number of elements (not the number of bytes!).
   * @param[out] x Array to be allocated.
   */
  template <typename T>
  static inline void zero_alloc(const size_t len, T **x)
  {
    *x = (T*) std::calloc(len, sizeof(T));
  }
  
  
  
  /**
   * Re-allocate an array. Wrapper around realloc(). If the realloc fails, the
   * array will be set to NULL.
   * 
   * @param[in] len Number of elements (not the number of bytes!).
   * @param[out] x Array to be re-allocated.
   */
  template <typename T>
  static inline void realloc(const size_t len, T **x)
  {
    void *realloc_ptr = std::realloc(*x, len*sizeof(T));
    if (realloc_ptr == NULL)
      std::free(*x);
    
    *x = (T*) realloc_ptr;
  }
  
  
  
  /**
   * Free an array if supplied pointer is not NULL. Wrapper around free().
   * 
   * @param[in] x Array to be allocated.
   */
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
    
    
    
    static inline int check_alloc()
    {
      return ALLOC_OK;
    }
    
    template <typename T>
    static inline int check_alloc(T *x)
    {
      if (x == NULL)
        return ALLOC_FAILED;
      else
        return ALLOC_OK;
    }
    
    template <typename T, typename... VAT>
    static inline int check_alloc(T *x, VAT... vax)
    {
      return check_alloc(x) + check_alloc(vax ...);
    }
    
    
    
    static inline void vafree(){}
    
    template <typename T, typename... VAT>
    static inline void vafree(T *x, VAT... vax)
    {
      arraytools::free(x);
      vafree(vax ...);
    }
  }
  
  
  
  /**
   * Check variable number of arrays. If one is NULL, then all others will be
   * automatically freed and std::bad_alloc() will be thrown.
   * 
   * @param[in] x Array.
   * @param[in] vax Optional more arrays.
   */
  template <typename T, typename... VAT>
  static inline void check_allocs(T *x, VAT... vax)
  {
    int check = check_alloc(x) + check_alloc(vax ...);
    
    if (check != ALLOC_OK)
    {
      arraytools::free(x);
      vafree(vax ...);
      
      throw std::bad_alloc();
    }
  }
}


#endif
