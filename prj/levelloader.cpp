#include "levelloader.h"
#include "EasyBMP.h"

//--------------------------------------------------------------

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{
}

//--------------------------------------------------------------

bool LevelLoader::loadLevelFiles( LevelData& levelData, const char* layoutFile, const char* descriptionFile )
{
    if ( !layoutFile || !layoutFile[0] || !descriptionFile || !descriptionFile[0] )
        return false;

    loadLayoutFile( levelData, layoutFile );
    loadDescriptionFile( levelData, descriptionFile );

    return true;
}

//--------------------------------------------------------------


bool LevelLoader::loadLayoutFile( LevelData& levelData, const char* layoutFile )
{
    BMP layout;
    layout.ReadFromFile( layoutFile );

    if ( layout.TellHeight() <= 0 || layout.TellWidth() <= 0 )
        return false;

    levelData.layout.init( layout.TellWidth(), layout.TellHeight() );
    for ( int i = 0; i < layout.TellHeight(); ++i )
    {
        for ( int q = 0; q < layout.TellWidth(); ++q )
        {
            levelData.layout.data[i][q].r = layout.GetPixel( i, q ).Red;
            levelData.layout.data[i][q].g = layout.GetPixel( i, q ).Green;
            levelData.layout.data[i][q].b = layout.GetPixel( i, q ).Blue;
        }
    }

    return true;
}

bool LevelLoader::loadDescriptionFile( LevelData& levelData, const char* descriptionFile )
{
    std::map< std::string, SBaseItem* > classes;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file( descriptionFile );
    if ( !result )
        return false;

    pugi::xml_node levelNode   = doc.child( "level" );
    pugi::xml_node classesNode = levelNode.child( "classes" );
    
    for ( pugi::xml_node node = classesNode.first_child(); node; node = node.next_sibling() )
    {
        const char* tag = node.name();
        if ( !tag || !tag[0] )
            continue;

        const char* className = node.attribute( "class" ).value();
        if ( !className || !className[0] )
            continue;

        SBaseItem* item = 0;
        if ( 0 == strcmp( tag, "free" ) )
            item = new SFreeItem;
        if ( 0 == strcmp( tag, "block" ) )
            item = new SBlockItem;
        if ( 0 == strcmp( tag, "hero" ) )
            item = new SHeroItem;
        if ( 0 == strcmp( tag, "check" ) )
            item = new SCheckpointItem;
        if ( 0 == strcmp( tag, "platform" ) )
            item = new SPlatformItem;
        if ( 0 == strcmp( tag, "gun" ) )
            item = new SGunItem;
        if ( 0 == strcmp( tag, "spikes" ) )
            item = new SSpikesItem;
        if ( 0 == strcmp( tag, "finish" ) )
            item = new SFinishItem;
        if ( 0 == strcmp( tag, "sprite" ) )
            item = new SSpriteItem;

        if ( item )
        {
            item->readXMLNode( node );
            classes[ className ] = item;
        }
    }

    pugi::xml_node objectsNode = levelNode.child( "objects" );
    for ( pugi::xml_node node = objectsNode.first_child(); node; node = node.next_sibling() )
    {
        int x = node.attribute("r").as_int(-1);
        int y = node.attribute("g").as_int(-1);
        int z = node.attribute("b").as_int(-1);

        if ( x < 0 || y < 0 || z < 0 )
            continue;
            
        for ( pugi::xml_node classNode = node.first_child(); classNode; classNode = classNode.next_sibling() )
        {
            const char* className = classNode.text().as_string();
            if ( !className || !className[0] )
                continue;

            auto foundClass = classes.find( className );
            if ( foundClass == classes.end() )
                continue;

            SElemIdx elemIdx( x, y, z );
            auto foundObj = levelData.objects.find( elemIdx );
            if ( foundObj == levelData.objects.end() )
            {
                GameObject* gameObj = new GameObject;
                gameObj->addClass( foundClass->second );
                levelData.objects[ elemIdx ] = gameObj;
            }
            else
            {
                foundObj->second->addClass( foundClass->second );
            }
        }        
    }
}

//--------------------------------------------------------------
