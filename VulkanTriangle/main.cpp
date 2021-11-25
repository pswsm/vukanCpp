#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>


class HelloTriangleApplication {
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  VkInstance instance;
  const uint32_t AMPL = 700;
  const uint32_t LLAR = 700;

  GLFWwindow* window;

  void initWindow(/* arguments */) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(AMPL, LLAR, "Test", nullptr, nullptr);
  }
  void initVulkan() {
    createInstance();
  }
  void createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
  }
  void mainLoop() {
    // Mentre la finestra NO es tanqui
    while (!glfwWindowShouldClose(window)) {
      // Recull events com ara clics i telcleig, o estat de la finestra. S'actaulitza a cada fotograma.
      // https://discourse.glfw.org/t/question-about-glfwpollevents/1524
      glfwPollEvents();
    }
  }
  void cleanup() {
    // Destrueix el recurs de glfw "window", aka la finestra
    glfwDestroyWindow(window);
    // Termina el proces de glfw?
    glfwTerminate();
  }
};

int main() {
  HelloTriangleApplication app;

  try {
      app.run();
  } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
