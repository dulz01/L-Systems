#pragma once

class tree_string {
  struct rule {
    char symbols;
    std::string replacement;
  };

  std::vector<rule> rules;
  std::string currentState;
  std::string previousState;

public:
  tree_string() {
    currentState = "F";
    rules = {
      //{ 'X', "F-[[X]+X]+F[+FX]-X" },
      { 'F', "FF-[-F+F+F]+[+F-F-F]" },
      { '[', "[" },
      { ']', "]" },
      { '+', "+" },
      { '-', "-" }
    };
  }

  void Load(std::string file) {

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
