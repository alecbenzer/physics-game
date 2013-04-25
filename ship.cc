#include "ship.h"

#include <Box2D/Box2D.h>
#include <cmath>
#include "drawing.h"

Ship::Ship() : health_(0.0) {}

Ship::~Ship() {
  b2World* world = base_body_->GetWorld();
  world->DestroyBody(base_body_);
}

void Ship::Init(b2World* world) {
  // body_def.position.Set(0.0, 0.0);
  body_def_.type = b2_dynamicBody;

  base_body_ = world->CreateBody(&body_def_);

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

  base_body_->SetUserData(this);

  health_ = base_body_->GetMass();
}

void Ship::Render() {
  DrawBody(base_body_);
  // DrawBody(gun_body_);
}

void Ship::Step(b2World* world) {
  double angle_offset = 0 - base_body_->GetAngle();
  base_body_->ApplyTorque(15 * angle_offset * angle_offset * angle_offset);
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

void Ship::HandleContact(b2Contact* contact, const b2ContactImpulse* impulse) {
  float impulse_value = impulse->normalImpulses[0];
  if (impulse->count > 1) {
    impulse_value += impulse->normalImpulses[1];
  }
  impulse_value /= 10.0;

  health_ -= impulse_value;
  printf("ship health: %lf\n", health_);
}

void Ship::ProcessInput(World* world) {
  if (world->button_down(SDL_BUTTON_LEFT)) {
    world->PerformRaycast(this->position(), world->mouse_position());

    if (world->raycast_body() != NULL) {
      b2Vec2 hit = world->raycast_point();
      b2Vec2 pos = this->position();

      float distance = (hit - pos).Length();

      b2Vec2 dir = hit - pos;
      dir.Normalize();

      if (distance > 2.0) {
        world->raycast_body()->ApplyForceToCenter(-90.0 * dir);
      }
    }
  }

  if (world->key_down(SDLK_q)) {
    this->Stabilize();
  } else {
    this->NoStabilize();
    if (world->key_down(SDLK_UP) || world->key_down(SDLK_w)) {
      this->ForceUp();
    }
    if (world->key_down(SDLK_DOWN) || world->key_down(SDLK_s)) {
      this->ForceDown();
    }
    if (world->key_down(SDLK_LEFT) || world->key_down(SDLK_a)) {
      this->ForceLeft();
    }
    if (world->key_down(SDLK_RIGHT) || world->key_down(SDLK_d)) {
      this->ForceRight();
    }
  }
}
