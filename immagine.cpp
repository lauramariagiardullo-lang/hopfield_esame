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

cv::Size Immagine::size_originale() const
{
  return image_originale_.size();
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
  assert(p.size() == N_neuroni);

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

image_4campi Immagine::conversione_openCV_to_SFML() const
{
  image_4campi conversione;
  cv::cvtColor(image_originale_, conversione.image_originale_4campi,
               cv::COLOR_BGR2RGBA);
  cv::cvtColor(image_binarizzata_, conversione.image_binarizzata_4campi,
               cv::COLOR_GRAY2BGRA);
  return conversione;
};

} // namespace pf