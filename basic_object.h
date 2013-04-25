#ifndef _BASIC_OBJECT_H
#define _BASIC_OBJECT_H

#include "object.h"

class BasicObject : public Object {
 public:
  explicit BasicObject()
    : Object(),
      body_(NULL),
      shape_(NULL) {
    body_def_.type = b2_dynamicBody;
  }

  ~BasicObject() {
    delete shape_;

    b2World* world = body_->GetWorld();
    world->DestroyBody(body_);
  }

  void set_initial_position(double x, double y) {
    body_def_.position.x = x;
    body_def_.position.y = y;
  }

  void set_box_shape(double hwidth, double hheight) {
    b2PolygonShape* poly = new b2PolygonShape;
    poly->SetAsBox(hwidth, hheight);

    if (shape_) delete shape_;
    shape_ = poly;
  }

  void set_dyanmic() {
    body_def_.type = b2_dynamicBody;
  }

  void set_static() {
    body_def_.type = b2_staticBody;
  }

  const b2Body* body() const {
    return body_;
  }

  virtual void Init(b2World* world);
  virtual void Render();

 private:
  DISALLOW_COPY_AND_ASSIGN(BasicObject);

  b2Body* body_;
  b2BodyDef body_def_;
  b2FixtureDef fixture_def_;
  b2Shape* shape_;
};

#endif  // _BASIC_OBJECT_H
