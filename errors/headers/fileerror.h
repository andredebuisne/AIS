#ifndef FILEERROR_H
#define FILEERROR_H

#include <QObject>

class FileError : public QObject
{
    Q_OBJECT
public:
    explicit FileError(int type = -1, QObject *parent = nullptr);

    int getType() const;
    void setType(int value);

    QString getMessage() const;

private:
    int type; //Type of error
    QString message;

signals:

public slots:
};

#endif // FILEERROR_H
