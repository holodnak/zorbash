//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_dice.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::on_stuck(void)
{
  TRACE_NO_INDENT();

  auto on_stuck = tp()->on_stuck_do();
  if (std::empty(on_stuck)) {
    return;
  }

  auto t = split_tokens(on_stuck, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(), (int) curr_at.x,
        (int) curr_at.y);

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_stuck call [%s] expected mod:function, got %d elems", on_stuck.c_str(), (int) on_stuck.size());
  }
}

void Thing::stuck(const std::string &why)
{
  dbg("Stuck: %s", why.c_str());
  TRACE_AND_INDENT();

  stuck_count_incr();

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (! iter->on_stuck_do().empty()) {
        iter->stuck(why);
      }
    }
  }
}

void Thing::unstuck(void)
{
  dbg("Unstuck");
  TRACE_AND_INDENT();

  stuck_count_set(0);

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (! iter->on_stuck_do().empty()) {
        iter->unstuck();
      }
    }
  }
}

//
// Are we stuck at the current location?
//
bool Thing::is_stuck_check(void)
{
  TRACE_NO_INDENT();

  bool stuck = false;

  //
  // Makes sure ghosts (or the cursor!) do not get stuck in webs.
  //
  if (is_ethereal()) {
    return false;
  }

  if (! is_monst() && ! is_player()) {
    return false;
  }

  if (is_frozen) {
    return true;
  }

  if (level->is_sticky(curr_at.x, curr_at.y)) {
    if (is_sticky()) {
      //
      // ok
      //
    } else if (buff_find_is_slippery()) {
      //
      // ok
      //
    } else {
      stuck = true;
    }
  }

  if (level->is_spiderweb(curr_at.x, curr_at.y)) {
    if (is_immune_to_spiderwebs()) {
      //
      // ok
      //
    } else if (buff_find_is_slippery() && (d20() < stat_str())) {
      //
      // Give a better chance to escape if slippery.
      //
    } else if (10 + d20() < stat_str()) {
      //
      // Give a chance to escape.
      //
    } else {
      stuck = true;
    }
  }

  if (level->is_barrel(curr_at.x, curr_at.y)) {
    if (is_flying()) {
      //
      // ok
      //
    } else if (15 + d20() < stat_str()) {
      //
      // Give a chance to escape.
      //
    } else {
      stuck = true;
    }
  }

  if (level->is_heavy(curr_at.x, curr_at.y)) {
    if (is_flying()) {
      //
      // ok
      //
    } else if (is_heavy()) {
      //
      // ok
      //
    } else {
      stuck = true;
    }
  }

  //
  // Blocked from moving by something stronger?
  //
  FOR_ALL_NON_INTERNAL_THINGS(level, it, curr_at.x, curr_at.y)
  {
    if (it == this) {
      continue;
    }

    if (! it->is_alive_monst()) {
      continue;
    }

    if (it->is_engulfer() || it->is_heavy()) {
      if (! d20roll(stat_str(), it->stat_str_total())) {
        stuck = true;
      }
    }
  }
  FOR_ALL_THINGS_END()

  return stuck;
}

void Thing::is_stuck_update(void)
{
  TRACE_NO_INDENT();

  //
  // Check if we are still stuck
  //
  if (stuck_count()) {
    if (! is_stuck_check()) {
      if (is_player()) {
        msg("You are no longer stuck!");
        stuck_count_set(0);
      }
      return;
    }

    //
    // Yes.
    //
    stuck("still stuck");
  } else {
    //
    // Are we newly stuck?
    //
    if (! is_stuck_check()) {
      return;
    }

    //
    // Yes.
    //
    stuck("newly stuck at location");

    if (is_player()) {
      if (level->is_spiderweb(curr_at.x, curr_at.y)) {
        msg("You are trapped in a web!");
      } else if (level->is_block_of_ice(curr_at.x, curr_at.y)) {
        msg("You are trapped in ice!");
      } else if (level->is_barrel(curr_at.x, curr_at.y)) {
        msg("You are trapped inside a barrel!");
      } else {
        msg("You are stuck!");
      }
    }
  }

  if (is_frozen) {
    popup(string_sprintf("%%fg=lightblue$!"));
  } else {
    popup(string_sprintf("%%fg=red$!"));
  }

  //
  // Shake the web or block of ice or barrel...
  //
  FOR_ALL_NON_INTERNAL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_player() || t->is_monst()) {
      t->wobble(pcg_random_range(5, 20));
    }
    if (t->is_spiderweb()) {
      t->wobble(5);
    }
    if (t->is_block_of_ice()) {
      t->wobble(5);
    }
    if (t->is_barrel()) {
      t->wobble(5);
    }
  }
  FOR_ALL_THINGS_END()
}

bool Thing::is_stuck_currently(void) { return stuck_count() > 0; }

int Thing::stuck_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return 0;
  }

  if (maybe_aip()) {
    return (aip()->stuck_count);
  }
  return 0;
}

int Thing::stuck_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count = v);
}

int Thing::stuck_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count -= v);
}

int Thing::stuck_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count += v);
}

int Thing::stuck_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count--);
}

int Thing::stuck_count_incr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count++);
}
