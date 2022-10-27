#include<iostream>
#include "tvector.h"
using namespace std;


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__
const int MAX_MATRIX_SIZE = 10000;
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (sz > MAX_MATRIX_SIZE)
      throw "Err";
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    return TDynamicVector<TDynamicVector<T>>::operator == (m);
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
    TDynamicMatrix<T> result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] * val;
    }
    return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    TDynamicVector<T> result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] * v;
    }
    return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    TDynamicMatrix<T> result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] + m.pMem[i];
    }
    return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    TDynamicMatrix<T> result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] - m.pMem[i];
    }
    return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    TDynamicMatrix result(sz);
    for (size_t i = 0; i < sz; i++)
    {
      for (size_t j = 0; j < sz; j++)
      {
        for (size_t k = 0; k < sz; k++)
        {
          result.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
        }
      }
    }
    return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    istr >> v.sz;
    TDynamicMatrix temp(sz);
    for (int i = 0; i < sz; i++)
      for (int j = 0; j < sz; j++)
        istr >> temp[i][j];
    v = temp;
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (int i = 0; i < v.sz; i++)
    {
      for (int j = 0; j < v.sz; j++)
        ostr << v[i][j] << "\t";
      ostr << "\n";
    }
    return ostr;
  }
};
#endif