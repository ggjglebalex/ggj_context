#ifndef __GAME_OBJECT_H
#define __GAME_OBJECT_H

//--------------------------------------------------------------

#include "xmlitems.h"

#include <vector>

//--------------------------------------------------------------

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void addClass( SBaseItem* item );

    void update( int dt = 0 );

private:
    std::vector< SBaseItem* > m_classes;

};

//--------------------------------------------------------------
#endif
