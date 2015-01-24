#include "gameobject.h"

//--------------------------------------------------------------

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
    for ( SBaseItem* item : m_classes )
        delete item;
}

//--------------------------------------------------------------

void GameObject::addClass( SBaseItem* item )
{
    if ( item )
        m_classes.push_back( item );
}

//--------------------------------------------------------------

void GameObject::update( int dt )
{

}

//--------------------------------------------------------------
