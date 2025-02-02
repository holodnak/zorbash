//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

void Thing::plant_tick(void)
{
  if (! level->is_carnivorous_plant(curr_at.x, curr_at.y)) {
    return;
  }

  if (! is_meat()) {
    return;
  }

  bool hit;

  //
  // Give the player a chance
  //
  hit = d20() >= stat_dex();

  if (hit) {
    dbg("Plant hit");
    TRACE_AND_INDENT();

    //
    // Attack if we are standing on a plant
    //
    FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_OBJ)
    {
      if (! t->is_carnivorous_plant()) {
        continue;
      }
      if (t == this) {
        continue;
      }
      AttackOptions attack_options {};
      t->attack(this, &attack_options);
      break;
    }
    FOR_ALL_THINGS_END()
  }
}
