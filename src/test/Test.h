#pragma once

namespace test {
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		//Update function run at a fixed framerate
		virtual void OnUpdate(float deltaTime) {}
		//On Render function for rendering
		virtual void OnRender() {}
		//Define and draw the ImGui stuff
		virtual void OnImGuiRender() {}
	};

}