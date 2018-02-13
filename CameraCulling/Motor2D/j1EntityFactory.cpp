#include "p2Log.h"

#include "j1Module.h"
#include "j1App.h"

#include "j1EntityFactory.h"
#include "j1Render.h"

#include "Entity.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Pathfinding.h"



#define SPAWN_MARGIN 50

j1EntityFactory::j1EntityFactory()
{
	name.create("entities");

	for (uint i = 0; i < MAX_ENTITIES; ++i)
		entities[i] = nullptr;
}

// Destructor
j1EntityFactory::~j1EntityFactory()
{
}

bool j1EntityFactory::Awake(pugi::xml_node& config) {

	bool ret = true;

	pugi::xml_node node = config.child("spritesheets").child("spritesheet");

	// Load texture paths
	/*
	CatPeasant_spritesheet = node.attribute("name").as_string();
	node = node.next_sibling("spritesheet");
	Monkey_spritesheet = node.attribute("name").as_string();
	*/
	//_load_texture_paths

	//PLAYER
	/*
	pugi::xml_node general_node = config.child("types").child("player").child("general");
	pugi::xml_node actual_node;

	actual_node = general_node.child("coll_offset");
	player.coll_offset = { actual_node.attribute("x").as_int(), actual_node.attribute("y").as_int(), actual_node.attribute("w").as_int(), actual_node.attribute("h").as_int() };
	player.gravity = general_node.child("gravity").attribute("value").as_float();
	actual_node = general_node.child("speed");
	player.speed = { actual_node.attribute("x").as_float(), actual_node.attribute("y").as_float() };
	player.check_collision_offset = general_node.child("check_collision").attribute("offset").as_uint();

	// Load animations
	pugi::xml_node animations_node = config.child("types").child("player").child("animations");

	//idle
	node = animations_node.child("idle");
	player.idle.speed = node.attribute("speed").as_float();
	player.idle.loop = node.attribute("loop").as_bool();
	player.coll_size = { node.child("frame").attribute("w").as_int(), node.child("frame").attribute("h").as_int() };
	for (node = node.child("frame"); node; node = node.next_sibling("frame")) {
		player.idle.PushBack({ node.attribute("x").as_int(), node.attribute("y").as_int(), node.attribute("w").as_int(), node.attribute("h").as_int() });
	}
	//_idle
	//_load_animations
	*/
	//_PLAYER

	return ret;
}

bool j1EntityFactory::Start()
{
	bool ret = true;

	LOG("Loading entities textures");

	/*
	CatPeasantTex = App->tex->Load(CatPeasant_spritesheet.GetString());
	*/

	return ret;
}

bool j1EntityFactory::PreUpdate()
{
	bool ret = true;

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type != ENTITY_TYPES::NO_TYPE)
		{
			SpawnEntity(queue[i]);
			queue[i].type = ENTITY_TYPES::NO_TYPE;
		}
	}

	return ret;
}

// Called before render is available
bool j1EntityFactory::Update(float dt)
{
	bool ret = true;

	for (uint i = 0; i < MAX_ENTITIES; ++i) {
		if (entities[i] != nullptr) {
			entities[i]->Move(dt);
		}
	}

	// Draw Map
	App->map->Draw();

	for (uint i = 0; i < MAX_ENTITIES; ++i)
		if (entities[i] != nullptr) {
			/*
			if (entities[i]->type == ENTITY_TYPES::CAT_PEASANT_)
				entities[i]->Draw(CatPeasantTex);
			else if (entities[i]->type == ENTITY_TYPES::IMP_)
				entities[i]->Draw(ImpTex);
			else if (entities[i]->type == ENTITY_TYPES::MONKEY_)
				entities[i]->Draw(MonkeyTex);
			else if (entities[i]->type == ENTITY_TYPES::PLAYER_)
				entities[i]->Draw(PlayerTex);
			else if (entities[i]->type == ENTITY_TYPES::CAT_)
				entities[i]->Draw(CatTex);
			*/
		}

	return ret;
}

bool j1EntityFactory::PostUpdate()
{
	bool ret = true;

	// Check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->dead) {
				delete entities[i];
				entities[i] = nullptr;
			}
		}
	}

	return ret;
}

// Called before quitting
bool j1EntityFactory::CleanUp()
{
	bool ret = true;

	LOG("Freeing all entities");

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type != ENTITY_TYPES::NO_TYPE)
		{
			queue[i].type = ENTITY_TYPES::NO_TYPE;
			queue[i].position = { 0,0 };
		}

		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}

	/*
	playerData = nullptr;

	App->tex->UnLoad(CatPeasantTex);
	*/

	return ret;
}

bool j1EntityFactory::AddEntities()
{
	bool ret = true;

	// TODO: define a large group of entities to add using AddEntity()

	return ret;
}

bool j1EntityFactory::AddEntity(EntityInfo& info)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (queue[i].type == ENTITY_TYPES::NO_TYPE)
		{
			queue[i].type = info.type;
			queue[i].position.x = info.position.x;
			queue[i].position.y = info.position.y;

			ret = true;
			break;
		}
	}

	return ret;
}

Entity* j1EntityFactory::SpawnEntity(const EntityInfo& info)
{
	// Find room for the new entity
	uint i = 0;
	for (; entities[i] != nullptr && i < MAX_ENTITIES; ++i);

	if (i != MAX_ENTITIES)
	{
		switch (info.type)
		{
		/*
		case ENTITY_TYPES::CAT_PEASANT_:
			entities[i] = new CatPeasant(info.position.x, info.position.y, info.path);
			entities[i]->type = ENTITY_TYPES::CAT_PEASANT_;
			return (Entity*)entities[i];
			break;

		case ENTITY_TYPES::PLAYER_:
			playerData = new Player(info.position.x, info.position.y);
			entities[i] = playerData;
			entities[i]->type = ENTITY_TYPES::PLAYER_;
			return (Entity*)entities[i];
			break;
		*/
		}
	}

	return nullptr;
}


// -------------------------------------------------------------
// -------------------------------------------------------------

bool j1EntityFactory::Load(pugi::xml_node& save)
{
	bool ret = true;

	pugi::xml_node node;

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
	}

	return ret;
}

bool j1EntityFactory::Save(pugi::xml_node& save) const
{
	bool ret = true;

	pugi::xml_node node;

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
	}

	return ret;
}