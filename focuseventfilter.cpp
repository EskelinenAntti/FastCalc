#include "focuseventfilter.h".h"

const QString SQRT("√");

FocusEventFilter::FocusEventFilter(QObject *parent) : QObject(parent)
{

}

bool FocusEventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if ( event->type() == QEvent::FocusOut ) {
        QFocusEvent *focusEvent = static_cast<QFocusEvent*>(event);
        if ( focusEvent->lostFocus() ) {
            // Catch
            return true;
        } else
            return false;
    }
    return false;
}
