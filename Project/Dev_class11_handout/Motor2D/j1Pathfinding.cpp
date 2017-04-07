#include "j1Pathfinding.h"
#include "j1App.h"
#include "j1Textures.h"
#include "p2Log.h"
#include"Character.h"
#include"j1Map.h"
#include"j1Enemy.h"
///class Pathfinding ------------------
// Constructors =======================
j1Pathfinding::j1Pathfinding()
{
}

// Destructors ========================
j1Pathfinding::~j1Pathfinding()
{

}

//Game Loop ===========================
bool j1Pathfinding::Start()
{
	//Generate map cluster abstraction
	j1Timer timer;
	//cluster_abstraction = new ClusterAbstraction(App->map, 10);
	LOG("Cluster abstraction generated in %.3f", timer.ReadSec());

	//Load debug tiles trexture
	//path_texture = App->tex->Load("maps/path_tex.png");

	return true;
}

bool j1Pathfinding::CleanUp()
{
	
	RELEASE_ARRAY(path_nodes);
	return true;
}

void j1Pathfinding::SetMap(uint width, uint height)
{
	this->width = width;
	this->height = height;
	map_min_x = 0;
	map_min_y = 0;
	map_max_x = width;
	map_max_y = height;
	RELEASE_ARRAY(path_nodes);
	int size = width*height;
	path_nodes = new PathNode[size];

}

void j1Pathfinding::SetMapLimits(int position_x, int position_y, int width, int height)
{
	map_min_x = position_x;
	map_min_y = position_y;
	map_max_x = position_x + width;
	map_max_y = position_y + height;
}


//Functionality =======================
//Methods used during the paths creation to work with map data
bool j1Pathfinding::IsWalkable(const iPoint & destination) const
{
	bool ret = false;
	uchar t = GetTileAt(destination);
	if (t)
		int x = 0;
	return (t == NOT_COLISION_ID);
}

bool j1Pathfinding::CheckBoundaries(const iPoint & pos) const
{
	return (pos.x >= map_min_x && pos.x < map_max_x && pos.y >= map_min_y && pos.y < map_max_y);
}

uchar j1Pathfinding::GetTileAt(const iPoint & pos) const
{
	if (CheckBoundaries(pos))
		return GetValueMap(pos.x, pos.y);

	return NOT_COLISION_ID;
}

uchar j1Pathfinding::GetValueMap(int x, int y) const
{
	//In future we will have to adapt because with this enemies only can be in logic 0
	return App->map->V_Colision[0]->data[(y*width) + x];
}


PathNode* j1Pathfinding::GetPathNode(int x, int y)
{
	return &path_nodes[(y*width) + x];
}



std::vector<iPoint>* j1Pathfinding::SimpleAstar(const iPoint& origin, const iPoint& destination)
{

	int size = width*height;
	std::fill(path_nodes, path_nodes + size, PathNode(-1, -1, iPoint(-1, -1), nullptr));
	iPoint dest_point(destination.x, destination.y);
	int ret = -1;
	//iPoint mouse_position = App->map->FixPointMap(destination.x, destination.y);
	/*iPoint map_origin = App->map->WorldToMap(origin.x, origin.y);
	iPoint map_goal = App->map->WorldToMap(dest_point.x, dest_point.y);*/
/*	if (map_origin == map_goal)
	{
		std::vector<iPoint>* path = new std::vector<iPoint>;
		path->push_back(mouse_position);
		return path;
	}*/

	if (IsWalkable(origin) && IsWalkable(dest_point))
	{
		ret = 1;
		OpenList open;
		PathNode* firstNode = GetPathNode(origin.x, origin.y);
		firstNode->SetPosition(origin);
		firstNode->g = 0;
		firstNode->h = origin.DistanceManhattan(dest_point);

		open.queue.push(firstNode);
		PathNode* current = nullptr;
		while (open.queue.size() != 0)
		{
			current = open.queue.top();
			open.queue.top()->on_close = true;
			open.queue.pop();
			if (current->pos == dest_point)
			{

				std::vector<iPoint>* path = new std::vector<iPoint>;
				last_path.clear();

				path->push_back(dest_point);
				iPoint mouse_cell = App->map->WorldToMap(dest_point.x, dest_point.y);
				if (mouse_cell == current->pos)
					current = GetPathNode(current->parent->pos.x, current->parent->pos.y);

				for (; current->parent != nullptr; current = GetPathNode(current->parent->pos.x, current->parent->pos.y))
				{
					last_path.push_back(current->pos);
					path->push_back({ current->pos.x, current->pos.y });



				}
				last_path.push_back(current->pos);

				return path;
			}
			else
			{
				PathList neightbords;
				current->FindWalkableAdjacents(&neightbords);
				for (std::list<PathNode*>::iterator item = neightbords.list.begin(); item != neightbords.list.end(); item++) {
					PathNode* temp = item._Mynode()->_Myval;

					if (temp->on_close == true)
					{
						continue;
					}
					else if (temp->on_open == true)
					{
						int last_g_value = (int)temp->g;
						temp->CalculateF(dest_point);
						if (last_g_value <temp->g)
						{
							temp->parent = GetPathNode(current->pos.x, current->pos.y);
						}
						else {
							temp->g = (float)last_g_value;
						}
					}
					else
					{
						temp->on_open = true;
						temp->CalculateF(dest_point);
						open.queue.push(temp);

					}
				}

				neightbords.list.clear();
			}
		}
	}

	return nullptr;
}

/// -----------------------------------


/// Struct PathNode -------------------
//Constructors ==============
PathNode::PathNode()
{

}

PathNode::PathNode(int g, int h, const iPoint & pos, const PathNode * parent) : g((float)g), h(h), pos(pos), parent(parent), on_close(false), on_open(false)
{
	int x = 0;
}

PathNode::PathNode(const PathNode & node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{
	int x = 0;
}

//Functionality =============
uint PathNode::FindWalkableAdjacents(PathList* list_to_fill) const
{
	iPoint cell(0,0);
	uint before = list_to_fill->list.size();
	bool northClose = false, southClose = false, eastClose = false, westClose = false;
	// south
	cell.create(pos.x, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
	{
		PathNode* node = App->pathfinding->GetPathNode(cell.x, cell.y);
		if (node->pos != cell) {
			node->parent = this;
			node->pos = cell;
		}
		list_to_fill->list.push_back(node);
	}
	else
	{
		southClose = true;
	}
	// north
	cell.create(pos.x, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
	{
		PathNode* node = App->pathfinding->GetPathNode(cell.x, cell.y);
		if (node->pos != cell) {
			node->parent = this;
			node->pos = cell;
		}
		list_to_fill->list.push_back(node);
	}
	else
	{
		northClose = true;
	}
	// east
	cell.create(pos.x + 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
	{
		PathNode* node = App->pathfinding->GetPathNode(cell.x, cell.y);
		if (node->pos != cell) {
			node->parent = this;
			node->pos = cell;
		}
		list_to_fill->list.push_back(node);
	}
	else
	{
		eastClose = true;
	}
	// west
	cell.create(pos.x - 1, pos.y);
	if (App->pathfinding->IsWalkable(cell))
	{
		PathNode* node = App->pathfinding->GetPathNode(cell.x, cell.y);
		if (node->pos != cell) {
			node->parent = this;
			node->pos = cell;
		}
		list_to_fill->list.push_back(node);
	}
	else
	{
		westClose = true;
	}

	return list_to_fill->list.size();
}

float PathNode::Score() const
{
	return g + h;
}

int PathNode::CalculateF(const iPoint & destination)
{

	g = parent->g + parent->pos.DistanceManhattan(pos);
	h = pos.DistanceManhattan(destination) * 10;
	return  (int)g + h;
}

void PathNode::SetPosition(const iPoint & value)
{
	pos = value;
}

//Operators =================
bool PathNode::operator==(const PathNode & node) const
{
	return pos == node.pos;
}

bool PathNode::operator!=(const PathNode & node) const
{
	return !operator==(node);
}
/// -----------------------------------


///Struct PathList --------------------
//Functionality =============
/*
std::list<PathNode>::iterator PathList::Find(const iPoint & point)
{
std::list<PathNode*>::iterator item = list.begin();
while (item != list.end())
{
if (item->pos == point) {
return item;
}
++item;
}

}


PathNode* PathList::GetNodeLowestScore() const
{
PathNode* ret = nullptr;
std::list<PathNode>::const_reverse_iterator item = list.crbegin();
float min = 65535;
while (item != list.crend())
{
if (item->Score() < min)
{
min = item->Score();
ret = &item.base()._Ptr->_Prev->_Myval;
}
++item;
}
return ret;
}*/


void j1Pathfinding::Move(Enemy * enemy, Character* player)
{
	if (enemy->green_enemy_path.size()) {

		static int i = 1;

		
		int temp = enemy->green_enemy_path[enemy->green_enemy_path.size() - i].x;
		int temp2 = enemy->green_enemy_path[enemy->green_enemy_path.size() - i].y;

		int x = 0;
		int y = 0;
		x = x + (enemy->green_enemy_path[enemy->green_enemy_path.size()-i].x - enemy->tile_pos.x);
		y = y + (enemy->green_enemy_path[enemy->green_enemy_path.size()- i].y - enemy->tile_pos.y);


		/*
		if (last_path.size() > 1) {
			x = x + (last_path[i + 1].x - enemy->array_pos.x);
			y = y + (last_path[i + 1].y - enemy->array_pos.y);
		}*/

		//enemy->actual_event = move;

		//Change this
		if (x >= 1) { x = 1; enemy->Enemy_Orientation = OrientationEnemy::right_enemy; }
		if (x <= -1) { x = -1;  enemy->Enemy_Orientation = OrientationEnemy::left_enemy; }
		if (y >= 1) { y = 1; enemy->Enemy_Orientation = OrientationEnemy::down_enemy; }
		if (y <= -1) { y = -1; enemy->Enemy_Orientation = OrientationEnemy::up_enemy; }


		enemy->pix_world_pos.x += x;
		enemy->pix_world_pos.y += y;

		if (enemy->tile_pos == enemy->green_enemy_path[enemy->green_enemy_path.size()-i]) {
			i++;
		}
		if (i == enemy->green_enemy_path.size() || enemy->tile_pos == player->tilepos) {
			i = 0;
			enemy->green_enemy_path.clear();
		}


	}

}