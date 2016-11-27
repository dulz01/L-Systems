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
    std::string treeStringMap;
    struct rule {
      char variable;
      std::string replacement;
    };
    std::vector<rule> rules;
    int counter;
    float rotation;

    turtle t;

  public:
    /// this is called when we construct the class before everything is initialised.
    example_lsystems(int argc, char **argv) : app(argc, argv) {
      treeStringMap = "F";

      //-----------------------------------------------------------------------
      // Sample tree rules
      //-----------------------------------------------------------------------
      //n=5, angle=25.7
      //axiom = F
      //F->F[+F]F[-F]F
      
      //n=5, angle=20
      //axiom = F
      //F[+F]F[-F][F]
      
      //n=4, angle=22.5
      //axiom = F
      //FF-[-F+F+F]+[+F-F-F]
      
      //n=7, angle=20
      //axiom = X
      //X->F[+X]F[-X]+X
      //F->FF

      //n=7, angle=25.7
      //axiom = X
      //X->F[+X][-X]FX
      //F->FF

      //n=5, angle=22.5
      //axiom = X
      //X->F-[[X]+X]+F[+FX]-X
      //F->FF
      rules = {
        { 'F', "FF-[-F+F+F]+[+F-F-F]" },
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
    }

    /// this is called once OpenGL is initialized
    void app_init() {
      app_scene = new visual_scene();
      app_scene->create_default_camera_and_lights();

      //material *red = new material(vec4(1, 0, 0, 1));
      //mesh_box *box = new mesh_box(vec3(4));
      //scene_node *node = new scene_node();
      //app_scene->add_child(node);
      //app_scene->add_mesh_instance(new mesh_instance(node, box, red));
    }

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) {
      int vx = 0, vy = 0;
      get_viewport_size(vx, vy);
      app_scene->begin_render(vx, vy);

      if (counter < 10) {
        std::cout << "Iteration " << counter++ << " : " << treeStringMap << std::endl;
        applyRules();
      }

      t.generate_tree(treeStringMap);
      t.draw_lines();
      //t.go_forward(0.125f);
      //t.turn_right(27.5f);
      //t.go_forward(0.125f);
      //t.turn_left(90.5f);
      //t.go_forward(0.125f);
    }
  };
}
