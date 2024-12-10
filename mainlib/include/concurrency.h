#pragma once

#include <mutex>
#include <string>

class SomeData {
    int m_a;
    std::string m_b;
    public:
      void doSomething();
};

class DataWrapper {
    SomeData m_data;
    std::mutex m_mutex;
    public:
      template <typename Function>
      void processData(Function userFunction) {
        std::lock_guard<std::mutex> lock(m_mutex);
        userFunction(m_data);
      }
};