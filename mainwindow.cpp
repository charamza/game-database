#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creaturemanager.h"
#include "locationdialog.h"
#include "sublocationdialog.h"
#include "creaturedialog.h"
#include <QSqlError>
#include <QItemSelectionModel>
#include <QDebug>
#include <QModelIndex>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../GameDatabase/world.db");
    db.open();

    query = new QSqlQuery();

    locations = new QSqlTableModel(this);
    locations->setTable("location");
    locations->select();
    locations->setHeaderData(1, Qt::Horizontal, "Název");
    locations->setHeaderData(2, Qt::Horizontal, "Potřebný level");
    ui->viewLocation->setModel(locations);
    ui->viewLocation->hideColumn(0);
    ui->viewLocation->setSelectionBehavior(QAbstractItemView::SelectRows);

    sublocations = new QSqlTableModel(this);
    sublocations->setTable("sublocation");
    sublocations->setHeaderData(2, Qt::Horizontal, "Název");
    ui->viewSublocation->setModel(sublocations);
    ui->viewSublocation->hideColumn(0);
    ui->viewSublocation->hideColumn(1);
    ui->viewSublocation->setSelectionBehavior(QAbstractItemView::SelectRows);

    creatures = new QSqlTableModel(this);
    creatures->setTable("location_creature");
    ui->viewCreature->setModel(creatures);
    ui->viewCreature->setSelectionBehavior(QAbstractItemView::SelectRows);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addLocation_clicked()
{
    LocationDialog dialog;
    if (dialog.exec() == QDialog::Accepted){
        query->prepare("INSERT INTO location (name, level) VALUES (:name, :level)");
        query->bindValue(":name", dialog.name);
        query->bindValue(":level", dialog.level);
        query->exec();
        locations->select();
    }
}

void MainWindow::on_removeLocation_clicked()
{
    this->removeRows(ui->viewLocation, locations, "location");
}

void MainWindow::removeRows(QTableView* view, QSqlTableModel* model, QString tablename)
{
    QItemSelectionModel *selection = view->selectionModel();
    if (selection->selectedRows().count() > 0) {
        QString sql = "DELETE FROM " + tablename + " WHERE id IN (";
        for (int i = 0; i < selection->selectedRows().count(); i++) {
            QModelIndex index = selection->selectedRows().at(i);
            if (i != 0) {
                sql+=", ";
            }
            sql+= QString::number(model->data(index).toInt());
        }
        sql+=")";
        query->prepare(sql);
        query->exec();
        model->select();
    } else {
        QMessageBox::warning(this, "Chyba", "Nevybral jsi žádné prvky ke smazání.");
    }
}

void MainWindow::on_addSublocation_clicked()
{
    SublocationDialog dialog;
    if (dialog.exec() == QDialog::Accepted){
        query->prepare("INSERT INTO sublocation (location, name) VALUES (:location, :name)");
        query->bindValue(":location", selectedLocation);
        query->bindValue(":name", dialog.name);
        query->exec();
        sublocations->select();
    }
}

void MainWindow::on_removeSublocation_clicked()
{
    this->removeRows(ui->viewSublocation, sublocations, "sublocation");
}

void MainWindow::on_viewLocation_clicked(const QModelIndex &index)
{
    QItemSelectionModel *selection = ui->viewLocation->selectionModel();
    int count = selection->selectedRows().length();
    if (count > 0) {
        QModelIndex index = selection->selectedRows().at(0);
        selectedLocation = locations->data(index).toInt();
        QString id = QString::number(selectedLocation);

        sublocations->setFilter("location = " + id);
        sublocations->select();

        creatures->setFilter("location = " + id);
        creatures->select();
    } else {

    }
}

void MainWindow::on_manageCreatures_clicked()
{
    CreatureManager manager;
    manager.exec();
}

void MainWindow::on_addCreature_clicked()
{
    CreatureDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        query->prepare("INSERT INTO location_creature (location, creature) VALUES (:location, :creature)");
        query->bindValue(":location", selectedLocation);
        query->bindValue(":creature", dialog.creature);
        query->exec();
        creatures->select();
    }
}

void MainWindow::on_removeCreature_clicked()
{

}
