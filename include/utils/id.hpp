#pragma once

#include "utils/types.hpp"

namespace id {

using id_t = u64;

// Generates and returns a new ID of type `id::id_t`.
id_t generate();

}  // namespace id
