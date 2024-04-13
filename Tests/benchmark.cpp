#include "benchmark/benchmark.h"
#include "bridge.h"
#include "raiitemplates.h"
#include <fstream>
#include <iostream>
#include <memory>

std::ostream& nullstream()
{
  static std::ofstream os;
  if( !os.is_open() )
  {
    os.open( "/dev/null", std::ofstream::out | std::ofstream::app );
  }
  return os;
}

void BM_rawptr_dereference( benchmark::State& state )
{
  for( auto _ : state )
  {
    ElectricCar* p = new ElectricCar( nullstream() );
    benchmark::DoNotOptimize( *p );
    p->drive();
    delete p;
  }
  state.SetItemsProcessed( 32 * state.iterations() );
}

void BM_scoped_ptr_dereference( benchmark::State& state )
{
  for( auto _ : state )
  {
    scoped_ptr< ElectricCar > p( new ElectricCar( nullstream() ) );
    benchmark::DoNotOptimize( *p );
    p->drive();
  }
  state.SetItemsProcessed( 32 * state.iterations() );
}

void BM_unique_ptr_dereference( benchmark::State& state )
{
  for( auto _ : state )
  {
    std::unique_ptr< ElectricCar > p( new ElectricCar( nullstream() ) );
    benchmark::DoNotOptimize( *p );
    p->drive();
  }
  state.SetItemsProcessed( 32 * state.iterations() );
}

BENCHMARK( BM_rawptr_dereference );
BENCHMARK( BM_scoped_ptr_dereference );
BENCHMARK( BM_unique_ptr_dereference );
BENCHMARK_MAIN();