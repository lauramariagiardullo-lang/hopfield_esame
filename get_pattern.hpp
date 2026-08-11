#ifndef PF_GET_PATTERN_HPP
#define PF_GET_PATTERN_HPP
#include <SFML/Graphics.hpp>
#include <filesystem>
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

class Immagine
{
 private:
  sf::Image image_originale_;
  sf::Image image_binarizzata_;

 public:
  explicit Immagine(std ::string const& file_name)
  {}
  void load_image(std::string const& file_name)
  {}
  sf::Image interpolazione() const
  {}
  std::vector<Stato_Neurone> binarizzazione() const
  {}
  void show_image() const {};
};

class Pattern
{
 private:
  std::vector<Stato_Neurone> pattern_;

 public:
};
} // namespace pf
#endif