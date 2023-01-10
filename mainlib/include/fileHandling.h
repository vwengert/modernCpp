#include <functional>
#include <memory>

std::unique_ptr<std::FILE, std::function<void(std::FILE*)>> openFileInMode(
    const char* name, const char* mode);