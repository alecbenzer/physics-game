#ifndef _SHIP_H
#define _SHIP_H

#include "object.h"

class Ship : public Object {
 public:
  Ship() {}
  ~Ship() {
    b2World* world = base_body_->GetWorld();
    world->DestroyBody(base_body_);
  }
  
  virtual void Init(b2World* world);
  virtual void Render();

  virtual void Step(b2World* world);

  void ForceUp();
  void ForceDown();
  void ForceLeft();
  void ForceRight();
  void Stabilize();
  void NoStabilize();

  b2Vec2 position() {
    return base_body_->GetPosition();
  }

 private:
  b2Body* base_body_;
  b2Body* gun_body_;
};

#endif  // _SHIP_H
