#pragma once
#include <vector>
#include <string>
#include <functional>
#include <iostream>
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

	class TestMenu: public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name) {
			std::cout<< "Registering Test :" << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};

}