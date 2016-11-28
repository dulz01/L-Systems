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

  point position_;

  line path_;

  float pi_;
  float distance_;
  bool out_of_view;

  std::vector<point> all_points_;
  std::vector<point> branch_points_;
  std::vector<line> lines_;

private:
  void go_forward() {

    float next_x = position_.x + distance_ * cos(pi_ * position_.dir / 180.0);
    float next_y = position_.y + distance_ * sin(pi_ * position_.dir / 180.0);

    path_.start = position_;
    position_.x = next_x;
    position_.y = next_y;

    path_.end = position_;

    all_points_.push_back(position_);
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

  void reset() {
    position_.x = 0.0f;
    position_.y = -1.0f;
    position_.dir = 90.0f;
  }

  bool is_in_view(point p) {
    return (p.x >= -1 && p.x <= 1 && p.y >= -1 && p.y <= 1);
  }

  bool check_within_bounds() {
    for (std::vector<point>::iterator it = all_points_.begin();
      it != all_points_.end(); ++it) {
      if (!is_in_view(*it)) {
        return false;
      } // end of if statement
      else {
        return true;
      } // end of else statement
    } // end of for loop
  }

public:
  turtle() : pi_(3.141592653f), distance_(0.125f) {
    out_of_view = true;

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

  void generate_tree(std::string& treeStringMap, float rotationAngle) {
      lines_.clear();
      branch_points_.clear();
      for (int i = 0; i < treeStringMap.length(); i++) {
        if (treeStringMap.at(i) == 'F') {
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

      reset();
  }
};