#ifndef RENDERER
#define RENDERER

#include <glad.h>
#include <vector>
using namespace std;

enum RenderGroups {
  Scene = 1,
  Menu = 2,
};

struct VisualObject {
  vector<float> triangles;
  int n_triangles;
};

class Renderer {
public:
  // Avoid leaks
  virtual ~Renderer() = default;

  int add(VisualObject object);
  void replace(int index, vector<float> triangles, int n_triangles,
               int n_previous_triangles);
  void remove(int index, int n_triangles);
  virtual void draw() = 0;

protected:
  virtual vector<float> get_flattened() = 0;
  virtual void update() = 0;

  unsigned int VAO;
  bool change; // Tracks changes in the visual objects
  int n_visual_objects;
  int n_triangles;
  vector<VisualObject> visual_objects;
};

#endif