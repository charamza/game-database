#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addLocation_clicked();

    void on_removeLocation_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQuery* query;
    QSqlTableModel *locations;
    QSqlTableModel *sublocations;
    QSqlDatabase db;
    int selectedLocation = -1;
};

#endif // MAINWINDOW_H
