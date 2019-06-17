#pragma once
/*
#pragma pack(push,1)
struct uint24_t
{
	unsigned int v : 24;
};
#pragma pack(pop)


class UInt24_t
{
private:
	const int Uint24_t_MAX = 16777215;
	const int Uint24_t_MIN = 0;
	unsigned char value[3]{}; // массивчик для хранения значащих байт
public:
	UInt24_t(){};

	UInt24_t(UInt24_t& val)
	{
		*this = val;
	}

	template <typename T>
	UInt24_t(T& val) // в зависимости от типа данных мы обрежем его до 3 первых байт, т.е. по сути гавно если значение больше Uint24_t_MAX
	{
		value[0] = val[0];
		value[1] = val[1];
		value[2] = val[2];
	}

	template <typename T>
	operator T(){
		return (0xff << 24) | (value[2] << 16)
							| (value[1] << 8)
							| value[0];
	}

	template <typename T>
	UInt24_t& operator= (T& input)
	{
		value[0] = input.value[0];
		value[1] = input.value[1];
		value[2] = input.value[2];
		return *this;
	}
	template<typename T>
	UInt24_t& operator= (T input)
	{
		value[0] = reinterpret_cast<unsigned char*>(&input)[0];
		value[1] = reinterpret_cast<unsigned char*>(&input)[1];
		value[2] = reinterpret_cast<unsigned char*>(&input)[2];
		return *this;
	}
	UInt24_t operator+(UInt24_t& input) 
	{
		
		value[0] = this->value[0] + reinterpret_cast<unsigned char*>(&input)[0];
		value[1] = this->value[1] + reinterpret_cast<unsigned char*>(&input)[1];
		value[2] = this->value[2] + reinterpret_cast<unsigned char*>(&input)[2];
		return *this;
	}
	~UInt24_t();
};
*/