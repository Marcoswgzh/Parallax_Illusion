#ifndef TRIANGLE_RENDERER
#define TRIANGLE_RENDERER

#include <glad.h>
#include <vector>
using namespace std;

struct VisualObject {
  vector<float> triangles;
  int n_triangles;
  bool plane;
};

class TriangleRenderer {
public:
  static TriangleRenderer *get_instance();

  // TriangleRenderer should not be cloneable
  TriangleRenderer(TriangleRenderer &other) = delete;

  // TriangleRenderer should not be assignable
  void operator=(const TriangleRenderer &) = delete;

  void update();
  int add(VisualObject object);
  void replace(int index, vector<float> triangles, int n_triangles,
               int n_previous_triangles);
  void remove(int index, int n_triangles);
  void draw();

private:
  TriangleRenderer();
  static TriangleRenderer *instance;

  bool change = true; // Tracks changes in the visual objects
  int n_visual_objects = 0;
  int n_triangles;
  vector<VisualObject> visual_objects;
  unsigned int VAO;

  vector<float> get_flattened();
};

#endif