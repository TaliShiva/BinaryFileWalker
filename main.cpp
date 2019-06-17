#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <string> 
#include <filesystem>
#include "UInt24_t.h"
#include <iterator>

std::vector<unsigned int> keys{};
std::string path = "C:\\Users\\trixter\\source\\repos\\BinPacketAnalyzer\\BinPacketAnalyzer\\pn";
std::string key_ints_path = "C:\\Users\\trixter\\source\\repos\\BinPacketAnalyzer\\BinPacketAnalyzer\\key_ints.txt";

template <typename T>
T GetBigEndianBytes(char* pData)
{
	T seg {};
	for (int i = 0; i < sizeof(T); i++) {
		seg = (seg << 8) + *reinterpret_cast<unsigned char*>(pData);
		pData++;
	}
	return seg;
};

template<typename T>
void CuttingByteArray(std::ifstream& data, std::ofstream& output, unsigned file_size, std::filesystem::path& file_path)
{
	std::vector<std::pair<T, T>> blocks{};
	int type_size = sizeof(T);
	int counter = 0;
	if(file_size <= type_size)
	{
		std::cerr << "маленький файл" << std::endl;
		return;
	}
	while (counter <= file_size - type_size)
	{
		char* le = new char[8];
		data.seekg(counter, std::ios_base::beg);
		data.read(le , type_size);
		unsigned int leb = *reinterpret_cast<T*>(le);
		unsigned int beb = GetBigEndianBytes<T>(le);
		for(auto&i: keys)
		{
			if(leb == i || beb == i)
			{
				output << "In file: " << file_path << std::endl;
				output << "Data shift " << counter << std::endl;
				output << "Key found " << i << std::endl;
				output << std::endl;
			}
		}
		counter++;
		delete[] le;
	}
};

void GetKeyIntsFromFile(std::string& path)
{
	std::ifstream keyFileBuffer(path, std::ios::in);
	if (!keyFileBuffer.is_open())
	{
		std::cerr << " File don't open (keys)" << std::endl;
	}
	std::string key;
	while(getline(keyFileBuffer, key))
	{
		keys.push_back(stoi(key));
	}
	keyFileBuffer.close();
}


int main() {
	
	//uint24_t cock{ 1 };
	
	GetKeyIntsFromFile(key_ints_path);
	std::ofstream outputBuffer("Logi.txt", std::ios::out);

	for(const auto& entry : std::filesystem::directory_iterator(path)) // обход по всем файлам, не зависимости от типа
	{
		if (!entry.is_regular_file()) {continue;}
		unsigned int file_size = std::filesystem::file_size(entry.path());
		std::filesystem::path file_path = entry.path();
		std::ifstream fileBuffer(entry.path(), std::ios::in | std::ios::binary);
		if (!fileBuffer.is_open())
		{
			std::cerr << "  File don't open (main)" << std::endl;
		}
		CuttingByteArray<uint8_t>(fileBuffer, outputBuffer, file_size, file_path);
		CuttingByteArray<uint16_t>(fileBuffer, outputBuffer, file_size, file_path);
		//CuttingByteArray<UInt24_t>(fileBuffer, outputBuffer, file_size);
		CuttingByteArray<uint32_t>(fileBuffer, outputBuffer, file_size, file_path);
		fileBuffer.close();
	}
	outputBuffer.close();
	std::cout << " Application finished" << std::endl;
	system("PAUSE");
	return 0;
}
