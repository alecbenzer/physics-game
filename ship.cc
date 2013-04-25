#include "ship.h"

#include <Box2D/Box2D.h>
#include <cmath>
#include <iostream>
#include "drawing.h"

using std::cerr;

void Ship::Init(b2World* world) {
  // base
  b2BodyDef body_def;
  body_def.position.Set(0.0, 0.0);
  body_def.type = b2_dynamicBody;

  base_body_ = world->CreateBody(&body_def);

  b2PolygonShape base_shape;
  base_shape.SetAsBox(0.5, 0.5);

  b2FixtureDef base_fixture_def;
  base_fixture_def.shape = &base_shape;
  base_fixture_def.density = 1.0;
  base_fixture_def.friction = 0.5;
  base_fixture_def.restitution = 0.3;

  base_body_->CreateFixture(&base_fixture_def);

  base_body_->SetGravityScale(0.0f);
  base_body_->SetAngularDamping(2.0);
  base_body_->SetLinearDamping(0.5);

  // gun
  /* body_def.position.Set(0.0, 0.9);

  gun_body_ = world->CreateBody(&body_def);

  b2PolygonShape gun_shape;
  gun_shape.SetAsBox(0.1, 1.0);

  b2FixtureDef gun_fixture_def;
  gun_fixture_def.shape = &gun_shape;
  gun_fixture_def.density = 1.0;
  gun_fixture_def.friction = 0.5;

  gun_body_->CreateFixture(&gun_fixture_def);

  gun_body_->SetGravityScale(0.0f);
  gun_body_->SetAngularDamping(1.0);

  // connect gun to body
  b2RevoluteJointDef joint_def;
  joint_def.Initialize(base_body_, gun_body_, base_body_->GetWorldCenter() + b2Vec2(0.0, 0.3));

  b2RevoluteJoint* joint =
    static_cast<b2RevoluteJoint*>(world->CreateJoint(&joint_def)); */
}

void Ship::Render() {
  DrawBody(base_body_);
  // DrawBody(gun_body_);
}

void Ship::Step(b2World* world) {
  /* for (b2ContactEdge* ce = base_body_->GetContactList(); ce; ce = ce->next) {
    b2Contact* c = ce->contact;
    b2Vec2 norm = c->GetManifold()->localNormal;
    cerr << "local norm: (" << norm.x << "," << norm.y << ")\n";
  } */

  double angle_offset = 0 - base_body_->GetAngle();
  base_body_->ApplyTorque(6 * angle_offset * angle_offset * angle_offset);
}

void Ship::ForceUp() {
  base_body_->ApplyForceToCenter(b2Vec2(0.0, -10.0));
}

void Ship::ForceDown() {
  base_body_->ApplyForceToCenter(b2Vec2(0.0, 10.0));
}

void Ship::ForceLeft() {
  base_body_->ApplyForceToCenter(b2Vec2(-10.0, 0.0));
}

void Ship::ForceRight() {
  base_body_->ApplyForceToCenter(b2Vec2(10.0, 0.0));
}

void Ship::Stabilize() {
  base_body_->SetLinearDamping(5.0);
}

void Ship::NoStabilize() {
  base_body_->SetLinearDamping(0.5);
}
