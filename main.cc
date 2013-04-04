#include "object.h"
#include "world.h"

int main(int argc, char* argv[]) {
  World world;
  world.SetViewHeight(30);
  world.Init();

  Object* box = world.NewObject();
  box->set_initial_position(0.0, 0.0);
  box->set_box_shape(1.0, 1.0);
  box->set_dynamic();
  box->Init();

  Object* stick = world.NewObject();
  stick->set_initial_position(0.4, 5.0);
  stick->set_box_shape(0.1, 1.0);
  stick->set_static();
  stick->Init();

  Object* floor = world.NewObject();
  floor->set_initial_position(0.0, 10.0);
  floor->set_box_shape(10.0, 1.0);
  floor->set_static();
  floor->Init();

  while (!world.done()) {
    world.Step();
    world.Render();
  }

  return 0;
}
