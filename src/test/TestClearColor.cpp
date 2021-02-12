#include "TestClearColor.h"
#include "../Renderer.h"
#include "imgui/imgui.h"
namespace test {
	//Initial the color
	TestClearColor::TestClearColor() :m_ClearColor{ 0.039f,0.729f,0.71f,1.0f }
	{
	}
	TestClearColor::~TestClearColor()
	{
	}
	void TestClearColor::OnUpdate(float deltaTime)
	{
	}
	void TestClearColor::OnRender()
	{
		//glClearColor specifies the red, green, blue, and alpha values used by glClear to clear the color buffers.
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		
		//glClear sets the bitplane area of the window to values 
		//previously selected by glClearColor, glClearDepth, and glClearStencil.
		//GL_COLOR_BUFFER_BIT Indicates the buffers currently enabled for color writing.
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

	}
	void TestClearColor::OnImGuiRender()
	{
		//Define the color control plane
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}