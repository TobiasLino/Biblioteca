//
// Created by tobias on 22/02/2020.
//
#include <string.h>
#include <iostream>
#include <string>
#include <list>

class Pessoa;

class Livro {
 public:
  Livro();
  bool operator== (const Livro& l) const;
  char* GetTitle() { return title_; }
 private:
  char *title_;
  Pessoa *pessoa_;
  friend std::ostream& operator<< (std::ostream& out, const Livro& l);
  friend std::ostream& operator<< (std::ostream& out, const Pessoa& p);
  friend void IncluiLivro();
};

class Autor {
 public:
  Autor();
  bool operator== (const Autor& a) const;
  std::string PrintaLivros();
 private:
  char *name_;
  std::list<Livro*> livros_;
  friend std::ostream& operator<< (std::ostream& out, Autor& a);
  friend std::ostream& operator<< (std::ostream& out, const Pessoa& p);
  friend void IncluiLivro();
  // friend void RetiraLivro();
};


class Pessoa {
 public:
  Pessoa();
  bool operator== (const Pessoa& p) const;
  char* GetName() { return name_; }
 private:
  char *name_;
  friend std::ostream& operator<< (std::ostream& out, const Pessoa& p);
  friend std::ostream& operator<< (std::ostream& out, const Livro& l);
  friend void IncluiLivro();
};


// Define um catalogo de autores
std::list<Autor*> catalogo['Z' + 1];

template<typename T>
std::ostream& operator<< (std::ostream& out, const std::list<T>& lst);
std::ostream& operator<< (std::ostream& out, const Livro& l);
std::ostream& operator<< (std::ostream& out, const Autor& a);
char* GetString(std::string msg);
// Função que encontra autor pelo nome
std::list<Autor*>::iterator FindIt(std::list<Autor*>& lst, const Autor& el);
void IncluiLivro();

int menu();

int main(void) {
  while (true) {
    switch (menu()) {
      case 1: IncluiLivro(); break;
      case 5: return 0;
      default: std::cout << "Entre com uma opção válida: ";;
    }
  }
}

bool Pessoa::operator== (const Pessoa &p) const {
  return strcmp(name_, p.name_) == 0;
}

Livro::Livro() {
  pessoa_ = 0;
}
bool Livro::operator== (const Livro &l) const {
  return strcmp(title_, l.title_) == 0;
}

bool Autor::operator== (const Autor &a) const {
  return strcmp(name_, a.name_) == 0;
}


std::string Autor::PrintaLivros() {
  std::string tmp = "";
  std::list<Livro*>::iterator i = this->livros_.begin();
  for (; i != this->livros_.end(); ++i) {
    tmp += (*i)->GetTitle();
    tmp += "\n";
  }
  return tmp;
}
std::ostream& operator<< (std::ostream& out, const Livro& l) {
  out << "    * " << l.title_;
  if (l.pessoa_ != 0)
    out << " - Foi emprestado por " << l.pessoa_->GetName();
  out << std::endl;
  return out;
}

std::ostream& operator<< (std::ostream& out, Autor& a) {
  out << a.name_ << "\n";
  out << a.PrintaLivros();
  return out;
}

char* GetString(std::string msg) {
  std::cout << msg;
  char* tmp;
  std::cin >> tmp;
  return tmp;
}

// Função que encontra autor pelo nome
std::list<Autor*>::iterator FindIt(std::list<Autor*>& lst, const Autor& el) {
  std::list<Autor*>::iterator ref = lst.begin();
  for (; ref != lst.end(); ref++) {
    if (**ref == el)
      break;
  }
  return ref;
}

void IncluiLivro() {
  Autor *nAutor = new Autor;
  Livro *nLivro = new Livro;

  nAutor->name_ = GetString("Entre com o nome do autor: ");
  nLivro->title_ = GetString("Entre com o titulo do livro: ");

  std::list<Autor*>::iterator oAutor =
          FindIt(catalogo[nAutor->name_[0]], *nAutor);

  if (oAutor == catalogo[nAutor->name_[0]]) {
    nAutor->livros_.push_front(nLivro);
    catalogo[nAutor->name_[0]].push_front(nAutor);
  } else {
    (*oAutor)->livros_.push_front(nLivro);
  }
}

int menu() {
  int option;
  std::cout << "\nEntre com as seguintes opções:\n"
            << "1. IncluirLivro\n"
            << "5. Sair\n"
            << "\nSua opção: ";
  std::cin >> option;
  std::cin.get();
  return option;
}
