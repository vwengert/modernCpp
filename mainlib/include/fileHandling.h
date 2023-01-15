#include <functional>
#include <memory>

std::unique_ptr<FILE, std::function<void(FILE*)>> openFileInMode(
    const char* name, const char* mode);
