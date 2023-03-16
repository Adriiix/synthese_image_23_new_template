#include <vector>
#include "glimac/default_shader.hpp"
#include "p6/p6.h"

struct Vertex2DUV {
    glm::vec2 position;
    glm::vec2 texture;

    Vertex2DUV(glm::vec2 pos, glm::vec2 tex) // constructeur
        : position(pos), texture(tex)
    {
    }
};

int main()
{
    auto ctx = p6::Context{{1280, 720, "TP4 EX4"}};
    ctx.maximize_window();

    // load shaders
    const p6::Shader shader = p6::load_shader(
        "shaders/tex2D.vs.glsl",
        "shaders/tex2D.fs.glsl"
    );

    // création des 3 sommets
    Vertex2DUV P1 = Vertex2DUV(glm::vec2(-1.f, -1.f), glm::vec2(0, 0));
    Vertex2DUV P2 = Vertex2DUV(glm::vec2(1.f, -1.f), glm::vec2(0, 0));
    Vertex2DUV P3 = Vertex2DUV(glm::vec2(0, 1.f), glm::vec2(0, 0));

    // création du vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // binding du vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // remplissage VBO
    std::vector<Vertex2DUV> vertices;
    vertices.push_back(P1);
    vertices.push_back(P2);
    vertices.push_back(P3);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2DUV), vertices.data(), GL_STATIC_DRAW);

    // debinder le VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // création du vao
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // binder le VAO
    glBindVertexArray(vao);

    // activation des attributs de vertex
    static constexpr GLuint VERTEX_ATTR_POSITION = 0;
    static constexpr GLuint VERTEX_ATTR_TEXTURE  = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

    //  spécification des attributs de vertex
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, position)); // specification des attributs de vertex

    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, texture)); // specification des attributs de vertex

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ctx.update = [&]() {
        shader.use();
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*********************************GLsizei stride
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}