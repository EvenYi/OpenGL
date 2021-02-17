#include "TestTexture2D.h"
#include "imgui/imgui.h"
namespace test {
	TestTexture2D::TestTexture2D():m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0))),
		m_Shader(std::make_unique<Shader>("res/shader/basic.shader")),
		m_Texture(std::make_unique<Texture>("res/textures/penpen.png")),
		m_TranslationA(glm::vec3(200, 200, 0)),
		m_TranslationB(glm::vec3(100, 100, 0))
	{
		// Texture image in our case is flip upside down.
		// Texture coordinate start from left bottom is (0,0)
		float position[] = {
		-50.0f, 50.0f, 0.0f, 1.0f,    //Squre point 0
		50.0f, 50.0f, 1.0f, 1.0f,		//Squre point 1 Duplicated point
		-50.0f, -50.0f, 0.0f, 0.0f,	//Squre point 2 Duplicated point
		50.0f, -50.0f, 1.0f, 0.0f		//Squre point 3
		}; //Define the data
		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer=std::make_unique<VertexBuffer>(position, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2); //Since our vertex is 2 dimensional the parameter is 2;
		layout.Push<float>(2); //Our vertex texture coordinate is 2 dimensional the parameter is 2;
		m_VAO->Addbuffer(*m_VertexBuffer, layout);
		unsigned int indices[] = {
			0,1,2, //The up triangle three vertex indices
			1,3,2  //The down triangle three vertex indices

		}; //Define the data
		m_IndexBuffer=std::make_unique<IndexBuffer>(indices, 6);
		m_Shader->Bind();
		m_Texture->Bind();
		//Since we bound our texture in slot 0
		m_Shader->SetUniform1i("u_Texture", 0);
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
			glm::mat4 mvp = m_Proj * m_View * mode;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO,*m_IndexBuffer, *m_Shader);

		}
		//Draw object B
		{
			glm::mat4 mode = glm::translate(glm::mat4(1.0), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * mode;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}
	void TestTexture2D::OnImGuiRender()
	{
		{
			//Since translation is 3D float we need use SliderFloat3
			ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
			ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
	}
}