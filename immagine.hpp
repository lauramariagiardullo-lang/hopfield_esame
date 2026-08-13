#ifndef PF_IMMAGINE_HPP
#define PF_IMMAGINE_HPP

#include "costanti.hpp"
#include "pattern.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <stdexcept>
#include <vector>

namespace pf {

std::vector<std::string> get_file_names(std::filesystem::path const& cartella)
{
  if (!std::filesystem::is_directory(cartella)) {
    throw std::runtime_error("il percorso fornito non è una cartella");
  }

  std::vector<std::string> file_names;
  for (auto const& entry : std::filesystem::directory_iterator(cartella)) {
    if (entry.is_regular_file()) {
      file_names.push_back(entry.path().string());
    }
  }

  if (cartella.empty()) {
    throw std::runtime_error(
        "la cartella è vuota o non contiene oggetti validi");
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
      throw std::runtime_error("file non valido, impossibile caricare il file");
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

} // namespace pf

#endif