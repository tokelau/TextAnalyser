#ifndef DICTITEM_H
#define DICTITEM_H

#include <QObject>
#include <QHash>
#include <QDebug>

class DictItem : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
//    Q_PROPERTY(QString path READ path NOTIFY pathChanged)
    Q_PROPERTY(QString prDate READ prDate NOTIFY prDateChanged)

    DictItem(QList<QString> data = QList<QString>(), QObject *parent = nullptr) : QObject(parent)
    {
        if (!data.isEmpty()) {
//            qDebug() << data;
            m_nName = data[0];
//            m_nPath = data[0];
            m_nPrDate = data[1];
        } else {

        }
    }

    QString m_nName;
//    QString m_nPath;
    QString m_nPrDate;

    QString name() const {
        return m_nName;
    }
//    QString path() const {
//        return m_nPath;
//    }
    QString prDate() const {
        return m_nPrDate;
    }
private:

signals:
    void nameChanged(QString);
//    void pathChanged(QString);
    void prDateChanged(QString);
public slots:
};

#endif // DICTITEM_H
