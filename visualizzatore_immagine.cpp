#include "visualizzatore_immagine.hpp"

namespace pf {

visualizzatore_immagine::visualizzatore_immagine(Immagine const& img)
{
  auto size{img.size_originale()};
  if (!texture_originale_.create(static_cast<unsigned int>(size.width),
                                 static_cast<unsigned int>(size.height))) {
    throw std::runtime_error(
        "impossibile creare la texture dell'immagine originale");
  }

  if (!texture_binarizzata_.create(larghezza_immagine, altezza_immagine)) {
    throw std::runtime_error(
        "impossibile creare la texture dell'immagine binarizzata");
  }
  image_4campi conversione{img.conversione_openCV_to_SFML()};
  texture_originale_.update(conversione.image_originale_4campi.data);
  texture_binarizzata_.update(conversione.image_binarizzata_4campi.data);
  sprite_originale_.setTexture(texture_originale_);
  sprite_binarizzata_.setTexture(texture_binarizzata_);
  sprite_binarizzata_.setScale(15.f, 15.f);
}

void visualizzatore_immagine::show_image(sf::RenderWindow& window) const
{
  window.clear();
  window.draw(sprite_originale_);
  window.draw(sprite_binarizzata_);
  window.display();
}

void visualizzatore_immagine::gestione_finestra(
    sf::RenderWindow& window, visualizzatore_immagine const& view)
{
  sf::Clock clock;
  while (window.isOpen() && clock.getElapsedTime().asSeconds() < 2.f) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    sf::Vector2f posizione_binarizzata{
        static_cast<float>(texture_originale_.getSize().x + 50),
        static_cast<float>(texture_originale_.getSize().y - 700)};
    sf::Vector2f posizione_originale{30.f, 50.f};
    sprite_originale_.setPosition(posizione_originale);
    sprite_binarizzata_.setPosition(posizione_binarizzata);
    view.show_image(window);
  }
};

void plot_grafico(dati_grafico const& dg, plstream& plot)
{
  assert(dg.dati_x.size() == dg.dati_y.size());
  PLINT N_punti{static_cast<PLINT>(dg.dati_y.size())};
  PLFLT x_max{*std::max_element(dg.dati_x.begin(), dg.dati_x.end()) + 5};
  PLFLT y_max{*std::max_element(dg.dati_y.begin(), dg.dati_y.end()) + 5};
  PLFLT x_min{0.0};
  PLFLT y_min{*std::min_element(dg.dati_y.begin(), dg.dati_y.end()) - 5};
  plot.init();
  plot.env(x_min, x_max, y_min, y_max, 0, 1);
  plot.lab(dg.etichetta_asse_x.data(), dg.etichetta_asse_y.data(),
           dg.titolo.data());
  plot.line(N_punti, dg.dati_x.data(), dg.dati_y.data());
};

void show_grafico_finestra(dati_grafico const& dg)
{
  plstream plot;
  plot.sdev("qtwidget");
  plot_grafico(dg, plot);
}

void salva_grafico_file(dati_grafico const& dg)
{
  plstream plot;
  plot.sdev("png");
  plot.sfnam("grafico_energia.png");
  plot_grafico(dg, plot);
}

} // namespace pf