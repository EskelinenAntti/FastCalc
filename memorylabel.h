#ifndef MEMORYLABEL_H
#define MEMORYLABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

/**
 * A QLabel that emits "clicked(MemoryLabel*)"-signal when being clicked.
 */
class MemoryLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MemoryLabel(QWidget* parent = Q_NULLPTR,
                         Qt::WindowFlags f  = Qt::WindowFlags());
    ~MemoryLabel();

signals:
    void clicked(MemoryLabel*);

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MEMORYLABEL_H
