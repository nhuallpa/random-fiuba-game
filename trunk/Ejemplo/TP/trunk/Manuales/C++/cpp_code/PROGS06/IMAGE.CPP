
class Image {
public:
				Image	(const int w, const int h);
private:
	const int	width;
	const int	height;
    //...
};

Image::Image (const int w, const int h) : width(w), height(h)
{
	//...
}
