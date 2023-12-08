#include "piece.hpp"

/**
 * @brief Class Echiquier qui contient le tableau de pièce représantant l'échiquier.
 * 
 */
class Echiquier
{
private:
    Piece *echiquier[8][8];
    bool danger[8][8];

public:
    /**
     * @brief Construct a new Echiquier object
     * 
     */
    Echiquier();
    /**
     * @brief Destroy the Echiquier object
     * 
     */
    ~Echiquier();
    /**
     * @brief affiche l'échiquier
     * 
     */
    void affiche() const;
    /**
     * @brief renvoie le nom de la piece
     * à la position dep
     *
     * @param dep
     * @return string
     */
    string get_nom(Square dep) const;
    /**
     * @brief renvoie 0 s'il n'y a pas de pièce dans le square arr, 1 sinon
     *
     * @param arr
     * @return true
     * @return false
     */
    bool chk_non_vide(Square arr) const;
    /**
     * @brief verifie si le déplacement est possible.
     * ici on vérifie seulement s'il y a une pièce dans la case de départ,
     * que la couleur de la piece est la même que celle du joueur actuel, et
     * que la case d'arrivé ne contient pas une pièce de la couleur du joueur actuel
     * return 1 si le mouvement est impossible, 0 sinon
     * 
     * @param Ldep 
     * @param Cdep 
     * @param Larr 
     * @param Carr 
     * @param couleur 
     * @param deplacement 
     * @return int 
     */
    int dep_imp(int Ldep, int Cdep, int Larr, int Carr, Couleur couleur, int deplacement = 1);
    /**
     * @brief Cette fonction fait le déplacement rèel des pièces sur l'echiquier.
     * S'il y a une piece sur la case d'arrivé, la mémoire de cette piece est libéré et
     * la position de la pièce qui se deplace est mis à jour.
     * 
     * @param Ldep 
     * @param Cdep 
     * @param Larr 
     * @param Carr 
     * @param prise_en_passante 
     */
    void faire_deplacement(int Ldep, int Cdep, int Larr, int Carr, int prise_en_passante = 0);
    
    /**
     * @brief fonction qui verifie si le déplacement voulu est possible.
     * Ici on verifie s'il n'y a pas d'obstacle lors d'un déplacement.
     * On vérifie aussi, lors d'une attaque, s'il y a une pièce adversaires sur la case
     * d'arrivée. Et si cela n'est pas le cas on vérifie s'il on peut faire une prise en passante.
     * return 1 si le déplacement est impossible, 0 sinon.
     * 
     * @param Ldep 
     * @param Cdep 
     * @param Larr 
     * @param Carr 
     * @param cp_pred_dep 
     * @param cp_pred_arr 
     * @param deplacement 
     * @param danger 
     * @return int 
     */

    int deplacement_pion(int Ldep, int Cdep, int Larr,
                         int Carr, Square cp_pred_dep, Square cp_pred_arr,
                         int deplacement = 1,
                         int danger = 0);
    /**
     * @brief Fonction qui fait le déplacement du cavalier.
     * On fait une fonction diffèrente pour le cavalier car ces la seule pièce
     * qui ne nécessite pas de détéction d'obstacle.
     * 
     * @param Ldep 
     * @param Cdep 
     * @param Larr 
     * @param Carr 
     * @param deplacement 
     * @return int 
     */
    int deplacement_cavalier(int Ldep, int Cdep, int Larr, int Carr, int deplacement = 1);
    /**
     * @brief fonction qui fait les déplacement pour les pièces qui ne sont ni le pion, ni le cavalier.
     * On vérifie ici s'il n'y a pas d'obstacle sur le chemin de la pièce.
     * return 1 si le déplacement n'est pas possible, 0 sinon.
     * 
     * @param Ldep 
     * @param Cdep 
     * @param Larr 
     * @param Carr 
     * @param deplacement 
     * @return int 
     */
    int deplacement_globale(int Ldep, int Cdep, int Larr, int Carr, int deplacement = 1);

    /**
     * @brief permet le déplacement d'une piece
     * deplacement vaut 0 s'il n y'a pas de déplacement à faire. S'il y a une erreur dans le déplacement, on écrit pas de message dans le terminal.
     * deplacement vaut 1 s'il s'agit d'un vrai déplacement à faire sur le jeu, si le mouvement n'est pas valide,
     * l'erreur sera écrite sur le terminal.
     * deplacement vaut 2 s'il s'agit d'un déplacement virtuel (deplacement temporaire le temps de vérifier certaines chose)
     * et qu'il faut écrire un commentaire si jamais le coup produit une erreur.
     * danger vaut 1 si deplace est utiliser via la fonction danger. Cela est nécessaire car pour la fonction danger
     * il ne faut prendre que les attaques possibles, or le pion est la seul piece où ses attaques et ses mouvements
     * sont distincts. Donc la variable danger permet de dire que l'on ne prend que les attaques des pièces
     * return 1 si le déplacement n'est pas valide, 0 sinon.
     *
     *
     * @param depart
     * @param arrive
     * @param couleur
     * @param cp_pred_dep
     * @param cp_pred_arr
     * @param deplacement
     * @param danger
     * @return int
     */
    int deplace(Square depart, Square arrive, Couleur couleur, Square cp_pred_dep, Square cp_pred_arr, int deplacement = 1, int danger = 0);
    /**
     * @brief affiche la pièce situé sur la case dep.
     * 
     * @param dep 
     */
    void affiche_piece(Square dep);
    /**
     * @brief verifie si le mouvement donné par le joueur Jcurr actuel est valable et s'il provoque un echec de son roi
     *  return 0 si le déplacement est valide, 1 si le déplacement met en échecs le roi du joueur actuel
     * , 2 si le mouvement est impossible.
     * 
     * @param Jcurr
     * @param depart
     * @param arrive
     * @param cp_pred_dep
     * @param cp_pred_arr
     * @param deplacement
     * @return int
     */
    int mvt_prod_echec(Couleur Jcurr, Square depart, Square arrive, Square cp_pred_dep, Square cp_pred_arr, int deplacement = 2);
    /**
     * @brief permet la promotion d'un pion
     *
     * @param arrive
     */
    void promotion(Square arrive);
    /**
     * @brief calcul les cases menacés par le joueur opposé à Jcurr
     *
     * @param Jcurr
     * @param cp_pred_dep
     * @param cp_pred_arr
     */
    void en_danger(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr);
    /**
     * @brief fonction qui fait le petit roque si cela est possible
     * renvoie 0 si le petit roque est fait, 1 sinon
     *
     * @param Jcurr
     * @param cp_pred_dep
     * @param cp_pred_arr
     * @return int
     */
    int petit_roque(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr);
    /**
     * @brief fonction qui fait le grand roque si cela est possible
     * renvoie 0 si le grand roque est réalisé, 1 sinon
     *
     * @param Jcurr
     * @param cp_pred_dep
     * @param cp_pred_arr
     * @return int
     */
    int grand_roque(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr);
    /**
     * @brief fonction qui test si le joueur actuel Jcurr est en echec et mat.
     * return 1 si Jcurr est en echec et mat, 0 sinon.
     * 
     * @param Jcurr 
     * @param cp_pred_dep 
     * @param cp_pred_arr 
     * @return int 
     */
    int echec_et_mat(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr);
    /**
     * @brief fonction qui test si le joueur actuel Jcurr est en echec. 
     * return 1 si Jcurr est en echec, 0 sinon.
     * 
     * @param Jcurr 
     * @param cp_pred_dep 
     * @param cp_pred_arr 
     * @return int 
     */
    int en_echec(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr);
    /**
     * @brief fonction qui vérifie s'il y a pat. 
     * return 1 si c'est le cas , 0 sinon.
     * 
     * @param Jcurr 
     * @param cp_pred_dep 
     * @param cp_pred_arr 
     * @return int 
     */
    int pat(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr);
    /**
     * @brief fonction qui affiche les cases occupés à la fin de la partie.
     * 
     */
    void affiche_fin(void) const;
    
    /**
     * @brief return 1 s'il n'y a pas de prise en passante possible sur l'echiquier, 0 sinon
     * 
     * @param couleur 
     * @param cp_pred_dep 
     * @param cp_pred_arr 
     * @return int 
     */
    int prise_passante_possible(Couleur couleur, Square cp_pred_dep, Square cp_pred_arr);

};