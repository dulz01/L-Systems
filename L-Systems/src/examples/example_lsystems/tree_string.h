#pragma once

class tree_string {
  struct rule {
    char symbols;
    std::string replacement;
  };

  std::vector<rule> rules;
  std::string treeStringMap;

public:
  tree_string() {
    treeStringMap = "F";
    rules = {
      //{ 'X', "F-[[X]+X]+F[+FX]-X" },
      { 'F', "FF-[-F+F+F]+[+F-F-F]" },
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
        if (treeStringMap.at(i) == rules.at(j).symbols) {
          new_str += rules.at(j).replacement;
          break;
        }
      }
    }
    treeStringMap = new_str;
  }

  std::string& get_TreeStringMap() {
    return treeStringMap;
  }
};
