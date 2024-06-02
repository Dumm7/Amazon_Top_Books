#include "filteredbooks.h"
#include "ui_filteredbooks.h"

FilteredBooks::FilteredBooks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilteredBooks)
{
    ui->setupUi(this);
    filter = new Filter();
    ui->pbOnlyMy->setVisible(false);
}

FilteredBooks::~FilteredBooks()
{
    delete ui;
}

void FilteredBooks::setTitle(const QString &genre, const QString &author) {
    QString title = "Amazon Bestselling " + genre + " from " + author + " from 2009-2019";
    ui->lTitle->setText(title);
    ui->lTitle->setWordWrap(true);
}

void FilteredBooks::setFilteredBooks(QList<Book> books) {
    m_books = books;
    QStandardItemModel *model = new QStandardItemModel();
    for (auto book: books) {
        QString currentBookTitle = book.getName() + " " + book.getAuthor();
        QStandardItem *item = new QStandardItem(currentBookTitle);
        if (book.isRead() && !isOnlyMyBooks) {
            item->setBackground(Qt::green);
        }
        model->appendRow(item);
    }
    ui->listResult->setModel(model);
}

void FilteredBooks::updateBooksList() {

}

void FilteredBooks::setIsUserLoggin(const bool isLoggin) {
    m_isUserLoggin = isLoggin;
    if (m_isUserLoggin) {
        ui->pbOnlyMy->setVisible(true);
    }
}

void FilteredBooks::on_pbFilter_clicked() {
    connect(filter, &Filter::changedFilters, this, &FilteredBooks::onFilterChanged);
    filter->show();
}

void FilteredBooks::onFilterChanged(QPair<int, int> price, QPair<int, int> years) {
    filter->close();
    emit changedFilters(price, years);
}

void FilteredBooks::on_pbOnlyMy_clicked() {
    isOnlyMyBooks = !isOnlyMyBooks;
    if (isOnlyMyBooks) {
        ui->pbOnlyMy->setText("All");
    }
    else {
        ui->pbOnlyMy->setText("Only my");
    }
    emit reloadBooksList(isOnlyMyBooks);
}


void FilteredBooks::on_listResult_clicked(const QModelIndex &index) {
    emit openDescription(m_books[index.row()].getId());
}

