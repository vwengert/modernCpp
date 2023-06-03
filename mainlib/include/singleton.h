#pragma once
#include <string>

class Singleton final
{
    public:
        static Singleton* instance();

        std::string configuration();
    private:
        Singleton();

        static Singleton* s_instance;
};
