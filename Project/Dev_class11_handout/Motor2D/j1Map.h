#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "j1Object.h"

// ----------------------------------------------------
struct Properties
{
	struct Property
	{
		p2SString name;
		int value;
	};

	~Properties()
	{

		for (std::list<Property*>::iterator item = list.begin(); item != list.cend(); ++item) {
			RELEASE((*item));
		}
		list.clear();
	}

	int Get(const char* name, int default_value = 0) const;

	std::list<Property*>	list;
};

// ----------------------------------------------------
struct MapLayer
{
	p2SString	name;
	int			width;
	int			height;
	uint*		data;
	Properties	properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		if (x < 0)return 0;
		if (y < 0)return 0;
		return data[(y*width) + x];
	}
};

struct ObjectLayer {
	p2SString	name;
	Properties	properties;
	ObjectLayer() 
	{}

	~ObjectLayer()
	{
		
	}

};

// ----------------------------------------------------
struct TileSet
{
	SDL_Rect GetTileRect(int id) const;

	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	std::list <TileSet*>		tilesets;
	std::list <MapLayer*>		layers;
	std::list <ObjectLayer*>	objects;
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	iPoint MapToWorld(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;
	bool CreateWalkabilityMap(int& width, int& height, uchar** buffer) const;
	bool CreateEnemyMap(int& width, int& height, uchar** buffer) const;
	bool CreateEnemyPathMap(int& width, int& height, uchar** buffer) const;

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadObjectLayer(pugi::xml_node& node, ObjectLayer* layer, int height);
	bool LoadConnectedObjects(pugi::xml_node& node);
	bool LoadProperties(pugi::xml_node& node, Properties& properties);
	
	TileSet* GetTilesetFromTileId(int id) const;

public:

	MapData data;
	std::vector<MapLayer*> V_Colision;
	std::vector<MapLayer*> V_Logic;
	std::vector<MapLayer*> V_Enemies;
	std::vector<MapLayer*> V_PathEnemies;
	//MapLayer* Logic;

private:

	
	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};
static int I_CAMERAMARGINTILE = 16;
#endif // __j1MAP_H__