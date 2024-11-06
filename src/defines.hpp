#ifndef DEBUGMODE
#include <iostream>
#  define DEBUG_LOG(x) do {std::cerr << x;} while (0)
#else
#  define DEBUG_LOG(x) do {} while (0)
#endif


