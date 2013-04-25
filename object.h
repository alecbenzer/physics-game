#ifndef _OBJECT_H
#define _OBJECT_H

#include <Box2D/Box2D.h>
#include "help.h"

class Object {
 public:
  Object() {}
  virtual ~Object() {}

  virtual void Init(b2World* world) = 0;
  virtual void Render() = 0;

  virtual void Step(b2World* world) {}

  virtual void HandleContact(b2Contact* contact, const b2ContactImpulse* impulse) {}

 private:
  DISALLOW_COPY_AND_ASSIGN(Object);
};

#endif  // _OBJECT_H
