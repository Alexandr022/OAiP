// lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lab3.h"

BMPfile initBMPstruct(FILE* file)
{
	BMPfile BMP;
	fread(&BMP.BMPHead, sizeof(BMP.BMPHead), 1, file);
	fread(&BMP.BMPinfo, sizeof(BMP.BMPinfo), 1, file);

	fseek(file, 0, SEEK_SET);
	BMP.head = (unsigned char*)malloc(BMP.BMPHead.offset);
	fread(BMP.head, sizeof(unsigned char), BMP.BMPHead.offset, file);

	BMP.pixels = (unsigned char*)malloc(BMP.BMPinfo.width * BMP.BMPinfo.height * BMP.BMPinfo.bitsPixels / 8);

	for (int i = 0; !feof(file); i++)
	{
		fread(&BMP.pixels[i], sizeof(unsigned char), 1, file);
	}

	return BMP;
}

void outputBMPfile(FILE* file, BMPfile BMP)
{
	fwrite(BMP.head, sizeof(unsigned char), BMP.BMPHead.offset, file);

	for (int i = 0; i < BMP.BMPinfo.width * BMP.BMPinfo.height * BMP.BMPinfo.bitsPixels / 8; i++)
	{
		fwrite(&BMP.pixels[i], sizeof(unsigned char), 1, file);
	}
}

void convertToNegative(BMPfile BMP)
{
	for (int i = 0; i < BMP.BMPinfo.width * BMP.BMPinfo.height * BMP.BMPinfo.bitsPixels / 8; i++)
	{
		BMP.pixels[i]= ~BMP.pixels[i];
	}
}

void convertToBlackAndWhite(BMPfile BMP)
{
	if (BMP.BMPinfo.bitsPixels == 24)
	{
		int gray;

		for (int i = 0; i < BMP.BMPinfo.width * BMP.BMPinfo.height * BMP.BMPinfo.bitsPixels / 8; i += 3)
		{
			gray = (BMP.pixels[i] + BMP.pixels[i + 1] + BMP.pixels[i + 2]) / 3;
			BMP.pixels[i] = gray;
			BMP.pixels[i + 1] = gray;
			BMP.pixels[i + 2] = gray;
		}
	}
	if (BMP.BMPinfo.bitsPixels == 16)
	{
		int i, j;
		unsigned char grayValue;
		int brightness = 128; 
		
		for (i = 0; i < BMP.BMPinfo.height; i++)
		{
			for (j = 0; j < BMP.BMPinfo.width; j++)
			{
				grayValue = 0.2989 * BMP.pixels[(i * BMP.BMPinfo.width + j) * 3 + 2] + 0.5870 * BMP.pixels[(i * BMP.BMPinfo.width + j) * 3 + 1] + 0.1140 * BMP.pixels[(i * BMP.BMPinfo.width + j) * 3];

				if (grayValue >= brightness)
				{
					BMP.pixels[(i * BMP.BMPinfo.width + j) * 3 + 2] = 255;
					BMP.pixels[(i * BMP.BMPinfo.width + j) * 3 + 1] = 255;
					BMP.pixels[(i * BMP.BMPinfo.width + j) * 3] = 255;
				}
				else
				{
					BMP.pixels[(i * BMP.BMPinfo.width + j) * 3 + 2] = 0;
					BMP.pixels[(i * BMP.BMPinfo.width + j) * 3 + 1] = 0;
					BMP.pixels[(i * BMP.BMPinfo.width + j) * 3] = 0;
				}
			}
		}
	}

	else
	{
		int gray;

		for (int i = 0; i < BMP.BMPinfo.width * BMP.BMPinfo.height * BMP.BMPinfo.bitsPixels / 8; i += 3)
		{
			gray = (0.2989 * BMP.pixels[i] + 0.5870 * BMP.pixels[i + 1] + 0.1140 * BMP.pixels[i + 2]) / 3;
			BMP.pixels[i] = gray;
			BMP.pixels[i + 1] = gray;
			BMP.pixels[i + 2] = gray;
		}
	}
}

void medianFilter(BMPfile* BMP, int filterSize)
{
	int pad = (4 - ((BMP->BMPinfo.width * BMP->BMPinfo.bitsPixels / 8) % 4)) % 4;

	unsigned char* tempPixels = (unsigned char*)malloc(BMP->BMPinfo.width * BMP->BMPinfo.height * BMP->BMPinfo.bitsPixels / 8);

	for (int i = 0; i < BMP->BMPinfo.width * BMP->BMPinfo.height * BMP->BMPinfo.bitsPixels / 8; i++)
	{
		tempPixels[i] = BMP->pixels[i];
	}

	for (unsigned int y = 0; y < BMP->BMPinfo.height; y++)
	{
		for (unsigned int x = 0; x < BMP->BMPinfo.width; x++)
		{
			int red = 0;
			int green = 0;
			int blue = 0;
			int count = 0;

			for (int fy = -filterSize / 2; fy <= filterSize / 2; fy++)
			{
				for (int fx = -filterSize / 2; fx <= filterSize / 2; fx++)
				{
					int xi = x + fx;
					int yi = y + fy;

					if (xi < 0 || xi >= BMP->BMPinfo.width || yi < 0 || yi >= BMP->BMPinfo.height)
					{
						continue;
					}

					int index = ((BMP->BMPinfo.height - yi - 1) * BMP->BMPinfo.width + xi) * BMP->BMPinfo.bitsPixels / 8;
					int b = tempPixels[index];
					int g = tempPixels[index + 1];
					int r = tempPixels[index + 2];
					blue += b;
					green += g;
					red += r;
					count++;
				}
			}
			int index = ((BMP->BMPinfo.height - y - 1) * BMP->BMPinfo.width + x) * BMP->BMPinfo.bitsPixels / 8;
			BMP->pixels[index] = (unsigned char)(blue / count);
			BMP->pixels[index + 1] = (unsigned char)(green / count);
			BMP->pixels[index + 2] = (unsigned char)(red / count);
		}
	}

	free(tempPixels);
}

int comparePixels(const void* a, const void* b)
{
	unsigned char pixelA = *(unsigned char*)a;
	unsigned char pixelB = *(unsigned char*)b;

	if (pixelA < pixelB)
	{
		return -1;
	}
	if (pixelA > pixelB)
	{
		return 1;
	}
	return 0;
}

void gammaCorrection(BMPfile BMP, double gamma)
{
	for (int i = 0; i < BMP.BMPinfo.width * BMP.BMPinfo.height * BMP.BMPinfo.bitsPixels / 8; i++)
	{
		double oldValue = (double)BMP.pixels[i];
		double newValue = pow(oldValue / 255.0, 1.0 / gamma) * 255.0;
		BMP.pixels[i] = (unsigned char)newValue;
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
