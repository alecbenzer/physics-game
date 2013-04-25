#include "basic_object.h"

#include "drawing.h"
#include <cstdio>

BasicObject::~BasicObject() {
  delete shape_;

  b2World* world = body_->GetWorld();
  world->DestroyBody(body_);
}

void BasicObject::Init(b2World* world) {
  body_ = world->CreateBody(&body_def_);

  if (shape_ == NULL) {
    b2PolygonShape* poly = new b2PolygonShape;
    poly->SetAsBox(1.0, 1.0);
    shape_ = poly;
  }

  fixture_def_.shape = shape_;
  fixture_def_.density = 1.5;
  fixture_def_.friction = 0.2f;
  fixture_def_.restitution = 0.3f;

  body_->CreateFixture(&fixture_def_);
  
  body_->SetLinearDamping(1.0);

  body_->SetUserData(this);

  health_ = body_->GetMass();
}

void BasicObject::Render() {
  DrawBody(body_);
}

void BasicObject::HandleContact(b2Contact* contact,
                                const b2ContactImpulse* impulse) {
  float impulse_value = impulse->normalImpulses[0];
  if (impulse->count > 1) {
    impulse_value += impulse->normalImpulses[1];
  }
  impulse_value /= 50.0;

  health_ -= impulse_value;
}
