#ifndef FILTEREDBOOKS_H
#define FILTEREDBOOKS_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMessageBox>
#include "book.h"
#include "filter.h"

namespace Ui {
class FilteredBooks;
}

class FilteredBooks : public QWidget
{
    Q_OBJECT

public:
    explicit FilteredBooks(QWidget *parent = nullptr);
    ~FilteredBooks();

    void setTitle(const QString &genre, const QString &author);
    void setFilteredBooks(QList<Book> books);
    void updateBooksList();
    void setIsUserLoggin(const bool isLoggin);

signals:
    void changedFilters(QPair<int, int> price, QPair<int, int> years);
    void reloadBooksList(bool isOnlyMy);
    void openDescription(int bookId);

private slots:
    void on_pbFilter_clicked();
    void onFilterChanged(QPair<int, int> price, QPair<int, int> years);

    void on_pbOnlyMy_clicked();

    void on_listResult_clicked(const QModelIndex &index);

private:
    Ui::FilteredBooks *ui;
    Filter *filter;
    QList<Book> m_books;
    bool m_isUserLoggin = false;
    bool isOnlyMyBooks = false;
};

#endif // FILTEREDBOOKS_H
