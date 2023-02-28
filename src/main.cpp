#include "window/Window.hpp"
#include "window/Events.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "loaders/png_load.hpp"

#include "color.hpp"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>


float vertices[] = {

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



    while(!Window::isShouldClose()){
        Events::pullEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();
        texture->bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        Window::swapBuffers();
    }

    delete shader;
	delete texture;
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

    Window::terminate();
    return 0;
}
