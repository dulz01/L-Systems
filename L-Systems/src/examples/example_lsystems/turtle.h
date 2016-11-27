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

  std::vector<point> branch_points_;
  std::vector<line> lines_;

private:
  void go_forward(float distance) {
    float next_x = position_.x + distance * cos(pi_ * position_.dir / 180.0);
    float next_y = position_.y + distance * sin(pi_ * position_.dir / 180.0);

    path_.start = position_;
    position_.x = next_x;
    position_.y = next_y;

    path_.end = position_;

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

public:
  turtle() : pi_(3.141592653f) {
    position_.x = 0.0f;
    position_.y = -1.0f;
    position_.dir = 90.0f;
  }

  void draw_lines() {
    // using the points data from generate_tree(), draw the lines between them.
    for (int i = 0; i < lines_.size(); i++) {
      glBegin(GL_LINES);
      glVertex2d(lines_.at(i).start.x, lines_.at(i).start.y);
      glVertex2d(lines_.at(i).end.x, lines_.at(i).end.y);
      glEnd();
    }
  }

  void generate_tree(std::string& treeStringMap, float rotationAngle) {
    for (int i = 0; i < treeStringMap.length(); i++) {
      if (treeStringMap.at(i) == 'F') {
        go_forward(0.025f);
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
  }
};