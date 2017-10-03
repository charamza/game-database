#include "creaturemanager.h"
#include "ui_creaturemanager.h"
#include "creaturecreatedialog.h"
#include <QMessageBox>

CreatureManager::CreatureManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatureManager)
{
    ui->setupUi(this);

    query = new QSqlQuery();

    model = new QSqlTableModel(this);
    model->setTable("creature");
    model->select();
    model->setHeaderData(1, Qt::Horizontal, "Název");
    model->setHeaderData(2, Qt::Horizontal, "Zlato");
    model->setHeaderData(3, Qt::Horizontal, "Zkušenosti");
    ui->viewCreature->setModel(model);
    ui->viewCreature->hideColumn(0);
    ui->viewCreature->setSelectionBehavior(QAbstractItemView::SelectRows);
}

CreatureManager::~CreatureManager()
{
    delete ui;
}

void CreatureManager::on_createCreature_clicked()
{
    CreatureCreateDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        query->prepare("INSERT INTO creature (name, golds, experiences) VALUES (:name, :gold, :exp)");
        query->bindValue(":name", dialog.name);
        query->bindValue(":gold", dialog.gold);
        query->bindValue(":exp", dialog.exp);
        query->exec();
        model->select();
    }
}

void CreatureManager::on_deleteCreature_clicked()
{
    QItemSelectionModel *selection = ui->viewCreature->selectionModel();
    if (selection->selectedRows().count() > 0) {
        QString sql = "DELETE FROM creature WHERE id IN (";
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
