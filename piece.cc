#include "piece.hpp"

string Piece::get_nom() const
{
    return nom;
}
Square Piece::get_position() const
{
    return position;
}
Couleur Piece::get_couleur() const
{
    return couleur;
}
Piece::Piece(Couleur couleur, string nom, Square position) : nom(nom), couleur(couleur), position(position)
{}
void Piece::set_position(int Larr, int Carr)
{
    position.set_colonne(Carr);
    position.set_ligne(Larr);
    a_bouger = 1;
    return;
}
void Piece::affiche() const
{
    cout << nom;
}
bool Piece::get_a_bouger()
{
    return a_bouger;
}

Piece::~Piece()
{}

Tour::Tour(Couleur couleur, string nom, Square position) : Piece(couleur, nom, position)
{}
int Tour::est_mouvement_legal(Square arrive) const 
{
    if ((position.get_colonne() != arrive.get_colonne() && position.get_ligne() == arrive.get_ligne()) || (position.get_colonne() == arrive.get_colonne() && position.get_ligne() != arrive.get_ligne()))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

Fou::Fou(Couleur couleur, string nom, Square position) : Piece(couleur, nom, position)
{}

int Fou::est_mouvement_legal(Square arrive) const
{
    if (absolue(position.get_colonne() - arrive.get_colonne()) == absolue(position.get_ligne() - arrive.get_ligne()))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

Dame::Dame(Couleur couleur, string nom, Square position) : Piece(couleur, nom, position)
{
}
int Dame::est_mouvement_legal(Square arrive) const
{
    if ((position.get_colonne() != arrive.get_colonne() && position.get_ligne() == arrive.get_ligne()) || (position.get_colonne() == arrive.get_colonne() && position.get_ligne() != arrive.get_ligne()) || (absolue(position.get_colonne() - arrive.get_colonne()) == absolue(position.get_ligne() - arrive.get_ligne())))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

Roi::Roi(Couleur couleur, string nom, Square position) : Piece(couleur, nom, position)
{
}
int Roi::est_mouvement_legal(Square arrive) const
{
    if (
        ((absolue(position.get_colonne() - arrive.get_colonne()) == absolue(position.get_ligne() - arrive.get_ligne())) && ((absolue(position.get_colonne() - arrive.get_colonne())) == 1)) || ((absolue(position.get_colonne() - arrive.get_colonne()) == 1) && (absolue(position.get_ligne() - arrive.get_ligne()) == 0)) || ((absolue(position.get_ligne() - arrive.get_ligne()) == 1) && (absolue(position.get_colonne() - arrive.get_colonne()) == 0)))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

Cavalier::Cavalier(Couleur couleur, string nom, Square position) : Piece(couleur, nom, position)
{}
int Cavalier::est_mouvement_legal(Square arrive) const
{
    if ((absolue(position.get_colonne() - arrive.get_colonne()) == 2 && absolue(position.get_ligne() - arrive.get_ligne()) == 1) || (absolue(position.get_colonne() - arrive.get_colonne()) == 1 && absolue(position.get_ligne() - arrive.get_ligne()) == 2))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

Pion::Pion(Couleur couleur, string nom, Square position) : Piece(couleur, nom, position)
{
}
int Pion::est_mouvement_legal(Square arrive) const
{
    if (a_bouger == 1)
    {
        if ((position.get_ligne() - arrive.get_ligne() == -1 && position.get_colonne() - arrive.get_colonne() == 0 && couleur == Blanc) || (position.get_ligne() - arrive.get_ligne() == -1 && absolue(position.get_colonne() - arrive.get_colonne()) == 1 && couleur == Blanc) || (position.get_ligne() - arrive.get_ligne() == 1 && position.get_colonne() - arrive.get_colonne() == 0 && couleur == Noir) || (position.get_ligne() - arrive.get_ligne() == 1 && absolue(position.get_colonne() - arrive.get_colonne()) == 1 && couleur == Noir))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if ((position.get_ligne() - arrive.get_ligne() == -1 && position.get_colonne() - arrive.get_colonne() == 0 && couleur == Blanc) || (position.get_ligne() - arrive.get_ligne() == -2 && position.get_colonne() - arrive.get_colonne() == 0 && couleur == Blanc) || (position.get_ligne() - arrive.get_ligne() == -1 && absolue(position.get_colonne() - arrive.get_colonne()) == 1 && couleur == Blanc) || (position.get_ligne() - arrive.get_ligne() == 1 && position.get_colonne() - arrive.get_colonne() == 0 && couleur == Noir) || (position.get_ligne() - arrive.get_ligne() == 2 && position.get_colonne() - arrive.get_colonne() == 0 && couleur == Noir) || (position.get_ligne() - arrive.get_ligne() == 1 && absolue(position.get_colonne() - arrive.get_colonne()) == 1 && couleur == Noir))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}