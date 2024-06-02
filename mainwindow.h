
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "book.h"
#include "favorite.h"
#include "filteredbooks.h"
#include "login.h"
#include "bookdescription.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbProceed_clicked();

    void chooseFavoriteShow();

    void fBooksShow();

    void onFilterChanged(QPair<int, int> price, QPair<int, int> years);

    void onAddBookToRead(int bookId);

    void onRemoveBookFromRead(int bookId, bool isOnlyMy);

    void on_pbSignUpSignIn_clicked();

    void onReloadBooksList(bool isOnlyMy);

    void on_pbDone_clicked();

    void on_leNameInputLine_textChanged(const QString &arg1);

    void showDescription(int bookId);

private:
    bool genreAndAuthorFilter(const Book &book, const QString &genre, const QString &author);
    bool priceAndYearFilter(const Book &book, int firstPriceValue, int secondPriceValue, int firstYear, int secondYear);
    static bool compareBooks(const Book &book1, const Book &book2);
    void setUserId(int userId);
    void sortBooks(QList<Book> &filteredBooks);
    void initDatabase();
    void initBooks();
    void initUsersBooks();
    Ui::MainWindow *ui;
    QMap<int, Book> books;
    Favorite *m_favorite;
    FilteredBooks *m_fBooks;
    QList<Book> m_filteredBooks;
    QSqlDatabase m_db;
    Login *m_login;
    int m_userId = -1;
    QMap<int, Book> m_userReadingBooks;
    QString m_name;
    QString m_path;
    bool hasBooksTable = true;
    bool isOnlyMyBooks = false;
};

#endif // MAINWINDOW_H
