#include "rete_hopfield.hpp"
#include "costanti.hpp"

namespace pf {

Rete_Hopfield::Rete_Hopfield(std::filesystem::path const& file_matrice)
{
  hebb_.carica(file_matrice);
}

void Rete_Hopfield::apprendimento(std::filesystem::path const& cartella_img,
                                  std::filesystem::path const& file_txt)
{
  auto paths{insieme_pattern(cartella_img)};
  hebb_.calcolo_matrice(paths);
  hebb_.salva(file_txt);
}

void Rete_Hopfield::aggiornamento_singolo_neurone(Pattern& corrotto,
                                                  std::size_t i) const

{
  assert(i < altezza_immagine);
  auto riga_i{hebb_.riga(i)};

  double somma{
      std::inner_product(riga_i.begin(), riga_i.end(), corrotto.begin(), 0.0)};
  Stato_Neurone neurone_aggiornato{somma > 0 ? Stato_Neurone::positivo
                                             : Stato_Neurone::negativo};
  corrotto[i] = neurone_aggiornato;
}

Pattern Rete_Hopfield::aggiornamento_pattern(Pattern& corrotto)
{
  for (std::size_t i{0}; i != corrotto.size(); ++i) {
    aggiornamento_singolo_neurone(corrotto, i);
  }
  return corrotto;
}

Pattern Rete_Hopfield::convergenza(Pattern& corrotto)
{
  auto precedente{corrotto};
  auto attuale{aggiornamento_pattern(corrotto)};
  if (precedente == attuale) {
    return attuale;
  } else {
    return convergenza(corrotto);
  }
}

Pattern Rete_Hopfield::richiamo(char metodo_corruzione,
                                Pattern const& originale)
{
  if (metodo_corruzione == 'r') {
    std::cout << "si inserisca la probabilità che un pixel venga corrotto";
    double probabilità;
    if (!(std::cin >> probabilità)) {
      throw std::runtime_error(
          "il tipo associato alla probabilità per il calcolo del rumore "
          "casuale non è accettabile");
    }
    Pattern corrotto{corruzione_rumore_casuale(originale, probabilità)};
    return convergenza(corrotto);
  } else if (metodo_corruzione == 't') {
    std::cout << "si inserisca la metà immagine interessata alla corruzione:\n"
              << "parte superiore[sup] \n"
              << "parte inferiore[inf] \n ";
    std::string metà_selezionata;
    if (!(std::cin >> metà_selezionata)) {
      throw std::runtime_error("il tipo associato alla porzione di immagine "
                               "interessata non è valido");
    }
    Pattern corrotto{corruzione_taglio(originale, metà_selezionata)};
    return convergenza(corrotto);
  }
  throw std::runtime_error("il metodo di corruzione inserito non è valido ");
};
} // namespace pf
