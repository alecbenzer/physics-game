#include "world.h"
#include "level.h"

#include <cstdio>
#include <vector>

int main(int argc, char* argv[]) {
  World world;
  world.SetViewHeight(30);
  world.Init();

  std::vector<Level*> levels;
  levels.push_back(new Level("levels/level1.lua"));
  levels.push_back(new Level("levels/level2.lua"));

  int level_index = 0;
  Level* current_level = levels[level_index];

  current_level->Setup(&world);

  while (!world.done()) {
    world.Step();
    current_level->Step(&world);

    if (current_level->won()) {
      printf("You beat level %d\n", level_index + 1);
      if (++level_index == levels.size()) {
        printf("You beat the game!\n");
        break;
      } else {
        delete current_level;
        world.ClearObjects();
        current_level = levels[level_index];
        current_level->Setup(&world);
      }
    } else if (current_level->lost()) {
      printf("You lost :(\n");
      break;
    }

    world.Render();
  }

  return 0;
}
