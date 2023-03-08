#ifndef __NO_H__
#define __NO_H__

#include <vector>
#include <string>

struct No{
  std::string id;
  std::string path;
  std::string tipo;
  No* dir_ant;
  std::vector<No*> filhos;
};


#endif