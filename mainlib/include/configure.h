
#pragma once

#include "appconfigurator.h"

std::unique_ptr< AppConfigurator > configure();
std::vector< std::unique_ptr< IAnimal > > createData( const std::unique_ptr< AppConfigurator >& config );
[[maybe_unused]] void displayData( const std::vector< std::unique_ptr< IAnimal > >& animals );
