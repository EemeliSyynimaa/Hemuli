#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>

#include "herobrowser.h"
#include "createhero.h"

namespace Ui {
class MainWindow;
class HeroBrowser;
class CreateHero;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openMainMenu();
    void openHeroBrowser();
    void openCreateHero();

    void hideAll();


    HeroBrowser heroBrowser;
    CreateHero createHero;

private slots:
    void on_newButton_clicked();
    void on_browseButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

};

#endif // MAINWINDOW_H
