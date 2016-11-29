#pragma once

class tree_string {
  struct rule {
    char symbols;
    std::string replacement;
  };

  int counter_;
  float rotation_;

  std::vector<rule> rules_;
  std::vector<std::string> previous_states_;

  std::string current_state_;

public:
  tree_string() {}

  int get_counter() {
    return counter_;
  }

  float get_rotation() {
    return rotation_;
  }

  void load(std::string infile) {
    rules_.clear();
    std::ifstream file(infile);

    file >> counter_ >> rotation_ >> current_state_;
    rule r;

    while (file >> r.symbols >> r.replacement) {
      rules_.push_back(r);
    }
  }

  void decrement_iteration() {
    current_state_ = previous_states_.back();
    previous_states_.pop_back();
  }

  void apply_rules() {
    std::string new_str;
    previous_states_.push_back(current_state_);
    for (int i = 0; i < current_state_.length(); i++) {
      for (std::vector<rule>::iterator it = rules_.begin();
        it != rules_.end(); ++it) {
        rule r = *it;

        if (current_state_.at(i) == r.symbols) {
          new_str += r.replacement;
          break;
        }
      }
    }
    current_state_ = new_str;
    //std::cout << current_state_ << std::endl;
  }

  std::string& get_TreeStringMap() {
    return current_state_;
  }
};
