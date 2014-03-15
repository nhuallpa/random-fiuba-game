
class Image {
public:
				Image	(const int w, const int h);
private:
	int	width;
	int	height;
	int	&widthRef;
    //...
};

Image::Image (const int w, const int h) : widthRef(width)
{
	//...
}
