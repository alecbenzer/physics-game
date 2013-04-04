#ifndef _OBJ_H
#define _OBJ_H

#include <Box2D/Box2D.h>
#include "help.h"

class Object {
  public:
    explicit Object(b2World* world);
    ~Object();

    // The following functions (everything up to Init) are intended to set the
    // **initial** state of the object, not to update its properties after
    // Init() is called. Eg, do not try to cause a dynamic object to become
    // static by calling set_static.

    void set_initial_position(double x, double y) {
      body_def_.position.Set(x, y);
    }

    void set_box_shape(double half_width, double half_height) {
      shape_.SetAsBox(half_width, half_height);
    }

    void set_dynamic() {
      body_def_.type = b2_dynamicBody;
    }

    void set_static() {
      body_def_.type = b2_staticBody;
    }

    void set_kinnematic() {
      body_def_.type = b2_kinematicBody;
    }

    void Init();

    void Render();

    // accessors
    b2BodyType body_type() const {
      return body_def_.type;
    }
  private:
    DISALLOW_COPY_AND_ASSIGN(Object);

    b2World* world_;  // handle to a b2World object
    b2Body* body_;
    b2BodyDef body_def_;
    b2PolygonShape shape_;
    b2FixtureDef fixture_def_;
};

#endif  // _OBJ_H
