#pragma once

class turtle {
  struct point {
    float x;
    float y;
    float dir;
  };

  struct line {
    point start;
    point end;
  };

  point max_position_;
  point min_position_;
  point position_;

  line path_;

  float pi_;
  float distance_;

  std::vector<point> branch_points_;
  std::vector<line> lines_;

private:
  void go_forward() {
    // uses polar to cartesian coordinates conversion.
    // angle is also converted to radians
    // https://www.mathsisfun.com/polar-cartesian-coordinates.html
    float next_x = position_.x + distance_ * cos(pi_ * position_.dir / 180.0);
    float next_y = position_.y + distance_ * sin(pi_ * position_.dir / 180.0);

    path_.start = position_;
    position_.x = next_x;
    position_.y = next_y;
    path_.end = position_;

    // saves minimum position and maximum position 
    // for rescaling calculations later.
    if (min_position_.x > position_.x) {
      min_position_.x = position_.x;
    }

    if (min_position_.y > position_.y) {
      min_position_.y = position_.y;
    }
    if (max_position_.x < position_.x) {
      max_position_.x = position_.x;
    }

    if (max_position_.y < position_.y) {
      max_position_.y = position_.y;
    }

    lines_.push_back(path_);
  }

  void turn_left(float angle) {
    position_.dir += angle;
  }

  void turn_right(float angle) {
    position_.dir -= angle;
  }

  void new_branch() {
    branch_points_.push_back(position_);
  }

  void return_to_trunk() {
    position_ = branch_points_.back();
    branch_points_.pop_back();
  }

  // converting the range from the tree to the range of the screen.
  // so we can scale the tree to fit into the camera view.
  // formula taken from Greg Neill's post 
  // on: https://groups.google.com/forum/#!topic/alt.math/sj4tTuXpxE0
  void rescale(bool is_width_constrained) {
    float tree_range_x = max_position_.x - min_position_.x;
    float tree_range_y = max_position_.y - min_position_.y;
    float screen_range = 1 - (-1);

    if (is_width_constrained) {
      for (int i = 0; i < lines_.size(); i++) {
        lines_[i].start.x = (max_position_.x * -1 - min_position_.x * 1) / (tree_range_x)+lines_[i].start.x * (screen_range) / (tree_range_x);
        lines_[i].end.x = (max_position_.x * -1 - min_position_.x * 1) / (tree_range_x)+lines_[i].end.x * (screen_range) / (tree_range_x);
        lines_[i].start.y = (max_position_.x * -1 - min_position_.x * 1) / (tree_range_x)+lines_[i].start.y * (screen_range) / (tree_range_x);
        lines_[i].end.y = (max_position_.x * -1 - min_position_.x * 1) / (tree_range_x)+lines_[i].end.y * (screen_range) / (tree_range_x);
      }// end of for loop
    }// end of if statement
    else {
      for (int i = 0; i < lines_.size(); i++) {
        lines_[i].start.x = 1 + ((max_position_.y * -1 - min_position_.y * 1) / (tree_range_y)+lines_[i].start.x * (screen_range) / (tree_range_y));
        lines_[i].end.x = 1 + ((max_position_.y * -1 - min_position_.y * 1) / (tree_range_y)+lines_[i].end.x * (screen_range) / (tree_range_y));
        lines_[i].start.y = (max_position_.y * -1 - min_position_.y * 1) / (tree_range_y)+lines_[i].start.y * (screen_range) / (tree_range_y);
        lines_[i].end.y = (max_position_.y * -1 - min_position_.y * 1) / (tree_range_y)+lines_[i].end.y * (screen_range) / (tree_range_y);
      }// end of for loop
    }// end of if statement
  }

  void reset() {
    position_.x = max_position_.x = min_position_.x = 0.0f;
    position_.y = max_position_.y = min_position_.y = -1.0f;
    position_.dir = max_position_.dir = min_position_.dir = 90.0f;
  }

public:
  turtle() : pi_(3.141592653f), distance_(1.0f) {
    reset();
  }

  void draw_lines() {
    // using the points data from generate_tree(), draw the lines between them.
    for (std::vector<line>::iterator it = lines_.begin();
    it != lines_.end(); ++it) {
      line l = *it;
      glBegin(GL_LINES);
      glVertex2d(l.start.x, l.start.y);
      glVertex2d(l.end.x, l.end.y);
      glEnd();
    }
  }

  void generate_tree(std::string& treeStringMap, float rotationAngle, float x, float y, float angle, bool widthConstrained) {
    lines_.clear();
    branch_points_.clear();
    for (int i = 0; i < treeStringMap.length(); i++) {
      if (treeStringMap.at(i) == 'F' || treeStringMap.at(i) == 'A' || treeStringMap.at(i) == 'B') {
        go_forward();
      }
      else if (treeStringMap.at(i) == '+') {
        turn_left(rotationAngle);
      }
      else if (treeStringMap.at(i) == '-') {
        turn_right(rotationAngle);
      }
      else if (treeStringMap.at(i) == '[') {
        new_branch();
      }
      else if (treeStringMap.at(i) == ']') {
        return_to_trunk();
      }
    } // end of for loop
    rescale(widthConstrained);
    set_origin(x, y, angle);
  }

  void set_origin(float x, float y, float angle) {
    position_.x = max_position_.x = min_position_.x = x;
    position_.y = max_position_.y = min_position_.y = y;
    position_.dir = max_position_.dir = min_position_.dir = angle;
  }
};