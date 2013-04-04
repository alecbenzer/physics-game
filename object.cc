#include "object.h"

#include <GL/gl.h>

const double kPi = 3.14159265358979;
const double kRadsToDegs = 180.0 / kPi;

Object::Object(b2World* world) : world_(world), body_(NULL) {
  body_def_.type = b2_dynamicBody;
}

Object::~Object() {
  if (body_ != NULL) {
    world_->DestroyBody(body_);
  }
}

void Object::Init() {
  body_ = world_->CreateBody(&body_def_);

  fixture_def_.shape = &shape_;
  fixture_def_.density = 1.0;
  fixture_def_.friction = 0.2f;

  body_->CreateFixture(&fixture_def_);
}

void Object::Render() {
  glLoadIdentity();

  const b2Vec2& pos = body_->GetPosition();
  glTranslatef(pos.x, pos.y, 0);
  glRotatef(body_->GetAngle() * kRadsToDegs, 0, 0, 1);

  glBegin(GL_LINE_LOOP);
  for (int i = 0;i < shape_.GetVertexCount(); ++i) {
    const b2Vec2& v = shape_.GetVertex(i);
    glVertex2f(v.x, v.y);
  }
  glEnd();
}
