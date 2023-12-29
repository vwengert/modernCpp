#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <openGL.h>
namespace
{
  void frameBufferSizeCallback( GLFWwindow*, int width, int height )
  {
    glViewport( 0, 0, width, height );
  }
}

OpenGL::OpenGL( int width, int height, const char* title )
  : m_window{ nullptr }
{
  glfwInit();
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

  m_window = glfwCreateWindow( width, height, title, nullptr, nullptr );
  if( m_window == nullptr )
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    throw;
  }

  glfwMakeContextCurrent( m_window );
  if( !gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress ) )
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    throw;
  }

  glfwSetFramebufferSizeCallback( m_window, frameBufferSizeCallback );
}

OpenGL::~OpenGL()
{
  glfwTerminate();
}

GLFWwindow* OpenGL::window()
{
  return m_window;
}

void OpenGL::setBackgroundColor( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
  glClearColor( red, green, blue, alpha );
  glClear( GL_COLOR_BUFFER_BIT );
}

unsigned int OpenGL::createAndCompileShader( const char* shaderGLSL, unsigned int shaderType )
{
  unsigned int vertexShader;
  vertexShader = glCreateShader( shaderType );
  glShaderSource( vertexShader, 1, &shaderGLSL, nullptr );
  glCompileShader( vertexShader );

  int success;
  char infoLog[ 512 ];
  glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
  if( !success )
  {
    glGetShaderInfoLog( vertexShader, 512, nullptr, infoLog );
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    throw;
  }
  return vertexShader;
}

unsigned int OpenGL::createShaderProgram( const std::vector< unsigned int >& shaders )
{
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  for( auto shader : shaders )
  {
    glAttachShader( shaderProgram, shader );
  }
  glLinkProgram( shaderProgram );

  int success;
  char infoLog[ 512 ];
  glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
  if( !success )
  {
    glGetProgramInfoLog( shaderProgram, 512, nullptr, infoLog );
    std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    throw;
  }

  for( auto shader : shaders )
  {
    glDeleteShader( shader );
  }

  return shaderProgram;
}

void OpenGL::drawVertices( unsigned int shaderProgram, float* vertices, long long size )
{
  unsigned int VBO;
  unsigned int VAO;
  glGenBuffers( 1, &VBO );
  glBindBuffer( GL_ARRAY_BUFFER, VBO );
  glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );

  glBindBuffer( GL_ARRAY_BUFFER, VBO );
  glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );

  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void* ) nullptr );
  glEnableVertexAttribArray( 0 );
  glUseProgram( shaderProgram );
  glGenVertexArrays( 1, &VAO );
  glBindVertexArray( VAO );
  glBindBuffer( GL_ARRAY_BUFFER, VBO );
  glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );

  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void* ) nullptr );
  glEnableVertexAttribArray( 0 );
  glUseProgram( shaderProgram );
  glBindVertexArray( VAO );
  glUseProgram( shaderProgram );
  glBindVertexArray( VAO );
  glDrawArrays( GL_TRIANGLES, 0, 3 );
}
