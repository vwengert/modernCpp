#include "modernLibrary.h"
#include "factory.h"
#include "singleton.h"
#include <iostream>


auto doWork() -> int
{
    std::cout << Singleton::instance()->configuration() << '\n';
    factoryDoWork();

    return 0;
}
