#include "benchmark/benchmark.h"
#include "bridge.h"
#include "raiitemplates.h"
#include <fstream>
#include <iostream>
#include <memory>

constexpr int kITERATIONMODIFIER = 32;

std::ostream& nullstream()
{
  static std::ofstream os; // NOLINT
  if( !os.is_open() )
  {
    os.open( "/dev/null", std::ofstream::out | std::ofstream::app );
  }
  return os;
}

void bmRawptrDereference( benchmark::State& state )
{
  for( auto _ : state ) // NOLINT
  {
    ElectricCar* pCar = new ElectricCar( nullstream() );
    benchmark::DoNotOptimize( *pCar );
    pCar->drive();
    delete pCar;
  }
  state.SetItemsProcessed( kITERATIONMODIFIER * state.iterations() );
}

void bmScopedPtrDereference( benchmark::State& state )
{
  for( auto _ : state ) // NOLINT
  {
    scoped_ptr< ElectricCar > pCar( new ElectricCar( nullstream() ) );
    benchmark::DoNotOptimize( *pCar );
    pCar->drive();
  }
  state.SetItemsProcessed( kITERATIONMODIFIER * state.iterations() );
}

void bmUniquePtrDereference( benchmark::State& state )
{
  for( auto _ : state ) // NOLINT
  {
    std::unique_ptr< ElectricCar > pCar( new ElectricCar( nullstream() ) );
    benchmark::DoNotOptimize( *pCar );
    pCar->drive();
  }
  state.SetItemsProcessed( kITERATIONMODIFIER * state.iterations() );
}

// NOLINTBEGIN
BENCHMARK( bmRawptrDereference );
BENCHMARK( bmScopedPtrDereference );
BENCHMARK( bmUniquePtrDereference );
BENCHMARK_MAIN();
// NOLINTEND
