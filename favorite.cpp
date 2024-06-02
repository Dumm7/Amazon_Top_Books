#include "favorite.h"
#include "ui_favorite.h"

Favorite::Favorite(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Favorite)
{
    ui->setupUi(this);
}

Favorite::~Favorite()
{
    delete ui;
}

void Favorite::addAuthors(const QSet<QString> &authors) {
    if (!authors.isEmpty())
        ui->cbAuthor->addItems(authors.values());
}

void Favorite::addGenres(const QSet<QString> &genres) {
    if (!genres.isEmpty())
        ui->cbGenre->addItems(genres.values());
}

QString Favorite::getGenre() const {
    if (!m_selectedGenre.isEmpty() && !m_selectedGenre.trimmed().isEmpty())
        return m_selectedGenre;
}

QString Favorite::getAuthor() const {
    if (!m_selectedAuthor.isEmpty() && !m_selectedAuthor.trimmed().isEmpty())
        return m_selectedAuthor;
}

void Favorite::on_cbGenre_currentTextChanged(const QString &arg1) {
    m_selectedGenre = arg1;
}


void Favorite::on_cbAuthor_currentTextChanged(const QString &arg1) {
    m_selectedAuthor = arg1;
}


void Favorite::on_cbAnyGenre_clicked(bool checked) {
    if (checked) {
        ui->cbGenre->setEnabled(false);
        m_selectedGenre = "Any";
    }
    else {
        ui->cbGenre->setEnabled(true);
        m_selectedGenre = ui->cbGenre->currentText();
    }
}


void Favorite::on_cbAnyAuthor_clicked(bool checked) {
    if (checked) {
        ui->cbAuthor->setEnabled(false);
        m_selectedAuthor = "Any";
    }
    else {
        ui->cbAuthor->setEnabled(true);
        m_selectedAuthor = ui->cbAuthor->currentText();
    }
}


void Favorite::on_pbProceed_clicked() {
    emit onPbProceedClicked();
}

