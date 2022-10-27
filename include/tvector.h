#include <iostream>
using namespace std;


// Динамический вектор - 
// шаблонный вектор на динамической памяти
#ifndef __TDynamicVector_H__
#define __TDynamicVector_H__
const int MAX_VECTOR_SIZE = 100000000;
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz < 0)
      throw "Err";
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
      throw "Err";
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    if (sz < 0)
      throw "Err";
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    pMem = nullptr;
    swap(*this, v);
  }
  ~TDynamicVector()
  {
    if (pMem != 0)
    {
      delete[]pMem;
      pMem = 0;
    }
    sz = 0;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v)
      return *this;
    TDynamicVector tmp(v);
    swap(*this, tmp);
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    swap(*this, v);
    return*this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    if (pMem == 0)
      throw "Err";
    if ((ind < 0) || (ind >= sz))
      throw "Err";
    return this->pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return this->pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (pMem == 0)
      throw "Err";
    if ((ind < 0) || (ind >= sz))
      throw "Err";
    return this->pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (pMem == 0)
      throw "Err";
    if ((ind < 0) || (ind >= sz))
      throw "Err";
    return this->pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz)
      return false;
    for (int i = 0; i < sz; i++)
    {
      if (pMem[i] != v.pMem[i])
        return false;
    }
    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz)
      return true;
    for (int i = 0; i < sz; i++)
    {
      if (pMem[i] != v.pMem[i])
        return true;
    }
    return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] + val;
    }
    return result;
  }
  TDynamicVector operator-(double val)
  {
    TDynamicVector result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] - val;
    }
    return result;
  }
  TDynamicVector operator*(double val)
  {
    TDynamicVector result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] * val;
    }
    return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw "Err";
    TDynamicVector result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] + v.pMem[i];
    }
    return result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw "Err";
    TDynamicVector result(sz);
    for (int i = 0; i < sz; i++)
    {
      result.pMem[i] = pMem[i] - v.pMem[i];
    }
    return result;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
    if (sz != v.sz)
      throw out_of_range("Vectors are different size");
    int res = 0;
    for (size_t i = 0; i < sz; i++)
      res += pMem[i] * v.pMem[i];
    return res;

  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};
#endif