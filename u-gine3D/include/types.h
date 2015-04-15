#ifndef UGINE_TYPES_H
#define UGINE_TYPES_H

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

#include "../lib/glfw/glfw3.h"
#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/glm/gtc/random.hpp"
#include "../lib/glm/gtc/type_ptr.hpp"
#include "smartptr.h"
#include <algorithm>
#include <cstddef>

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat4 mat4;
typedef glm::quat quat;

#define RENDER  Renderer::Instance()

#endif // UGINE_TYPES_H
