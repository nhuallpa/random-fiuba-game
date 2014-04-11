
#ifndef __CONTOUREXCEPTION__
#define __CONTOUREXCEPTION__

#include <string>
#include <exception>
#include <utility>

using namespace std;

namespace server_model_exp{
	
	class ContourExp : public exception{

		pair<int,string> e;
	public:
		ContourExp(pair<int,string> error) : exception(), e(error) {}
		const char* what() const throw();
		
	};
}

#endif /*__CONTOUREXCEPTION__*/
