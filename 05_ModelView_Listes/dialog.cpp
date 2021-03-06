#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    modele = new QStringListModel(this);


    // Pour construire le modèle, il faut procéder en 2 temps :
    // Etape 1 : Création des données
    QStringList list;

    // QStringList surcharge l'opérateur "<<"
    // pour vous permettre d'ajouter des éléments à l'intérieur simplement.

    list << "USA" << "France" << "Angleterre";

    // Toutefois il est aussi possible d'utiliser la méthode append()
    list.append("Chine");

    // Etape 2 ajout des données au modèle
    modele->setStringList(list);

    // Etape 3 associé la vue au modele
    ui->listView->setModel(modele);

    // Réglage des options
    // l'édition des items est declenchées si le clavier est pressé ou au double clique
    ui->listView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked );

    // la sélection multiple est autorisée
    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    ui->comboBox->setModel(modele);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonAjouter_clicked()
{
    // Ajouter un item à la fin de la liste

    // les méthodes rowCount et insertRows sont des virtuelles de la class QAbstractItemModel
    // Elles ont été reimplémentées dans QStringListModel
    // leurs noms apparaient en italic

    int ligneNb = modele->rowCount();
    modele->insertRows(ligneNb,1);
    QModelIndex index = modele->index(ligneNb);

    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);

}

void Dialog::on_pushButtonInserer_clicked()
{
    // Inserer un item à partir de la ligne courante du curseur
    int ligneNb = ui->listView->currentIndex().row();
    modele->insertRows(ligneNb,1);
    QModelIndex index = modele->index(ligneNb);

    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);
}

void Dialog::on_pushButtonEffacer_clicked()
{
    // Retirer un item

    qDebug() << " retirer !!";
    modele->removeRow(ui->listView->currentIndex().row());
}


void Dialog::on_pushButtonAfficher_clicked()
{
    // affiche les items sélectionnés dans une boite de dialogue

    QItemSelectionModel *selection = ui->listView->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    QString elementsSelectionnes;

    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = modele->data(listeSelections[i], Qt::DisplayRole);
        elementsSelectionnes += elementSelectionne.toString() + "<br />";
    }

    QMessageBox::information(this, "Eléments sélectionnés", elementsSelectionnes);
}
