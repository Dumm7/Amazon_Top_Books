#ifndef FILTER_H
#define FILTER_H

#include <QWidget>

namespace Ui {
class Filter;
}

class Filter : public QWidget
{
    Q_OBJECT

public:
    explicit Filter(QWidget *parent = nullptr);
    ~Filter();

signals:
    void changedFilters(QPair<int, int> price, QPair<int, int> years);

private slots:
    void on_cbRangePrice_clicked(bool checked);

    void on_cbRangeYear_clicked(bool checked);

    void on_pushButton_clicked();

private:
    Ui::Filter *ui;
};

#endif // FILTER_H
