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
#include <QSqlRecord>

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

    this->updateCreatures();
    this->lockSubbuttons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCreatures()
{
    if (selectedLocation == -1) {
        return;
    }

    query->prepare("SELECT location_creature.location, location_creature.creature, creature.id AS id, creature.name AS name FROM location_creature, creature WHERE location_creature.creature = creature.id AND location_creature.location = :location");
    query->bindValue(":location", selectedLocation);
    query->exec();

    ui->viewCreature->clear();

    while (query->next()) {
        QSqlRecord record = query->record();
        ui->viewCreature->addItem(record.value("name").toString());
    }
}

void MainWindow::lockSubbuttons()
{
    ui->addCreature->setDisabled(true);
    ui->removeCreature->setDisabled(true);
    ui->addSublocation->setDisabled(true);
    ui->removeSublocation->setDisabled(true);
}

void MainWindow::unlockSubbuttons()
{
    ui->addCreature->setDisabled(false);
    ui->removeCreature->setDisabled(false);
    ui->addSublocation->setDisabled(false);
    ui->removeSublocation->setDisabled(false);
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

        this->updateCreatures();
        this->unlockSubbuttons();
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
    dialog.setOptions(selectedLocation);
    if (dialog.exec() == QDialog::Accepted) {
        query->prepare("INSERT INTO location_creature (location, creature) VALUES (:location, :creature)");
        query->bindValue(":location", selectedLocation);
        query->bindValue(":creature", dialog.creature);
        query->exec();
        this->updateCreatures();
    }
}

void MainWindow::on_removeCreature_clicked()
{

}
