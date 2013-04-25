#ifndef _DRAWING_H
#define _DRAWING_H

const double kPi = 3.14159265358979;
const double kRadsToDegs = 180.0 / kPi;

class b2Body;

void DrawBody(const b2Body* body);

#endif  // _DRAWING_H
