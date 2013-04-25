#include "basic_object.h"

#include "drawing.h"

void BasicObject::Init(b2World* world) {
  body_ = world->CreateBody(&body_def_);

  if (shape_ == NULL) {
    b2PolygonShape* poly = new b2PolygonShape;
    poly->SetAsBox(1.0, 1.0);
    shape_ = poly;
  }

  fixture_def_.shape = shape_;
  fixture_def_.density = 1.0;
  fixture_def_.friction = 0.2f;
  fixture_def_.restitution = 0.3f;

  body_->CreateFixture(&fixture_def_);
  
  body_->SetLinearDamping(1.0);
}

void BasicObject::Render() {
  DrawBody(body_);
}
