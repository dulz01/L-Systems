#pragma once

class tree_string {
  struct rule {
    char symbols;
    std::string replacement;
  };

  int counter_;
  float rotation_;

  std::vector<rule> rules;
  std::string currentState;
  std::string previousState;

public:
  tree_string() {}

  int get_counter() {
    return counter_;
  }

  float get_rotation() {
    return rotation_;
  }

  void load(std::string infile) {
    std::ifstream file(infile);

    file >> counter_ >> rotation_ >> currentState;
    
    rule r;
    while (file >> r.symbols >> r.replacement) {
      rules.push_back(r);
    }
  }

  // Apply the rules to the axiom
  void applyRules() {
    std::string new_str;
    for (int i = 0; i < currentState.length(); i++) {
      for (std::vector<rule>::iterator it = rules.begin();
        it != rules.end(); ++it) {
        rule r = *it;

        if (currentState.at(i) == r.symbols) {
          new_str += r.replacement;
          break;
        }
      }
    }
    previousState = currentState;
    currentState = new_str;
  }

  std::string& get_TreeStringMap() {
    return currentState;
  }
};
