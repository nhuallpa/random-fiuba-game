#ifndef DataBmp24_H
#define DataBmp24_H

#include <list>
#include <vector>

#include "DataBmp.h"
#include "PixelBmp.h"


using namespace std;

class DataBmp24 : public DataBmp
{


public:
    DataBmp24(unsigned char* data,int row_padded, int height,int width);
    DataBmp24();
	virtual ~DataBmp24();

protected:
		void loadMatrix(unsigned char* data,int row_padded, int height,int width);


};

#endif // DataBmp24_H
