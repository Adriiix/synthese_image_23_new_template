#include <cstddef>
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
    auto ctx = p6::Context{{1280, 720, "TP3 EX6"}};
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
    vertices.push_back(Vertex2DColor(glm::vec2(0, 0), glm::vec3(1, 1, 1)));
    for (size_t i = 0; i < N; i++)
    {
        teta = (i * 2 * glm::pi<float>()) / N;
        vertices.push_back(Vertex2DColor(glm::vec2(glm::cos(teta), glm::sin(teta)), glm::vec3(1, 1, 1)));
    };

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // debinder le vbo

    // CREATION DU IBO
    GLuint ibo;
    glad_glGenBuffers(1, &ibo);

    // => On bind sur GL_ELEMENT_ARRAY_BUFFER, cible reservée pour les IBOs
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // => Tableau d'indices : ce sont les indices des sommets à dessiner
    // On en a 6 afin de former deux triangles
    // Chaque indice correspond au sommet correspondant dans le VBO

    std::vector<uint32_t> indices;

    for (size_t i = 1; i < N; i++)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    indices.push_back(0);
    indices.push_back(N);
    indices.push_back(1);

    // => On remplit l'IBO avec les indices :
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * N * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    // => Comme d'habitude on debind avant de passer à autre chose
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // CREATION DU VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao); // binder les vao

    // => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
    // cela a pour effet d'enregistrer l'IBO dans le VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

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

        // => On utilise glDrawElements à la place de glDrawArrays
        // Cela indique à OpenGL qu'il doit utiliser l'IBO enregistré dans le VAO
        glDrawElements(GL_TRIANGLES, 3 * N, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0); // debinder le vao
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();

    // liberation des ressources
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}