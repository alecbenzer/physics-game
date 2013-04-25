#include "drawing.h"

#include <GL/gl.h>
#include <Box2D/Box2D.h>

void DrawBody(const b2Body* body) {
  const b2Vec2& pos = body->GetPosition();
  const b2Fixture* fixture = body->GetFixtureList();

  for (; fixture; fixture = fixture->GetNext()) {
    glLoadIdentity();

    glTranslatef(pos.x, pos.y, 0);
    glRotatef(body->GetAngle() * kRadsToDegs, 0, 0, 1);

    glBegin(GL_LINE_LOOP);
    const b2PolygonShape* shape =
      dynamic_cast<const b2PolygonShape*>(fixture->GetShape());
    for (int i = 0;i < shape->GetVertexCount(); ++i) {
      const b2Vec2& v = shape->GetVertex(i);
      glVertex2f(v.x, v.y);
    }
    glEnd();
  }
}
