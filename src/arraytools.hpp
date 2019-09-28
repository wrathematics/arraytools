#ifndef SPVEC_ARRAYTOOLS_H
#define SPVEC_ARRAYTOOLS_H


#include <cstdlib>
#include <cstring>


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
}


#endif
