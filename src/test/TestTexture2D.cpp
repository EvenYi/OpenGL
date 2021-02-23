#include "TestTexture2D.h"
#include "imgui/imgui.h"
namespace test {
	TestTexture2D::TestTexture2D() :m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0))),
		m_Shader(std::make_unique<Shader>("res/shader/basic.shader")),
		m_Texture(std::make_unique<Texture>("res/textures/penpen.png")),
		m_Texture_T(std::make_unique<Texture>("res/textures/tears.png")),
		m_TranslationA(glm::vec3(200, 200, 0)),
		m_TranslationB(glm::vec3(100, 100, 0)),
		m_TranslationView(glm::vec3(0, 0, 0))
	{
		// Texture image in our case is flip upside down.
		// Texture coordinate start from left bottom is (0,0)
		float position[] = {
		-50.0f, 50.0f, 0.0f, 1.0f,0.18f,0.6f,0.96f,1.0f,0.0f,    //Squre point 0
		50.0f, 50.0f, 1.0f, 1.0f,0.18f,0.6f,0.96f,1.0f,0.0f,		//Squre point 1 Duplicated point
		-50.0f, -50.0f, 0.0f, 0.0f,0.18f,0.6f,0.96f,10.f,0.0f,	//Squre point 2 Duplicated point
		50.0f, -50.0f, 1.0f, 0.0f,0.18f,0.6f,0.96f,10.f,0.0f,	//Squre point 3

		70.0f, 50.0f, 0.0f, 1.0f,1.0f,0.93f,0.24f,1.0f,1.0f,    //Squre point 4
		170.0f, 50.0f, 1.0f, 1.0f,1.0f,0.93f,0.24f,1.0f,1.0f,	//Squre point 5 Duplicated point
		70.0f, -50.0f, 0.0f, 0.0f,1.0f,0.93f,0.24f,1.0f,1.0f,	//Squre point 6 Duplicated point
		170.0f, -50.0f, 1.0f, 0.0f,1.0f,0.93f,0.24f,1.0f,1.0f	//Squre point 7
		}; //Define the data
		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(position, 9 * 8 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2); //Since our vertex is 2 dimensional the parameter is 2;
		layout.Push<float>(2); //Our vertex texture coordinate is 2 dimensional the parameter is 2;
		layout.Push<float>(4); //Our color 4 dimensional the parameter is 2;
		layout.Push<float>(1); //Choose texture id;
		m_VAO->Addbuffer(*m_VertexBuffer, layout);
		unsigned int indices[] = {
			0,1,2, //The up triangle three vertex indices
			1,2,3, //The down triangle three vertex indices

			4,5,6, //The up triangle three vertex indices
			5,7,6 //The down triangle three vertex indices

		}; //Define the data
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);
		m_Shader->Bind();
		//Bound texture 0 in slot 0
		m_Texture->Bind();
		//Bound texture 1 in slot 1
		m_Texture_T->Bind(1);
	
		int samples[2] = { 0,1 };
		m_Shader->SetUniform1iv("u_Texture", 2, samples);
	}
	TestTexture2D::~TestTexture2D()
	{
	}
	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}
	void TestTexture2D::OnRender()
	{
		Renderer renderer;
		{
			glm::mat4 mode = glm::translate(glm::mat4(1.0), m_TranslationA);
			glm::mat4 view = glm::translate(m_View, m_TranslationView);
			glm::mat4 mvp = m_Proj * view * mode;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

		}
		/*
		//Draw object B
		{
			glm::mat4 mode = glm::translate(glm::mat4(1.0), m_TranslationB);
			glm::mat4 view = glm::translate(m_View, m_TranslationView);
			glm::mat4 mvp = m_Proj * view * mode;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
		*/
	}
	void TestTexture2D::OnImGuiRender()
	{
		{
			//Since translation is 3D float we need use SliderFloat3
			//ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
			//ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
			ImGui::SliderFloat3("TranslationView", &m_TranslationView.x, 0.0f, 100.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
	}
}