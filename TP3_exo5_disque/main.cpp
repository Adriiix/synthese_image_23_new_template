#include "glimac/default_shader.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/glm.hpp"
#include "p6/p6.h"

struct Vertex2DColor {
    glm::vec2 position;
    glm::vec3 color;
    Vertex2DColor()
    {
    }
    Vertex2DColor(glm::vec2 pos, glm::vec3 col)
    {
        position = pos;
        color    = col;
    }
};

int main()
{
    auto ctx = p6::Context{{1280, 720, "TP3 EX5"}};
    ctx.maximize_window();

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    // shaders
    const p6::Shader shader = p6::load_shader(
        "shaders/triangle.vs.glsl",
        "shaders/triangle.fs.glsl"
    );

    // CREATION DU VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo); // binder le buffer

    const size_t               N = 30; // nombre de triangle
    std::vector<Vertex2DColor> vertices;
    float                      teta;
    for (size_t i = 0; i < N; i++)
    {
        teta = (i * 2 * glm::pi<float>()) / N;
        vertices.push_back(Vertex2DColor(glm::vec2(0, 0), glm::vec3(1, 1, 1)));
        vertices.push_back(Vertex2DColor(glm::vec2(glm::cos(teta), glm::sin(teta)), glm::vec3(1, 1, 1)));
        vertices.push_back(Vertex2DColor(glm::vec2(glm::cos((2 * glm::pi<float>()) / N + teta), glm::sin((2 * glm::pi<float>()) / N + teta)), glm::vec3(1, 1, 1)));
    };

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // debinder le vbo

    // CREATION DU VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao); // binder les vao

    const GLuint VERTEX_ATTR_POSITION = 3;
    const GLuint VERTEX_ATTR_COLOR    = 8;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION); // attribut des vertex, avec 3 pour la position
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);    // attribut des vertex, avec 8 pour la couleur

    glBindBuffer(GL_ARRAY_BUFFER, vbo); // binder le buffer a nouveau

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)offsetof(Vertex2DColor, position)); // specification des attributs de vertex

    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)offsetof(Vertex2DColor, color)); // specification des attributs de vertex

    glBindBuffer(GL_ARRAY_BUFFER, 0); // debinder le vbo

    glBindVertexArray(0); // debinder le vao

    // Declare your infinite update loop.
    ctx.update = [&]() {
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao); // binder le vao

        shader.use();

        glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // on dessine le triangle

        glBindVertexArray(0); // debinder le vao
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();

    // liberation des ressources
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}