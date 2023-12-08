#include "Square.hpp"

int absolue(int a)
{
    if (a < 0)
    {
        return -a;
    }
    return a;
}

Square::Square(int ligne, int colonne) : ligne(ligne), colonne(colonne)
{}
Square::Square(string position) : ligne(position[1] - 49), colonne(position[0] - 97)
{}
int Square::get_ligne() const
{
    return ligne;
}
int Square::get_colonne() const
{
    return colonne;
}
void Square::set_colonne(int Carr)
{
    colonne = Carr;
}
void Square::set_ligne(int Larr)
{
    ligne = Larr;
}