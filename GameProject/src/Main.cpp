#define STB_IMAGE_IMPLEMENTATION


#include "Window.h"
#include "OrthographicCamera.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "Types.h"
#include "Renderer.h"

#include "Shader.h"
#include "Texture.h"


int main()
{
	bool left = false;
	bool right = false;
	std::vector<glm::vec2> pos(1024);
	for (size_t i = 0; i < 1024; i++)
	{
		pos[i] = glm::vec2(rand() % 800, rand() % 600);
	}


	Window m_window(800, 600, "Test");
	Renderer m_renderer;
	Event e;

	OrthographicCamera cam(0, 800, 600, 0);
	glm::vec3 camPos(0, 0, 0);

	Texture tex = loadTexture("assets/texture/player.png");

	Shader shader;
	shader.compile("assets/shader/vert.glsl", "assets/shader/frag.glsl");

	glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, tex.id);
	

	shader.bind();
	shader.setMat4("viewProjection", cam.GetViewProjectionMatrix());

	while (m_window.isOpen()) {
		while (m_window.pollEvent(e)) {
			switch (e.eventType) {
				case EventType::MouseMoved: {
					std::cout << "Mouse Pos " << e.position.x << " " << e.position.y << std::endl;
					break;
				}
				case EventType::KeyPressed: {
					if (e.keyboard.key == GLFW_KEY_RIGHT) {
						right = true;
					}
					else if (e.keyboard.key == GLFW_KEY_LEFT) {
						left = true;
					}
					else if (e.keyboard.key == GLFW_KEY_UP) {
						cam.setScale(glm::vec2(2.f, 2.f));
					}
					break;
				}
				case EventType::KeyReleased: {
					if (e.keyboard.key == GLFW_KEY_RIGHT) {
						right = false;
					}
					else if (e.keyboard.key == GLFW_KEY_LEFT) {
						left = false;
					}
					break;
				}
				default: {
					break;
				}
			}
		}

		if (right) {
			camPos.x++;
			cam.setPosition(camPos);
		}
		else if (left) {
			camPos.x--;
			cam.setPosition(camPos);
		}

		shader.setMat4("viewProjection", cam.GetViewProjectionMatrix());

		m_renderer.clear();
		m_renderer.batchBegin();
		for (int i = 0; i < 100; i++) {
			m_renderer.batchDraw(tex, { pos[i].x, pos[i].y, 10, 10 });
		}
		m_renderer.batchEnd();
		m_window.update();
	}
	return 0;
}
