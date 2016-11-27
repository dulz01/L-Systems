#pragma once

class tree_string {
  struct rule {
    char variable;
    std::string replacement;
  };

  std::vector<rule> rules;
  std::string treeStringMap;

public:
  tree_string() {
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

    treeStringMap = "X";
    rules = {
      { 'X', "F-[[X]+X]+F[+FX]-X" },
      { 'F', "FF" },
      { '[', "[" },
      { ']', "]" },
      { '+', "+" },
      { '-', "-" }
    };
  }

  // create the tree string
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

};
