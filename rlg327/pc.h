#ifndef PC_H
# define PC_H

# include <stdint.h>

# include "dims.h"
# include "character.h"
# include "dungeon.h"

typedef enum eq_slot {
  eq_slot_weapon,
  eq_slot_offhand,
  eq_slot_ranged,
  eq_slot_light,
  eq_slot_armor,
  eq_slot_helmet,
  eq_slot_cloak,
  eq_slot_gloves,
  eq_slot_boots,
  eq_slot_amulet,
  eq_slot_lring,
  eq_slot_rring,
  num_eq_slots
} eq_slot_t;

extern const char *eq_slot_name[num_eq_slots];

class pc : public character {
 private:
  void recalculate_speed();
  uint32_t has_open_inventory_slot();
  int32_t get_first_open_inventory_slot();
  object *from_pile(dungeon_t *d, pair_t pos);

 public:
  terrain_type_t known_terrain[DUNGEON_Y][DUNGEON_X];
  unsigned char visible[DUNGEON_Y][DUNGEON_X];
  object *eq[num_eq_slots];
  object *in[MAX_INVENTORY];

  uint32_t wear_in(uint32_t slot);
  uint32_t remove_eq(uint32_t slot);
  uint32_t drop_in(dungeon_t *d, uint32_t slot);
  uint32_t destroy_in(uint32_t slot);
  uint32_t pick_up(dungeon_t *d);
  pc();
  ~pc();
};

class object;
typedef struct dungeon dungeon_t;
#include "dungeon.h"

uint32_t pc_is_alive(dungeon_t *d);
void pc_config(dungeon_t *d);
uint32_t pc_next_pos(dungeon_t *d, pair_t dir);
void place_pc(dungeon_t *d);
void pc_learn_terrain(pc *p, pair_t pos, terrain_type_t ter);
terrain_type_t pc_learned_terrain(pc *p, int8_t y, int8_t x);
void pc_init_known_terrain(pc *p);
void pc_observe_terrain(pc *p, dungeon_t *d);
int32_t is_illuminated(pc *p, int8_t y, int8_t x);
void pc_reset_visibility(pc *p);
void pc_see_object(character *the_pc, object *o);

#endif
