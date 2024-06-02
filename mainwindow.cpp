#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_db = QSqlDatabase::database();
    initDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initDatabase() {
    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table' AND name='user_read_books'");
    if (!query.next()) {
        query.exec("CREATE TABLE user_read_books (userId INTEGER, bookId INTEGER)");
    }
    QSqlQuery query2("SELECT name FROM sqlite_master WHERE type='table' AND name='users'");
    if (!query2.next()) {
        query2.exec("CREATE TABLE users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)");
    }
    QSqlQuery query3("SELECT name FROM sqlite_master WHERE type='table' AND name='books'");
    if (!query3.next()) {
        query3.exec("CREATE TABLE books (id INTEGER PRIMARY KEY, name TEXT, author TEXT, rating REAL, reviews INT, price INT, year INT, genre TEXT, description TEXT, image TEXT)");
    }
}
