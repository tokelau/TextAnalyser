#ifndef DICTITEM_H
#define DICTITEM_H

#include <QObject>
#include <QHash>
#include <QDebug>
#include <QList>

class DictItem : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString prDate READ prDate NOTIFY prDateChanged)

    DictItem(QList<QString> data = QList<QString>(), QObject *parent = nullptr) : QObject(parent)
    {
        if (!data.isEmpty()) {
            m_nName = data[0];
            m_nPrDate = data[1];
        }
    }

    QString m_nName;
    QString m_nPrDate;

    QString name() const {
        return m_nName;
    }
    QString prDate() const {
        return m_nPrDate;
    }
private:

signals:
    void nameChanged(QString);
    void prDateChanged(QString);
public slots:
};

#endif // DICTITEM_H
