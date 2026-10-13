#include "immagine.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

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

Immagine::Immagine(std::filesystem::path const& file_path)
    : image_originale_{cv::imread(file_path.string())}
    , image_binarizzata_(altezza_immagine, larghezza_immagine, CV_8UC1)
{
  if (image_originale_.empty()) {
    throw std::runtime_error("file non valido, impossibile caricare il file");
  }
}

cv::Mat Immagine::resize_interpolazione()
{
  cv::Size dimensioni{altezza_immagine, larghezza_immagine};
  cv::resize(image_originale_, image_interpolata_, dimensioni, 0.0, 0.0,
             cv::INTER_LINEAR);
  return image_interpolata_;
}

Pattern Immagine::binarizzazione()
{
  cv::Mat image_bianconero(altezza_immagine, larghezza_immagine, CV_8UC1);
  cv::cvtColor(image_interpolata_, image_bianconero, cv::COLOR_BGR2GRAY);
  cv::threshold(image_bianconero, image_binarizzata_, limite_colore, 255,
                cv::THRESH_BINARY);
  Pattern p;
  for (int i{0}; i != image_binarizzata_.rows; ++i) {
    for (int j{0}; j != image_binarizzata_.cols; ++j) {
      auto neurone_bin{image_binarizzata_.at<uchar>(i, j) > 0.0
                           ? Stato_Neurone::positivo
                           : Stato_Neurone::negativo};
      p[static_cast<std::size_t>(i * image_binarizzata_.cols + j)] =
          neurone_bin;
    }
  }
  return p;
}

void Immagine::show_image(sf::RenderWindow& window) const
{
  sf::Texture texture_originale;
  sf::Texture texture_binarizzata;
  auto size{image_originale_.size()};
  if (!texture_originale.create(static_cast<unsigned int>(size.width),
                                static_cast<unsigned int>(size.height))) {
    throw std::runtime_error(
        "impossibile creare la texture dell'immagine originale");
  }

  if (!texture_binarizzata.create(larghezza_immagine, altezza_immagine)) {
    throw std::runtime_error(
        "impossibile creare la texture dell'immagine binarizzata");
  }
  cv::Mat image_originale_4campi;
  cv::Mat image_binarizzata_4campi;
  cv::cvtColor(image_originale_, image_originale_4campi, cv::COLOR_BGR2RGBA);
  cv::cvtColor(image_binarizzata_, image_binarizzata_4campi,
               cv::COLOR_GRAY2BGRA);
  texture_originale.update(image_originale_4campi.data);
  texture_binarizzata.update(image_binarizzata_4campi.data);
  sf::Sprite sprite_originale(texture_originale);
  sf::Sprite sprite_binarizzata(texture_binarizzata);
  sprite_binarizzata.setScale(10.f,10.f);

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
        static_cast<float>(texture_originale.getSize().x + 100),
        static_cast<float>(texture_originale.getSize().y-700)};
    sprite_binarizzata.setPosition(posizione_binarizzata);
    window.draw(sprite_binarizzata);
    window.display();
  }
}

} // namespace pf