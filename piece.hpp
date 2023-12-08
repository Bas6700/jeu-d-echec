#include "Square.hpp"

enum Couleur
{
    vide = 0,
    Blanc,
    Noir
};

/**
 * @brief Classe abstraite qui représente une pièce.
 * 
 */
class Piece
{
protected:
    string nom;
    Couleur couleur;
    Square position;
    bool a_bouger = 0;

public:
    /**
     * @brief Construct a new Piece object
     * 
     * @param couleur 
     * @param nom 
     * @param position 
     */
    Piece(Couleur couleur, string nom, Square position);
    /**
     * @brief Destroy the Piece object
     * 
     */
    virtual ~Piece() = 0;
    /**
     * @brief return le nom de la piece
     * 
     * @return string 
     */
    string get_nom() const;
    /**
     * @brief return la position de la piece.
     * 
     * @return Square 
     */
    Square get_position() const;
    /**
     * @brief return la couleur de la piece
     * 
     * @return Couleur 
     */
    Couleur get_couleur() const;
    /**
     * @brief Set la position de la pièce
     * 
     * @param Larr 
     * @param Carr 
     */
    void set_position(int Larr, int Carr);
    /**
     * @brief affiche le nom de la pièce dans le terminal
     * 
     */
    void affiche() const;
    /**
     * @brief fonction qui renvoie si la pièce a bougée.
     * 
     * @return true 
     * @return false 
     */
    bool get_a_bouger();
    /**
     * @brief fonction qui vérifie si le mouvement est légal pour la pièce.
     * 
     * @param arrive 
     * @return int 
     */
    virtual int est_mouvement_legal(Square arrive) const = 0;
};

/**
 * @brief classe concrète pour représenter une tour;
 * 
 */
class Tour : public Piece
{
public:
    /**
     * @brief Construct a new Tour object
     * 
     * @param couleur 
     * @param nom 
     * @param position 
     */
    Tour(Couleur couleur, string nom, Square position);
    /**
     * @brief fonction qui vérifie si le mouvement est légal pour la pièce.
     * 
     * @param arrive 
     * @return int 
     */
    int est_mouvement_legal(Square arrive) const override;
};

/**
 * @brief classe concrète pour représenter un Fou
 * 
 */
class Fou : public Piece
{
public:
    /**
     * @brief Construct a new Fou object
     * 
     * @param couleur 
     * @param nom 
     * @param position 
     */
    Fou(Couleur couleur, string nom, Square position);
    /**
     * @brief fonction qui vérifie si le mouvement est légal pour la pièce.
     * 
     * @param arrive 
     * @return int 
     */
    int est_mouvement_legal(Square arrive) const override;
};

/**
 * @brief classe concrète pour représenter une Dame.
 * 
 */
class Dame : public Piece
{
public:
    /**
     * @brief Construct a new Dame object
     * 
     * @param couleur 
     * @param nom 
     * @param position 
     */
    Dame(Couleur couleur, string nom, Square position);
    /**
     * @brief fonction qui vérifie si le mouvement est légal pour la pièce.
     * 
     * @param arrive 
     * @return int 
     */
    int est_mouvement_legal(Square arrive) const override;
};

/**
 * @brief classe concrète pour représenter un roi.
 * 
 */
class Roi : public Piece
{
public:
    /**
     * @brief Construct a new Roi object
     * 
     * @param couleur 
     * @param nom 
     * @param position 
     */
    Roi(Couleur couleur, string nom, Square position);
    /**
     * @brief fonction qui vérifie si le mouvement est légal pour la pièce.
     * 
     * @param arrive 
     * @return int 
     */
    int est_mouvement_legal(Square arrive) const override;
};

/**
 * @brief classe concrète pour représenter un Cavalier.
 * 
 */
class Cavalier : public Piece
{
public:
    /**
     * @brief Construct a new Cavalier object
     * 
     * @param couleur 
     * @param nom 
     * @param position 
     */
    Cavalier(Couleur couleur, string nom, Square position);
    /**
     * @brief fonction qui vérifie si le mouvement est légal pour la pièce.
     * 
     * @param arrive 
     * @return int 
     */
    int est_mouvement_legal(Square arrive) const override;
};

/**
 * @brief classe concrète pour représenter un Pion.
 * 
 */
class Pion : public Piece
{
public:
    /**
     * @brief Construct a new Pion object
     * 
     * @param couleur 
     * @param nom 
     * @param position 
     */
    Pion(Couleur couleur, string nom, Square position);
    /**
     * @brief fonction qui vérifie si le mouvement est légal pour la pièce.
     * 
     * @param arrive 
     * @return int 
     */
    int est_mouvement_legal(Square arrive) const override;
};