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
    tree_string ts;
    turtle t;

    float rotation_angle_;
    bool is_width_constrained_;

  public:
    /// this is called when we construct the class before everything is initialised.
    example_lsystems(int argc, char **argv) : app(argc, argv) {}
    
    void build_tree() {
      t.set_origin(ts.get_start_pos_x(), ts.get_start_pos_y(), ts.get_start_pos_angle());

      for (int i = 0; i < ts.get_counter(); i++) {
        ts.apply_rules();
      }

      t.generate_tree(ts.get_TreeStringMap(), ts.get_rotation(), ts.get_start_pos_x(), ts.get_start_pos_y(), ts.get_start_pos_angle(), is_width_constrained_);
    }

    void modify_tree() {
      if (is_key_going_down(key_q)) {
        ts.decrement_iteration();
        t.generate_tree(ts.get_TreeStringMap(), ts.get_rotation(), ts.get_start_pos_x(), ts.get_start_pos_y(), ts.get_start_pos_angle(), is_width_constrained_);
      }

      if (is_key_going_down(key_w)) {
        ts.apply_rules();
        t.generate_tree(ts.get_TreeStringMap(), ts.get_rotation(), ts.get_start_pos_x(), ts.get_start_pos_y(), ts.get_start_pos_angle(), is_width_constrained_);
      }

      if (is_key_down(key_a)) {
        rotation_angle_ += 0.25f;
        ts.set_rotation(rotation_angle_);
        t.generate_tree(ts.get_TreeStringMap(), ts.get_rotation(), ts.get_start_pos_x(), ts.get_start_pos_y(), ts.get_start_pos_angle(), is_width_constrained_);
      }

      if (is_key_down(key_s)) {
        rotation_angle_ -= 0.25f;
        ts.set_rotation(rotation_angle_);
        t.generate_tree(ts.get_TreeStringMap(), ts.get_rotation(), ts.get_start_pos_x(), ts.get_start_pos_y(), ts.get_start_pos_angle(), is_width_constrained_);
      }
    }

    void select_tree() {
      if (is_key_going_down(key_num_1)) {
        ts.load("Tree1.txt");
        rotation_angle_ = ts.get_rotation();
        is_width_constrained_ = false;
        build_tree();
      }

      if (is_key_going_down(key_num_2)) {
        ts.load("Tree2.txt");
        rotation_angle_ = ts.get_rotation();
        is_width_constrained_ = false;
        build_tree();
      }

      if (is_key_going_down(key_num_3)) {
        ts.load("Tree3.txt");
        rotation_angle_ = ts.get_rotation();
        is_width_constrained_ = false;
        build_tree();
      }

      if (is_key_going_down(key_num_4)) {
        ts.load("Tree4.txt");
        rotation_angle_ = ts.get_rotation();
        is_width_constrained_ = false;
        build_tree();
      }

      if (is_key_going_down(key_num_5)) {
        ts.load("Tree5.txt");
        rotation_angle_ = ts.get_rotation();
        is_width_constrained_ = false;
        build_tree();
      }

      if (is_key_going_down(key_num_6)) {
        ts.load("Tree6.txt");
        rotation_angle_ = ts.get_rotation();
        is_width_constrained_ = false;
        build_tree();
      }

      if (is_key_going_down(key_num_7)) {
        ts.load("DragonCurve.txt");
        rotation_angle_ = ts.get_rotation();
        is_width_constrained_ = true;
        build_tree();
      }

      if (is_key_going_down(key_num_8)) {
        ts.load("SierpinskiTriangle-Arrowhead.txt");
        rotation_angle_ = ts.get_rotation();
        is_width_constrained_ = true;
        build_tree();
      }

      if (is_key_going_down(key_num_9)) {
        ts.load("KochCurve.txt");
        rotation_angle_ = ts.get_rotation();
        is_width_constrained_ = true;
        build_tree();
      }
    }

    /// this is called once OpenGL is initialized
    void app_init() {
      app_scene = new visual_scene();
      app_scene->create_default_camera_and_lights();

      ts.load("Tree1.txt");

      rotation_angle_ = ts.get_rotation();
      is_width_constrained_ = false;

      build_tree();
    }

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) {
      int vx = 0, vy = 0;
      get_viewport_size(vx, vy);
      app_scene->begin_render(vx, vy);

      modify_tree();
      select_tree();

      t.draw_lines();
    }
  };
}
