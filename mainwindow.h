#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QTableView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateCreatures();
    void lockSubbuttons();
    void unlockSubbuttons();

private slots:
    void on_addLocation_clicked();

    void on_removeLocation_clicked();

    void on_addSublocation_clicked();

    void on_removeSublocation_clicked();

    void on_viewLocation_clicked(const QModelIndex &index);

    void on_manageCreatures_clicked();

    void on_addCreature_clicked();

    void on_removeCreature_clicked();

private:
    Ui::MainWindow *ui;
    void removeRows(QTableView* view, QSqlTableModel *model, QString tablename);
    QSqlQuery* query;
    QSqlTableModel *locations;
    QSqlTableModel *sublocations;
    QSqlTableModel *creatures;
    QSqlDatabase db;
    int selectedLocation = -1;
};

#endif // MAINWINDOW_H
