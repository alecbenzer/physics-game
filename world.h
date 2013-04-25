#ifndef _WORLD_H
#define _WORLD_H

#include <iostream>

#include <vector>
#include <set>
#include <SDL/SDL.h>
#include "object.h"
#include "help.h"

class RayCastCallback : public b2RayCastCallback {
 public:
  RayCastCallback() : body_(NULL) {}

  float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                      const b2Vec2& normal, float fraction);

  void reset() {
    body_ = NULL;
  }

  b2Body* body() { return body_; }
  b2Vec2 point() { return point_; }
  b2Vec2 normal() { return normal_; }

  b2Body* body_;
  b2Vec2 point_;
  b2Vec2 normal_;
};

class ContactListener : public b2ContactListener {
 public:
  void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

class World {
 public:

  World();
  ~World();

  void SetScreenSize(int w, int h) {
    window_width_ = w;
    window_height_ = h;
  }

  void SetViewHeight(int view_height) {
    view_height_ = view_height;
  }

  void SetViewCenter(double x, double y) {
    view_x_ = x;
    view_y_ = y;
  }

  void SetStepParams(double time_step, int velocity_iters, int position_iters) {
    time_step_ = time_step;
    velocity_iters_ = velocity_iters;
    position_iters_ = position_iters;
  }

  void AddObject(Object* obj);
  void ClearObjects();

  void Init();
  void Cleanup();

  void Step();
  void Render();

  void Message(std::string msg);

  bool done() { return done_; }

  void set_gravity(double down) {
    world_.SetGravity(b2Vec2(0.0, down));
  }

  bool key_down(SDLKey key) {
    return key_down_.find(key) != key_down_.end();
  }

  bool button_down(uint8 button) {
    return button_down_.find(button) != button_down_.end();
  }

  double mouse_x() {
    return mouse_x_;
  }

  double mouse_y() {
    return mouse_y_;
  }

  b2Vec2 mouse_position() {
    return b2Vec2(mouse_x_, mouse_y_);
  }

  void PerformRaycast(const b2Vec2& a, const b2Vec2& b);

  b2Body* raycast_body() {
    return raycast_callback_.body();
  }

  b2Vec2 raycast_point() {
    return raycast_callback_.point();
  }

 protected:
  b2World world_;

  // parameters for world simulation
  double time_step_;
  int velocity_iters_;
  int position_iters_;

 private:
  DISALLOW_COPY_AND_ASSIGN(World);

  RayCastCallback raycast_callback_;
  ContactListener contact_listener_;

  void UpdateViewport();

  // pixel dimmensions of the window we're displaying
  int window_width_;
  int window_height_;

  // the height (in Box2D units) that the window's height should represent
  double view_height_;

  // The width (in Box2D units) that the window's width represents. It's
  // calculated based on view_height_.
  double view_width_;

  // center (in Box2D coordinates) of the rendering view
  double view_x_;
  double view_y_;

  bool done_;

  std::vector<Object*> objects_;

  std::set<SDLKey> key_down_;

  std::set<uint8> button_down_;
  double mouse_x_;
  double mouse_y_;
};

#endif  // _WORLD_H
