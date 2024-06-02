
#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Error",
                              "Failed to connect to the database");
        return 1;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
