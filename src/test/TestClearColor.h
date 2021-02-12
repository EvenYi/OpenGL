#pragma once
#include "Test.h"

namespace test {
	class TestClearColor: public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		//Update function run at a fixed framerate
		void OnUpdate(float deltaTime) override;
		//On Render function for rendering
		void OnRender() override;
		//Define and draw the ImGui stuff
		void OnImGuiRender() override;

	private:
		//Store actual color
		float m_ClearColor[4];

	};

}