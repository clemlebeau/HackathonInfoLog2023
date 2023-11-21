#ifndef LERP_H
#define LERP_H

double lerp(double a, double b, double t) {
  return t * (b - a) + a;
}

#endif //LERP_H