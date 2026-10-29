#include <exception>
#include <iostream>

#include "costanti.hpp"
#include "immagine.hpp"
#include "matrice_pesi.hpp"
#include "pattern.hpp"
#include "rete_hopfield.hpp"
#include "visualizzatore_immagine.hpp"

int main()
{
  try {
    std::cout << "Di seguito sono riportate le immagini utilizzate per "
                 "l'addestramento della rete, ciascuna affiancata dalla "
                 "corrispondente immagine binarizzata \n ";

    auto nomi_file{pf::get_file_names(pf::path_cartella_immagini)};
    sf::RenderWindow w(sf::VideoMode(1400, 1100),
                       "immagini addestramento rete");
    for (auto& file : nomi_file) {
      pf::Immagine imag(file);
      imag.resize_interpolazione();
      imag.binarizzazione();
      pf::visualizzatore_immagine view(imag);
      view.gestione_finestra(w, view);
    }

    pf::Rete_Hopfield rete_neurale;
    rete_neurale.pf::Rete_Hopfield::apprendimento(pf::path_cartella_immagini,
                                                  pf::path_file_matrice_pesi);
    pf::Rete_Hopfield rete_addestrata(pf::path_file_matrice_pesi);

    std::cout << "si inserisca il tipo di corruzione del pattern scelto: \n"
              << "rumore casuale [r] \n"
              << "taglio [t] \n";
    char cp;
    std::cin >> cp;
    std::cout
        << "si scelga quale fra i pattern proposti si vuole corrompere, "
           "inserendo un intero compreso fra 0 e 10 "; // metterò 11 pattern o
                                                       // nel caso cambio il
                                                       // range
    int n;
    if (!(std::cin >> n) || n > pf::N_immagini_usate_per_addestramento
        || n < 0) {
      throw std::runtime_error("il valore inserito per la scelta del pattern "
                               "da corrompere non è valida");
    }
    pf::Pattern const pattern_selezionato =
        pf::insieme_pattern(pf::path_cartella_immagini)[static_cast<size_t>(n)];

    pf::dati_grafico plot_energia;
    plot_energia.titolo           = "grafico energia";
    plot_energia.etichetta_asse_x = "iterazioni";
    plot_energia.etichetta_asse_y = "energia";

    pf::Pattern pattern_finale{rete_addestrata.pf::Rete_Hopfield::richiamo(
        cp, pattern_selezionato, plot_energia.dati_y)};
    rete_addestrata.pf::Rete_Hopfield::pattern_originale_vs_pattern_finale(
        pattern_selezionato, pattern_finale);
    plot_energia.dati_x.resize((plot_energia.dati_y.size()));
    std::iota(plot_energia.dati_x.begin(), plot_energia.dati_x.end(), 0.0);
    show_grafico_finestra(plot_energia);
    salva_grafico_file(plot_energia);

  } catch (std::runtime_error const& e) {
    std::cerr << "eccezione catturata: " << e.what() << "\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "errore sconosciuto";
    return EXIT_FAILURE;
  }
}
