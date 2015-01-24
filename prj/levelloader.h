#ifndef __LOGIC_LEVEL_H
#define __LOGIC_LEVEL_H

//--------------------------------------------------------------

#include "gameobject.h"
#include "xmlitems.h"
#include "pugixml.hpp"

#include <map>

//--------------------------------------------------------------

struct SElemIdx
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    bool operator<( const SElemIdx& idx ) const
    {
        if ( r < idx.r ) return true;
        else if ( g < idx.g ) return true;
        else if ( b < idx.b ) return true;

        return false;
    }

    SElemIdx( unsigned int r = 0, unsigned int g = 0, unsigned int b = 0 )
        : r(r)
        , g(g)
        , b(b)
    {}
};

//--------------------------------------------------------------

struct LevelData
{
    std::map< SElemIdx, GameObject* > objects;

    struct SLayout
    {
        SElemIdx** data;
        int width;
        int height;

        void clear()
        {
            if ( data )
                for ( int i = 0; i < height; ++i )
                    delete[] data[i];
            delete[] data;
            data = 0;
            width = 0;
            height = 0;
        }

        void init( int w, int h )
        {
            clear();
            width  = w;
            height = h;

            data = new SElemIdx*[ height ];
            for ( int i = 0; i < height; ++i )
                data[i] = new SElemIdx[ width ];
        }

        SLayout()
            : width(0)
            , height(0)
            , data(0)
        {}
        ~SLayout()
        {
            clear();
        }
    };
    SLayout layout;
};

//--------------------------------------------------------------

class LevelLoader
{
public:

public:
    LevelLoader();
    ~LevelLoader();

    bool loadLevelFiles( LevelData& levelData, const char* layoutFile, const char* descriptionFile );

private:
    bool loadLayoutFile( LevelData& levelData, const char* layoutFile );
    bool loadDescriptionFile( LevelData& levelData, const char* descriptionFile );
};

//--------------------------------------------------------------
#endif