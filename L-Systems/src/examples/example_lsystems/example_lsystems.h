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
    int l_system_number_;
    tree_string ts[6];
    turtle t;

  public:
    /// this is called when we construct the class before everything is initialised.
    example_lsystems(int argc, char **argv) : app(argc, argv) {
      l_system_number_ = 0;
    }
    
    void build_tree() {
      for (int i = 0; i < ts[l_system_number_].get_counter(); i++) {
        ts[l_system_number_].applyRules();
      }

      t.generate_tree(ts[0].get_TreeStringMap(), ts[l_system_number_].get_rotation());
    }

    void select_tree() {
      if (is_key_going_down(key_num_1)) {
        l_system_number_ = 0;
        build_tree();
      }

      if (is_key_going_down(key_num_2)) {
        l_system_number_ = 1;
        build_tree();
      }

      if (is_key_going_down(key_num_3)) {
        l_system_number_ = 2;
        build_tree();
      }

      if (is_key_going_down(key_num_4)) {
        l_system_number_ = 3;
        build_tree();
      }

      if (is_key_going_down(key_num_5)) {
        l_system_number_ = 4;
        build_tree();
      }

      if (is_key_going_down(key_num_6)) {
        l_system_number_ = 5;
        build_tree();
      }
    }

    /// this is called once OpenGL is initialized
    void app_init() {
      app_scene = new visual_scene();
      app_scene->create_default_camera_and_lights();

      ts[0].load("Tree1.txt");
      ts[1].load("Tree2.txt");
      ts[2].load("Tree3.txt");
      ts[3].load("Tree4.txt");
      ts[4].load("Tree5.txt");
      ts[5].load("Tree6.txt");

      build_tree();
    }

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) {
      int vx = 0, vy = 0;
      get_viewport_size(vx, vy);
      app_scene->begin_render(vx, vy);

      select_tree();
      t.draw_lines();
    }
  };
}
