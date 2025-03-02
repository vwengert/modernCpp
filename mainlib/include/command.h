#pragma once

#include <memory>
#include <stack>

class CalculatorCommand
{
  public:
    virtual ~CalculatorCommand() = default;
    CalculatorCommand() = default;

    CalculatorCommand( const CalculatorCommand& ) = delete;
    CalculatorCommand& operator=( const CalculatorCommand& ) = delete;
    CalculatorCommand( CalculatorCommand&& ) = delete;
    CalculatorCommand& operator=( CalculatorCommand&& ) = delete;

    virtual int execute( int value ) const = 0;
    virtual int undo( int value ) const = 0;
};

class Add final : public CalculatorCommand
{
  public:
    explicit Add( int value );
    int execute( int value ) const override;
    int undo( int value ) const override;

  private:
    int m_value{};
};

class Substract final : public CalculatorCommand
{
  public:
    explicit Substract( int value );
    int execute( int value ) const override;
    int undo( int value ) const override;

  private:
    int m_value{};
};

class Calculator
{
  public:
    void compute( std::unique_ptr< CalculatorCommand > command );
    void undoLast();
    int result() const;
    void clear();

    using CommandStack = std::stack< std::unique_ptr< CalculatorCommand > >;

    int mCurrent{};
    CommandStack mCommands;
};
