#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"


using namespace std;

Laborator3::Laborator3(){}
Laborator3::~Laborator3(){}


void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	//pozitionare in centrul eranului
	translateX = resolution.x / 2;
	translateY = resolution.y / 2;


	{
		vector<VertexFormat> vertices
		{

			//definirea celor 5 puncte ce formeaza cele 2 triunghiuri
			//din structura unei nave
			VertexFormat(glm::vec3(-20, -40,  0), glm::vec3(1, 0.6, 0)),
			VertexFormat(glm::vec3(-20, 40,  0), glm::vec3(1, 0.6, 0)),
			VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1, 0.6, 0)),
			VertexFormat(glm::vec3(20, -40,  0), glm::vec3(1, 0.6, 0)),
			VertexFormat(glm::vec3(20, 40,  0), glm::vec3(1, 0.6, 0)),

		};

		vector<unsigned short> indices =
		{

			2,0,3,
			1,4,2,
		};



		Mesh *square1 = new Mesh("square1");
		square1->InitFromData(vertices, indices);
		AddMeshToList(square1);
	}

	{
		int dim = 5;
		vector<VertexFormat> vertices
		{
			
			//puncte necesare dreptunghiurilor ce sugereaza nr de vieti ramase
			VertexFormat(glm::vec3(dim, dim*2,  0), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(-dim, dim*2,  0), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(dim, -dim*2,  0), glm::vec3(1, 1, 0)),
			VertexFormat(glm::vec3(-dim, -dim*2,  0), glm::vec3(1, 1, 0)),


		};

		vector<unsigned short> indices = {
			1, 0, 3,
			3, 2, 0 };

		Mesh *scor1 = new Mesh("scor1");
		scor1->InitFromData(vertices, indices);
		AddMeshToList(scor1);
	}

}



void Laborator3::FrameStart()
{
	
	glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	if (lives_rem) {

		glm::ivec2 resolution = window->GetResolution();

		int i = 1;

		//in functie de care vieti ramase sunt randam un nr corespunzator de dreeptunghiuri
		while (i <= lives_rem)
		{
			std::string nume = "scor1";
			
			modelMatrix = glm::mat3(1);

			//pozitionam dreptunghiurile in coltul dreapta sus usor departate unele de altele
			modelMatrix = Transform2D::Translate(resolution.x - i * 40, resolution.y - 20);

			RenderMesh2D(meshes[nume], shaders["VertexColor"], modelMatrix);

			i++;
		}



	
		interval = interval + deltaTimeSeconds;
		if (interval >= spat)
		{
			
			int aux_ang = rand() % 360;

			//calcul coordonate relative nava inamic in functie de unghi si distanta 
			//fata de nava player
			float x_opo = 450*cos(float(aux_ang* M_PI/180));
			float y_opo = 450*sin(float(aux_ang* M_PI/180));


			std::string name("opos");
			
			//coordonate reale din cele relative
			float sumX = translateX + x_opo;
			float sumY = translateY + y_opo;
			oponents.push_back(struct_oponent(name, aux_ang, sumX, sumY, 1));


			vector<VertexFormat> vertices
			{
				//inamicii sunt de acelasi tip ca si nava player
				VertexFormat(glm::vec3(-15, -15,  0), glm::vec3(0.5, 0.8, 0)),
				VertexFormat(glm::vec3(-15, 15,  0), glm::vec3(0.5, 0.8, 0)),
			
				VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0.5, 0.8, 0)),
				VertexFormat(glm::vec3(15, -15,  0), glm::vec3(0.5, 0.8, 0)),
				VertexFormat(glm::vec3(15, 15,  0), glm::vec3(0.5, 0.8, 0)),

			};
			vector<unsigned short> indices =
			{
				1,2,4,
				0,3,2,
			};

			//decrementez intervalul de timp dintre aparitiile navelor inamic
			
			if (spat>0.55)
				spat = spat - 0.05;

			Mesh *opomsh = new Mesh(name);
			opomsh->InitFromData(vertices, indices);
			AddMeshToList(opomsh);

			interval = 0;
		

		}
		 i = 0;
		while( i < oponents.size()) {
			modelMatrix = glm::mat3(1);
			float x_aux = oponents[i].x;
			float y_aux = oponents[i].y;
			modelMatrix *= Transform2D::Translate(x_aux, y_aux);

			if (oponents[i].x !=-1 && oponents[i].y !=-1)
			{

				float diffy = translateY - oponents[i].y;
				float diffx = translateX - oponents[i].x;

				//calcul unghi necesar propulsarii navei inamic spre nava player
				oponents[i].angle = atan2f(diffy,diffx);

				modelMatrix = glm::mat3(1);

				oponents[i].y += 160 * deltaTimeSeconds *  sin(oponents[i].angle);
				oponents[i].x += 160 *deltaTimeSeconds *  cos(oponents[i].angle);
				

				modelMatrix *= Transform2D::Translate(x_aux, y_aux);

				modelMatrix *= Transform2D::Rotate(atan2f(diffy, diffx));

				RenderMesh2D(meshes[oponents[i].name], shaders["VertexColor"], modelMatrix);

			}
			i++;
		}

		modelMatrix = glm::mat3(1);

		modelMatrix *= Transform2D::Translate(translateX, translateY);
		
		int crsY = resolution.y - posY - translateY;
		int crsX = posX - translateX;
		angularStep = atan2(crsY, crsX);


		modelMatrix *= Transform2D::Rotate(angularStep);


		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
		i = 0;
		while (i < bullets.size()) {

			bullets[i].y += 380 * deltaTimeSeconds *  sin(bullets[i].angle);
			bullets[i].x += 380*deltaTimeSeconds *  cos(bullets[i].angle);
			

			modelMatrix = glm::mat3(1);
			float g_x = bullets[i].x;
			float g_y = bullets[i].y;
			modelMatrix *= Transform2D::Translate(g_x,g_y);

			//fac si rotatie pentru ca sunt de forma dreptunghiulara si
			//dorim sa plece "perpendicular"
			modelMatrix *= Transform2D::Rotate(bullets[i].angle + M_PI/2);
			RenderMesh2D(meshes[bullets[i].name], shaders["VertexColor"], modelMatrix);

			i++;
		}

		i = 0;
		int j = 0;
		while (i < oponents.size())
		{
			while (j < bullets.size())
			{

				//verific daca a avut loc vre-o coliziune
				if (oponents[i].x+20>bullets[j].x && oponents[i].x-20<bullets[j].x && oponents[i].y+20 > bullets[j].y && oponents[i].y-20 <bullets[j].y)
				{
					if (j < bullets.size())
						bullets.erase(bullets.begin() + j);
					oponents.erase(oponents.begin() + i);
					break;
				}
				j++;
			}
			i++;
		}
		
		j = 0;
		while (j < oponents.size())
		{
			//verific daca a avut loc vre-o coliziune care sa avariee nava player
			if (oponents[j].x + 20 > translateX && oponents[j].x - 20 < translateX && oponents[j].y +20 > translateY && oponents[j].y - 20 < translateY)
			{
				oponents.erase(oponents.begin() + j);
				lives_rem--;
			}
			j++;
		}

	}


	else 
	{
		//jocul s-a terminat schimb culoarea ecranului
		glClearColor(1, 0, 0.1, 0.5);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void Laborator3::FrameEnd(){}
void Laborator3::OnKeyPress(int key, int mods) {}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	//deplasare OX si OY nava
	if (window->KeyHold(GLFW_KEY_W)) translateY += deltaTime * 200;
	if (window->KeyHold(GLFW_KEY_A)) translateX -= deltaTime * 200;
	if (window->KeyHold(GLFW_KEY_D)) translateX += deltaTime * 200;
	if (window->KeyHold(GLFW_KEY_S)) translateY -= deltaTime * 200;
}


void Laborator3::OnKeyRelease(int key, int mods){}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	posX = mouseX;
	posY = mouseY;

}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}

void Laborator3::OnWindowResize(int width, int height) {}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	modelMatrix = glm::mat3(1);


	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {

		std::string name("gloante");
	
		bullets.push_back(struct_bullet(name, angularStep, translateX, translateY));
		Mesh *bull = new Mesh(name);

		{
			int dim = 5;
			vector<VertexFormat> vertices
			{
				//gloantele au forma dreptunghiulara L=2l
				VertexFormat(glm::vec3(-dim, -dim*2,  0), glm::vec3(0.5, 0.1, 1)),
				VertexFormat(glm::vec3(dim, dim*2,  0), glm::vec3(0.5, 0.1, 1)),
				VertexFormat(glm::vec3(-dim, 2*dim,  0), glm::vec3(0.5, 0.1, 1)),
				VertexFormat(glm::vec3(dim, -dim*2,  0), glm::vec3(0.5, 0.1, 1)),
			};

			vector<unsigned short> indices = { 
				2, 0, 3,
				1 ,3, 2, 
			};

	
			bull->InitFromData(vertices, indices);
			AddMeshToList(bull);
		}
		
	}

	modelMatrix *= Transform2D::Translate(translateX, translateY);

	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
}


void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}