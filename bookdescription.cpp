#include "bookdescription.h"
#include "ui_bookdescription.h"

BookDescription::BookDescription(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookDescription)
{
    ui->setupUi(this);
}

BookDescription::~BookDescription()
{
    delete ui;
}

void BookDescription::setBook(Book book) {
    this->book = book;
    ui->pbAdd->setVisible(!book.isRead() && userIsLogIn);
    ui->pbRemove->setVisible(book.isRead() && userIsLogIn);
    ui->lDescription->setText(this->book.getDescription());
    ui->lDescription->setWordWrap(true);
    QPixmap pixmap(this->book.getImagePath());
    ui->lImage->setPixmap(pixmap.scaled(ui->lImage->size(), Qt::KeepAspectRatioByExpanding));
}

void BookDescription::setUserIsLogIn(bool isLogin) {
    userIsLogIn = isLogin;
}

void BookDescription::setIsOnlyMyBook(bool isOnlyMy) {
    isOnlyMyBook = isOnlyMy;
}


void BookDescription::on_pbAdd_clicked() {
    book.setIsRead(false);
    ui->pbAdd->setVisible(false && userIsLogIn);
    ui->pbRemove->setVisible(true && userIsLogIn);
    emit addBookToRead(book.getId(), isOnlyMyBook);
}


void BookDescription::on_pbRemove_clicked() {
    book.setIsRead(true);
    ui->pbAdd->setVisible(true && userIsLogIn);
    ui->pbRemove->setVisible(false && userIsLogIn);
    emit removeBookFromRead(book.getId(), isOnlyMyBook);
}

