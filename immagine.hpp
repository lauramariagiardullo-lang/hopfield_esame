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

std::vector<std::filesystem::path>
get_file_names(std::filesystem::path const& cartella);

class Immagine
{
 private:
  sf::Image image_originale_;
  sf::Image image_binarizzata_;

 public:
  explicit Immagine(std ::filesystem::path const& file_path);

  sf::Image interpolazione() const //?
  {}

  Pattern binarizzazione();

  void show_image(sf::RenderWindow& window) const;
};

} // namespace pf

#endif