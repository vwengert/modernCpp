#pragma once

struct Node
{
  int mValue;
  Node* left{ nullptr };
  Node* right{ nullptr };

  explicit Node( const int value = 0 )
    : mValue( value )
  {
  }
};

template<typename T, typename... TP>
Node* traverse( T value, TP... values )
{
  return (value->*...->*values);
}