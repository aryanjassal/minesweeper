#include "utils/id.hpp"

id::id_t next_id = 0;

id::id_t id::generate() {
  return next_id++;
}
