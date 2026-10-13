#include <exception>
#include <iostream>

#include "costanti.hpp"
#include "immagine.hpp"
#include "matrice_pesi.hpp"
#include "pattern.hpp"
#include "rete_hopfield.hpp"

int main()
{
  try {
    pf::Rete_Hopfield rete_neurale;
    rete_neurale.pf::Rete_Hopfield::apprendimento(pf::path_cartella_immagini,
                                                  pf::path_file_matrice_pesi);
    std::cout << "si inserisca il tipo di corruzione del pattern scelto: \n"
              << "rumore casuale [r] \n"
              << "taglio [t] \n";
    char cp;
    std::cin >> cp;
    std::cout << "si scelga quale fra i pattern proposti si vuole corrompere, inserenndo un intero compreso fra 0 e 10 "; //metterò 11 pattern o nel caso cambio il range
    int n;
    if (!(std::cin>>n) || n>pf::insieme_pattern(pf::path_cartella_immagini).size()){
      throw std::runtime_error("il valore inserito per la scelta del pattern da corrompere non è valida");
    }
    pf::Pattern const pattern_selezionato=pf::insieme_pattern(pf::path_cartella_immagini[n]);
    pf::Pattern pattern_finale{rete_neurale.pf::Rete_Hopfield::richiamo(cp,pattern_selezionato)};


    auto nomi_file{pf::get_file_names(pf::path_cartella_immagini)};
    sf::RenderWindow w(sf::VideoMode(1400, 1100),
                       "immagini addestramento rete");
    //for (auto& file : nomi_file) {
     // pf::Immagine imag(file);
      //imag.resize_interpolazione();
      //imag.binarizzazione();
      //imag.show_image(w);
    //}
pf::Immagine imag(nomi_file[1]);
      imag.resize_interpolazione();
      imag.binarizzazione();
      imag.show_image(w);
    

    pf::Rete_Hopfield rete_neurale;
    // rete_neurale.Rete_Hopfield::apprendimento(pf::path_cartella_immagini,
    // pf::file_matrice_pesi );

  } catch (std::runtime_error const& e) {
    std::cerr << "eccezione catturata: " << e.what() << "\n";
    return EXIT_FAILURE;

  } catch (...) {
    std::cerr << "errore sconosciuto";
    return EXIT_FAILURE;
  }
}
