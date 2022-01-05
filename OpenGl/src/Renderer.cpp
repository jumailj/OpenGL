#include "Renderer.h"


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR) {
    }
}

bool  GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError())
    {
      //  logger::GetCoreLogger()->error("[opengl error]({0}):{1}\n file:{2}\n line:{3}", error, function, file, line);
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0)); // spcificing index data. (not vertex buffer);
}
