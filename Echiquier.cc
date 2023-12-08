#include "Echiquier.hpp"

#define NBCOL 8

Echiquier::Echiquier()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            echiquier[i][j] = nullptr;
        }
    }

    echiquier[0][0] = new Tour(Blanc, "\u2656", Square(0, 0));
    echiquier[0][1] = new Cavalier(Blanc, "\u2658", Square(0, 1));
    echiquier[0][2] = new Fou(Blanc, "\u2657", Square(0, 2));
    echiquier[0][3] = new Dame(Blanc, "\u2655", Square(0, 3));
    echiquier[0][4] = new Roi(Blanc, "\u2654", Square(0, 4));
    echiquier[0][5] = new Fou(Blanc, "\u2657", Square(0, 5));
    echiquier[0][6] = new Cavalier(Blanc, "\u2658", Square(0, 6));
    echiquier[0][7] = new Tour(Blanc, "\u2656", Square(0, 7));
    echiquier[7][0] = new Tour(Noir, "\u265C", Square(7, 0));
    echiquier[7][1] = new Cavalier(Noir, "\u265E", Square(7, 1));
    echiquier[7][2] = new Fou(Noir, "\u265D", Square(7, 2));
    echiquier[7][3] = new Dame(Noir, "\u265B", Square(7, 3));
    echiquier[7][4] = new Roi(Noir, "\u265A", Square(7, 4));
    echiquier[7][5] = new Fou(Noir, "\u265D", Square(7, 5));
    echiquier[7][6] = new Cavalier(Noir, "\u265E", Square(7, 6));
    echiquier[7][7] = new Tour(Noir, "\u265C", Square(7, 7));

    // allocation des pions
    for (unsigned char i(0); i < NBCOL; i++)
    {
        echiquier[1][i] = new Pion(Blanc, "\u2659", Square(1, i));
        echiquier[6][i] = new Pion(Noir, "\u265F", Square(6, i));
    }
}
void Echiquier::affiche() const
{
    string space5 = string(5, ' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    " << endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i(NBCOL - 1); i >= 0; i--)
    {
        cout << i + 1 << " ";
        for (int j(0); j < NBCOL; j++)
        {
            cout << "|";
            if (echiquier[i][j])
            {
                cout << "\u0020\u0020";
                echiquier[i][j]->affiche();
                cout << "\u0020"
                     << " ";
            }
            else
                cout << space5; // 2 ascii spaces
        }
        cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
        cout << endl;
    }
}
Echiquier::~Echiquier()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (echiquier[i][j])
            {
                delete echiquier[i][j];
            }
        }
    }
}

string Echiquier::get_nom(Square dep) const
{
    return echiquier[dep.get_ligne()][dep.get_colonne()]->get_nom();
}


bool Echiquier::chk_non_vide(Square arr) const
{
    if (echiquier[arr.get_ligne()][arr.get_colonne()] == NULL)
    {
        return 0;
    }
    return 1;
}

int Echiquier::dep_imp(int Ldep, int Cdep, int Larr, int Carr, Couleur couleur, int deplacement)
{
    if (!echiquier[Ldep][Cdep])
    {
        if (deplacement)
            cout << "coup invalide, il n'y a pas de pièce sur cette case" << endl;
        return 1;
    }
    if (echiquier[Ldep][Cdep]->get_couleur() != couleur)
    {
        if (deplacement)
            cout << "cette pièce ne vous appartient pas" << endl;
        return 1;
    }
    if (echiquier[Larr][Carr])
    {
        if (echiquier[Larr][Carr]->get_couleur() == couleur)
        {
            if (deplacement)
                cout << "coup impossible, vous ne pouvez pas manger l'une de vos pièce" << endl;
            return 1;
        }
    }
    return 0;
}
void Echiquier::faire_deplacement(int Ldep, int Cdep, int Larr, int Carr, int prise_en_passante)
{
    if (prise_en_passante)
    {
        delete echiquier[Ldep][Carr];
        echiquier[Ldep][Carr] = nullptr;
    }
    else
    {
        if (echiquier[Larr][Carr] != NULL)
            delete echiquier[Larr][Carr];
    }
    echiquier[Larr][Carr] = echiquier[Ldep][Cdep];
    echiquier[Larr][Carr]->set_position(Larr, Carr);
    echiquier[Ldep][Cdep] = nullptr;
}

int Echiquier::deplacement_pion(int Ldep, int Cdep, int Larr,
                     int Carr, Square cp_pred_dep, Square cp_pred_arr,
                     int deplacement,
                     int danger)
{
    int impossible = 0;
    int prise_en_passante = 0;

    if (Ldep > Larr && Cdep == Carr)
    {
        if (danger)
        {
            impossible = 1;
        }
        else
        {
            for (int i = 1; i <= (Ldep - Larr); i++)
            {
                if (echiquier[Ldep - i][Cdep] != NULL)
                {
                    impossible = 1;
                }
            }
        }
    }
    else if (Ldep < Larr && Cdep == Carr)
    {
        if (danger)
        {
            impossible = 1;
        }
        else
        {
            for (int i = 1; i <= (Larr - Ldep); i++)
            {
                if (echiquier[Ldep + i][Cdep] != NULL)
                {
                    impossible = 1;
                }
            }
        }
    }

    else if (Ldep < Larr && Cdep != Carr)
    {
        if (echiquier[Larr][Carr] == NULL)
        {
            if (echiquier[Ldep][Carr] != NULL && (echiquier[Ldep][Carr]->get_nom() == "\u265F") && (cp_pred_dep.get_ligne() - cp_pred_arr.get_ligne() == 2) && (cp_pred_dep.get_colonne() == cp_pred_arr.get_colonne()) && (cp_pred_arr.get_ligne() == Ldep) && (cp_pred_arr.get_colonne() == Carr))
            {
                prise_en_passante = 1;
            }
            else if (danger)
            {
            }
            else
            {
                impossible = 2;
            }
        }
    }
    else if (Ldep > Larr && Cdep != Carr)
    {

        if (echiquier[Larr][Carr] == NULL)
        {
            if (echiquier[Ldep][Carr] != NULL && (echiquier[Ldep][Carr]->get_nom() == "\u2659") && (cp_pred_arr.get_ligne() - cp_pred_dep.get_ligne() == 2) && (cp_pred_dep.get_colonne() == cp_pred_arr.get_colonne()) && (cp_pred_arr.get_ligne() == Ldep) && (cp_pred_arr.get_colonne() == Carr))
            {
                prise_en_passante = 1;
            }
            else if (danger)
            {
            }
            else
            {
                impossible = 2;
            }
        }
    }

    if (impossible)
    {
        if (deplacement)
        {
            if (impossible == 1)
                cout << "il y a une pièce sur le chemin" << endl;
            else
                cout << "il n'y a pas de pièce à attaqué" << endl;
        }
        return 1;
    }
    if (deplacement == 1)
        faire_deplacement(Ldep, Cdep, Larr, Carr, prise_en_passante);
    return 0;
}

int Echiquier::deplacement_cavalier(int Ldep, int Cdep, int Larr, int Carr, int deplacement)
{
    if (deplacement == 1)
        faire_deplacement(Ldep, Cdep, Larr, Carr);
    return 0;
}

int Echiquier::deplacement_globale(int Ldep, int Cdep, int Larr, int Carr, int deplacement)
{
    int impossible = 0;
    if (Ldep > Larr && Cdep == Carr)
    {
        for (int i = 1; i < (Ldep - Larr); i++)
        {
            if (echiquier[Ldep - i][Cdep] != NULL)
            {
                impossible = 1;
            }
        }
    }
    else if (Larr > Ldep && Cdep == Carr)
    {
        for (int i = 1; i < (Larr - Ldep); i++)
        {
            if (echiquier[Ldep + i][Cdep] != NULL)
            {
                impossible = 1;
            }
        }
    }
    else if (Cdep > Carr && Ldep == Larr)
    {
        for (int i = 1; i < (Cdep - Carr); i++)
        {
            if (echiquier[Ldep][Cdep - i] != NULL)
            {
                impossible = 1;
            }
        }
    }
    else if (Carr > Cdep && Larr == Ldep)
    {
        for (int i = 1; i < (Carr - Cdep); i++)
        {
            if (echiquier[Ldep][Cdep + i] != NULL)
            {
                impossible = 1;
            }
        }
    }
    else if (Ldep > Larr && Cdep > Carr)
    {
        for (int i = 1; i < (Ldep - Larr); i++)
        {
            if (echiquier[Ldep - i][Cdep - i] != NULL)
            {
                impossible = 1;
            }
        }
    }
    else if (Ldep > Larr && Carr > Cdep)
    {
        for (int i = 1; i < (Ldep - Larr); i++)
        {
            if (echiquier[Ldep - i][Cdep + i] != NULL)
            {
                impossible = 1;
            }
        }
    }
    else if (Larr > Ldep && Carr > Cdep)
    {
        for (int i = 1; i < (Larr - Ldep); i++)
        {
            if (echiquier[Ldep + i][Cdep + i] != NULL)
            {
                impossible = 1;
            }
        }
    }
    else if (Larr > Ldep && Cdep > Carr)
    {
        for (int i = 1; i < (Larr - Ldep); i++)
        {
            if (echiquier[Ldep + i][Cdep - i] != NULL)
            {
                impossible = 1;
            }
        }
    }
    if (impossible)
    {
        if (deplacement)
            cout << "il y a une pièce sur le chemin" << endl;
        return 1;
    }
    if (deplacement == 1)
        faire_deplacement(Ldep, Cdep, Larr, Carr);
    return 0;
}

int Echiquier::deplace(Square depart, Square arrive, Couleur couleur, Square cp_pred_dep, Square cp_pred_arr, int deplacement, int danger)
{
    int Ldep = depart.get_ligne();
    int Cdep = depart.get_colonne();
    int Larr = arrive.get_ligne();
    int Carr = arrive.get_colonne();
    if (dep_imp(Ldep, Cdep, Larr, Carr, couleur, deplacement))
    {
        return 1;
    }
    if (!echiquier[Ldep][Cdep]->est_mouvement_legal(arrive))
    {
        if (echiquier[Ldep][Cdep]->get_nom() == "\u2658" || echiquier[Ldep][Cdep]->get_nom() == "\u265E")
        {
            deplacement_cavalier(Ldep, Cdep, Larr, Carr, deplacement);
        }
        else if (echiquier[Ldep][Cdep]->get_nom() == "\u2659" || echiquier[Ldep][Cdep]->get_nom() == "\u265F")
        {
            if (danger == 1)
            {
                if (deplacement_pion(Ldep, Cdep, Larr, Carr, cp_pred_dep, cp_pred_arr, deplacement, 1))
                {
                    return 1;
                }
            }
            else if (deplacement_pion(Ldep, Cdep, Larr, Carr, cp_pred_dep, cp_pred_arr, deplacement))
            {
                return 1;
            }
        }
        else
        {
            if (deplacement_globale(Ldep, Cdep, Larr, Carr, deplacement))
                return 1;
        }
    }
    else
    {
        if (deplacement)
            cout << "mouvement illégal avec cette pièce" << endl;
        return 1;
    }
    return 0;
}
void Echiquier::affiche_piece(Square dep)
{
    cout << echiquier[dep.get_ligne()][dep.get_ligne()]->get_nom() << endl;
}
/**
 * @brief verifie si le mouvement donné par le joueur Jcurr actuel est valable et s'il provoque un echec de son roi
 *
 * @param Jcurr
 * @param depart
 * @param arrive
 * @param cp_pred_dep
 * @param cp_pred_arr
 * @param deplacement
 * @return int
 */
int Echiquier::mvt_prod_echec(Couleur Jcurr, Square depart, Square arrive, Square cp_pred_dep, Square cp_pred_arr, int deplacement)
{
    int impossible = 0;
    impossible = deplace(depart, arrive, Jcurr, cp_pred_dep, cp_pred_arr, deplacement);
    if (impossible) // si 1, le déplacement est impossible
        return 2;   // pas besoin de cout car il y en à déjà eut un
    Piece *piece = echiquier[arrive.get_ligne()][arrive.get_colonne()];
    echiquier[arrive.get_ligne()][arrive.get_colonne()] = echiquier[depart.get_ligne()][depart.get_colonne()];
    echiquier[depart.get_ligne()][depart.get_colonne()] = nullptr;
    impossible = en_echec(Jcurr, cp_pred_dep, cp_pred_arr); // 1 si echec
    echiquier[depart.get_ligne()][depart.get_colonne()] = echiquier[arrive.get_ligne()][arrive.get_colonne()];
    echiquier[arrive.get_ligne()][arrive.get_colonne()] = piece;
    return impossible;
}


void Echiquier::promotion(Square arrive)
{
    char piece;
    int Larr = arrive.get_ligne();
    int Carr = arrive.get_colonne();
    if (Larr == 7 || Larr == 0)
    {
        if (echiquier[Larr][Carr]->get_nom() == "\u265F" || echiquier[Larr][Carr]->get_nom() == "\u2659")
        {
            do
            {
                cout << "un pion peut-être promu:tapez C(cavalier) ou F(fou) ou D(Dame) ou T(tour)";
                cin >> piece;
            } while (piece != 'C' && piece != 'F' && piece != 'D' && piece != 'T');
            Couleur couleur = echiquier[Larr][Carr]->get_couleur();
            delete echiquier[Larr][Carr];
            if (piece == 'C')
            {
                if (couleur == Blanc)
                {
                    echiquier[Larr][Carr] = new Cavalier(Blanc, "\u2658", arrive);
                }
                else
                {
                    echiquier[Larr][Carr] = new Cavalier(Noir, "\u265E", arrive);
                }
            }
            else if (piece == 'F')
            {
                if (couleur == Blanc)
                {
                    echiquier[Larr][Carr] = new Fou(Blanc, "\u2657", arrive);
                }
                else
                {
                    echiquier[Larr][Carr] = new Fou(Noir, "\u265D", arrive);
                }
            }
            else if (piece == 'D')
            {
                if (couleur == Blanc)
                {
                    echiquier[Larr][Carr] = new Dame(Blanc, "\u2655", arrive);
                }
                else
                {
                    echiquier[Larr][Carr] = new Dame(Noir, "\u265B", arrive);
                }
            }
            else
            {
                if (couleur == Blanc)
                {
                    echiquier[Larr][Carr] = new Tour(Blanc, "\u2656", arrive);
                }
                else
                {
                    echiquier[Larr][Carr] = new Tour(Noir, "\u265C", arrive);
                }
            }
        }
    }
}

void Echiquier::en_danger(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr)
{
    Couleur jouopp = Noir;
    if (Jcurr == Noir)
    {
        jouopp = Blanc;
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            danger[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                for (int l = 0; l < 8; l++)
                {
                    Square dep(i, j);
                    Square arr(k, l);
                    if (deplace(dep, arr, jouopp, cp_pred_dep, cp_pred_arr, 0, 1) == 0)
                    {
                        danger[k][l] = 1; // 1 = danger
                    }
                }
            }
        }
    }
}
/**
 * @brief fonction qui fait le petit roque si cela est possible
 * renvoie 0 si le petit roque est fait, 1 sinon
 *
 * @param Jcurr
 * @param cp_pred_dep
 * @param cp_pred_arr
 * @return int
 */
int Echiquier::petit_roque(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr)
{
    bool impossible = 1;
    en_danger(Jcurr, cp_pred_dep, cp_pred_arr);
    if (Jcurr == Blanc)
    {
        if (echiquier[0][4] != NULL && echiquier[0][7] != NULL && // vrai ici tout
            echiquier[0][4]->get_nom() == "\u2654" &&
            echiquier[0][4]->get_a_bouger() == 0 &&
            echiquier[0][7]->get_nom() == "\u2656" &&
            echiquier[0][7]->get_a_bouger() == 0 &&
            echiquier[0][6] == NULL &&
            echiquier[0][5] == NULL)
        {
            en_danger(Jcurr, cp_pred_dep, cp_pred_arr);
            if (danger[0][5] == 0 && danger[0][6] == 0)
            {
                faire_deplacement(0, 4, 0, 6);
                faire_deplacement(0, 7, 0, 5);
                impossible = 0;
            }
        }
    }
    else if (Jcurr == Noir)
    {

        if (echiquier[7][4] != NULL && echiquier[7][7] != NULL &&
            echiquier[7][4]->get_nom() == "\u265A" &&
            echiquier[7][4]->get_a_bouger() == 0 &&
            echiquier[7][7]->get_nom() == "\u265C" &&
            echiquier[7][7]->get_a_bouger() == 0 &&
            echiquier[7][6] == NULL &&
            echiquier[7][5] == NULL)
        {
            en_danger(Jcurr, cp_pred_dep, cp_pred_arr);
            if (danger[7][5] == 0 && danger[7][6] == 0)
            {
                faire_deplacement(7, 4, 7, 6);
                faire_deplacement(7, 7, 7, 5);
                impossible = 0;
            }
        }
    }
    if (impossible)
        cout << "petit roque impossible" << endl;
    return impossible;
}


int Echiquier::grand_roque(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr)
{
    bool impossible = 1;
    en_danger(Jcurr, cp_pred_dep, cp_pred_arr);
    if (Jcurr == Blanc)
    {
        if (echiquier[0][4] != NULL &&
            echiquier[0][0] != NULL &&
            echiquier[0][4]->get_nom() == "\u2654" &&
            echiquier[0][4]->get_a_bouger() == 0 &&
            echiquier[0][0]->get_nom() == "\u2656" &&
            echiquier[0][0]->get_a_bouger() == 0 &&
            echiquier[0][1] == NULL &&
            echiquier[0][2] == NULL &&
            echiquier[0][3] == NULL)
        {
            if (danger[0][2] == 0 && danger[0][3] == 0)
            {
                faire_deplacement(0, 4, 0, 2);
                faire_deplacement(0, 0, 0, 3);
                impossible = 0;
            }
        }
    }
    else if (Jcurr == Noir)
    {
        if (echiquier[7][4] != NULL &&
            echiquier[7][0] != NULL &&
            echiquier[7][4]->get_nom() == "\u265A" &&
            echiquier[7][4]->get_a_bouger() == 0 &&
            echiquier[7][0]->get_nom() == "\u265C" &&
            echiquier[7][0]->get_a_bouger() == 0 &&
            echiquier[7][1] == NULL &&
            echiquier[7][2] == NULL &&
            echiquier[7][3] == NULL)
        {
            if (danger[7][2] == 0 && danger[7][3] == 0)
            {
                faire_deplacement(7, 4, 7, 2);
                faire_deplacement(7, 0, 7, 3);
                impossible = 0;
            }
        }
    }
    if (impossible)
        cout << "grand roque impossible" << endl;
    return impossible;
}
int Echiquier::echec_et_mat(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                for (int l = 0; l < 8; l++)
                {
                    Square dep(i, j);
                    Square arr(k, l);
                    if (!mvt_prod_echec(Jcurr, dep, arr, cp_pred_dep, cp_pred_arr, 0))
                    {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
int Echiquier::en_echec(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr)
{
    en_danger(Jcurr, cp_pred_dep, cp_pred_arr);
    if (Jcurr == Blanc)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (echiquier[i][j] != NULL && echiquier[i][j]->get_nom() == "\u2654")
                {
                    return danger[i][j]; // 1 si echec, 0 sinon
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (echiquier[i][j] != NULL && echiquier[i][j]->get_nom() == "\u265A")
                {
                    return danger[i][j]; // 1 si echec, 0 sinon
                }
            }
        }
    }
    exit(1);
}
int Echiquier::pat(Couleur Jcurr, Square cp_pred_dep, Square cp_pred_arr)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                for (int l = 0; l < 8; l++)
                {
                    Square dep(i, j);
                    Square arr(k, l);
                    if (!mvt_prod_echec(Jcurr, dep, arr, cp_pred_dep, cp_pred_arr, 0))
                    {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
void Echiquier::affiche_fin(void) const
{
    string position;
    string name;
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (echiquier[i][j] != NULL)
            {
                name = echiquier[i][j]->get_nom();
                if (name == "\u2656")
                    position += "wR"; // Rook W
                else if (name == "\u2658")
                    position += "wN"; // Knight W
                else if (name == "\u2657")
                    position += "wB"; // Bishop W
                else if (name == "\u2655")
                    position += "wQ"; // Queen W
                else if (name == "\u2654")
                    position += "wK"; // King W
                else if (name == "\u2659")
                    position += "wP"; // Pawn W

                else if (name == "\u265C")
                    position += "bR"; // Rook B
                else if (name == "\u265E")
                    position += "bN"; // Knight B
                else if (name == "\u265D")
                    position += "bB"; // Bishop B
                else if (name == "\u265B")
                    position += "bQ"; // Queen B
                else if (name == "\u265F")
                    position += "bP"; // Pawn B
                else
                    position += "bK"; // King B
            }
            position += ',';
        }
    }
    cout << position << endl;
}

int Echiquier::prise_passante_possible(Couleur couleur, Square cp_pred_dep, Square cp_pred_arr)
{
    int Ldep = cp_pred_dep.get_ligne();
    int Cdep = cp_pred_dep.get_colonne();
    int Larr = cp_pred_arr.get_ligne();
    int Carr = cp_pred_arr.get_colonne();
    string pion_actuel;
    if(couleur == Noir)
        pion_actuel = "\u265F";
    else
        pion_actuel = "\u2659";
    if(echiquier[Larr][Carr] == NULL)
    {
        return 1;
    }
    if(echiquier[Larr][Carr]->get_nom() != "\u2659" && echiquier[Larr][Carr]->get_nom() != "\u265F")
    {        
        return 1;
    }
    if(absolue(Larr - Ldep) == 2 && Cdep == Carr )
    {
        if((Carr - 1) != -1 && echiquier[Larr][Carr - 1] != NULL && echiquier[Larr][Carr - 1]->get_nom() == pion_actuel)
        {
            return 0;
        }
        if( (Carr + 1) != 8 && echiquier[Larr][Carr + 1] != NULL && echiquier[Larr][Carr+1]->get_nom() == pion_actuel )
        {
            return 0;
        }
    }
    return 1;
}