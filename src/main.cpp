#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <memory>
#include <openGL.h>

void processInput( GLFWwindow* window )
{
  if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
  {
    glfwSetWindowShouldClose( window, true );
  }
}

auto main() -> int
{
  auto engine = std::make_unique< OpenGL >( 800, 600, "modern C++" );

  float vertices[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };

  // generate a simple vertex shader
  const char* vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "void main()\n"
                                   "{\n"
                                   " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                   "}\n";
  // generate a simple fragment shader
  const char* fragmentShaderSource = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                     "}\n";

  std::vector< unsigned int > shaders;
  shaders.push_back( engine->createAndCompileShader( vertexShaderSource, GL_VERTEX_SHADER ) );
  shaders.push_back( engine->createAndCompileShader( fragmentShaderSource, GL_FRAGMENT_SHADER ) );

  unsigned int shaderProgram = engine->createShaderProgram( shaders );
  shaders.clear();

  while( !glfwWindowShouldClose( engine->window() ) )
  {
    processInput( engine->window() );
    glfwPollEvents();
    engine->setBackgroundColor( 0.2f, 0.3f, 0.3f, 1.0f );
    engine->drawVertices( shaderProgram, vertices, sizeof vertices );
    glfwSwapBuffers( engine->window() );
  }

  return 0;
}
