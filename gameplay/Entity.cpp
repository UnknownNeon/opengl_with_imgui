#include "Entity.h"

goof::Entity::~Entity()
{

}


bool goof::Entity::CheckCollisions(gf_render::shapes* toCollide , int index)
{
	
	bool collision_x = (toCollide->loc_vec_shape[index].x + toCollide->object_scale[index].x) >= ((entity_position + entity_position_init).x) 
							&&
						((entity_position + entity_position_init).x + size.x >= toCollide->loc_vec_shape[index].x);

	bool collision_y = (toCollide->loc_vec_shape[index].y + toCollide->object_scale[index].y) >= ((entity_position + entity_position_init).y)
						&&
					   ((entity_position + entity_position_init).y + size.y >= toCollide->loc_vec_shape[index].y);

	return collision_x && collision_y;
}

bool goof::Entity::doCollisions_with_all(bool state, gf_render::shapes* game_object_pointer)
{
	int count = 0;
	if (state)
	{
		for (int i = 0; i < game_object_pointer->loc_vec_shape.size(); i++) {
			if (CheckCollisions(game_object_pointer, i)) {
				count++;
			}
		}
	}
	is_colliding = count > 0 ? true : false;
	return is_colliding;
}

goof::Entity::Entity() : size(glm::vec3(50.f)) ,entity_position_init(glm::vec3(0.f))
{
}

void goof::character2d::update_pos(float x, float y, float z, Shader& sha)
{

	entity_position += glm::vec3(x, y, z);
	if (is_gravity_enabled)
		entity_position.y += gravity_value;

	follow_camera.cameraPos = glm::vec3(entity_position.x, entity_position.y, 1.f);
	
	
	if (is_colliding) {
		gf_render::Draw(player_sprite, goof::RED, entity_position + entity_position_init, sha, size);
	}
	else
	{
		gf_render::Draw(player_sprite, goof::BLUE, entity_position + entity_position_init, sha, size);
	}
	sha.setMat4("view", follow_camera.lookAt());
}

goof::character2d::character2d()
{
}

goof::character2d::~character2d()
{
}

goof::character2d::character2d(float x, float y, float z) 
{
	size = glm::vec3(50.f);
	entity_position_init = glm::vec3(x, y, z);
}

goof::character3d::character3d()
{
}

goof::character3d::~character3d()
{
}

void goof::character3d::update_pos(float x, float y, float z, Shader& sha)
{
	if (z == 1)
		entity_position += follow_camera.cameraFront;
	if (z == -1)
		entity_position -= follow_camera.cameraFront;
	if (x == 1)
		entity_position += glm::normalize(glm::cross(follow_camera.cameraUp, follow_camera.cameraFront));
	if (x == -1)
		entity_position -= glm::normalize(glm::cross(follow_camera.cameraUp, follow_camera.cameraFront));
	
	follow_camera.cameraPos = entity_position;

	//needed to draw player;
	//gf_render::Draw(player_sprite, goof::BLUE, entity_position , sha, size);
	sha.setMat4("view", follow_camera.lookAt());
}
