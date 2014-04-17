#ifndef DataBmp32_H
#define DataBmp32_H

#include <list>
#include <vector>

#include "DataBmp.h"
#include "PixelBmp.h"


using namespace std;

class DataBmp32 : public DataBmp
{


public:
    DataBmp32(unsigned char* data,int row_padded, int height,int width);
    DataBmp32();
	virtual ~DataBmp32();

protected:
		void loadMatrix(unsigned char* data,int row_padded, int height,int width);


};

#endif // DataBmp32_H
