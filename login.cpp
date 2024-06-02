#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QtSql/QSqlQuery>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login() {
    delete ui;
}

void Login::on_pbApplySignIn_clicked() {
    if (ui->leNameSignIn->text().isEmpty() ||
        ui->lePasswordSignIn->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Fill in all fields");
        return;
    }
    QSqlQuery query;
    query.prepare("SELECT id, password FROM users "
                  "WHERE username = :username");
    query.bindValue(":username", ui->leNameSignIn->text());
    if (query.exec() && query.next()) {
        int userId = query.value(0).toInt();
        QString storedPassword = query.value(1).toString();
        if (storedPassword == ui->lePasswordSignIn->text()) {
            emit loggedIn(userId);
            this->close();
        } else {
            QMessageBox::warning(this, "Error", "Invalid password");
        }
    } else {
        QMessageBox::warning(this, "Error",
                             "No user with this name was found");
    }
}


void Login::on_pbApplySignUp_clicked() {
    if (ui->leNameSignUp->text().isEmpty() ||
        ui->lePasswordSignUp->text().isEmpty() ||
        ui->leConfirmPasswordSignUp->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Fill in all fields");
        return;
    }
    if (ui->lePasswordSignUp->text() != ui->leConfirmPasswordSignUp->text()) {
        QMessageBox::warning(this, "Error", "Passwords don't match");
        return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) "
                  "VALUES (:username, :password)");
    query.bindValue(":username", ui->leNameSignUp->text());
    query.bindValue(":password", ui->lePasswordSignUp->text());
    if (query.exec()) {
        QSqlQuery queryId("SELECT last_insert_rowid()");
        queryId.next();
        int userId = query.lastInsertId().toInt();
        emit loggedIn(userId);
        this->close();
    } else {
        QMessageBox::warning(this, "Error",
                             "User with this name already exists");
    }
}

