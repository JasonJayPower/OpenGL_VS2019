#include "Window.h"
#include <iostream>

void glfwErrorCallback(int error, const char* description)
{
	std::cout << "GLFW error " << error << ": " << description << std::endl;
}


Window::Window(int width, int height, const char* title)
	: m_window{ nullptr }
{
	initialise(width, height, title);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Window::isOpen() const noexcept
{
	return !glfwWindowShouldClose(m_window);
}

bool Window::pollEvent(Event& e)
{
	if (!m_eventQueue.empty()) {
		e = std::move(m_eventQueue.front());
		m_eventQueue.pop();
		return true;
	}
	return false;
}

void Window::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Window::initialise(int width, int height, const char* title)
{
	// Check for errors
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	intialiseEvents();

	glfwMakeContextCurrent(m_window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
	glfwSwapInterval(0);
}

void Window::intialiseEvents()
{
	glfwSetWindowUserPointer(m_window, &m_eventQueue);

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto events = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
		switch (action) {
			case GLFW_PRESS: {
				events->emplace(Event{ EventType::KeyPressed, {key, mods} });
				break;
			}
			case GLFW_RELEASE: {
				events->emplace(Event{ EventType::KeyReleased, {key, mods} });
				break;
			}
		}
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
		auto events = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
		switch (action) {
			case GLFW_PRESS: {
				events->emplace(Event{ EventType::MouseButtonPressed, {button, mods} });
				break;
			}
			case GLFW_RELEASE: {
				events->emplace(Event{ EventType::MouseButtonReleased, {button, mods} });
				break;
			}
		}
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
		auto events = static_cast<EventQueue*>(glfwGetWindowUserPointer(window));
		events->emplace(Event{ EventType::MouseMoved, { static_cast<int>(xPos), static_cast<int>(yPos) } });
	});
}
