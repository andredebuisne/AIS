#ifndef VIEWOBJECTWIDGET_H
#define VIEWOBJECTWIDGET_H

#include <QWidget>

class ViewObjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewObjectWidget(QWidget *parent = nullptr, QString filePath = nullptr, int objectId = -2);
    void createLayout();

private:
    QString filePath;
    int objectId;

signals:

public slots:
};

#endif // VIEWOBJECTWIDGET_H
