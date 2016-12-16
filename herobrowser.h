#ifndef HEROBROWSER_H
#define HEROBROWSER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QListWidgetItem>

class MainWindow;

namespace Ui {
class HeroBrowser;
}

class HeroBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit HeroBrowser(QSqlDatabase& db, MainWindow* window);
    ~HeroBrowser();

    void refresh();

private slots:
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_backButton_clicked();

private:
    Ui::HeroBrowser* ui;
    QSqlDatabase& db;
    MainWindow* window;
};

#endif // HEROBROWSER_H
