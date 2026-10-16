#ifndef PF_VISUALIZZATORE_IMMAGINE_HPP
#define PF_VISUALIZZATORE_IMMAGINE_HPP
#include "immagine.hpp"

namespace pf {
class visualizzatore_immagine
{
  sf::Texture texture_originale_;
  sf::Texture texture_binarizzata_;
  sf::Sprite sprite_originale_;
  sf::Sprite sprite_binarizzata_;

 public:
  explicit visualizzatore_immagine(Immagine const& img);
  
  void show_image(sf::RenderWindow& window) const;
  void gestione_finestra(sf::RenderWindow& window, visualizzatore_immagine const& view);
 
};
} // namespace pf

#endif