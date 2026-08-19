#include "immagine.hpp"

namespace pf {

std::vector<std::filesystem::path>
get_file_names(std::filesystem::path const& cartella)
{
  if (!std::filesystem::is_directory(cartella)) {
    throw std::runtime_error("il percorso fornito non è una cartella");
  }

  std::vector<std::filesystem::path> file_names;
  for (auto const& entry : std::filesystem::directory_iterator(cartella)) {
    if (entry.is_regular_file()) {
      file_names.push_back(entry.path());
    }
  }

  if (file_names.empty()) {
    throw std::runtime_error(
        "la cartella è vuota o non contiene oggetti validi");
  }

  return file_names;
}

Immagine::Immagine(std ::filesystem::path const& file_path)
{
  if (!image_originale_.loadFromFile(file_path)) {
    throw std::runtime_error("file non valido, impossibile caricare il file");
  }
  image_binarizzata_.create(larghezza_immagine, altezza_immagine,
                            sf::Color::White);
}

Pattern Immagine::binarizzazione()
{
  sf::Image image_interpolata{interpolazione()};
  Pattern p;
  for (unsigned int i{0}; i != larghezza_immagine; ++i) {
    for (unsigned int j{0}; j != altezza_immagine; ++j) {
      sf::Color pixel{image_interpolata.getPixel(i, j)};
      auto neurone_bin{(pixel.r + pixel.b + pixel.g) / 3 > limite_colore
                           ? Stato_Neurone::positivo
                           : Stato_Neurone::negativo};
      auto pixel_bin{(pixel.r + pixel.b + pixel.g) / 3 > limite_colore
                         ? sf::Color::White
                         : sf::Color::Black};
      image_binarizzata_.setPixel(i, j, pixel_bin);
      p[j * larghezza_immagine + i] = neurone_bin;
    }
  }
  return p;
}

void Immagine::show_image(sf::RenderWindow& window) const
{
  sf::Texture texture_originale;
  sf::Texture texture_binarizzata;
  if (!texture_originale.loadFromImage(image_originale_)) {
    throw std::runtime_error("impossibile caricare l'immagine iniziale");
  }
  if (!texture_binarizzata.loadFromImage(image_binarizzata_)) {
    throw std::runtime_error("impossibile caricare l'immagine binarizzata");
  }
  sf::Sprite sprite_originale(texture_originale);
  sf::Sprite sprite_binarizzata(texture_binarizzata);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear();
    window.draw(sprite_originale);
    sf::Vector2f posizione_binarizzata{
        static_cast<float>(image_originale_.getSize().x + 50),
        static_cast<float>(image_originale_.getSize().y)};
    sprite_binarizzata.setPosition(posizione_binarizzata);
    window.draw(sprite_binarizzata);
    window.display();
  }
}

} // namespace pf