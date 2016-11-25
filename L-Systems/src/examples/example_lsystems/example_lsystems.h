////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
namespace octet {
  /// Scene containing a box with octet.
  class example_lsystems : public app {
    // scene for drawing box
    ref<visual_scene> app_scene;

    // L-systems variables
    std::string axiom;

    struct rule {
      char variable;
      std::string replacement;
    };

    std::vector<rule> rules;

    int counter;

  public:
    /// this is called when we construct the class before everything is initialised.
    example_lsystems(int argc, char **argv) : app(argc, argv) {
      axiom = "F";
      rules = {
        {'F', "F[+F]F[-F]F"}
      };
      counter = 0;

    }

    void applyRules() {
      std::string new_str;
      new_str = axiom;
      for (int i = 0; i < (int)axiom.length(); i++) {
        for (int j = 0; i < (int)rules.size(); j++) {
          if (axiom.at(i) == rules.at(j).variable) {
            new_str.erase(i);
            new_str.append(rules.at(j).replacement);
            axiom = new_str;
            break;
          }
        }
      }

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

      if (counter < 5) {
        std::cout << "Iteration " << counter++ << " : "<< axiom << std::endl;
        applyRules();
      }

      // update matrices. assume 30 fps.
      app_scene->update(1.0f / 30);

      // draw the scene
      app_scene->render((float)vx / vy);

      // tumble the box  (there is only one mesh instance)
      scene_node *node = app_scene->get_mesh_instance(0)->get_node();
      node->rotate(1, vec3(1, 0, 0));
      node->rotate(1, vec3(0, 1, 0));
    }
  };
}
