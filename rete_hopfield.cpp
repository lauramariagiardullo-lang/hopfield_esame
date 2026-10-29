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
  // assert(paths.size()==N_immagini_usate_per_addestramento);

  hebb_.calcolo_matrice(paths);

  hebb_.salva(file_txt);
}

void Rete_Hopfield::aggiornamento_singolo_neurone(Pattern& corrotto,
                                                  std::size_t i) const

{
  assert(i < N_neuroni);
  auto riga_i{hebb_.riga(i)};

  double somma{
      std::inner_product(riga_i.begin(), riga_i.end(), corrotto.begin(), 0.0)};
  Stato_Neurone neurone_aggiornato{somma > 0   ? Stato_Neurone::positivo
                                   : somma < 0 ? Stato_Neurone::negativo
                                               : corrotto[i]};
  corrotto[i] = neurone_aggiornato;
}

Pattern Rete_Hopfield::aggiornamento_pattern(Pattern& corrotto)
{
  for (std::size_t i{0}; i != corrotto.size(); ++i) {
    aggiornamento_singolo_neurone(corrotto, i);
  }
  return corrotto;
}

double Rete_Hopfield::funzione_energia(Pattern const& p) const
{
  assert(p.size() == N_neuroni);
  std::vector<std::size_t> indici(p.size());
  assert(indici.size() == p.size());
  std::iota(indici.begin(), indici.end(), 0);
  double somma_completa = std::accumulate(
      indici.begin(), indici.end(), 0.0,
      [this, &p](double somma, std::size_t i) {
        auto contributo_singola_riga = std::inner_product(
            hebb_.riga(i).begin(), hebb_.riga(i).end(), p.begin(), 0.0);
        return somma + p[i] * contributo_singola_riga;
      });
  double energia{-0.5 * somma_completa};
  return energia;
};

Pattern Rete_Hopfield::convergenza(Pattern& corrotto,
                                   std::vector<double>& vettore_energia)
{
  auto precedente{corrotto};
  auto attuale{aggiornamento_pattern(corrotto)};
  vettore_energia.push_back(funzione_energia(attuale));
  if (precedente == attuale) {
    return attuale;
  } else {
    return convergenza(attuale, vettore_energia);
  }
}

Pattern Rete_Hopfield::richiamo(char metodo_corruzione,
                                Pattern const& originale,
                                std::vector<double>& vettore_energia)
{
  if (metodo_corruzione == 'r') {
    std::cout << "si inserisca la probabilità, compresa fra 0 e 1, che un "
                 "pixel venga corrotto \n ";
    double probabilità;
    if (!(std::cin >> probabilità)) {
      throw std::runtime_error(
          "il tipo associato alla probabilità per il calcolo del rumore "
          "casuale non è accettabile");
    }
    Pattern corrotto{corruzione_rumore_casuale(originale, probabilità)};
    vettore_energia.push_back(Valore_Neurone(corrotto[0]));
    return convergenza(corrotto, vettore_energia);
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
    vettore_energia.push_back(Valore_Neurone(corrotto[0]));
    return convergenza(corrotto, vettore_energia);
  }
  throw std::runtime_error("il metodo di corruzione inserito non è valido ");
};

void Rete_Hopfield::pattern_originale_vs_pattern_finale(
    Pattern const& originale, Pattern const& finale) const
{
  assert(originale.size() == finale.size());
  if (originale == finale) {
    std::cout << "ricostruzione del pattern corretta\n"
              << "il pattern finale, ottenuto dal richiamo della rete sul "
                 "pattern coorrotto, è uguale al pattern originale\n";
  } else {
    std::size_t i{0};
    auto N_differenti = std::count_if(originale.begin(), originale.end(),
                                      [&](Stato_Neurone const& n) {
                                        std::size_t const indice{i};
                                        ++i;
                                        return n != finale[indice];
                                      });
    auto percentuale{(static_cast<double>(N_differenti) / N_neuroni) * 100};
    std::cout << "il pattern originale e quello finale non sono identici:\n"
              << "differiscono del " << percentuale << "%\n";
  }
};

} // namespace pf
