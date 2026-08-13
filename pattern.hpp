#ifndef PF_GET_PATTERN_HPP
#define PF_GET_PATTERN_HPP
#include "costanti.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <stdexcept>
#include <vector>

namespace pf {
enum class Stato_Neurone : int8_t
{
  positivo = +1,
  negativo = -1,
};

int Valore_Neurone(Stato_Neurone s)
{
  int v{static_cast<int>(s)};
  return v;
}

std::vector<std::string>
get_file_names(std::filesystem::path const& cartella_immagini)
{
  std::vector<std::string> file_names;
  for (auto const& entry :
       std::filesystem::directory_iterator(cartella_immagini)) {
    if (entry.is_regular_file()) {
      file_names.push_back(entry.path().string());
    }
  }
  return file_names;
}

class Immagine
{
 private:
  sf::Image image_originale_;
  sf::Image image_binarizzata_;

 public:
  explicit Immagine(std ::string const& file_name)
  {
    if (!image_originale_.loadFromFile(file_name))
      throw std::runtime_error("impossibile caricare il file");
  }
  void load_image(std::string const& file_name)
  {
    if (!image_originale_.loadFromFile(file_name))
      throw std::runtime_error("impossibile caricare il file");
  }
  sf::Image interpolazione() const
  {}
  Pattern binarizzazione() const
  {}
  void show_image() const {};
};

class Pattern
{
 private:
  std::vector<Stato_Neurone> pattern_;

 public:
  Pattern()
      : pattern_(N_neuroni){};

  std::size_t size() const
  {
    return pattern_.size();
  }

  auto begin() const
  {
    return pattern_.begin();
  }
  auto end() const
  {
    return pattern_.end();
  }
  
};

bool operator==(Pattern const& a, Pattern const& b)
{
  assert(a.size() == N_neuroni);
  assert(b.size() == N_neuroni);
  return std::equal(a.begin(), a.end(), b.begin());
}
} // namespace pf
#endif