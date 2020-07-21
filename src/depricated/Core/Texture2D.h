#ifndef TGAME_TEXTURE2D_H
#define TGAME_TEXTURE2D_H

#include "moduleDefinitions.h"
#include <GL/glew.h>

class Texture2D
{
public:
  // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
  unsigned int id;
  // texture image dimensions
  GLsizei width, height;// width and height of loaded image in pixels
  // texture Format
  GLint internalFormat;// format of texture object
  unsigned int imageFormat;// format of loaded image
  // texture configuration
  GLint wrapS;// wrapping mode on S axis
  GLint wrapT;// wrapping mode on T axis
  GLint filterMin;// filtering mode if texture pixels < screen pixels
  GLint filterMax;// filtering mode if texture pixels > screen pixels
  // constructor (sets default texture modes)
  Texture2D();
  // generates texture from image data
  void Generate(GLsizei _width, GLsizei _height, unsigned char *_data);
  // binds the texture as the current active GL_TEXTURE_2D texture object
  void Bind() const;
};


#endif// TGAME_TEXTURE2D_H
