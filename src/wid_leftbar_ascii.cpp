//
// Copyleft goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_thing_info.hpp"

static point wid_leftbar_last_thing_position;

static void wid_leftbar_ascii_display(Widp w, point tl, point br)
{
  TRACE_NO_INDENT();

  auto level = game->get_current_level();
  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  auto id = wid_get_thing_id_context(w);

  //
  // If the thing is destroyed it should have removed itself from this list.
  // So if we don't find it, we cannot display it.
  //
  if (std::find(level->wid_leftbar_things.begin(), level->wid_leftbar_things.end(), id) ==
      level->wid_leftbar_things.end()) {
    return;
  }

  auto t = level->thing_find(id);
  if (t) {
    t->blit_ascii_at(tl, true /* lit */, true /* leftbar */);
  }
}

static void wid_leftbar_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  if (game->state != Game::STATE_NORMAL) {
    return;
  }

  auto id = wid_get_thing_id_context(w);
  auto t  = game->level->thing_find_optional(id);
  if (unlikely(! t)) {
    return;
  }

  game->wid_thing_info_create(t);
}

static void wid_leftbar_over_end(Widp w)
{
  TRACE_NO_INDENT();
  wid_thing_info_fini("leftbar");
}

static void wid_leftbar_ascii_describe(Levelp level, Thingp t, int &y_at, int width, bool allow_carried = false,
                                       bool first = false)
{
  TRACE_NO_INDENT();

  auto player = level->player;
  if (! player) {
    return;
  }

  //
  // Covers carried or equipped items
  //
  if (! allow_carried) {
    if (t->immediate_owner()) {
      return;
    }
  }

  level->wid_leftbar_things.push_back(t->id);

  y_at++;
  {
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "It");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    auto  s  = dynprintf("%%fg=gray$%s", t->text_short_capitalised().c_str());
    wid_set_pos(w, tl, br);
    if (t->immediate_owner()) {
      wid_set_text(w, "+ " + std::string(s));
      wid_set_text_lhs(w, true);
    } else {
      wid_set_text(w, s);
    }
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
    wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
    wid_set_thing_id_context(w, t);
    myfree(s);
  }

  {
    TRACE_NO_INDENT();
    auto  w  = wid_new_plain(wid_leftbar, "It tile");
    point tl = make_point(width + 1, y_at);
    point br = make_point(width + 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_thing_id_context(w, t);
    wid_set_on_display(w, wid_leftbar_ascii_display);
    wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
    wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
    wid_set_thing_id_context(w, t);
  }

  if (t->is_on_fire()) {
    y_at++;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "(On fire)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "(On fire)");
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
    wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
    wid_set_thing_id_context(w, t);
  }

  if (t->is_frozen) {
    y_at++;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "(Frozen)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "(Frozen)");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
    wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
    wid_set_thing_id_context(w, t);
  }

  if (t->is_burnt) {
    y_at++;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "(Burnt)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "(Burnt)");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
    wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
    wid_set_thing_id_context(w, t);
  }

  if (t->is_falling) {
    y_at++;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "(Falling)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "(Falling)");
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
    wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
    wid_set_thing_id_context(w, t);
  }

  if (t->is_dead) {
    y_at++;
    TRACE_NO_INDENT();
    auto  w  = wid_new_square_button(wid_leftbar, "(Deceased)");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_pos(w, tl, br);
    if (t->is_undead()) {
      wid_set_text(w, "(Vanquished)");
    } else if (t->is_monst()) {
      wid_set_text(w, "(Dead)");
    } else {
      wid_set_text(w, "(Broken)");
    }
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
    wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
    wid_set_thing_id_context(w, t);
  } else {
    if (t->is_monst() && (game->tick_current - t->tick_last_i_attacked() < 2)) {
      y_at++;
      TRACE_NO_INDENT();
      auto  w  = wid_new_square_button(wid_leftbar, "(Attacking)");
      point tl = make_point(0, y_at);
      point br = make_point(width - 1, y_at);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "(Attacking)");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
      wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
      wid_set_thing_id_context(w, t);
    }

    if (t->stuck_count() > 1) {
      y_at++;
      TRACE_NO_INDENT();
      auto  w  = wid_new_square_button(wid_leftbar, "(Stuck)");
      point tl = make_point(0, y_at);
      point br = make_point(width - 1, y_at);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "(Stuck)");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
      wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
      wid_set_thing_id_context(w, t);
    } else if (t->is_sleeping) {
      y_at++;
      TRACE_NO_INDENT();
      auto  w  = wid_new_square_button(wid_leftbar, "(Sleeping)");
      point tl = make_point(0, y_at);
      point br = make_point(width - 1, y_at);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "(Sleeping)");
      wid_set_style(w, UI_WID_STYLE_DARK);
      wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
      wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
      wid_set_thing_id_context(w, t);
    } else if (t->is_monst() && (t->idle_count() > 1)) {
      y_at++;
      TRACE_NO_INDENT();
      auto  w  = wid_new_square_button(wid_leftbar, "(Idle)");
      point tl = make_point(0, y_at);
      point br = make_point(width - 1, y_at);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "(Idle)");
      wid_set_style(w, UI_WID_STYLE_DARK);
      wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
      wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
      wid_set_thing_id_context(w, t);
    }
  }

  if (player && t->maybe_aip()) {
    for (auto p1 : t->aip()->move_path) {
      if (p1 == player->curr_at) {
        y_at++;
        TRACE_NO_INDENT();
        auto  w  = wid_new_square_button(wid_leftbar, "(Hunting)");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "(Hunting)");
        wid_set_style(w, UI_WID_STYLE_DARK);
        wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
        wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
        wid_set_thing_id_context(w, t);
      }
    }
  }

  if (t->is_door() || t->is_ascend_dungeon() || t->is_descend_dungeon()) {
    if (t->is_open) {
      y_at++;
      TRACE_NO_INDENT();
      auto  w  = wid_new_square_button(wid_leftbar, "(Open)");
      point tl = make_point(0, y_at);
      point br = make_point(width - 1, y_at);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "(Open)");
      wid_set_style(w, UI_WID_STYLE_GREEN);
      wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
      wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
      wid_set_thing_id_context(w, t);
    } else {
      y_at++;
      TRACE_NO_INDENT();
      auto  w  = wid_new_square_button(wid_leftbar, "(Closed)");
      point tl = make_point(0, y_at);
      point br = make_point(width - 1, y_at);
      wid_set_pos(w, tl, br);
      if (t->is_door()) {
        wid_set_text(w, "(Locked)");
      } else {
        wid_set_text(w, "(Closed)");
      }
      wid_set_style(w, UI_WID_STYLE_DARK);
      wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
      wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
      wid_set_thing_id_context(w, t);
    }
  }

  if (! t->is_dead) {
    if (t->is_monst()) {
      y_at++;
      {
        TRACE_NO_INDENT();
        auto  w  = wid_new_plain(wid_leftbar, "Health-bar");
        point tl = make_point(0, y_at);
        point br = make_point(tl.x + width - 1, tl.y);
        wid_set_pos(w, tl, br);

        int i     = (((float) t->health() / ((float) t->health_max()))) * ((float) UI_HEALTH_BAR_STEPS - 1);
        i         = std::min(i, UI_HEALTH_BAR_STEPS - 1);
        i         = std::max(i, 0);
        auto icon = "health_bar_ascii_" + std::to_string(i);
        wid_set_fg_tilename(w, icon);
        wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
        wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
        wid_set_thing_id_context(w, t);
      }
      {
        TRACE_NO_INDENT();
        auto  w  = wid_new_plain(wid_leftbar, "Health");
        point tl = make_point(0, y_at);
        point br = make_point(width - 1, y_at);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Health");
        wid_set_shape_none(w);
        wid_set_text_lhs(w, true);
        wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
        wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
        wid_set_thing_id_context(w, t);
      }
      {
        TRACE_NO_INDENT();
        auto  w  = wid_new_plain(wid_leftbar, "health-value");
        point tl = make_point(3, y_at);
        point br = make_point(tl.x + width - 4, tl.y);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);

        std::string s = std::to_string(t->health()) + "/" + std::to_string(t->health_max());
        wid_set_text(w, s);
        wid_set_text_rhs(w, true);
        wid_set_on_mouse_over_begin(w, wid_leftbar_over_begin);
        wid_set_on_mouse_over_end(w, wid_leftbar_over_end);
        wid_set_thing_id_context(w, t);
      }
    }
  }

  //
  // Display all items as one block, and then a blank line
  //
  {
    int orig_y_at = y_at;
    FOR_ALL_EQUIP(e)
    {
      auto iter = t->equip_get(e);
      if (iter) {
        wid_leftbar_ascii_describe(level, iter, y_at, width, "+ ");
      }
    }

    if (orig_y_at != y_at) {
      y_at++;
    }
  }

  if (t->curr_at == wid_leftbar_last_thing_position) {
    //
    // Things at the same location are grouped
    //
  } else if (t->immediate_owner()) {
    //
    // Carried items are grouped
    //
  } else {
    y_at++;
  }

  wid_leftbar_last_thing_position = t->curr_at;
}

bool wid_leftbar_ascii_create(void)
{
  DBG2("Remake leftbar");
  TRACE_AND_INDENT();

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  int width = UI_LEFTBAR_WIDTH;
  int y_at  = 0;

  {
    TRACE_NO_INDENT();
    point tl = make_point(0, UI_TOPCON_VIS_HEIGHT);
    point br = make_point(width + 1, TERM_HEIGHT - 1);

    wid_leftbar = wid_new_square_window("wid leftbar");
    wid_set_ignore_scroll_events(wid_leftbar, true);
    wid_set_pos(wid_leftbar, tl, br);
    wid_set_style(wid_leftbar, UI_WID_STYLE_SOLID_NONE);
    wid_lower(wid_leftbar);
  }

  wid_leftbar_last_thing_position = point(-1, -1);
  {
    ///////////////////////////////////////////////////////////////////////////
    // Monsters (alive)
    ///////////////////////////////////////////////////////////////////////////
    std::vector< Thingp > m;
    FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL(game->level, t)
    {
      if (! t->is_alive_monst()) {
        continue;
      }

      auto player = level->player;

      if (! get(level->can_see_currently.can_see, t->curr_at.x, t->curr_at.y)) {
        continue;
      }

      if (! level->can_see_unimpeded(player->curr_at, t->curr_at)) {
        continue;
      }

      m.push_back(t);
    }
    FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL_END(game->level)

    sort(m.begin(), m.end(),
         [](Thingp a, Thingp b) -> bool { return (a->curr_at.x > b->curr_at.x) && (a->curr_at.y > b->curr_at.y); });

    for (auto n : m) {
      wid_leftbar_ascii_describe(level, n, y_at, width, false /* allow carried */);
    }
  }

  {
    ///////////////////////////////////////////////////////////////////////////
    // Monsters (dead)
    ///////////////////////////////////////////////////////////////////////////
    std::vector< Thingp > m;
    FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL(game->level, t)
    {
      if (! t->is_dead) {
        continue;
      }

      auto player = level->player;
      if (t->is_player()) {
        continue;
      }

      if (! get(level->can_see_currently.can_see, t->curr_at.x, t->curr_at.y)) {
        continue;
      }

      if (! level->can_see_unimpeded(player->curr_at, t->curr_at)) {
        continue;
      }

      m.push_back(t);
    }
    FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL_END(game->level)

    sort(m.begin(), m.end(),
         [](Thingp a, Thingp b) -> bool { return (a->curr_at.x > b->curr_at.x) && (a->curr_at.y > b->curr_at.y); });

    for (auto n : m) {
      wid_leftbar_ascii_describe(level, n, y_at, width, false /* allow carried */);
    }
  }

  {
    ///////////////////////////////////////////////////////////////////////////
    // Items
    ///////////////////////////////////////////////////////////////////////////
    std::vector< Thingp > m;
    FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL(game->level, t)
    {
      if (! t->is_item()) {
        continue;
      }

      auto player = level->player;
      if (t->is_player()) {
        continue;
      }

      if (! get(level->can_see_currently.can_see, t->curr_at.x, t->curr_at.y)) {
        continue;
      }

      if (! level->can_see_unimpeded(player->curr_at, t->curr_at)) {
        continue;
      }

      m.push_back(t);
    }
    FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL_END(game->level)

    sort(m.begin(), m.end(),
         [](Thingp a, Thingp b) -> bool { return (a->curr_at.x > b->curr_at.x) && (a->curr_at.y > b->curr_at.y); });

    bool first = true;
    for (auto n : m) {
      wid_leftbar_ascii_describe(level, n, y_at, width, false /* allow carried */, first);
      first = false;
    }
  }

  {
    ///////////////////////////////////////////////////////////////////////////
    // Important environmental items
    ///////////////////////////////////////////////////////////////////////////
    std::vector< Thingp > m;
    FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL(game->level, t)
    {
      if (! t->is_door() && ! t->is_ascend_sewer() && ! t->is_descend_sewer() && ! t->is_ascend_dungeon() &&
          ! t->is_descend_dungeon() && ! t->is_brazier() && ! t->is_spiderweb() && ! t->is_barrel() &&
          ! t->is_block_of_ice()) {
        continue;
      }

      auto player = level->player;
      if (t->is_player()) {
        continue;
      }

      if (! get(level->can_see_currently.can_see, t->curr_at.x, t->curr_at.y)) {
        continue;
      }

      if (! level->can_see_unimpeded(player->curr_at, t->curr_at)) {
        continue;
      }

      m.push_back(t);
    }
    FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL_END(game->level)

    sort(m.begin(), m.end(),
         [](Thingp a, Thingp b) -> bool { return (a->curr_at.x > b->curr_at.x) && (a->curr_at.y > b->curr_at.y); });

    bool first = true;
    for (auto n : m) {
      wid_leftbar_ascii_describe(level, n, y_at, width, false /* allow carried */, first);
      first = false;
    }
  }

  wid_update(wid_leftbar);

  DBG2("Remade leftbar");

  return true;
}
