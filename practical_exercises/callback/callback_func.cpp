#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

enum cbFlags {
	ENUM_CB_NONE = -1,
	ENUM_CB_ONE,
	ENUM_CB_TWO,
	ENUM_CB_THREE,
	ENUM_CB_FOUR,
	ENUM_CB_MAX,
};

typedef int (*cbFuncPtr)(int, string);

class CBFunc {
    private:
	vector<vector<cbFuncPtr> > mVecFunc;
	// 已经注册的flag
	vector<cbFlags> mVecFlag;
	std::map<cbFlags, vector<cbFuncPtr> > mCallBackList;
	bool executeCallBack(cbFlags flag)
	{
		if (flag < ENUM_CB_NONE || flag > ENUM_CB_MAX) {
			cout << "ERROR, flag out range!!" << endl;
			return false;
		}

		vector<cbFuncPtr> vecFuc(mVecFunc[flag]);

		for (auto const func : vecFuc) {
			if (func)
				func(flag, "func");
		}
		return true;
	}

    public:
	CBFunc()
	{
		mVecFunc.resize(sizeof(cbFlags));
		cout << "call CBFunc" << endl;
	}

	~CBFunc()
	{
		cout << "call ~CBFunc" << endl;
	}
	bool setCallBack(cbFuncPtr func, cbFlags flag)
	{
		if (!func) {
			cout << "callback func is null!" << endl;
			return false;
		}
		if (flag < ENUM_CB_NONE || flag > ENUM_CB_MAX) {
			cout << "ERROR, flag out range!!" << endl;
			return false;
		}
		// 如果没有注册，则进行注册
		// if (!count(mVecFunc[flag - 1].begin(), mVecFunc[flag - 1].end(),
		// 	   func)) {
		// 	mVecFunc[flag - 1].push_back(func);
		// }

		vector<cbFuncPtr> vecFunc(mVecFunc[flag]);

		if (count(vecFunc.begin(), vecFunc.end(), func) > 0) {
			cout << "Error, func has registered!!\n";
			return true;
		} else {
			mVecFlag.push_back(flag);
		}
		// cout << std::hex << " func:" << func << std::oct << endl;
		mVecFunc[flag].push_back(func);
		// 更新注册列表
		mCallBackList.insert(std::pair<cbFlags, vector<cbFuncPtr> >(
			flag, mVecFunc[flag]));
		// cout << "mVecFunc size:" << mVecFunc[flag].size() << endl;
		return true;
	}

	int cbOneProgram(void)
	{
		cout << "cb one program called\n";
		executeCallBack(ENUM_CB_ONE);
		return 0;
	}
	int cbTwoProgram(void)
	{
		cout << "cb two program called\n";
		executeCallBack(ENUM_CB_TWO);
		return 0;
	}
	int cbThreeProgram(void)
	{
		cout << "cb three program called\n";
		executeCallBack(ENUM_CB_THREE);
		return 0;
	}
};

int callBackFunc1(int i, string str)
{
	cout << "callBackFunc1 i:" << i << " str:" << str << endl;
	return 0;
}
int callBackFunc1_1(int i, string str)
{
	cout << "callBackFunc1_1 i:" << i << " str:" << str << endl;
	return 0;
}

int callBackFunc2(int i, string str)
{
	cout << "callBackFunc2 i:" << i << " str:" << str << endl;
	return 0;
}

int callBackFunc3(int i, string str)
{
	cout << "callBackFunc3 i:" << i << " str:" << str << endl;
	return 0;
}

int main()
{
	CBFunc *cb = new CBFunc();
	// 注册
	cb->setCallBack(&callBackFunc1, ENUM_CB_ONE);
	cb->setCallBack(&callBackFunc1, ENUM_CB_ONE); // error， 已经注册过
	cb->setCallBack(&callBackFunc1_1, ENUM_CB_ONE);
	cb->setCallBack(&callBackFunc2, ENUM_CB_TWO);

	// 开始处理
	cb->cbOneProgram();
	cb->cbTwoProgram();
	cb->cbThreeProgram();
	if (cb)
		delete cb;
	return 0;
}
