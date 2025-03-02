#include "command.h"

Add::Add( const int value )
  : m_value( value )
{
}

int Add::execute( const int value ) const
{
  return value + m_value;
}

int Add::undo( const int value ) const
{
  return value - m_value;
}

Substract::Substract( const int value )
  : m_value( value )
{
}

int Substract::execute( const int value ) const
{
  return value - m_value;
}

int Substract::undo( const int value ) const
{
  return value + m_value;
}

void Calculator::compute( std::unique_ptr< CalculatorCommand > command )
{
  mCurrent = command->execute( mCurrent );
  mCommands.push( std::move( command ) );
}

void Calculator::undoLast()
{
  if( mCommands.empty() )
  {
    return;
  }
  const auto command = std::move( mCommands.top() );
  mCommands.pop();
  mCurrent = command->undo( mCurrent );
}

int Calculator::result() const
{
  return mCurrent;
}

void Calculator::clear()
{
  mCurrent = 0;
  CommandStack{}.swap( mCommands );
}
