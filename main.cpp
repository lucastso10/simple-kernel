#include <iostream>
#include <experimental/filesystem>
#include <string.h>
#include <vector>
#include <fstream> 
#include "No.h"
using namespace std;

// g++ -std=c++17 main.cpp -lstdc++fs <--- compila com isso

namespace fs = experimental::filesystem;

std::string rootPath = fs::current_path();

No* iniciarArvore()
{
  No* root = new No;
  root -> id = "/";
  root -> path = rootPath;
  root -> dir_ant = nullptr;
  root -> tipo = "d";
  return root;
}

vector<string> split(string str, char deli){
  string temp = "";
  vector<string> args;
  for(int i = 0; i < str.length(); i++){
    if (str[i] == deli){
      args.push_back(temp);
      temp = "";
    } else{
      temp += str[i];
    }
  }
  args.push_back(temp);
  return args;
}


int command_interpreter(string command){
  switch (command[0]){
    case 'e':
      return 0;
    case 'm':
      return 1;
    case 'c':
      return 2;
    case 'd':
      return 3;
    case 'l':
      return 4;
    case 'h':
      return 5;
  }
  return -1;
}

void create_directory_arq(No* current, string command){
  vector<string> args = split(command, ' ');

  if (args.size() > 3){
    cout << "Error! Muitos argumentos!\n";
    return;
  } else if (args.size() <= 2){
    cout << "Error! Insira o tipo depois o nome do novo diretório!\n";
    return;
  }

  if ( args[1] == "a"){
    fstream file;
    file.open(current -> path + '/' + args[2], ios::out);
    file.close();
  } else if (args[1] == "d"){
    fs::create_directory(current -> path + '/' + args[2]);
  } else {
    cout << "Error! Tipo inválido!\n";
    return;
  }

  No* temp = new No;
  temp -> id = args[2];
  temp -> path = current -> path + '/' + args[2];
  temp -> dir_ant = current;
  temp -> tipo = args[1];

  current -> filhos.push_back(temp);
}

No* change_directory(No* current, string command){
  vector<string> args = split(command, ' ');

  if (args.size() > 2){
    cout << "Error! Muitos argumentos!\n";
    return nullptr;
  } else if (args.size() <= 1){
    cout << "Error! Insira o nome do diretório!\n";
    return nullptr;
  }

  if (args[1] == "..")
    return current -> dir_ant;

  for (int i = 0; i < current -> filhos.size() ; i++){
    if (args[1] == current -> filhos[i] -> id && current -> filhos[i] -> tipo == "d"){
      return current -> filhos[i];
    }
  }
  cout << "Erro! Diretório não encontrado!\n";
  return nullptr;
}

void remove_arq(No* current, string command){
  vector<string> args = split(command, ' ');

  if (args.size() > 2){
    cout << "Error! Muitos argumentos!\n";
    return;
  } else if (args.size() <= 1){
    cout << "Error! Insira o nome do diretório!\n";
    return;
  }

  for (int i = 0; i < current -> filhos.size() ; i++){
    if (args[1] == current -> filhos[i] -> id && current -> filhos[i] -> tipo == "a"){
      fs::remove(current -> filhos[i] -> path);
      current -> filhos.erase(current -> filhos.begin()+i);
      return;
    }
  }  
}

void list(No* current){
  for (int i = 0; i < current -> filhos.size() ; i++){
    if (current -> filhos[i] -> tipo == "d")
      cout << "/" << current -> filhos[i] -> id << "  ";
    else
      cout << current -> filhos[i] -> id << "  ";
  }
  cout << "\n";
}

void print_help(){
  cout << "m - criar diretório/arquivo\nc - mudar diretório corrente\nd - remover um arquivo\nl - listar diretorio\n";
}

int main(int argc, char **argv) {

  if (argc > 2){
    cout << "Erro! Muitos argumentos!\n";
    return 0;
  } else if (argc == 2){
    cout << "Iniciando... com o diretório " << argv[1] << " como root!\n";
    rootPath = argv[1];
  }
  
  No* root = iniciarArvore();
  No* current = root;
  No* temp;
  string command;
  int interpreter = 10;
  cout << "\n\n\n============= Bem vindo ao nosso shell! ===============\n\n\n";

  while (1){
    cout << "\n[" << current -> id << "] >> ";
    getline(cin, command);

    interpreter = command_interpreter(command);

    switch(interpreter){
      case 0:
        return 0;
      case 1:
        create_directory_arq(current, command);
        break;
      case 2:
        temp = change_directory(current, command);
        if (temp != nullptr)
          current = temp;
        break;
      case 3:
        remove_arq(current, command);
        break;
      case 4:
        list(current);
        break;
      case 5:
        print_help();
        break;
    }
  }
}