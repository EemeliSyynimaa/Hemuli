#ifndef CREATEHERO_H
#define CREATEHERO_H

#include <QWidget>
#include <QSqlDatabase>
#include <QListWidgetItem>
#include "hero.h"

class MainWindow;

namespace Ui {
class CreateHero;
}

class CreateHero : public QWidget
{
    Q_OBJECT

public:
    explicit CreateHero(QSqlDatabase& db, MainWindow* window);
    ~CreateHero();

    void init();
    void updateSummary();

    Hero hero;

    void changeTab(int i);

private slots:
    void on_raceWidget_itemDoubleClicked(QListWidgetItem*);
    void on_classWidget_itemDoubleClicked(QListWidgetItem*);
    void on_perksWidget_itemDoubleClicked(QListWidgetItem*);
    void on_nameWidget_textChanged(const QString &arg1);

    void on_strBox_valueChanged(QString arg1);
    void on_agiBox_valueChanged(QString arg1);
    void on_dexBox_valueChanged(QString arg1);
    void on_intBox_valueChanged(QString arg1);

    void on_SaveButton_clicked();
    void on_ageBox_valueChanged(const QString &arg1);
    void on_backButton_clicked();

private:
    Ui::CreateHero* ui;
    QSqlDatabase& db;
    MainWindow* window;

    int perk_index;
};

#endif // CREATEHERO_H
