#pragma once
#include "Shader.h"
#include "Texture.h"

namespace gf_render {

	static Shader default_shader;

	class shapes {

	private:
		template<typename T>
		void serializeVector(std::ostream& out, const std::vector<T>& vec) const {
			size_t size = vec.size();
			out.write(reinterpret_cast<const char*>(&size), sizeof(size));
			out.write(reinterpret_cast<const char*>(vec.data()), size * sizeof(T));
		}

		template<typename T>
		void deserializeVector(std::istream& in, std::vector<T>& vec) {
			size_t size;
			in.read(reinterpret_cast<char*>(&size), sizeof(size));
			vec.resize(size);	
			in.read(reinterpret_cast<char*>(vec.data()), size * sizeof(T));
		}
	
	protected:
		unsigned int VBO, VAO ,EBO = 0;
		int size_vertices = 0;

	public:
	
		goof::Texture2D tex;
		static unsigned int primitive_counter;
		bool verify_texture_presence = false;

		shapes() = default;
		std::string name = "shape";
		
		std::vector<glm::vec3>::iterator erase_iter;


		std::vector<glm::vec3> loc_vec_shape;
		std::vector<glm::vec4> color_index;
		std::vector<glm::vec3> object_scale;
		std::vector<unsigned int> tex_per_item;

		inline unsigned int getVBO() { return VBO; };
		inline unsigned int getVAO() { return VAO; };
		inline unsigned int getEBO() { return EBO; };
		inline unsigned int getSize_Vertices() { return size_vertices; };
		inline void set_name(std::string name) { this->name = name; };
		inline void set_texture(const char* path) { tex.Init(path); verify_texture_presence = true; }
		
		virtual void serialize(std::ostream& out) const {
			serializeVector(out, loc_vec_shape);
			serializeVector(out, color_index);
			serializeVector(out, object_scale);
			serializeVector(out, tex_per_item);
		}

		virtual void deserialize(std::istream& in) {
			deserializeVector(in, loc_vec_shape);
			deserializeVector(in, color_index);
			deserializeVector(in, object_scale);
			deserializeVector(in, tex_per_item);
		}


	};

	class Triangle : public shapes {
	public:
		std::string name = "Triangle";
		Triangle();
		~Triangle();

		void serialize(std::ostream& out) const override {
			shapes::serialize(out);
		}

		void deserialize(std::istream& in) override {
			shapes::deserialize(in);
		}
	};

	class Rect : public shapes {
	public:
		std::string name = "Rectangle";
		Rect();
		~Rect();

		void serialize(std::ostream& out) const override {
			shapes::serialize(out);
		}

		void deserialize(std::istream& in) override {
			shapes::deserialize(in);
		}
	};

	class Cube :public shapes {
	public:
		std::string name = "Cube";
		Cube();
		~Cube();
		void serialize(std::ostream& out) const override {
			shapes::serialize(out);
		}

		void deserialize(std::istream& in) override {
			shapes::deserialize(in);
		}
	};

	void Draw(shapes& tri , const float* COLOR = nullptr,
					glm::vec3 Postion = glm::vec3(0.0f,0.0f,0.0f),
					Shader& shader = default_shader,
					glm::vec3 Scale =glm::vec3(1.0f),
					unsigned int tex_ID = 0,
					goof::Texture2D* tex = nullptr);

	void ClearScreen();
	void setWireframeMode(bool set);
	
	
}
