#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback( GLFWwindow*, int width, int height )
{
  glViewport( 0, 0, width, height );
}

void processInput( GLFWwindow* window )
{
  if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
  {
    glfwSetWindowShouldClose( window, true );
  }
}

void setBackground()
{
  glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
  glClear( GL_COLOR_BUFFER_BIT );
}

auto main() -> int
{
  glfwInit();
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

  GLFWwindow* window = glfwCreateWindow( 800, 600, "ModernCPP", nullptr, nullptr );
  if( window == nullptr )
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent( window );
  if( !gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress ) )
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  glViewport( 0, 0, 800, 600 );
  glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

  while( !glfwWindowShouldClose( window ) )
  {
    processInput( window );
    glfwPollEvents();
    setBackground();
    glfwSwapBuffers( window );
  }

  glfwTerminate();
  return 0;
}
