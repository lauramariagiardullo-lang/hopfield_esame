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

class Immagine
{
 private:
  cv::Mat image_originale_;
  cv::Mat image_interpolata_;
  cv::Mat image_binarizzata_;

 public:
  explicit Immagine(std ::filesystem::path const& file_path);


  cv::Mat resize_interpolazione();

  Pattern binarizzazione();

  void show_image(sf::RenderWindow& window) const;
};

} // namespace pf

#endif