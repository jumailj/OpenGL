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
