#include <exception>
#include <iostream>

#include "immagine.hpp"
#include "matrice_pesi.hpp"
#include "pattern.hpp"
#include "rete_hopfield.hpp"

int main()
{
  try {
    std::cout << "si inserisca il tipo di corruzione del pattern scelto: \n"
              << "rumore casuale [r] \n"
              << "taglio [t] \n";

    char cp{};
    std::cin >> cp;












} catch (std::runtime_error const& e) {
    std::cerr << "eccezione catturata: " << e.what() << "\n";
    return EXIT_FAILURE;

  } catch (...) {
    std::cerr << "errore sconosciuto";
    return EXIT_FAILURE;
  }
}
