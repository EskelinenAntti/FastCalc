#include "memorylabel.h"

MemoryLabel::MemoryLabel(QWidget* parent,
                         Qt::WindowFlags f)
    : QLabel(parent){

}

MemoryLabel::~MemoryLabel(){}

void MemoryLabel::mousePressEvent(QMouseEvent* event){
    
    // Emit pointer to this object in clicked signal so the slot getting the
    // signal knows which object send the signal.
    emit clicked(this);
}
