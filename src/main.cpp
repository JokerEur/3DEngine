#include "window/Window.hpp"
#include "window/Events.hpp"
#include "window/Camera.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "loaders/png_load.hpp"

#include "color.hpp"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>


float vertices[] = {
		// x    y     z     u     v
	   -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
		1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
	   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int main(int argc, char const *argv[])
{
    Window::initialize(1280,720,"Window");
    Events::initialize();

    glClearColor(0.6f, 0.62f,0.65f , 1);

    Shader *shader = loadShader("../res/main.glslv", "../res/main.glslf");
    if(shader == nullptr){
        std::cerr << BOLDRED << "failed to load shader"<< RESET << '\n';
        Window::terminate();
        return 1;
    }

    Texture* texture = load_texture("../res/img.png");
	if (texture == nullptr){
		std::cerr<< BOLDRED << "failed to load texture"<< RESET << std::endl;
		delete shader;
		Window::terminate();
		return 1;
	}

    // Create VAO
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	glClearColor(0.6f,0.62f,0.65f,1);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	extern Camera* camera; //! fix this extern variable

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.5f,0,0));


	float lastTime = static_cast<float>(SDL_GetTicks()) / 1000.0f;
	float delta{0.0f};

	float speed = 5.0f;

	float camX = 0.0f;
	float camY = 0.0f;

    while(!Window::isShouldClose()){
		float currentTime = static_cast<float>(SDL_GetTicks())/ 1000.0f;
		delta = lastTime - currentTime;
		lastTime = currentTime;

		if(Events::justPressed(SDLK_TAB)){
			Events::toogleCursor();
		}

		if(Events::pressed(SDLK_w)){
			camera->position_ -= camera->front_ * delta * speed;
		}
		if(Events::pressed(SDLK_s)){
			camera->position_ += camera->front_ * delta * speed;
		}
		if(Events::pressed(SDLK_a)){
			camera->position_ += camera->right_ * delta * speed;
		}
		if(Events::pressed(SDLK_d)){
			camera->position_ -= camera->right_ * delta * speed;
		}

		if (Events::cursorLocked){
			camY += -Events::deltaY / 720 * 2;
			camX += -Events::deltaX / 720 * 2;

			if (camY < -glm::radians(89.0f)){
				camY = -glm::radians(89.0f);
			}
			if (camY > glm::radians(89.0f)){
				camY = glm::radians(89.0f);
			}

			camera->rotation_ = glm::mat4(1.0f);
			camera->rotate(camY, camX, 0);
		}


        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();
		shader->uniformMatrix("model" , model);
		shader->uniformMatrix("projview", camera->getProjection()*camera->getView());
        texture->bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);


        Events::pullEvents();
        Window::swapBuffers();
    }

    delete shader;
	delete texture;
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

    Window::terminate();
    return 0;
}
