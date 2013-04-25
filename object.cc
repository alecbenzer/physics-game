#include "object.h"

#include <GL/gl.h>

// no-op?

/* void Object::Init(b2BodyDef body_def) {
  body_def_ = body_def;
  body_ = world_->CreateBody(&body_def);

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
} */
