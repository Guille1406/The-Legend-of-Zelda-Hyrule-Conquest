#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PathFinding.h"
#include "j1Player.h"

j1PathFinding::j1PathFinding() : j1Module(), map(NULL), last_path(DEFAULT_PATH_LENGTH),width(0), height(0)
{
	name.create("pathfinding");
}

// Destructor
j1PathFinding::~j1PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool j1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	last_path.Clear();
	RELEASE_ARRAY(map);
	return true;
}

// Sets up the walkability map
void j1PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
}

// Utility: return true if pos is inside the map boundaries
bool j1PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
			pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool j1PathFinding::IsWalkable(const iPoint& pos) const
{
	iPoint temp;
	temp.x = pos.x;
	temp.y = pos.y;
	uchar t = GetTileAt(temp);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar j1PathFinding::GetTileAt(const iPoint& pos) const
{
	if(CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

void j1PathFinding::Move(Character * character, Character* other)
{
	if (last_path.Count()>0) {

		static int i = 0;
		
		int temp = last_path[i].x;
		int temp2 = last_path[i].y;

		int x = 0;
		int y = 0;
		x  = x + (last_path[i].x - character->tilepos.x);
		y = y + (last_path[i].y - character->tilepos.y);

		if (last_path.Count() > 1) {
			x = x + (last_path[i + 1].x - character->tilepos.x);
			y = y + (last_path[i + 1].y - character->tilepos.y);
		}
		character->actual_event = move;
		
		//Change this
		if (x > 1) { x = 1; character->character_direction = right;		}
		if (x < -1) { x = -1;  character->character_direction = left;		}
		if (y > 1) { y = 1; character->character_direction = down;		}
		if (y < -1) { y = -1; character->character_direction = up;		}

		
		character->pos.x += x;
		character->pos.y += y;

		if (character->tilepos == last_path[i]) {
			i++;
		}
		if (i == last_path.Count() || character->tilepos == other->tilepos) {
			i = 0;
			last_path.Clear();
		}
		

	}
	
}

// To request all tiles involved in the last generated path
const p2DynArray<iPoint>* j1PathFinding::GetLastPath() const
{
	return &last_path;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::Find(const iPoint& point) const
{
	p2List_item<PathNode>* item = list.start;
	while(item)
	{
		if(item->data.pos == point)
			return item;
		item = item->next;
	}
	return NULL;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::GetNodeLowestScore() const
{
	p2List_item<PathNode>* ret = NULL;
	int min = 65535;

	p2List_item<PathNode>* item = list.end;
	while(item)
	{
		if(item->data.Score() < min)
		{
			min = item->data.Score();
			ret = item;
		}
		item = item->prev;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& list_to_fill) const
{
	iPoint cell1;
	iPoint cell2;
	iPoint cell;
	uint before = list_to_fill.list.count();

int pos_x = pos.x ;
	int pos_y = pos.y ;
	// north
	cell1.create(pos.x, pos.y - 1);
	cell2.create(pos.x + 1, pos.y - 1);
	cell.create(pos.x, pos.y - 1);
	if(App->pathfinding->IsWalkable(cell1) && App->pathfinding->IsWalkable(cell2))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// south
	cell1.create(pos.x, pos.y + 2);
	cell2.create(pos.x +1, pos.y + 2);
	cell.create(pos.x, pos.y + 1);
	if(App->pathfinding->IsWalkable(cell1)&& App->pathfinding->IsWalkable(cell2))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// east
	cell1.create(pos.x + 2, pos.y);
	cell2.create(pos.x + 2, pos.y+1);
	cell.create(pos.x +1, pos.y );
	if(App->pathfinding->IsWalkable(cell1) && App->pathfinding->IsWalkable(cell2))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	// west
	cell1.create(pos.x - 1, pos.y);
	cell2.create(pos.x - 1, pos.y+1);
	cell.create(pos.x - 1, pos.y );
	if(App->pathfinding->IsWalkable(cell1) && App->pathfinding->IsWalkable(cell2))
		list_to_fill.list.add(PathNode(-1, -1, cell, this));

	return list_to_fill.list.count();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int j1PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	int ret = 0;
	
	if (!IsWalkable(origin) && !IsWalkable(destination))
		return -1;

	
	PathList open;
	PathList close;
	open.list.add(PathNode(0, 0, origin, NULL));


	while (open.list.count() != 0)
	{

		p2List_item<PathNode>* activeNode = close.list.add(open.GetNodeLowestScore()->data);
		open.list.del(open.GetNodeLowestScore());



		if (activeNode->data.pos == destination)
		{
			last_path.Clear();
			PathNode item = activeNode->data;
			while (item.parent != NULL)
			{
				last_path.PushBack(item.pos);
				item = *item.parent;
			}
			last_path.Flip();
			return ret;
			
		}



		PathList temp;
		activeNode->data.FindWalkableAdjacents(temp);
		p2List_item<PathNode>* tempItem = temp.list.start;



		while (tempItem)
		{
			if (close.Find(tempItem->data.pos) == NULL)
			{
				tempItem->data.CalculateF(destination);
				///Compare G
				if (p2List_item<PathNode>* comparisor = open.Find(tempItem->data.pos))
				{
					if (comparisor->data.g > tempItem->data.g)
					{
						comparisor->data.parent = tempItem->data.parent;
					}
				}
				else
					open.list.add(tempItem->data);
			}

			tempItem = tempItem->next;
			ret++;
		}

	}

	

	return ret;
}

