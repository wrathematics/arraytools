#ifndef TYPE_RECOVERER_HPP
#define TYPE_RECOVERER_HPP
#pragma once


#define SET_TYPE(T, obj) using T = decltype(+obj.x)

template <typename T, typename S>
struct TypeRecoverer
{
  T x;
  S y;
};


#endif
