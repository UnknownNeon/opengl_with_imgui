/*
MADE IN 2024;
@ TODO (*) - Priority
	-Maake a container for game objects here and keep a count 
	-Load ^ info to save file
	-Collisions are not imple (implemented wonky *) 
	-Audio is not imple
	-Player speed is wonky neeed fix (*)
	-Add input bindings (verrrrrrrrrrrrrry lazzzzzzzzzzzzzy to implement this shit )
	-make INPUT CLASSS (Consider)  

	COLLISION WITH AN ONJECT IF DETECTED CAN BE HANDLED BY THE USER CODE.
 
*/

#include "Engine.h"

#include "imgui/imgui.h"
#include "imgui/imgui_stdlib.h"
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <future>
#include "InputManager.h"

void goof::setViewMode(Shader& shader, glm::mat4 MODE)
{
	shader.setMat4("projection", MODE);
}


void goof::run()
{

	_Window window;
	InputManager manager(window.getWindow());

	Shader sha;
	sha.load_shader("dep/basic.vert");
	sha.load_shader("dep/basic.frag");
	sha.init_and_use_shader();

	Texture2D tex;
	tex.Init("dep/tex1.png");
	Texture2D tex2;
	tex.Init("dep/tex2.png");
	TextureManager manage;

	gf_render::Triangle triangle;
	gf_render::Rect rect;
	gf_render::Cube cube;

	//goof::Camera camera;
	goof::character2d player2d(W_HEIGHT/2, W_WIDTH/2 ,0.0f);
	goof::character3d player3d;

	//IMGUI STATES:
	goof::IMGUI::Init(window.getWindow());
	static bool show_wireframe = false;
	static bool view_mode = false;
	static bool possess_camera = false;
	static bool cursor_lock = false;

	const char* items[2] = {  "Prespective [3D]", "Orthographic [2D]" };
	static const char* current_item = items[1];


	/////////////////////GAAAAAAAAAAAAAAME LOOOOOOOOOOOOOOOOOOOOOOOOOOP//////////////////////////////////////

	while (window.isWindowOpen())
	{

		gf_render::ClearScreen();


		if (possess_camera && current_item == items[1]) {

			player2d.doCollisions_with_all(true, &rect);
			player2d.update_pos( manager.getAxisX(), -manager.getAxisY(), 0, sha);
		}
		if (possess_camera && current_item == items[0]) {

			//window.processInput(&player3d,GOOF_MODE_3D);
			player3d.update_pos( -manager.getAxisX(), player3d.forward, manager.getAxisY(), sha);
		}
		window.set_cursor_lock(cursor_lock);
		

		//dearimgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//----------------

		{

			ImGui::Begin("Debug window game....");                        

			ImGui::Text("Graphics Settings : ");              
			ImGui::Checkbox("Show Wireframe", &show_wireframe);  
			ImGui::Checkbox("Possess the camera", &possess_camera);
			ImGui::Checkbox("Cursor lock", &cursor_lock);
			if(!possess_camera)
				ImGui::Text("Posess the camera to move the player .");
			gf_render::setWireframeMode(show_wireframe);

			
			ImGui::Text("[WARNING :] While in orthographic \n dont W or S (Go forward or back)");
			if (ImGui::BeginCombo("#combo", current_item)) 
			{
				for (int n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					bool is_selected = (current_item == items[n]); 
					if (ImGui::Selectable(items[n], is_selected))
						current_item = items[n];
						if (is_selected)
							ImGui::SetItemDefaultFocus();   
				}
				ImGui::EndCombo();
			}
			if (current_item == items[0])
				goof::setViewMode(sha, prespective);
			if (current_item == items[1])
				goof::setViewMode(sha, orthographic);


			if (ImGui::Button("Reset Camera")) {
				player2d.entity_position = glm::vec3(0.f);
				player3d.entity_position = glm::vec3(0.f);
			}

			goof::IMGUI::render_primitives(triangle,sha);
			goof::IMGUI::render_primitives(rect, sha);
			goof::IMGUI::render_primitives(cube, sha);


			//////////////////////////////////
			//
			//
			//	SAVING AND LOADING start
			//
			//
			//
			/////////////////////////////////////
			if (ImGui::Button("Save files")) {
				std::ofstream file1("dep/save1.dat", std::ios::binary);
				if (file1.is_open()) {
					triangle.serialize(file1);
					rect.serialize(file1);
					cube.serialize(file1);
					file1.close();
				}
				else {
					std::cerr << "Error: Unable to open save file for writing.\n";
				}
		
				ImGui::Text("Files Saved Successfully");
			}
			if (ImGui::Button("Load files")) {
				std::ifstream file1("dep/save1.dat", std::ios::binary);
				if (file1.is_open()) {
					triangle.deserialize(file1);
					rect.deserialize(file1);
					cube.deserialize(file1);
					file1.close();
				}
				else
				{
					std::cerr << "Error: Unable to open file for reading.\n";
				}
	
			}

			//////////////////////////////////
			//
			//
			//	SAVING AND LOADING end
			//
			//
			//
			/////////////////////////////////////

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.swap_and_pollevents();
			
	}

	goof::IMGUI::Destroy();
}


void goof::IMGUI::Init(GLFWwindow* the_Window)
{
	
	const char* glsl_version = "#version 330";

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(the_Window, true);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplOpenGL3_Init(glsl_version);
}

void goof::IMGUI::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void goof::IMGUI::render_primitives(gf_render::shapes& cube, Shader& sha, goof::Texture2D* tex)
{
	
	
	if (ImGui::Button(("Add " + cube.name).c_str())) {

		cube.loc_vec_shape.push_back(glm::vec3(0.f, 0.f, 0.f));
		cube.color_index.push_back(glm::vec4(1.f, 1.f, 1.f , 1.f));
		cube.object_scale.push_back(glm::vec3(50.f));
		cube.tex_per_item.push_back(0);
	}

	ImGui::SameLine();
	if (ImGui::Button(("ERASE ALL : " + cube.name).c_str())) {
		cube.loc_vec_shape.clear();
		cube.color_index.clear();
		cube.object_scale.clear();
	}

	//Inittializing the vector iterator and falgs to delete deleted objs
	cube.erase_iter = cube.loc_vec_shape.begin();
	std::vector<bool> delete_flags(cube.loc_vec_shape.size(), false);
	
	//new window
	if(cube.loc_vec_shape.size() != 0)
		ImGui::Begin(cube.name.c_str());
	
	//ADD multiple objects:
	for (int n = 0; n < cube.loc_vec_shape.size(); n++) {

		ImGui::Text("item : %d", n);
		std::string  temp = std::to_string(n);

		ImGui::SliderFloat((cube.name + temp + "X").c_str(), &(cube.loc_vec_shape[n].x), -(float)WORLD_LENGTH, (float)WORLD_LENGTH);
		ImGui::SliderFloat((cube.name + temp + "Y").c_str(),&(cube.loc_vec_shape[n].y), -(float)WORLD_LENGTH, (float)WORLD_LENGTH);
		ImGui::SliderFloat((cube.name + temp + "Z").c_str(), &(cube.loc_vec_shape[n].z), -(float)WORLD_LENGTH, (float)WORLD_LENGTH);
		//scaling
		ImGui::SliderFloat3(("size " + cube.name + temp).c_str(), glm::value_ptr(cube.object_scale[n]), 0.f , (float)WORLD_LENGTH);
	
		//ImGui::SameLine();
		
		//color change:
		ImGui::ColorEdit3(("Color" + cube.name + temp).c_str(), glm::value_ptr(cube.color_index[n]));
		//colorend

		
		if (ImGui::BeginCombo(("2D Textures" + cube.name + " " + temp).c_str(), cube.tex_per_item[n] == 0 ? "Select a texture" : std::to_string(cube.tex_per_item[n]).c_str())) {
			for (int i = 0; i < TextureManager::Texture_2D_ID.size(); i++) {
				bool isSelected = (cube.tex_per_item[n] == i);
				if (ImGui::Selectable(std::to_string(TextureManager::Texture_2D_ID[i]).c_str(), isSelected))
					cube.tex_per_item[n] = TextureManager::Texture_2D_ID[i];
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		if (ImGui::Button(("Delete " + cube.name +" "+ temp).c_str())) {
			delete_flags[n] = true;
		}

		gf_render::Draw(cube, glm::value_ptr(cube.color_index[n]), cube.loc_vec_shape[n],sha,cube.object_scale[n], cube.tex_per_item[n] ,tex);
	}

	if (cube.loc_vec_shape.size() != 0)
		ImGui::End();

	//delete multiple objects
	for (int n = 0; n < cube.loc_vec_shape.size(); ++n) {
		if (delete_flags[n]) {
			cube.erase_iter = cube.loc_vec_shape.erase(cube.erase_iter);
			cube.color_index.erase(std::next(cube.color_index.begin(), n));
			cube.object_scale.erase(std::next(cube.object_scale.begin(), n));
			cube.tex_per_item.erase(std::next(cube.tex_per_item.begin(), n));
		}
		else {
			++cube.erase_iter;
		}
	}
	
}


void goof::play_game(const char* Scene_1)
{
	_Window window;

	Shader sha;
	sha.load_shader("dep/basic.vert");
	sha.load_shader("dep/basic.frag");
	sha.init_and_use_shader();


	Texture2D tex;
	tex.Init("dep/tex1.png");
	Texture2D tex2;
	tex.Init("dep/tex2.png");

	gf_render::Triangle triangle;
	gf_render::Rect rect;
	gf_render::Cube cube;


	goof::character2d player2d(W_HEIGHT / 2, W_WIDTH / 2, 0.0f);

	std::ifstream file1(Scene_1, std::ios::binary);
	if (file1.is_open()) {
		triangle.deserialize(file1);
		rect.deserialize(file1);
		cube.deserialize(file1);
		file1.close();
	}
	else
	{
		std::cerr << "Error: Unable to open file for reading.\n";
	}
	while (window.isWindowOpen()) {


		gf_render::ClearScreen();


		window.processInput(&player2d);
		player2d.doCollisions_with_all(true, &rect);
		player2d.update_pos(player2d.right, -player2d.up, 0, sha);

		goof::setViewMode(sha, orthographic);

		goof::render_game_level_objects(triangle, sha);
		goof::render_game_level_objects(rect, sha);
		goof::render_game_level_objects(cube, sha);

		window.swap_and_pollevents();
	}

}

void goof::render_game_level_objects(gf_render::shapes& cube, Shader& sha, goof::Texture2D* tex)
{
	for (int n = 0; n < cube.loc_vec_shape.size(); n++) {
		gf_render::Draw(cube, glm::value_ptr(cube.color_index[n]), cube.loc_vec_shape[n], sha, cube.object_scale[n], cube.tex_per_item[n],tex);
	}
}
