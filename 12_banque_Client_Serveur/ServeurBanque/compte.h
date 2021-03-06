#ifndef COMPTE_H
#define COMPTE_H
#include <QString>
#include <QtSql>



class compte
{
public:
    compte();
    ~compte();

    bool obtenirSolde(QString idCompte, QString &solde);
    bool obtenirTitulaire(QString idCompte, QString &titulaire);
    int EffectuerOperation(QString idCompte, QString montant, QString description);
    bool obtenirReleveCompte(QString idCompte, QString &releveCompte);



private:
    QSqlDatabase   dbBanque;  // la connexion au serveur MySQL base snirBanque
    bool connecte;
};

#endif // COMPTE_H
