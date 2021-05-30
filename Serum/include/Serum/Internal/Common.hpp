/// @file Common.hpp
/// Contains common includes and definitions shared across Serum header files.

#ifndef SERUM_INTERNAL_COMMON_HPP
#define SERUM_INTERNAL_COMMON_HPP

/// Indicates that Serum has been included.
#define SERUM

/// The major component of this version of Serum.
#define SERUM_VERSION_MAJOR 0

/// The minor component of this version of Serum.
#define SERUM_VERSION_MINOR 3

/// The patch component of this version of Serum.
#define SERUM_VERSION_PATCH 0

#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <memory>
#include <unordered_map>
#include <any>
#include <type_traits>
#include <optional>
#include <typeindex>
#include <iomanip>
#include <ostream>
#include <functional>
#include <algorithm>
#include <utility>

#include "Serum/SerumException.hpp"

#endif // SERUM_INTERNAL_COMMON_HPP
