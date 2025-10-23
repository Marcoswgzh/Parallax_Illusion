#ifndef TRIANGLE_RENDERER
#define TRIANGLE_RENDERER

#include <glad.h>
#include <vector>
using namespace std;

struct VisualObject {
  vector<float> triangles;
  int n_triangles;
};

class TriangleRenderer {
public:
  TriangleRenderer();
  void update();
  int add(vector<float> triangles, int n_traingles);
  void replace(int index, vector<float> triangles, int n_triangles,
               int n_previous_triangles);
  void remove(int index, int n_triangles);
  void draw();
  void show();

private:
  bool change = true; // Tracks changes in the triangles
  int n_visual_objects = 0;
  int n_triangles;
  vector<VisualObject> triangles; // TODO: Change name to visual objects
  unsigned int VAO;

  vector<float> get_flattened();
};

#endif