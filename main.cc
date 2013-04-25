#include "basic_object.h"
#include "world.h"
#include "ship.h"

#include <iostream>
using std::cerr;
using std::endl;

int main(int argc, char* argv[]) {
  World world;
  world.SetViewHeight(30);
  world.Init();

  BasicObject* box = new BasicObject();
  box->set_initial_position(-2.0, 0.0);
  box->set_box_shape(1.0, 1.0);
  box->set_dyanmic();

  BasicObject* stick = new BasicObject();
  stick->set_initial_position(0.4, 5.0);
  stick->set_box_shape(0.1, 1.0);
  stick->set_static();

  BasicObject* floor = new BasicObject();
  floor->set_initial_position(0.0, 10.0);
  floor->set_box_shape(10.0, 1.0);
  floor->set_static();

  world.AddObject(box);
  world.AddObject(stick);
  world.AddObject(floor);

  Ship ship;
  world.AddObject(&ship);

  while (!world.done()) {

    world.Step();
    world.Render();

    if (world.key_down(SDLK_UP) || world.key_down(SDLK_w)) {
      ship.ForceUp();
    }
    if (world.key_down(SDLK_DOWN) || world.key_down(SDLK_s)) {
      ship.ForceDown();
    }
    if (world.key_down(SDLK_LEFT) || world.key_down(SDLK_a)) {
      ship.ForceLeft();
    }
    if (world.key_down(SDLK_RIGHT) || world.key_down(SDLK_d)) {
      ship.ForceRight();
    }

    if (world.button_down(SDL_BUTTON_LEFT)) {
      world.PerformRaycast(ship.position(), world.mouse_position());

      if (world.raycast_body() != NULL) {
        cerr << "hit\n";
        b2Vec2 hit = world.raycast_point();
        b2Vec2 pos = ship.position();

        float distance = (hit - pos).Length();

        b2Vec2 dir = hit - pos;
        dir.Normalize();

        cerr << "dir: " << dir.x << "," << dir.y << "\n";

        if (distance > 2.0) {
          world.raycast_body()->ApplyForceToCenter(-90.0 * dir);
        }
      }
    }

    if (world.key_down(SDLK_q)) {
      ship.Stabilize();
    } else {
      ship.NoStabilize();
    }
  }

  return 0;
}
