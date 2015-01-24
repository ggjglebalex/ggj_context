#ifndef __XML_ITEMS_H
#define __XML_ITEMS_H

//--------------------------------------------------------------

#include "pugixml.hpp"

#include <string>

//--------------------------------------------------------------

struct SColor
{
    unsigned int r;
    unsigned int g;
    unsigned int b;

    SColor( unsigned int r = 0, unsigned int g = 0, unsigned int b = 0 )
        : r(r)
        , g(g)
        , b(b)
    {}
};

//--------------------------------------------------------------

enum EItemType
{
    BASE,
    FREE,
    BLOCK,
    HERO,
    CHECKPOINT,
    PLATFORM,
    GUN,
    SPIKES,
    FINISH,
    SPRITE
};

enum EActivationAct
{
    LEFT,
    RIGHT,
    LEFTRIGT,
    FALL,
    JUMP
};

//--------------------------------------------------------------

struct SBaseItem
{
    EItemType type;

    SBaseItem( EItemType type = BASE ): type( type ) {}
    
    bool operator<( const SBaseItem& item ) const { return type < item.type; }
    virtual void readXMLNode( const pugi::xml_node& node ) {}
};

//--------------------------------------------------------------

struct SFreeItem: SBaseItem
{
    SColor color;
    float speed;

    void readXMLNode( const pugi::xml_node& node ) override 
    {
        pugi::xml_node tempNode = node.child( "speed" );
        if ( tempNode )
            speed = tempNode.text().as_float(0.0f);

        tempNode = node.child( "color" );
        if ( tempNode )
        {
            color.r = tempNode.attribute("r").as_int(255);
            color.g = tempNode.attribute("g").as_int(255);
            color.b = tempNode.attribute("b").as_int(255);
        }
    }

    SFreeItem()
        : SBaseItem( FREE )
        , color( 255, 255, 255 )
        , speed(0.0f)
    {}
};

struct SBlockItem: SBaseItem
{
    SColor color;

    void readXMLNode( const pugi::xml_node& node ) override 
    {
        pugi::xml_node tempNode = node.child( "color" );
        if ( tempNode )
        {
            color.r = tempNode.attribute("r").as_int(0);
            color.g = tempNode.attribute("g").as_int(0);
            color.b = tempNode.attribute("b").as_int(0);
        }
    }

    SBlockItem()
        : SBaseItem( BLOCK )
        , color( 0, 0, 0 )
    {}
};

struct SHeroItem: SBaseItem
{
    SColor color;
    float speed;
	float jump;	
    bool isWASD;
	
    void readXMLNode( const pugi::xml_node& node ) override 
    {
        pugi::xml_node tempNode = node.child( "speed" );
        if ( tempNode )
            speed = tempNode.text().as_float(0.0f);

        tempNode = node.child( "jump" );
        if ( tempNode )
            jump = tempNode.text().as_float(0.0f);

        tempNode = node.child( "controls" );
        if ( tempNode )
            isWASD = 0 == strcmp( "WASD", tempNode.text().as_string() );

        tempNode = node.child( "color" );
        if ( tempNode )
        {
            color.r = tempNode.attribute("r").as_int(255);
            color.g = tempNode.attribute("g").as_int(255);
            color.b = tempNode.attribute("b").as_int(255);
        }
    }

    SHeroItem()
        : SBaseItem( HERO )
        , color( 0, 0, 0 )
        , speed(0.0f)
        , jump(0.0f)
        , isWASD( false )
    {}
};

struct SCheckpointItem: SBaseItem
{
    SCheckpointItem()
        : SBaseItem( CHECKPOINT )
    {}
};

struct SPlatformItem: SBaseItem
{
    SColor color;
    SColor activationColor;

    enum EMode 
    {
        ACTION,
        LINKED,
        ALWAYS
    };
    EMode mode;
    bool isHorizontal;
    int rangeX;
    int rangeY;

    enum EMoveMode
    {
        CYCLE,
        CYCLERET,
        ONEWAY
    };
    EMoveMode moveMode;
    float speed;
    bool isActiveOnStart;
    EActivationAct act;
    float scaler;

    SPlatformItem()
        : SBaseItem( PLATFORM )
        , isHorizontal( false )      
        , rangeX(0)
        , rangeY(0)
        , speed(0.0f)
        , isActiveOnStart(false)
        , scaler(0.0f)
    {}
};

struct SGunItem: SBaseItem
{
    enum EGunDir
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    EGunDir dir;
    float rate;
    float speed;
    SColor activationColor;
    EActivationAct act;

    SGunItem()
        : SBaseItem( GUN ) {}
};

struct SSpikesItem: SBaseItem
{
    SSpikesItem()
        : SBaseItem( SPIKES )
    {}
};

struct SFinishItem: SBaseItem
{
    SFinishItem()
        : SBaseItem( FINISH ) 
    {}
};

struct SSpriteItem: SBaseItem
{
    bool isStretched;
    int tilesizeX;
    int tilesizeY;
    std::string path;

    SSpriteItem()
        : SBaseItem( SPRITE ) 
        , isStretched( true )
        , tilesizeX(0)
        , tilesizeY(0)
    {}
};

//--------------------------------------------------------------
#endif
