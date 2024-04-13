#include "benchmark/benchmark.h"
#include "raiitemplates.h"
#include <iostream>
#include <memory>

void BM_rawptr_dereference( benchmark::State& state )
{
  int* p = new int;
  for( auto _ : state )
  {
    benchmark::DoNotOptimize( *p );
  }
  delete p;
  state.SetItemsProcessed( 32 * state.iterations() );
}

void BM_scoped_ptr_dereference( benchmark::State& state )
{
  scoped_ptr< int > p( new int );
  for( auto _ : state )
  {
    benchmark::DoNotOptimize( *p );
  }
  state.SetItemsProcessed( 32 * state.iterations() );
}

void BM_unique_ptr_dereference( benchmark::State& state )
{
  std::unique_ptr< int > p( new int );
  for( auto _ : state )
  {
    benchmark::DoNotOptimize( *p );
  }
  state.SetItemsProcessed( 32 * state.iterations() );
}

BENCHMARK( BM_rawptr_dereference );
BENCHMARK( BM_scoped_ptr_dereference );
BENCHMARK( BM_unique_ptr_dereference );
BENCHMARK_MAIN();