#include <iostream>

int main()
{
	int i = 0, &r = i;
	auto a = r;   // a��һ��������r��i�ı�������i����һ��������

	const int ci = i, &cr = ci;
	auto b = ci; // b��һ��������ci�Ķ���const���Ա����Ե��ˣ�
	auto c = cr; // c��һ��������cr��ci�ı�����ci������һ������const��
	auto d = &i; // d��һ������ָ�루�����ĵ�ַ����ָ��������ָ�룩
	auto e = &ci; // e��һ��ָ������������ָ�루�Գ�������ȥ��ַ��һ�ֵײ�const��

	const auto f = ci; // ci������������int��f��const int
	auto &g = ci; // g��һ�����ͳ������ã��󶨵�ci

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << e << std::endl;
	std::cout << f << std::endl;
	std::cout << g << std::endl;
	std::cout << "--------------" << std::endl;
	a = 42; b = 42; c = 42; //d = 42; e = 42; g = 42;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << e << std::endl;
	std::cout << f << std::endl;
	std::cout << g << std::endl;

	return 0;
}