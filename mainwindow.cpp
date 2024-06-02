
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_favorite = new Favorite();
    m_fBooks = new FilteredBooks();
    ui->pbProceed->setEnabled(false);
    m_db = QSqlDatabase::database();
    m_login = new Login();
    initDatabase();
    ui->pbProceed->setEnabled(false);
    ui->lError->setVisible(false);
    m_path = QDir::currentPath() + "/BooksFile/books.csv";
    initBooks();
}

MainWindow::~MainWindow() {
    delete m_favorite;
    delete m_fBooks;
    delete m_login;
    delete ui;
}

void MainWindow::on_pbProceed_clicked() {
    this->hide();
    if (m_name.isEmpty() || m_name.trimmed().isEmpty()) {
        ui->lError->setVisible(true);
        return;
    }
    else {
        chooseFavoriteShow();
    }
}

bool MainWindow::compareBooks(const Book &book1, const Book &book2) {
    if (book1.getRating() != book2.getRating()) {
        return book1.getRating() > book2.getRating();
    }
    else {
        return book1.getReviewsCount() > book2.getReviewsCount();
    }
}

void MainWindow::setUserId(int userId) {
    this->m_userId = userId;
    ui->pbSignUpSignIn->setVisible(false);
    m_fBooks->setIsUserLoggin(true);
    initUsersBooks();
    this->hide();
    chooseFavoriteShow();
}

void MainWindow::sortBooks(QList<Book> &filteredBooks) {
    std::sort(filteredBooks.begin(), filteredBooks.end(), MainWindow::compareBooks);
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
        hasBooksTable = false;
        query3.exec("CREATE TABLE books (id INTEGER PRIMARY KEY, name TEXT, author TEXT, rating REAL, reviews INT, price INT, year INT, genre TEXT, description TEXT, image TEXT)");
    }
}

void MainWindow::initBooks() {
    if (!m_path.isEmpty() && !hasBooksTable) {
        // загружаем данные о книгах из выбранного файла
        QFile file(m_path);
        if (file.open(QIODevice::ReadOnly)) {

            QTextStream in(&file);
            in.readLine();
            int counter = 0;
            while (!in.atEnd()) {
                QStringList line = in.readLine().split(",");
                if (line.size() == 7) {
                    Book book;
                    book.setName(line[0]);
                    book.setAuthor(line[1]);
                    book.setRating(line[2].toDouble());
                    book.setReviewsCount(line[3].toInt());
                    book.setPrice(line[4].toInt());
                    book.setYear(line[5].toInt());
                    book.setGenre(line[6]);
                    book.setId(counter);
                    books[counter] = book;
                    counter++;
                    QSqlQuery query;
                    query.prepare("INSERT INTO books (id, name, author, rating, reviews, price, year, genre) "
                                  "VALUES (:id, :name, :author, :rating, :reviews, :price, :year, :genre)");
                    query.bindValue(":id", book.getId());
                    query.bindValue(":name", book.getName());
                    query.bindValue(":author", book.getAuthor());
                    query.bindValue(":rating", book.getRating());
                    query.bindValue(":reviews", book.getReviewsCount());
                    query.bindValue(":price", book.getPrice());
                    query.bindValue(":year", book.getYear());
                    query.bindValue(":genre", book.getGenre());
                    query.exec();
                }
            }
            file.close();
            ui->pbProceed->setEnabled(true);
        }
    }
    else {
        QSqlQuery query("SELECT id, name, author, rating, reviews, price, year, genre, description, image FROM books");

        while (query.next()) {
            Book book;
            book.setId(query.value(0).toInt());
            book.setName(query.value(1).toString());
            book.setAuthor(query.value(2).toString());
            book.setRating(query.value(3).toDouble());
            book.setReviewsCount(query.value(4).toInt());
            book.setPrice(query.value(5).toInt());
            book.setYear(query.value(6).toInt());
            book.setGenre(query.value(7).toString());
            book.setDescription(query.value(8).toString());
            QString imageName = query.value(9).toString();
            QString imagePath = QDir::currentPath() + "/Image/" + imageName;
            book.setImagePath(imagePath);
            books[book.getId()] = book;
        }
    }
}

void MainWindow::initUsersBooks() {
    if (m_userId != -1) {
        QSqlQuery query("SELECT bookId FROM user_read_books WHERE userId = " + QString::number(m_userId));

        while (query.next()) {
            int bookId = query.value(0).toInt();
            if (books.contains(bookId)) {
                Book book = books.value(bookId);
                book.setIsRead(true);
                books[bookId] = book;
                m_userReadingBooks.insert(bookId, book);
            }
        }
        m_fBooks->setIsUserLoggin(true);
    }
}

void MainWindow::chooseFavoriteShow() {
    QSet<QString> authors;
    QSet<QString> genres;
    for (auto book : books.values()) {
        authors.insert(book.getAuthor());
        genres.insert(book.getGenre());
    }
    m_favorite->addAuthors(authors);
    m_favorite->addGenres(genres);
    connect(m_favorite, &Favorite::onPbProceedClicked, this, &MainWindow::fBooksShow);
    m_favorite->show();
}

bool MainWindow::genreAndAuthorFilter(const Book &book, const QString &genre, const QString &author) {
    if (genre == "Any" && author == "Any") {
        return true;
    } else if (genre == "Any") {
        return book.getAuthor() == author;
    } else if (author == "Any") {
        return book.getGenre() == genre;
    } else {
        return book.getGenre() == genre && book.getAuthor() == author;
    }
}

bool MainWindow::priceAndYearFilter(const Book &book, int firstPriceValue, int secondPriceValue, int firstYear, int secondYear) {
    bool priceMatch = true;
    bool yearMatch = true;
    if (secondPriceValue == 0) {
        if (firstPriceValue != 0)
            priceMatch = book.getPrice() >= firstPriceValue;
    }
    else {
            if (firstPriceValue != 0)
                priceMatch =  book.getPrice() >= firstPriceValue && book.getPrice() <= secondPriceValue;
            else
                priceMatch = book.getPrice() <= secondPriceValue;

    }
    if (secondYear == 0) {
        if (firstYear != 0)
                yearMatch = book.getYear() >= firstYear;
    }
    else {
            if (firstYear != 0)
                yearMatch =  book.getYear() >= firstYear && book.getYear() <= secondYear;
            else
                yearMatch = book.getYear() <= secondYear;

    }
    return yearMatch && priceMatch;
}

void MainWindow::fBooksShow() {
    QList<Book> filteredBooks;
    std::copy_if(books.begin(), books.end(), std::back_inserter(filteredBooks),
                 [=](const Book &book) { return genreAndAuthorFilter(book, m_favorite->getGenre(), m_favorite->getAuthor()); });
    m_fBooks->setFilteredBooks(filteredBooks);
    m_filteredBooks = filteredBooks;
    connect(m_fBooks, &FilteredBooks::changedFilters, this, &MainWindow::onFilterChanged);
    connect(m_fBooks, &FilteredBooks::reloadBooksList, this, &MainWindow::onReloadBooksList);
    connect(m_fBooks, &FilteredBooks::openDescription, this, &MainWindow::showDescription);
    m_favorite->hide();
    m_fBooks->setTitle(m_favorite->getGenre(), m_favorite->getAuthor());
    m_fBooks->show();
}

void MainWindow::onFilterChanged(QPair<int, int> price, QPair<int, int> years) {
    int firstPriceValue = price.first;
    int secondPriceValue = price.second;
    int firstYear = years.first;
    int secondYear = years.second;
    QList<Book> filteredBooks;
    QList<Book> selectedBooks = m_filteredBooks;
    std::copy_if(selectedBooks.begin(), selectedBooks.end(), std::back_inserter(filteredBooks),
                 [=](const Book &book) { return priceAndYearFilter(book, firstPriceValue, secondPriceValue, firstYear, secondYear); });
    m_fBooks->setFilteredBooks(filteredBooks);
}

void MainWindow::onAddBookToRead(int bookId) {
    Book book = books.value(bookId);
    book.setIsRead(true);
    books[bookId] = book;
    m_userReadingBooks[bookId] = book;
    if (m_userId == -1) {
            QMessageBox::warning(this, "Error", "Sign up");
            return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO user_read_books (userId, bookId) "
                  "VALUES (:userId, :bookId)");
    query.bindValue(":userId", m_userId);
    query.bindValue(":bookId", bookId);
    query.exec();
    onReloadBooksList(false);
}

void MainWindow::onRemoveBookFromRead(int bookId, bool isOnlyMy) {
    m_userReadingBooks.remove(bookId);
    Book book = books.value(bookId);
    book.setIsRead(false);
    books[bookId] = book;
    QSqlQuery query;
    query.prepare("DELETE FROM user_read_books WHERE userId = :userId AND bookId = :bookId");
    query.bindValue(":userId", m_userId);
    query.bindValue(":bookId", bookId);
    query.exec();
    onReloadBooksList(isOnlyMy);
}


void MainWindow::on_pbSignUpSignIn_clicked() {
    connect(m_login, &Login::loggedIn, this, &MainWindow::setUserId);
    m_login->show();
}

void MainWindow::onReloadBooksList(bool isOnlyMy) {
    isOnlyMyBooks = isOnlyMy;
    QMap<int, Book> booksSelected = isOnlyMy ? m_userReadingBooks : books;
    QList<Book> filteredBooks;
    std::copy_if(booksSelected.begin(), booksSelected.end(), std::back_inserter(filteredBooks),
                 [=](const Book &book) { return genreAndAuthorFilter(book, m_favorite->getGenre(), m_favorite->getAuthor()); });
    m_fBooks->setFilteredBooks(filteredBooks);
    m_filteredBooks = filteredBooks;
}


void MainWindow::on_pbDone_clicked() {
    QString name = ui->leNameInputLine->text();
    if (name.isEmpty() || name.trimmed().isEmpty()) {
            ui->lError->setVisible(true);
            return;
    }
    m_name = name;
    ui->pbProceed->setEnabled(true);
}


void MainWindow::on_leNameInputLine_textChanged(const QString &arg1) {
    if (ui->lError->isVisible() && !arg1.isEmpty() && !arg1.trimmed().isEmpty())
            ui->lError->setVisible(false);
}

void MainWindow::showDescription(int bookId) {
    Book book = books.value(bookId);
    BookDescription *bookDescription = new BookDescription();
    bookDescription->setUserIsLogIn(m_userId != -1);
    bookDescription->setIsOnlyMyBook(isOnlyMyBooks);
    bookDescription->setBook(book);
    connect(bookDescription, &BookDescription::removeBookFromRead, this, &MainWindow::onRemoveBookFromRead);
    connect(bookDescription, &BookDescription::addBookToRead, this, &MainWindow::onAddBookToRead);
    bookDescription->show();
}

