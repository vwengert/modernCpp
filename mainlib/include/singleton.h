#pragma once
#include <memory>
#include <string>

class Singleton final
{
    public:
     static std::shared_ptr<Singleton> instance();

     std::string configuration() const;

     auto configuration() -> std::string;

    private:
     Singleton() = default;

     static std::shared_ptr<Singleton> s_instance;
};
