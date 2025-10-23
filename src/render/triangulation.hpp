#ifndef TRIANGULATION
#define TRIANGULATION

// TODO: Implement this class
/*
 * This object should get as input a sequence of vertices (with their colors,
 * which should be skipped here) and return a sequence of triangles.
 */
class Triangulation {
public:
  Triangulation();

  // For now returns a float pointer to an imaginary array
  // TODO: Method signature might need to be changed for actual implementation
  float *create_triangles(float[][18]);

private:
};

#endif