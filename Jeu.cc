#include "Jeu.hpp"


Jeu::Jeu() : jcurr(Blanc), cp_pred_arr()
{}
void Jeu::affiche() const
{
    echiquier.affiche();
}

void Jeu::init_coup_initial()
{
    cp_pred_dep = "a1";
    cp_pred_arr = "a1";
    prise_passante_possible = 0;
}

void Jeu::init_nbr_coup()
{
    nbr_coup = 0;
}

void Jeu::init_historique(void)
{
    debut = new historique;
    debut->nbr_echiquier_pred = 1;
    debut->noeud_suivant = NULL;
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (echiquier.chk_non_vide(Square(i, j)) == 1)
            {
                debut->echiquier[i][j] = echiquier.get_nom(Square(i, j));
            }
        }
    }
}

void Jeu::creer_suite_historique(void)
{
    historique *nv_echiquier = new historique;
    nv_echiquier->noeud_suivant = NULL;
    debut->nbr_echiquier_pred = debut->nbr_echiquier_pred + 1;
    historique *ancien_echiquier;
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (echiquier.chk_non_vide(Square(i, j)) == 1)
            {
                nv_echiquier->echiquier[i][j] = echiquier.get_nom(Square(i, j));
            }
        }
    }
    ancien_echiquier = debut;
    while ((ancien_echiquier->noeud_suivant != NULL))
        ancien_echiquier = ancien_echiquier->noeud_suivant;
    ancien_echiquier->noeud_suivant = nv_echiquier;
}

void Jeu::free_historique()
{
    historique *a_supp = debut;
    historique *suivant;
    while (a_supp != NULL)
    {
        suivant = a_supp->noeud_suivant;
        delete a_supp;
        a_supp = suivant;
    }
}


int Jeu::regle_trois_coup()
{
    int nbr_coup_similaire = 0;
    int num_tester = 1;
    int similaire = 1;
    historique *a_tester = debut;
    historique *suite = debut->noeud_suivant;
    while (num_tester != debut->nbr_echiquier_pred)
    {
        for (int i = num_tester; i < debut->nbr_echiquier_pred; i++)
        {
            for (int k = 7; k >= 0; k--)
            {
                for (int l = 0; l < 8; l++)
                {
                    if (a_tester->echiquier[k][l] != suite->echiquier[k][l])
                    {
                        similaire = 0;
                        break;
                    }
                }
                if (!similaire)
                    break;
            }
            suite = suite->noeud_suivant;
            if (similaire)
                nbr_coup_similaire++;
            similaire = 1;
        }
        if (nbr_coup_similaire >= 3)
        {
            return 1;
        }
        nbr_coup_similaire = 0;
        num_tester++;
        a_tester = a_tester->noeud_suivant;
        suite = a_tester->noeud_suivant;
    }
    return 0;
}

void Jeu::affiche_bienvenu() const
{
    cout << endl;
    cout << "   Bienvenu dans le jeu d'echecs   " << endl << endl;
    cout << "Pour jouer, c'est plutôt simple! " << endl;
    cout << "Il faut écrire en notation algébrique." << endl;
    cout << "Ainsi on écrit les deux cases accollés, donc la case de départ et d'arrivée" << endl;
    cout << "sous la forme lettre (désigant la colonne) puis chiffre (désignant la ligne)";
    cout << " ex: a2a4 déplace le pion de la case a2 en a4 " << endl;
    cout << "Pour un petit roque tapez O-O" << endl;
    cout << "Pour un grand roque tapez O-O-O" << endl;
    cout << "tapez /quit si vous voulez quitter" << endl;
}

void Jeu::affiche_aide()
{
    cout << endl;
    cout << "** saisie incorrecte **" << endl
         << endl;
    cout << "Il faut écrire en notation algébrique." << endl;
    cout << "Ainsi on écrit les deux cases accollés, donc la case de départ et d'arrivée" << endl;
    cout << "sous la forme lettre (désigant la colonne) puis chiffre (désignant la ligne)";
    cout << " ex: a2a4 déplace le pion de la case a2 en a4" << endl;
    cout << "Pour un petit roque tapez O-O" << endl;
    cout << "Pour un grand roque tapez O-O-O" << endl;
    cout << "tapez /quit si vous voulez quitter" << endl;
}

bool Jeu::saisie_correcte(string const &cmd)
{
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd, mouvmtpattern);
}

bool Jeu::saisie_correcte_petitroque(string const &cmd)
{
    regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}

bool Jeu::saisie_correcte_grandroque(string const &cmd)
{
    regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}

int Jeu::jouer()
{
    string coup;
    string dep;
    string arr;
    int echec = 0;
    int sortir = 1;
    int e;

    if(prise_passante_possible == 1)
    {
        prise_passante_possible = 0;
        free_historique();
        init_historique();
    }
    if(echiquier.prise_passante_possible(jcurr,cp_pred_dep,cp_pred_arr) == 0)
    {
        prise_passante_possible = 1;
    }
    if (regle_trois_coup())
    {
        cout << "égalité par la regle des trois coups" << endl;
        return 0;
    }

    if (nbr_coup == 50)
    {
        cout << "il y a égalité car 50 coup ont été joué sans prise de pièce ni mouvement de piece" << endl;
        return 0;
    }
    echec = echiquier.en_echec(jcurr, cp_pred_dep, cp_pred_arr);
    if (echec)
    {
        if (echiquier.echec_et_mat(jcurr, cp_pred_dep, cp_pred_arr))
        {
            if (jcurr == Blanc)
                cout << "le joueur noir à gagner" << endl;
            else
                cout << "le joueur blanc à gagner" << endl;
            return 0;
        }
        if (jcurr == Blanc)
            cout << "Le roi blanc est en echec" << endl;
        else
            cout << "Le roi noir est en echec" << endl;
    }
    if (echiquier.pat(jcurr, cp_pred_dep, cp_pred_arr))
    {
        cout << "Il y a égalité car pat" << endl;
        return 0;
    }
    while (sortir)
    {
        if (jcurr == Blanc)
            cout << "joueur blanc veuillez saisir le coup à jouer: ";
        else
            cout << "joueur noir veuillez saisir le coup à jouer: ";
        cin >> coup;
        if (coup == "/quit")
        {
            return 0;
        }
        else
        {
            if (coup.length() == 4)
            {
                if (!saisie_correcte(coup))
                {
                    affiche_aide();
                    return 1;
                }
                else
                {
                    dep = coup.substr(0, 2);
                    arr = coup.substr(2, 2);
                }
                if ( (e = echiquier.mvt_prod_echec( jcurr, Square(dep), Square(arr), Square(cp_pred_dep), Square(cp_pred_arr) ) ) )
                {
                    if (e == 1)
                        cout << "met votre roi en echec" << endl;
                }
                else
                {
                    if (echiquier.get_nom(Square(dep)) == "\u2659" || echiquier.get_nom(Square(dep)) == "\u265F" || echiquier.chk_non_vide(arr) == 1)
                    {
                        nbr_coup = 0;
                    }
                    sortir = echiquier.deplace(Square(dep), Square(arr), jcurr, Square(cp_pred_dep), Square(cp_pred_arr));
                    if (!sortir)
                    {
                        creer_suite_historique();
                        cp_pred_dep = dep;
                        cp_pred_arr = arr;
                    }
                }
            }
            else if (coup.length() == 3)
            {
                if (echec == 1)
                {
                    cout << "roi en echec donc petit-roque impossible" << endl;
                }
                else if (!saisie_correcte_petitroque(coup))
                {
                    affiche_aide();
                    return 1;
                }
                else
                {
                    sortir = echiquier.petit_roque(jcurr, cp_pred_dep, cp_pred_arr);
                    if (!sortir)
                    {
                        free_historique();
                        init_historique();
                        cp_pred_dep = "a1";
                        cp_pred_arr = "a1";
                    }
                }
            }
            else if (coup.length() == 5)
            {
                if (echec == 1)
                {
                    cout << "roi en echec donc grand-roque impossible" << endl;
                }
                else if (!saisie_correcte_grandroque(coup))
                {
                    affiche_aide();
                    return 1;
                }
                else
                {
                    sortir = echiquier.grand_roque(jcurr, cp_pred_dep, cp_pred_arr);
                    if (!sortir)
                    {
                        free_historique();
                        init_historique();
                        cp_pred_dep = "a1";
                        cp_pred_arr = "a1";
                    }
                }
            }
            else
            {
                cout << "coup invalide " << endl;
                affiche_aide();
                return 1;
            }
        }
    }
    nbr_coup++;

    echiquier.promotion(Square(arr));
    if (jcurr == Blanc)
    {
        jcurr = Noir;
    }
    else
    {
        jcurr = Blanc;
    }
    return 1;
}
void Jeu::affiche_fin(void) const
{
    echiquier.affiche_fin();
}
