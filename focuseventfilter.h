#ifndef FOCUSEVENTFILTER_H
#define FOCUSEVENTFILTER_H

#include <QObject>
#include <QKeyEvent>
#include <Qtwidgets>

class FocusEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit FocusEventFilter(QObject *parent = nullptr);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

signals:

public slots:
};

#endif // FOCUSEVENTFILTER_H
