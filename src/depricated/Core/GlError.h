#ifndef TGAME_GLERROR_H
#define TGAME_GLERROR_H

namespace TGEngine::core {
// Ask Opengl for errors:
// Result is printed on the standard output
// usage :
//      glCheckError(__FILE__,__LINE__);
class GlError {
public:
  static void glCheckError(const char *file, unsigned int line);
};

}

#endif// TGAME_GLERROR_H
