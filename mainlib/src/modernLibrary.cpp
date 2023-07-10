#include "modernLibrary.h"

#include <iostream>

#include "abstractfabric.h"
#include "factory.h"
#include "mathematics.h"
#include "singleton.h"
#include "visitor.h"

auto doWork() -> int
{
    std::cout << Singleton::instance()->configuration() << '\n';
    factoryDoWork();
    abstractFactoryDoWork();

    VisitorWorker worker;
    worker.showPrices();

    doMultiply();

    return 0;
}
