#include <memory>

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>

#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	vk::raii::Context	context;
	vk::raii::Instance	instance = nullptr;

	GLFWwindow* window = nullptr;

	void initWindow() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void initVulkan() {
		createInstance();
	}

	void createInstance() {
		constexpr vk::ApplicationInfo appInfo{
			.pApplicationName	= "Hello Triangle",
			.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
			.pEngineName		= "No Engine",
			.apiVersion			= vk::ApiVersion14
		};

		uint32_t glfwExtensionsCount = 0;
		auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

		auto extensionProperties = context.enumerateInstanceExtensionProperties();
		for (uint32_t i = 0; i < glfwExtensionsCount; ++i) {
			bool found = false;
			for (auto extension : extensionProperties) {
				if (strcmp(extension.extensionName, glfwExtensions[i]) == 0) {
					found = true;
					break;
				}
			}

			if (found == false) {
				throw std::runtime_error("Required glfw extension not supported: " + std::string(glfwExtensions[i]));
			}
		}

		vk::InstanceCreateInfo createInfo{
			.pApplicationInfo = &appInfo,
			.enabledExtensionCount = glfwExtensionsCount,
			.ppEnabledExtensionNames = glfwExtensions
		};

		instance = vk::raii::Instance(context, createInfo);
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}
	}

	void cleanup() {
		glfwDestroyWindow(window);

		glfwTerminate();
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