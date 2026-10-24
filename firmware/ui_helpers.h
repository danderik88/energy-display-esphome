#pragma once
// Small helpers shared by ui.yaml and the tile modules in tiles/.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string>
#include "lvgl.h"

namespace ui {

// Number with Italian decimal comma; NaN (HA unavailable/unknown) -> "--", never 0
inline std::string fmt(float v, const char *f) {
  if (std::isnan(v)) return "--";
  char b[24];
  snprintf(b, sizeof b, f, v);
  std::string s(b);
  std::replace(s.begin(), s.end(), '.', ',');
  return s;
}

inline bool bad(const std::string &s) { return s.empty() || s == "unavailable" || s == "unknown"; }

inline void text(lv_obj_t *o, const std::string &s) { lv_label_set_text(o, s.c_str()); }

constexpr uint32_t MUTED = 0xA9B4BF;

// Widgets registered by ui.yaml on every refresh (cheap), used by the tile modules
struct Tile { lv_obj_t *icon_bg, *icon, *val, *cap; };
inline Tile tiles[5];
inline lv_obj_t *pop[7];  // icon_bg, icon, title, value, names, vals, text
inline lv_obj_t *pop_extra[4];  // extra popup widgets owned by modules, hidden before each popup

inline void tile(int slot, const char *glyph, uint32_t col, const std::string &val, const std::string &cap,
                 uint32_t cap_col = MUTED) {
  Tile &t = tiles[slot];
  if (t.val == nullptr) return;
  lv_label_set_text(t.icon, glyph);
  lv_obj_set_style_text_color(t.icon, lv_color_hex(col), 0);
  lv_obj_set_style_bg_color(t.icon_bg, lv_color_hex(col), 0);
  text(t.val, val);
  text(t.cap, cap);
  lv_obj_set_style_text_color(t.cap, lv_color_hex(cap_col), 0);
}

// names / vals: one row per line ("\n"), shown as two aligned columns
inline void popup(const char *glyph, uint32_t col, const std::string &title, const std::string &value,
                  const std::string &names, const std::string &vals, const std::string &body) {
  if (pop[0] == nullptr) return;
  lv_obj_set_style_bg_color(pop[0], lv_color_hex(col), 0);
  lv_label_set_text(pop[1], glyph);
  lv_obj_set_style_text_color(pop[1], lv_color_hex(col), 0);
  text(pop[2], title);
  text(pop[3], value);
  lv_obj_set_style_text_color(pop[3], lv_color_hex(col), 0);
  text(pop[4], names);
  text(pop[5], vals);
  text(pop[6], body);
}

}  // namespace ui
