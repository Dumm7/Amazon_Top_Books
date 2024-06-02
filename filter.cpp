#include "filter.h"
#include "ui_filter.h"

Filter::Filter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Filter)
{
    ui->setupUi(this);
    ui->sbYear2->setVisible(false);
    ui->line2->setVisible(false);
    ui->sbPrice2->setVisible(false);
    ui->line1->setVisible(false);
}

Filter::~Filter()
{
    delete ui;
}

void Filter::on_cbRangePrice_clicked(bool checked) {
    ui->sbPrice2->setVisible(checked);
    ui->line1->setVisible(checked);
}


void Filter::on_cbRangeYear_clicked(bool checked) {
    ui->sbYear2->setVisible(checked);
    ui->line2->setVisible(checked);
}


void Filter::on_pushButton_clicked() {
    int firstPriceValue = ui->sbPrice->value();
    int secondPriceValue = ui->cbRangePrice->isChecked() ? ui->sbPrice2->value() : 0;
    int firstYear = ui->sbYear->value();
    int secondYear = ui->cbRangeYear->isChecked() ? ui->sbYear2->value() : 0;

    QPair<int, int> prices = qMakePair(firstPriceValue, secondPriceValue);
    QPair<int, int> years = qMakePair(firstYear, secondYear);
    emit changedFilters(prices, years);
}

