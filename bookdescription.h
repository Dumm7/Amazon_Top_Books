#ifndef BOOKDESCRIPTION_H
#define BOOKDESCRIPTION_H

#include <QWidget>
#include "book.h"

namespace Ui {
class BookDescription;
}

class BookDescription : public QWidget
{
    Q_OBJECT

public:
    explicit BookDescription(QWidget *parent = nullptr);
    ~BookDescription();
    void setBook(Book book);
    void setUserIsLogIn(bool isLogin);
    void setIsOnlyMyBook(bool isOnlyMy);

signals:
    void removeBookFromRead(int bookId, bool isOnlyMy);
    void addBookToRead(int bookId, bool isOnlyMy);

private slots:
    void on_pbAdd_clicked();

    void on_pbRemove_clicked();

private:
    Ui::BookDescription *ui;
    Book book;
    bool userIsLogIn = false;
    bool isOnlyMyBook = false;
};

#endif // BOOKDESCRIPTION_H
