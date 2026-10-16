#ifndef PF_IMMAGINE_HPP
#define PF_IMMAGINE_HPP

#include "costanti.hpp"
#include "pattern.hpp"
#include <SFML/Graphics.hpp>
#include <opencv2/core.hpp>
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <stdexcept>
#include <vector>

namespace pf {

std::vector<std::filesystem::path>
get_file_names(std::filesystem::path const& cartella);

struct image_4campi
{ // necessaria per la conversione conrretta dei dati da openCv a SFML
  cv::Mat image_originale_4campi;
  cv::Mat image_binarizzata_4campi;
};

class Immagine
{
 private:
  cv::Mat image_originale_;
  cv::Mat image_interpolata_;
  cv::Mat image_binarizzata_;

 public:
  explicit Immagine(std::filesystem::path const& file_path);

  cv::Size size_originale() const;

  cv::Mat resize_interpolazione();

  Pattern binarizzazione();

  image_4campi conversione_openCV_to_SFML() const;

};

} // namespace pf

#endif