#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <iomanip>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define _USE_MATH_DEFINES
#include <cmath>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/Log.h"
#include "Core/Input.h"

#include "Renderer/Buffer.h"
#include "Renderer/Context.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"