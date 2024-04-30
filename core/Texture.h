#pragma once
#include "Shader.h"

namespace goof {

	class TextureManager {
	public:

		static std::vector<unsigned int> Texture_2D_ID;
		static std::vector<unsigned int> Texture_3D_ID;

		TextureManager() = default;
	};

	class Texture2D : public TextureManager {
		
		unsigned int ID;
		unsigned int manager_ID;
		

	public:

		Texture2D();
		~Texture2D();

		void Init( const char* file_name);
		inline unsigned int get_tex2d_id() { return ID; }
		void use(Shader& shader);

	};
	
}