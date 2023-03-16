#include "glimac/default_shader.hpp"
#include "p6/p6.h"

int main()
{
    auto ctx = p6::Context{{1280, 720, "TP4 EX3"}};
    ctx.maximize_window();

    const p6::Shader shader = p6::load_shader(
        "shaders/mandelbrot.vs.glsl",
        "shaders/mandelbrot.fs.glsl"
    );

    // creation du vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);
    // binding du vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // remplissage VBO
    GLfloat vertices[] = {
        -1.f, 1.f,
        1.f, 1.f,
        1.f, -1.f,
        1.f, -1.f,
        -1.f, -1.f,
        -1.f, 1.f};

    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    // debinder le VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // création du VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    // binder le VAO
    glBindVertexArray(vao);
    // activation des attributs de vertex
    static constexpr GLuint vertex_attr_position = 0;
    glEnableVertexAttribArray(vertex_attr_position);
    //  spécification des attributs de vertex
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(vertex_attr_position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (const GLvoid*)(0 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // Declare your infinite update loop.

    ctx.update = [&]() {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        /*********************************GLsizei stride
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}