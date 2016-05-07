#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

/*
#include <windows.h>
#include <fstream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	char *s = "C:\\3.bmp";

	ifstream input;
	input.open(s, ios::binary);

	input.read(reinterpret_cast<char*>(&bfh.bfType), sizeof(bfh.bfType));
	input.read(reinterpret_cast<char*>(&bfh.bfSize), sizeof(bfh.bfSize));
	input.read(reinterpret_cast<char*>(&bfh.bfReserved1), sizeof(bfh.bfReserved1));
	input.read(reinterpret_cast<char*>(&bfh.bfReserved2), sizeof(bfh.bfReserved2));
	input.read((char*)&bfh.bfOffBits, sizeof(bfh.bfOffBits));

	input.seekg(sizeof(bih), ios_base::cur);
	


	cout << sizeof(bfh) << " " << sizeof(bih) << " " << endl;
	cout << bfh.bfOffBits << endl;

	char a;

	input.read(&a, 1);

	cout << (int)a << endl;


int main() {
	ofstream os("temp.bmp", ios::binary);

	unsigned char signature[2] = { 'B', 'M' };
	unsigned int fileSize = 14 + 40 + 100 * 100 * 4;
	unsigned int reserved = 0;
	unsigned int offset = 14 + 40;

	unsigned int headerSize = 40;
	unsigned int dimensions[2] = { 100, 100 };
	unsigned short colorPlanes = 1;
	unsigned short bpp = 32;
	unsigned int compression = 0;
	unsigned int imgSize = 100 * 100 * 4;
	unsigned int resolution[2] = { 2795, 2795 };
	unsigned int pltColors = 0;
	unsigned int impColors = 0;

	os.write(reinterpret_cast<char*>(signature), sizeof(signature));
	os.write(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
	os.write(reinterpret_cast<char*>(&reserved), sizeof(reserved));
	os.write(reinterpret_cast<char*>(&offset), sizeof(offset));

	os.write(reinterpret_cast<char*>(&headerSize), sizeof(headerSize));
	os.write(reinterpret_cast<char*>(dimensions), sizeof(dimensions));
	os.write(reinterpret_cast<char*>(&colorPlanes), sizeof(colorPlanes));
	os.write(reinterpret_cast<char*>(&bpp), sizeof(bpp));
	os.write(reinterpret_cast<char*>(&compression), sizeof(compression));
	os.write(reinterpret_cast<char*>(&imgSize), sizeof(imgSize));
	os.write(reinterpret_cast<char*>(resolution), sizeof(resolution));
	os.write(reinterpret_cast<char*>(&pltColors), sizeof(pltColors));
	os.write(reinterpret_cast<char*>(&impColors), sizeof(impColors));

	unsigned char x, r, g, b;

	for (int i = 0; i < dimensions[1]; ++i)
	{
		for (int j = 0; j < dimensions[0]; ++j)
		{
			x = 0;
			r = rand() % 256;
			g = rand() % 256;
			b = rand() % 256;
			os.write(reinterpret_cast<char*>(&b), sizeof(b));
			os.write(reinterpret_cast<char*>(&g), sizeof(g));
			os.write(reinterpret_cast<char*>(&r), sizeof(r));
			os.write(reinterpret_cast<char*>(&x), sizeof(x));
		}
	}

	os.close();

	system("pause");
	return 0;
}
*/

int colorExtraction(unsigned int byte, int mask) {
	if (mask == 0) return 0;

	int Mask = mask;
	int maskPadding = 0;

	while (!(Mask & 1)) {
		Mask >>= 1;
		maskPadding++;
	}

	return (mask & byte) >> maskPadding;
}


int main() {
	setlocale(LC_ALL, "rus");


	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	ifstream input("C:\\Users\\Public\\Pictures\\111.bmp", ios::binary);

	unsigned int RedMask, GreenMask, BlueMask, AlphaMask = 0;
	/*
	input.read(reinterpret_cast<char*>(&bfh.bfType), sizeof(bfh.bfType));
	input.read(reinterpret_cast<char*>(&bfh.bfSize), sizeof(bfh.bfSize));
	input.read(reinterpret_cast<char*>(&bfh.bfReserved1), sizeof(bfh.bfReserved1));
	input.read(reinterpret_cast<char*>(&bfh.bfReserved2), sizeof(bfh.bfReserved2));
	input.read(reinterpret_cast<char*>(&bfh.bfOffBits), sizeof(bfh.bfOffBits));
	*/
	input.read(reinterpret_cast<char*>(&bfh), sizeof(bfh));

	if (bfh.bfOffBits != 54) {
		cout << "ОШИБКА! \n Такая картинка не поддерживается" << endl;
		system("pause");
		return 0;
	}

	input.read(reinterpret_cast<char*>(&bih.biSize), sizeof(bih.biSize));
	
	
	if (bih.biSize != 40) {
		cout << "ОШИБКА! \n Такая картинка не поддерживается" << endl;
		system("pause");
		return 0;
	}



	input.read(reinterpret_cast<char*>(&bih.biWidth), sizeof(bih.biWidth));
	input.read(reinterpret_cast<char*>(&bih.biHeight), sizeof(bih.biHeight));
	input.read(reinterpret_cast<char*>(&bih.biPlanes), sizeof(bih.biPlanes));
	input.read(reinterpret_cast<char*>(&bih.biBitCount), sizeof(bih.biBitCount));
	input.read(reinterpret_cast<char*>(&bih.biCompression), sizeof(bih.biCompression));
	input.read(reinterpret_cast<char*>(&bih.biSizeImage), sizeof(bih.biSizeImage));
	input.read(reinterpret_cast<char*>(&bih.biXPelsPerMeter), sizeof(bih.biXPelsPerMeter));
	input.read(reinterpret_cast<char*>(&bih.biYPelsPerMeter), sizeof(bih.biYPelsPerMeter));
	input.read(reinterpret_cast<char*>(&bih.biClrUsed), sizeof(bih.biClrUsed));
	input.read(reinterpret_cast<char*>(&bih.biClrImportant), sizeof(bih.biClrImportant));

	RGBQUAD **rgb;

	rgb = new RGBQUAD *[bih.biHeight];
	for (int i = 0; i < bih.biHeight; i++) {
		rgb[i] = new RGBQUAD[bih.biWidth];
	}

	int linePadding = ((bih.biWidth * (bih.biBitCount / 8)) % 4) & 3;

	unsigned int colorsCount = bih.biBitCount >> 3;
	if (colorsCount < 3) {
		colorsCount = 3;
	}

	if (bih.biBitCount != 24) {
		cout << "Ошибка! \n на данный момент поддерживаются только 24-битные картинки!" << endl;
	}

	int bitsOnColor = bih.biBitCount / colorsCount;
	unsigned int maskValue = (1 << bitsOnColor) - 1;
	RedMask = maskValue << (bitsOnColor * 2);
	GreenMask = maskValue << (bitsOnColor);
	BlueMask = maskValue;

	unsigned int byte;

	for (int i = 0; i < bih.biHeight; i++) {
		for (int j = 0; j < bih.biWidth; j++) {
			input.read(reinterpret_cast<char*>(&byte), bih.biBitCount / 8);
			rgb[i][j].rgbRed = colorExtraction(byte, RedMask);
			rgb[i][j].rgbGreen = colorExtraction(byte, GreenMask);
			rgb[i][j].rgbBlue = colorExtraction(byte, BlueMask);
		}
		input.seekg(linePadding, ios_base::cur);
	}

	for (int i = bih.biHeight-1; i >= 0; i--) {
		for (int j = bih.biWidth-1; j >= 0; j--) {
			cout << (int)rgb[i][j].rgbRed << "\\" << (int)rgb[i][j].rgbGreen << "\\" << (int)rgb[i][j].rgbBlue << " ";
		}
		cout << endl;
	}

	system("pause");

}