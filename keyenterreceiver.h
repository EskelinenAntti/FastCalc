#ifndef KEYENTERRECEIVER_H
#define KEYENTERRECEIVER_H

#include <QObject>

class keyEnterReceiver : public QObject
{
    Q_OBJECT
public:
    explicit keyEnterReceiver(QObject *parent = nullptr);

signals:

public slots:
};

#endif // KEYENTERRECEIVER_H
