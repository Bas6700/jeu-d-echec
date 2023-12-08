#include "Echiquier.hpp"
#include <regex>

/**
 * @brief structure qui permet de tracé l'historique de la partie
 * 
 */
typedef struct historique
{
    string echiquier[8][8];
    historique *noeud_suivant;
    int nbr_echiquier_pred;
}historique;


/**
 * @brief Gére le jeu. Fournit des méthodes pour initier et terminer le jeu.
 * 
 * 
 */
class Jeu
{
private:
    Echiquier echiquier;
    Couleur jcurr;
    string cp_pred_dep;
    string cp_pred_arr;
    historique *debut;
    int nbr_coup;
    int prise_passante_possible;

public:
    /**
     * @brief Construct a new Jeu object
     * 
     */
    Jeu();
    /**
     * @brief affiche la bienvenu au joueurs et explique les règles.
     * 
     */
    void affiche_bienvenu() const;
    /**
     * @brief affiche l'échiquier
     * 
     */
    void affiche() const;
    /**
     * @brief initialise les coup initial Cp_pred_dep et cp_pred_arr.
     * 
     */
    void init_coup_initial();
    /**
     * @brief initialise le nombre de coup à zéro.
     * 
     */
    void init_nbr_coup();
    /**
     * @brief on intialise l'historique qui est nécessaire pour faire la règle des 3 coups.
     * 
     */
    void init_historique(void);
    /**
     * @brief on créer la suite de l'historique de la partie.
     * 
     */
    void creer_suite_historique(void);
    /**
     * @brief on supprime l'historique actuel, utile si l'historique ne sert plus à rien.
     * Comme l'historique est utilisé que par la fonction regle_trois_coup(), s'il y a un grand roque
     * ou un petit roque ou la possibilité d'avoir une prise en passante, alors l'historique actuel ne sert
     * plus à rien car la regle de la répetition des coups souligne bien qu'il faut les mêmes positions de pièce
     * trois fois et que les actions des pièces possible soit les mêmes. Or la prise en passante n'est valable qu'un tour
     * et un joueur ne peut faire qu'un roque par partie. 
     * 
     */
    void free_historique();
    /**
     * @brief test la regle des 3 coups
     * renvoie 1 s'il y a trois fois le même echiquier durant la partie
     * 0 sinon
     * 
     * @return int 
     */
    int regle_trois_coup();
    /**
     * @brief fonction qui permet de jouer.
     * 
     * @return int 
     */
    int jouer();
    /**
     * @brief fonction qui affiche les position finales occupées par les pièces.
     * 
     */
    void affiche_fin(void) const;
    /**
     * @brief affiche de l'aide pour l'utilisateur si ça commande n'est pas valide.
     * 
     */
    void affiche_aide();
    /**
     * @brief vérifie si la saisie est correcte pour un déplacement de pièce
     * 
     * @param cmd 
     * @return true 
     * @return false 
     */
    bool saisie_correcte(string const &cmd);
    /**
     * @brief vérifie si la saisie est correcte pour un petit roque.
     * 
     * @param cmd 
     * @return true 
     * @return false 
     */
    bool saisie_correcte_petitroque(string const &cmd);
    /**
     * @brief verifie si la saisie est correcte pour un grand roque.
     * 
     * @param cmd 
     * @return true 
     * @return false 
     */
    bool saisie_correcte_grandroque(string const &cmd);
};