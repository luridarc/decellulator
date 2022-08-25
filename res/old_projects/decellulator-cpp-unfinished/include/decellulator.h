#pragma once

#ifdef _WIN32
  #define decellulator_EXPORT __declspec(dllexport)
#else
  #define decellulator_EXPORT
#endif

#include <cstdlib>

decellulator_EXPORT void decellulator();

