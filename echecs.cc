#include "Jeu.hpp"

int main(void)
{
    Jeu ech;
    bool cont = true;
    ech.affiche_bienvenu();
    ech.init_coup_initial();
    ech.init_nbr_coup();
    ech.init_historique();
    while (cont)
    {
        ech.affiche();
        cont = ech.jouer();
    }
    ech.free_historique();
    ech.affiche_fin();
    return 0;
}