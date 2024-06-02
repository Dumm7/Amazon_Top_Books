
#include "book.h"

Book::Book() {}

void Book::setId(const int id) {
    this->id = id;
}


QString Book::getName() const {
    return name;
}

void Book::setName(const QString &name) {
    this->name = name;
}

QString Book::getAuthor() const {
    return author;
}

void Book::setAuthor(const QString &author) {
    this->author = author;
}

QString Book::getGenre() const {
    return genre;
}

void Book::setGenre(const QString &genre) {
    this->genre = genre;
}

double Book::getPrice() const {
    return price;
}

void Book::setPrice(double price) {
    this->price = price;
}

int Book::getYear() const {
    return year;
}

void Book::setYear(int year) {
    this->year = year;
}

double Book::getRating() const {
    return rating;
}

void Book::setRating(double rating) {
    this->rating = rating;
}

int Book::getReviewsCount() const {
    return reviewsCount;
}

void Book::setReviewsCount(int reviewsCount) {
    this->reviewsCount = reviewsCount;
}

void Book::setIsRead(const bool value) {
    this->isReadBook = value;
}

void Book::setDescription(QString description) {
    this->description = description;
}

void Book::setImagePath(const QString value) {
    this->imagePath = value;
}
