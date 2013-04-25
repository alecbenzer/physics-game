#ifndef _SHIP_H
#define _SHIP_H

#include "object.h"
#include "world.h"

class Ship : public Object {
 public:
  Ship();
  ~Ship();
  
  virtual void Init(b2World* world);
  virtual void Render();

  virtual void Step(b2World* world);

  void ForceUp();
  void ForceDown();
  void ForceLeft();
  void ForceRight();
  void Stabilize();
  void NoStabilize();

  void ProcessInput(World* world);

  virtual void HandleContact(b2Contact* contact, const b2ContactImpulse* impulse);

  b2Vec2 position() {
    return base_body_->GetPosition();
  }

  void set_initial_position(double x, double y) {
    body_def_.position.x = x;
    body_def_.position.y = y;
  }

  double health() { return health_; }

 private:
  b2BodyDef body_def_;
  b2Body* base_body_;

  double health_;
};

#endif  // _SHIP_H
