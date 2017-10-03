#ifndef CREATUREMANAGER_H
#define CREATUREMANAGER_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QTableView>

namespace Ui {
class CreatureManager;
}

class CreatureManager : public QDialog
{
    Q_OBJECT

public:
    explicit CreatureManager(QWidget *parent = 0);
    ~CreatureManager();

private slots:
    void on_createCreature_clicked();

    void on_deleteCreature_clicked();

private:
    Ui::CreatureManager *ui;
    QSqlTableModel *model;
    QSqlQuery *query;
};

#endif // CREATUREMANAGER_H
