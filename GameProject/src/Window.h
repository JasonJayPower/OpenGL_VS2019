#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <queue>
#include "Event.h"


class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();

	bool isOpen() const noexcept;

	bool pollEvent(Event& e);
	void update();
private:
	using EventQueue = std::queue<Event>;


	void initialise(int width, int height, const char* title);
	void intialiseEvents();

	GLFWwindow* m_window;

	EventQueue m_eventQueue;
};
