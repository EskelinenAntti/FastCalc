#ifndef MEMORY_H
#define MEMORY_H

#include <QObject>

/**
 * Store the old calculations in a QStringList and return them when needed.
 */
class Memory : public QObject
{
public:
    Memory();
    void addToMemory(QString calc);
    QString loadPrev(QString currentCalc);
    QString loadNext(QString currentCalc);
    void clearMemory();

    void deactivate();
private:
    // A list where all the calculations are stored.
    QStringList m_list;
    // Store the index of mList item that is being viewed.
    int m_index;
    // Last input in the LineEdit before the memory is being browsed.
    QString m_cache;
    // True, if the memory is being browsed. For example, if user is browsing
    // old calculations. This is set to false if for example a new calculation
    // is made or an old calculation is edited.
    bool m_memoryIsActive;
};

#endif // MEMORY_H
