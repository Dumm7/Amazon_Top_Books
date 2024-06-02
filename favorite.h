#ifndef FAVORITE_H
#define FAVORITE_H

#include <QWidget>

namespace Ui {
class Favorite;
}

class Favorite : public QWidget
{
    Q_OBJECT

public:
    explicit Favorite(QWidget *parent = nullptr);
    ~Favorite();

    void addAuthors(const QSet<QString> &authors);
    void addGenres(const QSet<QString> &genres);
    QString getGenre() const;
    QString getAuthor() const;

signals:
    void onPbProceedClicked();

private slots:
    void on_cbGenre_currentTextChanged(const QString &arg1);

    void on_cbAuthor_currentTextChanged(const QString &arg1);

    void on_cbAnyGenre_clicked(bool checked);

    void on_cbAnyAuthor_clicked(bool checked);

    void on_pbProceed_clicked();

private:
    Ui::Favorite *ui;
    QString m_selectedAuthor;
    QString m_selectedGenre;
};

#endif // FAVORITE_H
