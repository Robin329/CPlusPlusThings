#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <string.h>

using namespace std;

enum cbFlags {
	ENUM_CB_NONE = -1,
	ENUM_CB_ONE,
	ENUM_CB_TWO,
	ENUM_CB_THREE,
	ENUM_CB_FOUR,
	ENUM_CB_MAX,
};

typedef struct user_data {
	string str;
	char ch;
	float f;
} user_data;
typedef struct out_data {
	bool result;
	int ret;
} out_data;

typedef int (*cbFuncPtr)(int, user_data *);

class CBFunc {
    private:
	vector<vector<cbFuncPtr> > mVecFunc;
	// 已经注册的flag
	vector<cbFlags> mVecFlag;
	user_data mUserData[sizeof(cbFlags)][32];
	std::map<cbFlags, vector<cbFuncPtr> > mCallBackList;
	bool executeCallBack(cbFlags flag, void *out)
	{
		if (flag < ENUM_CB_NONE || flag > ENUM_CB_MAX) {
			cout << "ERROR, flag out range!!" << endl;
			return false;
		}

		vector<cbFuncPtr> vecFuc(mVecFunc[flag]);
		int count = 0;
		out_data *outData = reinterpret_cast<out_data *>(out);

		for (auto const func : vecFuc) {
			if (func) {
				outData->ret =
					func(flag, &mUserData[flag][count]);
				outData->result = true;
				cout << "mOutData[" << flag << "][" << count
				     << "] ret:" << outData->ret << endl;
				++count;
			}
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
	bool setCallBack(cbFuncPtr func, cbFlags flag, void *in)
	{
		if (!func || !in) {
			cout << "callback func is null!" << endl;
			return false;
		}
		if (flag < ENUM_CB_NONE || flag > ENUM_CB_MAX) {
			cout << "ERROR, flag out range!!" << endl;
			return false;
		}

		vector<cbFuncPtr> vecFunc(mVecFunc[flag]);

		if (count(vecFunc.begin(), vecFunc.end(), func) > 0) {
			cout << "Error, func has registered!!\n";
			return true;
		} else {
			mVecFlag.push_back(flag);
		}
		// cout << std::hex << " func:" << func << std::oct << endl;
		mVecFunc[flag].push_back(func);
		user_data *data = (struct user_data *)malloc(sizeof(user_data));

		memcpy(&mUserData[flag][mVecFunc[flag].size()], data,
		       sizeof(user_data));
		// 更新注册列表
		mCallBackList.insert(std::pair<cbFlags, vector<cbFuncPtr> >(
			flag, mVecFunc[flag]));
		// cout << "mVecFunc size:" << mVecFunc[flag].size() << endl;
		if (data)
			free(data);
		return true;
	}

	int cbOneProgram(void)
	{
		out_data out;
		memset(&out, 0, sizeof(out_data));

		executeCallBack(ENUM_CB_ONE, &out);
		cout << "cb one program called out(" << out.result << ", "
		     << out.ret << ")\n";
		return 0;
	}
	int cbTwoProgram(void)
	{
		out_data out;
		memset(&out, 0, sizeof(out_data));

		executeCallBack(ENUM_CB_TWO, &out);
		cout << "cb two program called out(" << out.result << ", "
		     << out.ret << ")\n";
		return 0;
	}
	int cbThreeProgram(void)
	{
		out_data out;
		memset(&out, 0, sizeof(out_data));

		executeCallBack(ENUM_CB_THREE, &out);
		cout << "cb three program called out(" << out.result << ", "
		     << out.ret << ")\n";
		return 0;
	}
};

// 外部需要回调的函数
int callBackFunc(int i, user_data *data)
{
	if (!data) {
		cout << "data is NULL!!!" << endl;
		return -1;
	}

	switch (i) {
	case 0:
		cout << "callBackFunc1 i:" << i << " ch:" << data->ch
		     << " f:" << data->f << endl;
		return 1;
	case 1:
		cout << "callBackFunc2 i:" << i << " ch:" << data->ch
		     << " f:" << data->f << endl;
		return 2;
	case 2:
		cout << "callBackFunc3 i:" << i << " ch:" << data->ch
		     << " f:" << data->f << endl;
		return 3;
	default:
		break;
	}

	return 5;
}
int callBackFuncPro(int i, user_data *data)
{
	if (!data) {
		cout << "data or out is NULL!!!" << endl;
		return -1;
	}
	cout << "callBackFunc Pro i:" << i << " ch:" << data->ch
	     << " f:" << data->f << endl;
	return 6;
}

int main()
{
	CBFunc *cb = new CBFunc();
	// 注册
	user_data data1 = { "inData1", 1, 1.0 };
	user_data data2 = { "inData2", 2, 2.0 };
	user_data data3 = { "inData3", 3, 3.0 };
	out_data out1, out2, out3;
	memset(&out1, 0, sizeof(out_data));
	memset(&out2, 0, sizeof(out_data));
	memset(&out3, 0, sizeof(out_data));
	cb->setCallBack(callBackFunc, ENUM_CB_ONE, &data1);

	cb->setCallBack(callBackFunc, ENUM_CB_ONE,
			&data2); // error， 已经注册过

	cb->setCallBack(callBackFuncPro, ENUM_CB_ONE, &data3);

	// 开始处理
	cb->cbOneProgram();
	cout << "out1: result:" << out1.result << " ret:" << out1.ret << endl;
	cb->cbTwoProgram();
	cout << "out2: result:" << out2.result << " ret:" << out2.ret << endl;
	cb->cbThreeProgram();
	cout << "out3: result:" << out3.result << " ret:" << out3.ret << endl;
	if (cb)
		delete cb;

	return 0;
}
