#pragma once
#include "Test.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Texture.h"
namespace test {
	class TestTexture2D: public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		//Update function run at a fixed framerate
		void OnUpdate(float deltaTime) override;
		//On Render function for rendering
		void OnRender() override;
		//Define and draw the ImGui stuff
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Texture> m_Texture_T;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB, m_TranslationView;
	};

}
