#pragma once

#include "Camera.h"
#include "Renderer.h"
#include <future>

namespace goof {

	class Entity {

	protected:
		bool CheckCollisions(gf_render::shapes* toComparet0, int index);
		float gravity_value = 9.8;

	public:
		goof::Camera follow_camera;

		glm::vec3 entity_position = glm::vec3(0.0f,0.0f,0.0f);
		glm::vec3 entity_position_init;
		glm::vec3 size;
		glm::vec3 temporary_position;
		
		bool is_colliding = false;
		bool is_gravity_enabled = false;

		int up = 0;
		int right = 0;
		int forward = 0;

		
		virtual bool doCollisions_with_all(bool state = false, gf_render::shapes* game_object_pointer = nullptr);

	public:
		Entity();
		~Entity();
		
	};

	class character2d : public Entity {

		gf_render::Rect player_sprite;

	public:

		character2d();
		~character2d();

		character2d(float x, float y, float z);
		void update_pos(float x, float y, float z, Shader& shader);
		inline void set_gravity(float value) { this->gravity_value = value; }
	};

	class character3d : public Entity {

		gf_render::Cube player_sprite;

	public:
		character3d();
		~character3d();

		void update_pos(float x, float y, float z, Shader& shader);
	};
}