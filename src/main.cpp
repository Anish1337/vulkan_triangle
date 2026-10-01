#include <vulkan/vulkan.h>

#include <iostream>

int main()
{
    std::cout << "Vulkan header version: "
        << VK_HEADER_VERSION << '\n';

    return 0;
}