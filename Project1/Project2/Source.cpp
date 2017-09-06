#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;
/*
 * @Author: Gu Tiankai
 * @Desc: A Generator for virus' features
 * @Date: 2017.05.29
 */

/*
 *	==============================================>
 *		Declaration Part
 *  ==============================================>
 */
//#define DEBUG_SWITCH	//���Կ���
//#define HAS_GENERATED	//�ж��Ƿ��Ѿ����ɷֲ�ʽ�ļ� (��һ����ر�, ֮�����ע��)
//#define HEX			16//ʮ������
#define GEN_FACTOR  ((int)10000000)
#define CAPACITY	((int)100)
#define TOP_K		((int)1000)

class Sorter
{
public:
#ifndef HEX
	auto rev_generate() -> vector<long long>;		//��������
	auto ord_generate() -> vector<long long>;		//˳������
	auto rnd_generate() -> vector<long long>;		//�������
	//auto inorder_generate() -> vector<long long>;	//ԭ������
#endif
#ifdef HEX
	auto rev_generate() -> vector<string>;		//��������
	auto ord_generate() -> vector<string>;		//˳������
	auto rnd_generate() -> vector<string>;		//�������
#endif

	Sorter() : generator(Generator(/*Customization Number*/)){}

private:
	class Generator	//�����������
	{
	public:
		Generator(int _genTols = GEN_FACTOR / CAPACITY) : genTols(_genTols)
		{
			vals.reserve(genTols);	hexVals.reserve(genTols);
			vals.resize(genTols);	hexVals.resize(genTols);
			init();
		}
#ifndef HEX
		auto get() -> vector<long long> {return vals;} //����������ģ������
#endif
#ifdef HEX
		auto get() -> vector<string> {return hexVals; }	//����������ģ������
#endif

	private:
		vector<long long> vals;
		vector<string> hexVals;//ign
		int genTols;

		void init();
	};
	Generator generator;
};

class FileOut
{
public:
	FileOut():fileName_prefix("data"), fileName_suffix(".txt")		//���ɷֲ�ʽ�ļ� (RAII)
	{
		srand(time(NULL));
		for (int i = 0; i < CAPACITY; i++)
		{
#ifndef HAS_GENERATED
			Sorter sorter;
			ofstream out;
			stringstream ss;
			string buffer;
#ifndef HEX
			vector<long long>nums = sorter.rnd_generate();
#endif
#ifdef HEX
			vector<string>hexNums = sorter.rnd_generate();
#endif
#endif
			string fileName = fileName_prefix + to_string(i) + fileName_suffix;
			lists.resize(CAPACITY);
			lists[i] = fileName;
#ifndef HAS_GENERATED
#ifndef HEX
			for_each(begin(nums), end(nums), [&buffer](int val) -> void{
				buffer += to_string(val) + " ";
			});
#endif
#ifdef  HEX
			for_each(begin(hexNums), end(hexNums), [&buffer](string val) -> void{
				buffer += val + " ";
			});
#endif
			ss.rdbuf()->sputn(buffer.c_str(), buffer.size());	//buffered
			out.open(fileName, ios::out);
			out << ss.rdbuf();
			ss.str("");
			out.close();
#endif
		}
	}

	auto getFileName() -> vector<string>& {  return lists; }	// ��ȡ�����ļ���
private:
	vector<string> lists;
	string fileName_prefix;
	string fileName_suffix;
};

class FileIn
{
public:
	FileIn()
	{
	}

	const vector<long long> getArrayInDiskByFileName(string fileName);		//�����ļ��������������
	void matrix2vector(const vector<vector<long long>>&, vector<long long>& __list);	//����ά����ת��Ϊһά����
};

class Solution
{
#define PAR(i)	((i-1)/2)		//��ȡ���ڵ�����
#define LEFT(i) (2*i+1)			//��ȡ��ڵ�����
#define RIGHT(i) (2*i+2)		//��ȡ�ҽڵ�����

public:
	Solution() {}
	Solution(vector<long long> _vals):vals(_vals){ initHeap(); }
	
	void changeVals(vector<long long> _vals) { vals.clear(); vals = _vals; initHeap();}	//���Ľ�������
	void selelectK(vector<long long>& __klist, int k);	//ѡ��ǰK����

private:
	vector<long long> vals;

	void initHeap();
	void matinHeap(int i, int length);
};
/*
 *	==============================================>
 *		Declaration Part End
 *  ==============================================>
 */

/*
 *	==============================================
 *		Implementation Part
 *  ==============================================
 */
inline void Sorter :: Generator :: init()
{
	srand(time(NULL));
	//for (int i = 0; i < genTols; ++i)
	//	vals.push_back(long long(rand()));

	// for high efficiency
	string oxarys = "123456789ABCDEF";
#ifndef HEX
	for_each(begin(vals), end(vals), [=](long long& val) mutable -> void {
		val = long long(rand());
	});
#endif
#ifdef HEX
	for_each(begin(hexVals), end(hexVals), [=](string& hexVal) mutable -> void {
		std::random_shuffle(begin(oxarys), end(oxarys));
		hexVal = oxarys.substr(0, 8);
	});
#endif

	sort(vals.begin(), vals.end());
}

#ifndef HEX
inline vector<long long> Sorter::rev_generate()
{
	vector<long long> _vals = generator.get();
	int i = 0, j = _vals.size() - 1;
	while (i < j)
	{
		auto tmp = _vals[i];
		_vals[i] = _vals[j];
		_vals[j] = tmp;

		i++; j--;
	}

	return move(_vals);
}

inline vector<long long> Sorter::ord_generate()
{
	return move(generator.get());
}

inline vector<long long> Sorter::rnd_generate()
{
	vector<long long> _vals = generator.get();
	for (int i = 0; i < _vals.size(); ++i)
	{
		int rndindex = (int)rand()%_vals.size();
		auto tmp =  _vals[rndindex];
		_vals[rndindex] = _vals[i];
		_vals[i] = tmp;
	}

	return move(_vals);
}
#endif

#ifdef HEX
inline vector<string> Sorter::rev_generate()
{
	vector<string> _vals = generator.get();
	int i = 0, j = _vals.size() - 1;
	while (i < j)
	{
		auto tmp = _vals[i];
		_vals[i] = _vals[j];
		_vals[j] = tmp;

		i++; j--;
	}

	return move(_vals);
}

inline vector<string> Sorter::ord_generate()
{
	return move(generator.get());
}

inline vector<string> Sorter::rnd_generate()
{
	vector<string> _vals = generator.get();
	for (int i = 0; i < _vals.size(); ++i)
	{
		int rndindex = (int)rand()%_vals.size();
		auto tmp =  _vals[rndindex];
		_vals[rndindex] = _vals[i];
		_vals[i] = tmp;
	}

	return move(_vals);
}
#endif
//inline vector<long long> Sorter::inorder_generate()
//{
//	return generator.get();
//}

inline void Solution::initHeap()
{ 
	int size = vals.size() - 1;
	if (size <= 0)
		return;

	for (int i = PAR(size); i >= 0; i --)
		matinHeap(i, size);
}

inline void Solution::matinHeap(int i, int length)
{
	if (vals.size() <= 0)
		return;

	while (i >= 0 && i <= PAR(length) && vals[i] < max(vals[LEFT(i)], vals[RIGHT(i)<length?RIGHT(i):LEFT(i)]))
	{
		int maxindex = vals[LEFT(i)] > vals[RIGHT(i)<length?RIGHT(i):LEFT(i)] ? LEFT(i) : RIGHT(i)<length?RIGHT(i):LEFT(i);
		int tmp = vals[i];
		vals[i] = vals[maxindex];
		vals[maxindex] = tmp;

		i = maxindex;
	}
}

//ѡ��ǰK����
inline void Solution::selelectK(vector<long long>& __klist, int k)
{
	if (vals.size() <= 0)
		return;

	__klist.clear();

	for (int i = vals.size() - 1; vals.size() -1 - i != k && i >= 0; i--)
	{
		__klist.push_back(vals[0]);
		vals[0] = vals[i];
		matinHeap(0, i);
	}
}

//�����ļ��������������
inline const vector<long long> FileIn::getArrayInDiskByFileName(string fileName)
{
	ifstream fin(fileName, ios::in);
	if (!fin.is_open())
	{
		cout << "Open File Error" << endl;
		exit(0xff);
	}
	
	stringstream ss;
	string val;
	vector<long long> vals;

	ss << fin.rdbuf();
	while (ss >> val){
#ifndef HEX
		vals.push_back(atoi(val.c_str()));
#endif
#ifdef HEX
		vals.push_back(strtoul(val.c_str(), nullptr, HEX));
#endif
	}

#ifdef DEBUG_SWITCH
	cout << "debuging... " << endl;
	cout << "size: " << vals.size() << endl;
	for (const auto& e : vals)
		cout << e << " ";
	cout << endl;
#endif
	return move(vals);
}

//����ά����ת��Ϊһά����
inline void FileIn :: matrix2vector(const vector<vector<long long>>& vals2d, vector<long long>& __list)
{
	for (const auto& vals : vals2d)
		for (const auto& v : vals)
			__list.push_back(v);
}
/*
 *	==============================================
 *		Implementation Part End
 *  ==============================================
 */



int main()
{
	cout << "Creating Data Set... " << endl;
	int index = 0;
	FileOut fout;		//RAII 
	cout << "Creating Data Set Finished... " << endl;
	FileIn fin;
	Solution solution;
	vector<vector<long long>> val2d(CAPACITY, vector<long long>(TOP_K, 0));

	for(const auto& file : fout.getFileName())
	{
		solution.changeVals(
			fin.getArrayInDiskByFileName(file));	
		solution.selelectK(val2d[index++], TOP_K);
	}

	vector<long long> mixed2dVector;
	fin.matrix2vector(val2d, mixed2dVector);

	vector<long long> topk;
	solution.changeVals(mixed2dVector);
	solution.selelectK(topk, TOP_K);

	for (const auto& e: topk)
		cout << e << " ";
	cout << endl;
}