////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
namespace octet {

  class turtle {
    float x_, y_;
    float dir_;

    std::vector<float> points_;
    std::vector<float> lines_;

  public:
    turtle() : x_(0), y_(-1), dir_(0) {}

    // specific instructions of the turtle's movements
    void forward(float distance) {
     //if i go forward, I have to take angle into account. 
    }
    void left(float angle) { }
    void right(float angle) { }

    void draw_lines() {
      // using the points data from generate_tree(), draw the lines between them.
    }

    void generate_tree() {
      // make the turtle go through the string instructions for the tree.
      // save the positions of the points
      // turtle generates a tree for each iteration.
    }

  };


  /// Scene containing a box with octet.
  class example_lsystems : public app {
    // scene for drawing box
    ref<visual_scene> app_scene;

    // L-systems variables
    std::string treeStringMap;
    struct rule {
      char variable;
      std::string replacement;
    };
    std::vector<rule> rules;
    int counter;
    float rotation;

  public:
    /// this is called when we construct the class before everything is initialised.
    example_lsystems(int argc, char **argv) : app(argc, argv) {
      treeStringMap = "F";
      rules = {
        { 'F', "F[+F]F[-F]F" },
        { '[', "[" },
        { ']', "]" },
        { '+', "+" },
        { '-', "-" }
      };
      counter = 0;

      rotation = 25.7f;
    }

    // create the tree string map
    void applyRules() {
      std::string new_str;
      for (int i = 0; i < treeStringMap.length(); i++) {
        for (int j = 0; j < rules.size(); j++) {
          if (treeStringMap.at(i) == rules.at(j).variable) {
            new_str += rules.at(j).replacement;
            break;
          }
        }
      }
      treeStringMap = new_str;
      printf("ApplyRules\n");
    }

    /// this is called once OpenGL is initialized
    void app_init() {
      app_scene = new visual_scene();
      app_scene->create_default_camera_and_lights();

      material *red = new material(vec4(1, 0, 0, 1));
      mesh_box *box = new mesh_box(vec3(4));
      scene_node *node = new scene_node();
      app_scene->add_child(node);
      app_scene->add_mesh_instance(new mesh_instance(node, box, red));
    }

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) {
      int vx = 0, vy = 0;
      get_viewport_size(vx, vy);
      app_scene->begin_render(vx, vy);

      if (counter < 7) {
        std::cout << "Iteration " << counter++ << " : " << treeStringMap << std::endl;
        applyRules();
      }

      glBegin(GL_LINES);
      glVertex2d(0.0f, 0.0f);
      glVertex2d(1.0f, 1.0f);
      glEnd();

      //  // update matrices. assume 30 fps.
      //  app_scene->update(1.0f / 30);

      //  // draw the scene
      //  app_scene->render((float)vx / vy);

      //  // tumble the box  (there is only one mesh instance)
      //  scene_node *node = app_scene->get_mesh_instance(0)->get_node();
      //  node->rotate(1, vec3(1, 0, 0));
      //  node->rotate(1, vec3(0, 1, 0));
    }
  };
}
