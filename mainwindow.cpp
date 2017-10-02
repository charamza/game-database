#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "locationdialog.h"
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

    query = new QSqlQuery(db);

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
    QItemSelectionModel *selection = ui->viewLocation->selectionModel();
    if (selection->selectedRows().count() > 0) {
        QString sql = "DELETE FROM location WHERE id IN (";
        for (int i = 0; i < selection->selectedRows().count(); i++) {
            QModelIndex index = selection->selectedRows().at(i);
            if (i != 0) {
                sql+=", ";
            }
            sql+= QString::number(locations->data(index).toInt());
        }
        sql+=")";
        query->prepare(sql);
        query->exec();
        locations->select();
    } else {
        QMessageBox::warning(this, "Chyba", "Nevybral jsi žádné prvky ke smazání.");
    }
}
