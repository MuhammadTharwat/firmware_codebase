/**
  ******************************************************************************
  * @file			noncopyable.hpp
  * @description	Noncopyable Class
  * @author			Muhammad Tharwat
  * @version		V0.0
  * @date			4-August-2023
  ******************************************************************************
*/
#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_
class noncopyable
{
public:
  noncopyable() = default;
  ~noncopyable() = default;

private:
  noncopyable(const noncopyable &) = delete;
  noncopyable &operator=(const noncopyable &) = delete;
};

#endif /*NONCOPYABLE_H_*/