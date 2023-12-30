#include <Hazel.h>
#include <stdio.h>

class SandBox : public Hazel::Application {
public:
	SandBox();
	~SandBox();
	void Run() override;
	bool TestEvent();
};

SandBox::SandBox()
{

}

SandBox::~SandBox()
{

}

void SandBox::Run()
{
	HZ_CORE_TRACE("SandBox Run()");
	Hazel::KeyPressEvent p(1, 1);
	Hazel::EventDispatcher dis(p);
	//dis.Dispatch()

	while (true)
	{
		
	}
}

bool SandBox::TestEvent()
{

}

Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();
}