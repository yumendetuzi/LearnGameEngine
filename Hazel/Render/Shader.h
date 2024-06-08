#pragma once
#include <string>
namespace Hazel {
	class  Shader {
	public:
		Shader(const std::string& vertex, const std::string& fragment);
		~Shader();
		void Bind();
		void Unbind();
	private:
		int mID;		
	};

}
