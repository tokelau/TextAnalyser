#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include <QtCore>

//класс для отображения списка обработанных словарем файлов в виде кнопок
class ButtonItem: public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString fName READ fName NOTIFY fNameChanged)

    ButtonItem(QString data = "", QObject *parent = nullptr) : QObject(parent) {
        m_nFName = data;
    }

    QString m_nFName;

    QString fName() const {
        return m_nFName;
    }
signals:
    void fNameChanged(QString);
};

#endif // BUTTONITEM_H
