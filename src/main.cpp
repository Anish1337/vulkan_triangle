#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
// pulls Vulkan headers
#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif
// for window creation
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
// for EXIT_SUCCESS and EXIT_FAILURE macros
#include <cstdlib>
// for reporting and propagating errors
#include <iostream>
#include <stdexcept>
// other
#include <algorithm>
#include <cstring>
#include <ranges>
#include <string>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window = nullptr;
    // handles instance and raii context
    vk::raii::Context  context;
    vk::raii::Instance instance = nullptr;

    void initWindow() {
        glfwInit(); // init the glfw lib

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // disable resizing

        window = glfwCreateWindow(
            WIDTH,
            HEIGHT,
            "Vulkan", // window name
            nullptr, // monitor
            nullptr // for OpenGL
        );
    }

    void initVulkan() {
        createInstance();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    // destroy resources/close glfw
    void cleanup() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    
    //  connects application to Vulkan API
    void createInstance() {
        // describes the application  
        constexpr vk::ApplicationInfo appInfo{
            .pApplicationName = "Hello Triangle",
            .applicationVersion = VK_MAKE_VERSION(1,0,0),
            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion = vk::ApiVersion14 };

        // check required extensions
        uint32_t glfwExtensionCount = 0;
        auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        // verify Vulkan supports extensions
        auto extensionProperties = context.enumerateInstanceExtensionProperties();
        for (uint32_t i = 0; i < glfwExtensionCount; ++i)
        {
            if (std::ranges::none_of(extensionProperties,
                [glfwExtension = glfwExtensions[i]](auto const& extensionProperty)
                { return strcmp(extensionProperty.extensionName, glfwExtension) == 0; }))
            {
                throw std::runtime_error("Required GLFW extension not supported: " + std::string(glfwExtensions[i]));
            }
        }
            
        // describes how the isntance should be created
        vk::InstanceCreateInfo createInfo{
            .pApplicationInfo = &appInfo,
            .enabledExtensionCount = glfwExtensionCount,
            .ppEnabledExtensionNames = glfwExtensions };

        // creates instance and stores ownership in class member
        instance = vk::raii::Instance(context, createInfo);
    }
  };

int main() {
    try {
        HelloTriangleApplication app;
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}