#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;
/*
 * @Author: Gu Tiankai
 * @Desc: K-Sort in Memory
 * @Date: 2017.05.13
 */

/*
 *	==============================================>
 *		Declaration Part
 *  ==============================================>
 */

//#define DEBUG_SWITCH	//������Ϣ����
#define GEN_FACTOR  ((int)1000)
#define TOP_K		((int)100)	

class Sorter
{
public:
	auto rev_generate() -> vector<unsigned int>;		//��������
	auto ord_generate() -> vector<unsigned int>;		//˳������
	auto rnd_generate() -> vector<unsigned int>;		//�������
	auto inorder_generate() -> vector<unsigned int>;	//ԭ������

	/*Default: vector<unsigned int>().max_size()/GEN_FACTOR*/
	Sorter() : generator(Generator(/*Customization Number*/)){}

private: 
	class Generator //�����������
	{
	public:
		Generator(int _genTols = vector<unsigned int>().max_size()/GEN_FACTOR) : genTols(_genTols)
		{
			vals.reserve(genTols);
			vals.resize(genTols);
			init();
		}

		auto get() -> vector<unsigned int> {return vals;} //����������ģ������

	private:
		vector<unsigned int> vals;
		int genTols;

		void init();
	};
	Generator generator;
};

class Solution
{
#define PAR(i)	((i-1)/2)		//��ȡ���ڵ�����
#define LEFT(i) (2*i+1)			//��ȡ��ڵ�����
#define RIGHT(i) (2*i+2)		//��ȡ�ҽڵ�����

public:
	Solution() {}
	Solution(vector<unsigned int> _vals):vals(_vals){ initHeap(); }
	
	void changeVals(vector<unsigned int> _vals) { vals.clear(); vals = _vals; initHeap();}	//���Ľ�������
	void selelectK(vector<unsigned int>& __klist, int k);	//ѡ��ǰK����

private:
	vector<unsigned int> vals;

	void initHeap();
	void matinHeap(int i, int length);
};

/*
 *	==============================================<
 *		Declaration Part End
 *  ==============================================<
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
	//	vals.push_back(unsigned int(rand()));

	// for high efficiency
	for_each(begin(vals), end(vals), [=](unsigned int& val) mutable -> void {
		val = unsigned int(rand());
	});

	sort(vals.begin(), vals.end());
}

////��������
inline vector<unsigned int> Sorter::rev_generate()
{
	vector<unsigned int> _vals = generator.get();
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

//˳������
inline vector<unsigned int> Sorter::ord_generate()
{
	return move(generator.get());
}

//�������
inline vector<unsigned int> Sorter::rnd_generate()
{
	vector<unsigned int> _vals = generator.get();
	for (int i = 0; i < _vals.size(); ++i)
	{
		int rndindex = (int)rand()%_vals.size();
		auto tmp =  _vals[rndindex];
		_vals[rndindex] = _vals[i];
		_vals[i] = tmp;
	}

	return move(_vals);
}


inline vector<unsigned int> Sorter:: inorder_generate()
{
	return move(generator.get());
}

inline void Solution::initHeap()
{ 
	int size = vals.size() - 1;
	for (int i = PAR(size); i >= 0; i --)
		matinHeap(i, size);
}

inline void Solution::matinHeap(int i, int length)
{
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
inline void Solution::selelectK(vector<unsigned int>& __klist, int k)
{
	__klist.clear();

	for (int i = vals.size() - 1; vals.size() -1 - i != k && i >= 0; i--)
	{
		__klist.push_back(vals[0]);
		vals[0] = vals[i];
		matinHeap(0, i);
	}
}

/*
 *	==============================================
 *		Implementation Part End
 *  ==============================================
 */



/*
 *	==============================================
 *		Test Part Start
 *  ==============================================
 */
int main()
{
	Sorter sorter;
	vector<unsigned int> list = sorter.ord_generate();
	Solution s(sorter.ord_generate());
	
	cout << "Default Toltal: vector<unsigned int>().max_size()/GEN_FACTOR" << endl;
	cout << "Top-K: " << TOP_K << "\n" << endl;
	vector<unsigned int> klist;
	s.selelectK(klist, TOP_K);
	cout << "Test Case 1(In Ord): ";
#ifdef DEBUG_SWITCH
	for (const auto& e: list)
		cout << e << " ";
	cout << endl <<  endl;
#endif
	for (const auto& e: klist)
		cout << e << " ";
	cout << endl << endl;

	list = sorter.rev_generate();
	s.changeVals(sorter.rev_generate());
	s.selelectK(klist, TOP_K);
	cout << "Test Case 2(Rev Ord): ";
#ifdef DEBUG_SWITCH
	for (const auto& e: list)
		cout << e << " ";
	cout << endl <<  endl;
#endif
	for (const auto& e: klist)
		cout << e << " ";
	cout << endl << endl;

	list = sorter.rnd_generate();
	s.changeVals(sorter.rnd_generate());
	s.selelectK(klist, TOP_K);
	cout << "Test Case 3(Rnd Ord): ";
#ifdef DEBUG_SWITCH
	for (const auto& e: list)
		cout << e << " ";
	cout << endl <<  endl;
#endif
	for (const auto& e: klist)
		cout << e << " ";
	cout << endl << endl;
}
/*
 *	==============================================
 *		Test Part End
 *  ==============================================
 */