#pragma once

#include <vector>
class GLFWwindow;

class OpenGL
{
  public:
    OpenGL( int width, int height, const char* title );
    ~OpenGL();

    static unsigned int createAndCompileShader( const char* shaderGLSL, unsigned int shaderType );
    static unsigned int createShaderProgram( const std::vector< unsigned int >& shaders );
    static void drawVertices( unsigned int shaderProgram, float* vertices, long long size );
    static void setBackgroundColor( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
    static void pollEvents();
    void processInput();
    void swapBuffers();
    GLFWwindow* window();

  private:
    GLFWwindow* m_window;
};