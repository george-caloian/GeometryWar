#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>


struct struct_oponent {
	std::string name;
	float angle;
	float x, y;
	int life;
	struct_oponent(std::string name, float angle, float x, float y, int life) :name(name), angle(angle), x(x), y(y), life(life) {}
};

struct struct_bullet {
	std::string name;
	float angle;
	float x, y;
	struct_bullet(std::string name, float angle, float x, float y):name(name), angle(angle), x(x), y(y) {}
};



class Laborator3 : public SimpleScene
{
	public:
		Laborator3();
		~Laborator3();

		void Init() override;
		Mesh * CreateMesh(const char * name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
	

	protected:
		glm::mat3 modelMatrix;
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;
		float posX, posY ;
		
		std::vector<struct_bullet> bullets;
		float interval = 0;
		std::vector<struct_oponent> oponents;
		int lives_rem = 3;
	
		float spat = 2;
		
		
		
};



