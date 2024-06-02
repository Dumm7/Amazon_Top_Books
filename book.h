#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
public:
    Book();

    int getId() const { return id; };
    void setId(const int id);

    QString getName() const;
    void setName(const QString &name);

    QString getAuthor() const;
    void setAuthor(const QString &author);

    QString getGenre() const;
    void setGenre(const QString &genre);

    double getPrice() const;
    void setPrice(double price);

    int getYear() const;
    void setYear(int year);

    double getRating() const;
    void setRating(double rating);

    int getReviewsCount() const;
    void setReviewsCount(int reviewsCount);

    bool isRead() const { return isReadBook; }
    void setIsRead(const bool value);

    QString getDescription() const { return description; }
    void setDescription(QString description);

    QString getImagePath() const { return imagePath; }
    void setImagePath(const QString value);

private:
    int id;
    QString name;
    QString author;
    QString genre;
    double price;
    int year;
    double rating;
    int reviewsCount;
    bool isReadBook = false;
    QString description;
    QString imagePath;
};

#endif // BOOK_H
