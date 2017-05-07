#include "j1Player.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Pathfinding.h"
#include <algorithm>
#include"j1Collision.h"
#include "O_ChangeHeight.h"
#include "O_Button.h"
#include "O_DoubleButton.h"
#include "O_Movable_BLock.h"
#include "O_Fall.h"
#include"j1Enemy.h"
#include "j1HUD.h"
#include"j1Audio.h"
#include"HyruleBombSoldier_Enemy.h"
bool j1Player::Awake(pugi::xml_node& config)
{
	//This need to be cleaned
	Link = new P_Link();
	Zelda = new P_Zelda();
	
	cooperative = true;
	
	//Link->sprites_vector = new std::vector<Animation>;
	//Zelda->sprites_vector = new std::vector<Animation>;	
	
	Link->sprites_folder = config.child("folder").child_value();
	Zelda->sprites_folder = config.child("folder").child_value();
	
	
	Link->Link_Hurt_Audio= App->audio->LoadFx("audio/fx/link hurt.wav");
	Link->Link_Sword_Audio = App->audio->LoadFx("audio/fx/fighter sword 1.wav");
	Link->Link_Sword_Collides_Sword_Audio= App->audio->LoadFx("audio/fx/sword shine 1.wav");
	Zelda->Throw_Audio = App->audio->LoadFx("audio/fx/throw.wav");
	Fall_Players_Audio = App->audio->LoadFx("audio/fx/fall.wav");
	Zelda->Arrow_Audio = App->audio->LoadFx("audio/fx/arrow 2.wav");
	Zelda->Arrow_Hit_Wall_Audio = App->audio->LoadFx("audio/fx/arrow hit wall.wav");
	App->enemy->enemy_dies_audio = App->audio->LoadFx("audio/fx/enemy dies.wav");
	App->enemy->enemy_pathfinding_audio = App->audio->LoadFx("audio/fx/soldier.wav");
	
	//TEMP SPEED ANIMATION
	


	return true;
}

bool j1Player::Start()
{
	Link->collision = App->collision->AddCollider({ Link->pos.x,Link->pos.y,32,32 }, collider_link, Link, this);
	Link->front_collider = App->collision->AddCollider({ Link->tilepos.x * 8,Link->tilepos.y * 8 + 32,32,16 }, front_link, Link, this);
	Zelda->collision = App->collision->AddCollider({ Zelda->pos.x,Zelda->pos.y,32,32 }, collider_zelda, Zelda, this);
	Zelda->front_collider = App->collision->AddCollider({ Zelda->pos.x,Zelda->pos.y + 32,32,16 }, front_zelda, Zelda, this);

	Link->movement_direction = move_idle;
	Zelda->movement_direction = move_idle;
	Link->actual_event = player_event::idle;
	Zelda->actual_event = player_event::idle;
	Link->character_direction = direction::down;
	Zelda->character_direction = direction::down;

	Link->LoadAnimation("sprites/Link_Spritesheet_Finale.xml");
	Zelda->LoadAnimation("sprites/Zelda_Spritesheet_Finale.xml");

	selected_character = Link;
	other_character = Zelda;
	change = false;
	cooperative = true;
	Link->collision_by_enemy_timmer.Start();
	Audio_Fx_Timer.Start();
	Link->enemy_col_sword_sword_timer.Start();

	Link->doing_script = false;
	Zelda->doing_script = false;
	Link->is_rolling = false;
	Link->im_lifting = false;
	Link->can_jump = false;
	Link->can_walk = true;
	Link->can_pick_up = false;
	Zelda->is_picked = false;
	Zelda->is_rolling = false;
	Zelda->can_jump = false;
	Zelda->can_move = true;
	
	//TEMP
	Link->sprites_vector[player_event::attack * 4 + direction::up].speed = 0.12f;
	Link->sprites_vector[player_event::attack * 4 + direction::down].speed = 0.12f;
	Link->sprites_vector[player_event::attack * 4 + direction::left].speed = 0.12f;
	Link->sprites_vector[player_event::attack * 4 + direction::right].speed = 0.12f;

	return true;
}

bool j1Player::PreUpdate()
{
	
	return true;
}

bool j1Player::Update(float dt)
{
	
	
	if (!paused) {
		Link->can_fall = true;
		Zelda->can_fall = true;

		//Change the tile_pos
		Link->tilepos.x = (Link->pos.x + 8) / 16;
		Link->tilepos.y = (Link->pos.y + 8) / 16;
		Zelda->tilepos.x = (Zelda->pos.x + 8) / 16;
		Zelda->tilepos.y = (Zelda->pos.y + 8) / 16;

		Link->GetAdjacents();
		Zelda->GetAdjacents();

		//2 Players
		if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
			//	cooperative = !cooperative;
			selected_character = Link;
			other_character = Zelda;
		}

		if (cooperative == true) {
			Link->link_sword_collider_update();
			Link->GetEvent();
			Zelda->GetEvent();
			Link->ExecuteEvent(dt);
			Zelda->ExecuteEvent(dt);


		}

		//Draw the two characters
		//Draw();

		//Change the positions of player colliders
		Link->collision->SetPos(Link->pos.x, Link->pos.y, Link->GetLogicHeightPlayer());
		Zelda->collision->SetPos(Zelda->pos.x, Zelda->pos.y, Zelda->GetLogicHeightPlayer());
		Link->UpdateColliderFront();
		Zelda->UpdateColliderFront();
		Zelda->UpdateArrows();
	}
	return true;
}

bool j1Player::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		App->scene->ChangeScene(before_dungeon);
		App->player->Link->pos = { 660,1200 };
		App->player->Zelda->pos = { 620,1200 };
	}
	return true;
}

bool j1Player::CleanUp() {
	App->tex->UnLoad(Link->entity_texture);
	App->tex->UnLoad(Zelda->entity_texture);
	Link->sprites_vector.clear();
	Zelda->sprites_vector.clear();
	if (Link != nullptr)
	{
		if ((Link->collision != nullptr) && (Link->front_collider != nullptr))
		{
			//Link->collision->to_delete = true;
			//Link->front_collider->to_delete = true;
		}
	}
	if (Zelda != nullptr)
	{
		if ((Zelda->collision != nullptr) && (Zelda->front_collider != nullptr))
		{
			//Zelda->collision->to_delete = true;
			//Zelda->front_collider->to_delete = true; // This may crash, can't read memory
		}
	}
	return true;
}

void j1Player::Draw(int height, int y_pos)
{

	if(height ==Link->logic_height && y_pos == Link->tilepos.y)
	App->render->Blit(Link->entity_texture, Link->pos.x - Link->actual_animation.GetCurrentFrame().pivot.x, Link->pos.y - Link->actual_animation.GetCurrentFrame().pivot.y, &Link->actual_animation.GetCurrentFrame().rect);
	if(height ==Zelda->logic_height && y_pos == Zelda->tilepos.y)
	App->render->Blit(Zelda->entity_texture, Zelda->pos.x - Zelda->actual_animation.GetCurrentFrame().pivot.x, Zelda->pos.y - Zelda->actual_animation.GetCurrentFrame().pivot.y, &Zelda->actual_animation.GetCurrentFrame().rect);
	
	
	
}




void j1Player::ActivatePathfinding()
{

	/*static bool pathfinding_active = true;
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		pathfinding_active = !pathfinding_active;
	}
	if (pathfinding_active == true) {
		App->pathfinding->CreatePath(other_character->tilepos, selected_character->tilepos);
		
	}

	int dist = 0;
	dist = sqrt((selected_character->tilepos.x - other_character->tilepos.x)* (selected_character->tilepos.x - other_character->tilepos.x) + (selected_character->tilepos.y - other_character->tilepos.y)*(selected_character->tilepos.y - other_character->tilepos.y));

	if (chase == true&& dist >3 && pathfinding_active == true) {
		App->pathfinding->Move(other_character, selected_character);

	}
	else {		
		other_character->actual_event = idle;
		
	}

		if (other_character->tilepos == selected_character->tilepos || App->pathfinding->GetLastPath()->Count() == 0) {
			App->pathfinding->DeletePath();
			chase = false;
		}
		else chase = true;
	*/
}

bool j1Player::Move_Camera()
{

	int mult = -1;
	static int i = 0;
	
	//Time between character change
	const int time = 20;

	static float rest_x;
	static float rest_y;
	int sum_x = 0;
	int sum_y = 0;
	int x = (int)(other_character->pos.x * App->win->GetScale() - selected_character->pos.x * App->win->GetScale());
	int y = (int)(other_character->pos.y * App->win->GetScale() - selected_character->pos.y * App->win->GetScale());

	if (x > 0)mult = 1;

	rest_x = rest_x + x % time;
	rest_y = rest_y + y % time;

	if (mult * rest_x >= time) {
		sum_x = mult;
		rest_x = rest_x - time * mult;
	}

	mult = -1;
	if (y > 0)mult = 1;

	if (mult * rest_y >= time) {
		sum_y = mult;
		rest_y = rest_y - time * mult;
	}
	App->render->camera.x = App->render->camera.x + x / time + sum_x;
	App->render->camera.y = App->render->camera.y + y / time + sum_y;
	if (i >= time) {
		change = false;
		i = 0;
		rest_x = 0;
		rest_y = 0;
	}
	i++;
	
	return false;
}

void j1Player::OnCollision(Collider * collider1, Collider * collider2)
{

	Character* character = nullptr;
	if (collider1->type == collider_link || collider2->type == collider_link)
		character = Link;
	else if (collider1->type == collider_zelda || collider2->type == collider_zelda)
		character = Zelda;
	else if (collider1->type == front_zelda || collider2->type == front_zelda)
		character = Zelda;
	else if (collider1->type == front_link || collider2->type == front_link)
		character = Link;


	/*TO OBJECT-------
	------
	if (collider1->type == collider_button) {
		static bool audio = false;
		if (!audio) {
			App->audio->PlayFx(App->audio->button_sound);
			audio = true;
		}
		Button* temp = (Button*)collider1->parent;
		temp->Action();
		temp->texture_rect = temp->pressed_button;
	}
	else if (collider2->type == collider_button) {
		static bool audio = false;

		Button* temp = (Button*)collider2->parent;
		temp->Action();
		temp->texture_rect = temp->pressed_button;
		if (!audio) {
			App->audio->PlayFx(App->audio->button_sound);
			audio = true;
		}
	}
	else if (collider1->type == collider_double_button) {
		DoubleButton* temp = (DoubleButton*)collider2->parent;
		temp->characters_on++;
		temp->Action();

	}
	else if (collider2->type == collider_double_button) {
		DoubleButton* temp = (DoubleButton*)collider2->parent;
		temp->characters_on++;
		temp->Action();

	}
	else if (collider1->type == collider_warp) {
		Object* temp = (Object*)collider1->parent;
		loop_game_menu = true;
	}
	else if (collider2->type == collider_warp) {
		Object* temp = (Object*)collider2->parent;
		loop_game_menu = true;
	}
	else if (collider1->type == collider_change_height) {
		ChangeHeight* temp = (ChangeHeight*)collider1->parent;
		character->ChangeLogicHeightPlayer(temp->height);

	}
	else if (collider2->type == collider_change_height) {
		ChangeHeight* temp = (ChangeHeight*)collider2->parent;
		character->ChangeLogicHeightPlayer(temp->height);

	}
	else if (collider1->type == collider_jump) {
		if (character->can_move == false && character->doing_script == false) {
			App->audio->PlayFx(Fall_Players_Audio);
			character->can_jump = true;

		}
	}
	else if (collider2->type == collider_jump) {
		if (character->can_move == false && character->doing_script == false) {
			App->audio->PlayFx(Fall_Players_Audio);
			character->can_jump = true;

		}
	}
	-----------
	-----------*/
	if (collider1->type == front_link) {
		if (collider2->type == collider_zelda && !Link->im_lifting)
			Link->can_pick_up = true;



	}
	else if (collider2->type == front_link) {
		if (collider1->type == collider_zelda && !Link->im_lifting)
			Link->can_pick_up = true;

	}

	
	
	else if (collider1->type == COLLIDER_TYPE::collider_link_sword && collider2->type == COLLIDER_TYPE::collider_enemy_sword) {
		Enemy* n_enemy = (Enemy*)collider2->parent;
		if (Link->collision_by_enemy_timmer.Read() > 1500) {
			App->audio->PlayFx(Link->Link_Sword_Collides_Sword_Audio);
			Link->collision_by_enemy_timmer.Start();
			if (Link->Compare_Link_Sword_Collision(n_enemy)) {
				n_enemy->state = EnemyState::push_back_enemy;
				n_enemy->enemy_doing_script = true;
				Link->Collision_Sword_EnemySword();
				Link->link_sword_impact_sword = true;
			}
		}
	}


	/*TO DELETE-------
	-----------------
	else if (collider1->type == COLLIDER_TYPE::collider_enemy_sword && collider2->type == COLLIDER_TYPE::collider_link_sword) {
		Enemy* n_enemy = (Enemy*)collider2->parent;
		if (Link->collision_by_enemy_timmer.Read() > 1500) {
			App->audio->PlayFx(Link->Link_Sword_Collides_Sword_Audio);
			Link->collision_by_enemy_timmer.Start();
			if (Link->Compare_Link_Sword_Collision(n_enemy)) {
				n_enemy->state = EnemyState::push_back_enemy;
				n_enemy->enemy_doing_script = true;
				Link->Collision_Sword_EnemySword();
				Link->link_sword_impact_sword = true;
			}
		}
	}
	-----------
	----------*/
	else if (collider1->type == COLLIDER_TYPE::collider_link && collider2->type == COLLIDER_TYPE::collider_enemy) {
		Enemy* n_enemy = (Enemy*)collider2->parent;
		if (Link->is_rolling == false) {
			//roll_timer
			//if (Link->roll_timer.Read() > 1500) {
			if (Link->collision_by_enemy_timmer.Read() > 1500) {
				App->audio->PlayFx(Link->Link_Hurt_Audio);
				Link->roll_timer.Start();
				Link->collision_by_enemy_timmer.Start();
				//Link->Collision_Sword_EnemySword();
				Link->actual_event = player_event::push_backwards;
				Link->doing_script = true;
				Link->Direction_Push_Election();
				half_hearts_test_purpose--;
			}
			//}
		}
	}

	


	else if (collider1->type == COLLIDER_TYPE::collider_link_sword && collider2->type == COLLIDER_TYPE::collider_enemy) {
		Enemy* n_enemy = (Enemy*)collider2->parent;
		n_enemy->Enemy_Hit_Comprobation(collider1);

	}

	/* TO ENEMY------
	-----------------
	else if (collider1->type == COLLIDER_TYPE::collider_enemy_sword && collider2->type == COLLIDER_TYPE::collider_link) {
		Enemy* n_enemy = (Enemy*)collider2->parent;
		if (Link->is_rolling == false) {
			//if (Link->roll_timer.Read() > 1500) {
			if (Link->collision_by_enemy_timmer.Read() > 1500) {
				Link->collision_by_enemy_timmer.Start();
				Link->actual_event = player_event::push_backwards;
				Link->doing_script = true;
				Link->Direction_Push_Election();
				half_hearts_test_purpose--;

			}
			//}
		}
	}
	------------
	----------*/


	/*TO DELETE-------
	-----------------
	else if (collider1->type == COLLIDER_TYPE::collider_link && collider2->type == COLLIDER_TYPE::collider_enemy_sword) {
		Enemy* n_enemy = (Enemy*)collider2->parent;
		if (Link->is_rolling == false) {
			if (Link->roll_timer.Read() > 1500) {
				if (Link->collision_by_enemy_timmer.Read() > 1500) {
					Link->collision_by_enemy_timmer.Start();
					Link->actual_event = player_event::push_backwards;
					Link->doing_script = true;
					Link->Direction_Push_Election();
					half_hearts_test_purpose--;

				}
			}
		}
	}
	-----------
	-----------*/

	/*TO_ENEMY-----
	---------------
	else if (collider1->type == COLLIDER_TYPE::collider_enemy_sword && collider2->type == COLLIDER_TYPE::collider_zelda) {
		Enemy* n_enemy = (Enemy*)collider2->parent;
		if (Zelda->is_rolling == false) {
			if (Link->collision_by_enemy_timmer.Read() > 1500) {
				Link->collision_by_enemy_timmer.Start();
				Zelda->actual_event = player_event::push_backwards;
				Zelda->doing_script = true;
				Zelda->Direction_Push_Election();
				half_hearts_test_purpose--;
			}

		}
	}
	-----------
	-----------*/
	else if (collider1->type == COLLIDER_TYPE::collider_zelda && collider2->type == COLLIDER_TYPE::collider_enemy) {
		Enemy* n_enemy = (Enemy*)collider2->parent;
		if (Zelda->is_rolling == false) {
			//roll_timer
			//if (Link->roll_timer.Read() > 1500) {
			if (Zelda->collision_by_enemy_timmer.Read() > 1500) {
				App->audio->PlayFx(Link->Link_Hurt_Audio);
				Zelda->roll_timer.Start();
				Zelda->collision_by_enemy_timmer.Start();
				Zelda->actual_event = player_event::push_backwards;
				Zelda->doing_script = true;
				Zelda->Direction_Push_Election();
				half_hearts_test_purpose--;
			}
			//}
		}
	}
	else if (collider1->type == COLLIDER_TYPE::collider_link && collider2->type == COLLIDER_TYPE::collider_colour_block) {
		Object* temp_colour_block = (Object*)collider2->parent;
		if(temp_colour_block->active)
		App->player->Link->can_fall = false;
	}
	else if (collider1->type == COLLIDER_TYPE::collider_zelda && collider2->type == COLLIDER_TYPE::collider_colour_block) {
		Object* temp_colour_block = (Object*)collider2->parent;
		if (temp_colour_block->active)
		App->player->Zelda->can_fall = false;
	}

	else if (collider1->type == COLLIDER_TYPE::collider_zelda && collider2->type == COLLIDER_TYPE::collider_fall) {
		if (App->player->Zelda->can_fall && !App->player->Zelda->doing_script) {
			Fall* temp = (Fall*)collider2->parent;
			App->player->Zelda->pos = { temp->fallpos.x * 16,temp->fallpos.y * 16 };
		}
		
	}

	else if (collider1->type == COLLIDER_TYPE::collider_link && collider2->type == COLLIDER_TYPE::collider_fall) {
		if (App->player->Link->can_fall) {
			Fall* temp = (Fall*)collider2->parent;
			App->player->Link->pos = { temp->fallpos.x * 16,temp->fallpos.y * 16 };
		}
		
	}


	//Bomb explosion Collider doesn't detect the collision with Link

	else if (collider1->type == COLLIDER_TYPE::collider_link && collider2->type == COLLIDER_TYPE::coolider_bomb_explosion) {
		Link->actual_event = player_event::push_backwards;
		Link->doing_script = true;
		Link->Direction_Push_Election();
		Enemy_Bomb* n_bomb = (Enemy_Bomb*)collider2->parent;
		n_bomb->bomb_collider_explosion->to_delete = true;
		half_hearts_test_purpose--;
	}
	else if (collider1->type == COLLIDER_TYPE::collider_zelda && collider2->type == COLLIDER_TYPE::coolider_bomb_explosion) {
		Zelda->actual_event = player_event::push_backwards;
		Zelda->doing_script = true;
		Zelda->Direction_Push_Election();
		Enemy_Bomb* n_bomb = (Enemy_Bomb*)collider2->parent;
		n_bomb->bomb_collider_explosion->to_delete = true;
		half_hearts_test_purpose--;
	}	
	else if (collider1->type == COLLIDER_TYPE::front_link && collider2->type == COLLIDER_TYPE::collider_movable_object) {
		if (!Link->can_walk) {
			Movable_Block* temp_object = (Movable_Block*)collider2->parent;
			temp_object->Action(Link);
		}

	}
	else if (collider1->type == COLLIDER_TYPE::front_zelda && collider2->type == COLLIDER_TYPE::collider_movable_object) {
		if (!Zelda->can_walk) {
			Movable_Block* temp_object = (Movable_Block*)collider2->parent;
			temp_object->Action(Zelda);
		}

	}

}

void j1Player::EndCollision(Collider * collider1, Collider * collider2)
{
	Character* character = nullptr;
	if (collider1->type == collider_link || collider2->type == collider_link)
		character = Link;
	else if (collider1->type == collider_zelda || collider2->type == collider_zelda)
		character = Zelda;
	else if (collider1->type == front_zelda || collider2->type == front_zelda)
		character = Zelda;
	else if (collider1->type == front_link || collider2->type == front_link)
		character = Link;


	if (collider2->type == collider_button) {
		static bool audio = false;
		if (!audio) {
			App->audio->PlayFx(App->audio->button_sound);
			audio = true;
		}
		Button* temp = (Button*)collider2->parent;
		temp->EndAction();
		//temp->texture_rect = temp->pressed_button;
	}
	/*else if (collider1->type == COLLIDER_TYPE::collider_link && collider2->type == COLLIDER_TYPE::collider_colour_block) {

			App->player->Link->can_fall = true;
	}
	else if (collider1->type == COLLIDER_TYPE::collider_zelda && collider2->type == COLLIDER_TYPE::collider_colour_block) {
		
			App->player->Zelda->can_fall = true;
	}*/
}

void j1Player::StartCollision(Collider * collider1, Collider * collider2)
{
	if (collider1->type == collider_arrow) {
		if (collider2->type == collider_diana) {
			Object* temp = (Object*)collider2->parent;
			if (temp->name == "diana_2") {
				App->enemy->appear_enemies = true;
			}
			temp->Action();
		}

		else if (collider2->type == collider_boss_little_eye) {
			Boss* temp_boss = (Boss*)collider2->parent;
			Arrow* arrow_temp = (Arrow*)collider1->parent;
			if (temp_boss->foot_live > 0)
				temp_boss->foot_live--;
			arrow_temp->can_move = false;
			//arrow_temp->is_attached = true;
			collider1->to_delete = true;
		}
		else {
			Arrow* arrow_temp = (Arrow*)collider1->parent;
			arrow_temp->can_move = false;
			arrow_temp->is_attached = true;
			arrow_temp->attached_enemy = (Enemy*)collider2->parent;
			arrow_temp->offset.x = arrow_temp->pos.x - arrow_temp->attached_enemy->pos.x;
			arrow_temp->offset.y = arrow_temp->pos.y - arrow_temp->attached_enemy->pos.y;

			if (collider1->type == collider_arrow)
				collider1->to_delete = true;
			Enemy* n_enemy = (Enemy*)collider2->parent;
			n_enemy->Enemy_Hit_Comprobation(collider1);
		}
	}

	else if (collider1->type == COLLIDER_TYPE::collider_link && collider2->type == COLLIDER_TYPE::collider_boss_hit) {
		//roll_timer
		//if (Link->roll_timer.Read() > 1500) {
		if (Link->collision_by_enemy_timmer.Read() > 1500) {
			App->audio->PlayFx(Link->Link_Hurt_Audio);
			Link->roll_timer.Start();
			Link->collision_by_enemy_timmer.Start();
			//Link->Collision_Sword_EnemySword();
			Link->actual_event = player_event::push_backwards;
			Link->doing_script = true;
			Link->Direction_Push_Election();
			half_hearts_test_purpose--;
		}
		//}

	}
	else if (collider1->type == COLLIDER_TYPE::collider_zelda && collider2->type == COLLIDER_TYPE::collider_boss_hit) {
		//roll_timer
		//if (Link->roll_timer.Read() > 1500) {
		if (Zelda->collision_by_enemy_timmer.Read() > 1500) {
			App->audio->PlayFx(Link->Link_Hurt_Audio);
			Zelda->roll_timer.Start();
			Zelda->collision_by_enemy_timmer.Start();
			//Link->Collision_Sword_EnemySword();
			Zelda->actual_event = player_event::push_backwards;
			Zelda->doing_script = true;
			Zelda->Direction_Push_Election();
			half_hearts_test_purpose--;
		}
		//}

	}
	else if (collider1->type == COLLIDER_TYPE::collider_zelda && collider2->type == COLLIDER_TYPE::collider_boss_explosion) {
		//roll_timer
		//if (Link->roll_timer.Read() > 1500) {
		if (Zelda->collision_by_enemy_timmer.Read() > 1500) {
			App->audio->PlayFx(Link->Link_Hurt_Audio);
			Zelda->roll_timer.Start();
			Zelda->collision_by_enemy_timmer.Start();
			//Link->Collision_Sword_EnemySword();
			if (!Zelda->is_picked) {
				Zelda->actual_event = player_event::push_backwards;
				Zelda->doing_script = true;
				Zelda->Direction_Push_Election();
			}
			half_hearts_test_purpose--;
		}
		//}

	}
	else if (collider1->type == COLLIDER_TYPE::collider_link && collider2->type == COLLIDER_TYPE::collider_boss_explosion) {
		//roll_timer
		//if (Link->roll_timer.Read() > 1500) {
		if (Link->collision_by_enemy_timmer.Read() > 1500) {
			App->audio->PlayFx(Link->Link_Hurt_Audio);
			Link->roll_timer.Start();
			Link->collision_by_enemy_timmer.Start();
			//Link->Collision_Sword_EnemySword();
			Link->actual_event = player_event::push_backwards;
			Link->doing_script = true;
			Link->Direction_Push_Election();
			half_hearts_test_purpose--;
		}
		//}

	}
	else if (collider1->type == COLLIDER_TYPE::collider_zelda && collider2->type == COLLIDER_TYPE::collider_boss_recover) {
		
		if (!Zelda->is_picked) {
			Zelda->doing_script = true;
			Zelda->Direction_Push_Election();
			Zelda->logic_height = 0;
		}

	}
	else if (collider1->type == COLLIDER_TYPE::collider_link_sword && collider2->type == COLLIDER_TYPE::collider_boss_foot) {
		Foot* temp_foot = (Foot*)collider2->parent;
		if (temp_foot->parent_boss->foot_live > 0)
			temp_foot->parent_boss->foot_live--;

	}
	else if (collider1->type == COLLIDER_TYPE::collider_arrow && collider2->type == COLLIDER_TYPE::collider_boss_little_eye) {
		int x = 0;

	}

}


