#include <iostream>
#include <string>

using namespace std;

/**
 * @brief classe qui représente une case de l'echiquier.
 * 
 */
class Square
{
private:
    int ligne;
    int colonne;

public:
    /**
     * @brief Constructeur de Square avec deux int.
     * 
     * @param ligne 
     * @param colonne 
     */
    Square(int ligne, int colonne);
    /**
     * @brief Constructeur de square avec un string
     * 
     * @param position 
     */
    Square(string position);
    /**
     * @brief return la ligne du Square
     * 
     * @return int 
     */
    int get_ligne() const;
    /**
     * @brief return la colonne du Square.
     * 
     * @return int 
     */
    int get_colonne() const;
    /**
     * @brief Set la colonne du Square
     * 
     * @param Carr 
     */
    void set_colonne(int Carr);
    /**
     * @brief Set la ligne du Square
     * 
     * @param Larr 
     */
    void set_ligne(int Larr);
};
/**
 * @brief fonction qui return la valeur absolue.
 * 
 * @param a 
 * @return int 
 */
int absolue(int a);