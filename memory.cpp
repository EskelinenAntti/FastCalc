#include "memory.h"

Memory::Memory()
{
    Memory::clearMemory();
}

void Memory::addToMemory(QString calc)
{
    /**
      * Add a new item to mList.
      * @param calc: Calculation (without answer) to be added.
      */
    m_list.append(calc);

    // Update the index.
    m_index = m_list.size();

    // If new calculation is added, presume that the user is not browsing old
    // calculations.
    m_memoryIsActive = false;
}

QString Memory::loadPrev(QString currentCalc)
{   /**
      * Return previous calculation in the previous slot of
      * mList, if there is any.
      * @param currentCalc: Contents of a LineEdit-object.
      * @return PrevCalc: Previous calculation.
      * @return currentCalc: Same as @param currentCalc.
      */
    // Check if there are any items in the memory.
    if (m_list.size() > 0){
        if (m_index > 0){
            m_index -= 1;
        }

        // Check if the memory was already being browsed. If not, store the
        // currentCalc in cache.
        if (m_memoryIsActive == false){
           m_cache = currentCalc;
        }

        // Memory is atleast now being browsed if it already wasn't.
        m_memoryIsActive = true;

        QString prevCalc = m_list[m_index];

        return prevCalc;

    } else {
        return currentCalc;
    }
}


QString Memory::loadNext(QString currentCalc)
{
    /**
      * Return next calculation in the mList if there is any.
      * @param currentCalc: Input of a LineEdit-object.
      * @return currentCalc: Same as @param currentCalc.
      * @return cache: Calculation stored in cache.
      * @return mList[mIndex]: Next item in mList.
      */
    if (m_memoryIsActive){
        if (m_index < m_list.size()){
            m_index += 1;
        }
        if (m_index <= m_list.size() - 1){
            return m_list[m_index];
        } else if ( m_index == m_list.size() ){
            return m_cache;
        }
    } else {
        return currentCalc;
    }
}

void Memory::clearMemory()
{
    /**
      * Remove all items in the memory and update the mIndex.
      */
    m_list.clear();
    m_index = 0;
    m_memoryIsActive = false;
}

void Memory::deactivate()
{
    /**
      * Set the mIndex to the index of the last item in the mList. Also set
      * the memoryIsActive to false, because the user is not browsing the memory
      * anymore.
      */
    m_memoryIsActive = false;
    m_index = m_list.size();
}


