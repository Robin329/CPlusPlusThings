## 练习13.1

> 拷贝构造函数是什么？什么时候使用它？

如果一个构造函数的第一个参数是自身类类型的引用，且任何额外参数都有默认值，则此构造函数是拷贝构造函数。当使用**拷贝初始化**时，我们会用到拷贝构造函数。

## 练习13.2

> 解释为什么下面的声明是非法的：
```cpp
Sales_data::Sales_data(Sales_data rhs);
```

参数类型应该是引用类型。

## 练习13.3

> 当我们拷贝一个StrBlob时，会发生什么？拷贝一个StrBlobPtr呢？

当我们拷贝 StrBlob时，会使 `shared_ptr` 的引用计数加1。当我们拷贝 StrBlobPtr 时，引用计数不会变化。

## 练习13.4

> 假定 Point 是一个类类型，它有一个public的拷贝构造函数，指出下面程序片段中哪些地方使用了拷贝构造函数：
```cpp
Point global;
Point foo_bar(Point arg) // 1
{
	Point local = arg, *heap = new Point(global); // 2: Point local = arg,  3: Point *heap = new Point(global) 
	*heap = local; 
	Point pa[4] = { local, *heap }; // 4, 5
	return *heap;  // 6
}
```

上面有6处地方使用了拷贝构造函数。


## [练习13.5](exercise13_5.h)

> 给定下面的类框架，编写一个拷贝构造函数，拷贝所有成员。你的构造函数应该动态分配一个新的string，并将对象拷贝到ps所指向的位置，而不是拷贝ps本身：
```cpp
class HasPtr {
public:
	HasPtr(const std::string& s = std::string()):
		ps(new std::string(s)), i(0) { }
private:
	std::string *ps;
	int i;
}
```

## 练习13.6

> 拷贝赋值运算符是什么？什么时候使用它？合成拷贝赋值运算符完成什么工作？什么时候会生成合成拷贝赋值运算符？

拷贝赋值运算符是一个名为 `operator=` 的函数。当赋值运算发生时就会用到它。合成拷贝赋值运算符可以用来禁止该类型对象的赋值。如果一个类未定义自己的拷贝赋值运算符，编译器会为它生成一个合成拷贝赋值运算符。

## 练习13.7

> 当我们将一个 StrBlob 赋值给另一个 StrBlob 时，会发生什么？赋值 StrBlobPtr 呢？

会发生浅层复制。

## [练习13.8](exercise13_8.h)

> 为13.1.1节练习13.5中的 HasPtr 类编写赋值运算符。类似拷贝构造函数，你的赋值运算符应该将对象拷贝到ps指向的位置。

## 练习13.9

> 析构函数是什么？合成析构函数完成什么工作？什么时候会生成合成析构函数？

析构函数是类的一个成员函数，名字由波浪号接类名构成。它没有返回值，也不接受参数。合成析构函数可被用来阻止该类型的对象被销毁。当一个类未定义自己的析构函数时，编译器会为它生成一个合成析构函数。

## 练习13.10

> 当一个 StrBlob 对象销毁时会发生什么？一个 StrBlobPtr 对象销毁时呢？

当一个 StrBlob 对象被销毁时，`shared_ptr` 的引用计数会减少。当 StrBlobPtr 对象被销毁时，不影响引用计数。

## [练习13.11](exercise13_11.h)

> 为前面练习中的 HasPtr 类添加一个析构函数。

## 练习13.12

> 在下面的代码片段中会发生几次析构函数调用？
```cpp
bool fcn(const Sales_data *trans, Sales_data accum)
{
	Sales_data item1(*trans), item2(accum);
	return item1.isbn() != item2.isbn();
}
```

三次，分别是 accum、item1和item2。

## [练习13.13](exercise13_13.cpp)

> 理解拷贝控制成员和构造函数的一个好方法的定义一个简单的类，为该类定义这些成员，每个成员都打印出自己的名字：
```cpp
struct X {
	X() {std::cout << "X()" << std::endl;}
	X(const X&) {std::cout << "X(const X&)" << std::endl;}
}
```
给 X 添加拷贝赋值运算符和析构函数，并编写一个程序以不同的方式使用 X 的对象：将它们作为非引用参数传递；动态分配它们；将它们存放于容器中；诸如此类。观察程序的输出，直到你确认理解了什么时候会使用拷贝控制成员，以及为什么会使用它们。当你观察程序输出时，记住编译器可以略过对拷贝构造函数的调用。

## 练习13.14

> 假定 numbered 是一个类，它有一个默认构造函数，能为每个对象生成一个唯一的序号，保存在名为 mysn 的数据成员中。假定 numbered 使用合成的拷贝控制成员，并给定如下函数：
```cpp
void f (numbered s) { cout << s.mysn < endl; }
```
则下面代码输出什么内容？
```cpp
numbered a, b = a, c = b;
f(a); f(b); f(c);
```

输出3个完全一样的数。

## 练习13.15

> 假定numbered 定义了一个拷贝构造函数，能生成一个新的序列号。这会改变上一题中调用的输出结果吗？如果会改变，为什么？新的输出结果是什么？

会输出3个不同的数。并且这3个数并不是a、b、c当中的数。

## 练习13.16

> 如果 f 中的参数是 const numbered&，将会怎样？这会改变输出结果吗？如果会改变，为什么？新的输出结果是什么？

会输出 a、b、c的数。

## 练习13.17

> 分别编写前三题中所描述的 numbered 和 f，验证你是否正确预测了输出结果。

[13.14](exercise13_17_1.cpp) | [13.15](exercise13_17_2.cpp) | [13.16](exercise13_17_3.cpp)

## [练习13.18](exercise13_18.h)

> 定义一个 Employee 类，它包含雇员的姓名和唯一的雇员证号。为这个类定义默认构造函数，以及接受一个表示雇员姓名的 string 的构造函数。每个构造函数应该通过递增一个 static 数据成员来生成一个唯一的证号。

## [练习13.19](exercise13_19.h)

> 你的 Employee 类需要定义它自己的拷贝控制成员吗？如果需要，为什么？如果不需要，为什么？实现你认为 Employee 需要的拷贝控制成员。

## 练习13.20

> 解释当我们拷贝、赋值或销毁 TextQuery 和 QueryResult 类对象时会发生什么？

成员会被复制。

## 练习13.21

> 你认为 TextQuery 和 QueryResult 类需要定义它们自己版本的拷贝控制成员吗？如果需要，为什么？实现你认为这两个类需要的拷贝控制操作。

合成的版本满足所有的需求。因此不需要自定义拷贝控制成员。

## [练习13.22](exercise13_22.h)

> 假定我们希望 HasPtr 的行为像一个值。即，对于对象所指向的 string 成员，每个对象都有一份自己的拷贝。我们将在下一节介绍拷贝控制成员的定义。但是，你已经学习了定义这些成员所需的所有知识。在继续学习下一节之前，为 HasPtr 编写拷贝构造函数和拷贝赋值运算符。

## 练习13.23

> 比较上一节练习中你编写的拷贝控制成员和这一节中的代码。确定你理解了你的代码和我们的代码之间的差异。

## 练习13.24

> 如果本节的 HasPtr 版本未定义析构函数，将会发生什么？如果未定义拷贝构造函数，将会发生什么？

如果未定义析构函数，将会发生内存泄漏。如果未定义拷贝构造函数，将会拷贝指针的值，指向同一个地址。

## 练习13.25

> 假定希望定义 StrBlob 的类值版本，而且希望继续使用 shared_ptr，这样我们的 StrBlobPtr 类就仍能使用指向vector的 weak_ptr 了。你修改后的类将需要一个拷贝的构造函数和一个拷贝赋值运算符，但不需要析构函数。解释拷贝构造函数和拷贝赋值运算符必须要做什么。解释为什么不需要析构函数。

拷贝构造函数和拷贝赋值运算符要重新动态分配内存。因为 StrBlob 使用的是智能指针，当引用计数为0时会自动释放对象，因此不需要析构函数。

## [练习13.26](exercise13_26.h)

> 对上一题中描述的 strBlob 类，编写你自己的版本。

## [练习13.27](exercise13_27.h)

> 定义你自己的使用引用计数版本的 HasPtr。

## [练习13.28](exercise13_28.h)

> 给定下面的类，为其实现一个默认构造函数和必要的拷贝控制成员。
```cpp
(a) 
class TreeNode {
pravite:
	std::string value;
	int count;
	TreeNode *left;
	TreeNode *right;	
};
(b)
class BinStrTree{
pravite:
	TreeNode *root;	
};
```

## 练习13.29

> 解释 swap(HasPtr&, HasPtr&)中对 swap 的调用不会导致递归循环。

这其实是3个不同的函数，参数类型不一样，所以不会导致递归循环。

## [练习13.30](exercise13_30.h)

> 为你的类值版本的 HasPtr 编写 swap 函数，并测试它。为你的 swap 函数添加一个打印语句，指出函数什么时候执行。

## [练习13.31](exercise13_31.h)

> 为你的 HasPtr 类定义一个 < 运算符，并定义一个 HasPtr 的 vector。为这个 vector 添加一些元素，并对它执行 sort。注意何时会调用 swap。

## 练习13.32

> 类指针的 HasPtr 版本会从 swap 函数收益吗？如果会，得到了什么益处？如果不是，为什么？

不会。类值的版本利用swap交换指针不用进行内存分配，因此得到了性能上的提升。类指针的版本本来就不用进行内存分配，所以不会得到性能提升。

## 练习13.33

> 为什么Message的成员save和remove的参数是一个 Folder&？为什么我们不能将参数定义为 Folder 或是 const Folder？

因为 save 和 remove 操作需要更新指定 Folder。

## 练习13.34 : [h](exercise13_34.h) | [cpp](exercise13_34.cpp)

> 编写本节所描述的 Message。

## 练习13.35

> 如果Message 使用合成的拷贝控制成员，将会发生什么？

在赋值后一些已存在的 `Folders` 将会与 `Message` 不同步。

## 练习13.36 : [h](exercise13_34.h) | [cpp](exercise13_34.cpp)

> 设计并实现对应的 Folder 类。此类应该保存一个指向 Folder 中包含  Message 的 set。

## 练习13.37 : [h](exercise13_34.h) | [cpp](exercise13_34.cpp)

> 为 Message 类添加成员，实现向 folders 添加和删除一个给定的 Folder*。这两个成员类似Folder 类的 addMsg 和 remMsg 操作。

## 练习13.38

> 我们并未使用拷贝交换方式来设计 Message 的赋值运算符。你认为其原因是什么？

对于动态分配内存的例子来说，拷贝交换方式是一种简洁的设计。而这里的 Message 类并不需要动态分配内存，用拷贝交换方式只会增加实现的复杂度。

## 练习13.39 : [hpp](exercise13_39.h) | [cpp](exercise13_39.cpp)

> 编写你自己版本的 StrVec，包括自己版本的 reserve、capacity 和 resize。

## 练习13.40: [hpp](exercise13_39.h) | [cpp](exercise13_39.cpp)

> 为你的 StrVec 类添加一个构造函数，它接受一个 initializer_list<string> 参数。

## 练习13.41

> 在 push_back 中，我们为什么在 construct 调用中使用后置递增运算？如果使用前置递增运算的话，会发生什么？

会出现 `unconstructed`。

## 练习13.42

> 在你的 TextQuery 和 QueryResult 类中用你的 StrVec 类代替vector<string>，以此来测试你的 StrVec 类。

## 练习13.43

> 重写 free 成员，用 for_each 和 lambda 来代替 for 循环 destroy 元素。你更倾向于哪种实现，为什么？

**重写**：
```cpp
for_each(elements, first_free, [this](std::string &rhs){ alloc.destroy(&rhs); });
```
更倾向于函数式写法。

## 练习13.44

> 编写标准库 string 类的简化版本，命名为 String。你的类应该至少有一个默认构造函数和一个接受 C 风格字符串指针参数的构造函数。使用 allocator 为你的 String类分配所需内存。

[hpp](exercise13_44.h) | [cpp](exercise13_44.cpp) | [Test](exercise13_44_main.cpp)

## 练习13.45

> 解释左值引用和右值引用的区别？

定义：
* 常规引用被称为左值引用
* 绑定到右值的引用被称为右值引用。

## 练习13.46

> 什么类型的引用可以绑定到下面的初始化器上？
```cpp
int f();
vector<int> vi(100);
int? r1 = f();
int? r2 = vi[0];
int? r3 = r1;
int? r4 = vi[0] * f();
```

```cpp
int f();
vector<int> vi(100);
int&& r1 = f();
int& r2 = vi[0];
int& r3 = r1;
int&& r4 = vi[0] * f();
```

## 练习13.47 : [hpp](exercise13_44.h) | [cpp](exercise13_44.cpp) 

> 对你在练习13.44中定义的 String类，为它的拷贝构造函数和拷贝赋值运算符添加一条语句，在每次函数执行时打印一条信息。

## [练习13.48](exercise13_44_main.cpp)

> 定义一个vector<String> 并在其上多次调用 push_back。运行你的程序，并观察 String 被拷贝了多少次。

## 练习13.49

> 为你的 StrVec、String 和 Message 类添加一个移动构造函数和一个移动赋值运算符。

## 练习13.50

> 在你的 String 类的移动操作中添加打印语句，并重新运行13.6.1节的练习13.48中的程序，它使用了一个vector<String>，观察什么时候会避免拷贝。

```cpp
String baz()
{
    String ret("world");
    return ret; // first avoided
}

String s5 = baz(); // second avoided
```

## 练习13.51

> 虽然 unique_ptr 不能拷贝，但我们在12.1.5节中编写了一个 clone 函数，它以值的方式返回一个 unique_ptr。解释为什么函数是合法的，以及为什么它能正确工作。

在这里是移动的操作而不是拷贝操作，因此是合法的。

## 练习13.52

> 详细解释第478页中的 HasPtr 对象的赋值发生了什么？特别是，一步一步描述 hp、hp2 以及 HasPtr 的赋值运算符中的参数 rhs 的值发生了什么变化。

左值被拷贝，右值被移动。

## 练习13.53 : [hpp](exercise13_53.h) | [cpp](exercise13_53.cpp) 

> 从底层效率的角度看，HasPtr 的赋值运算符并不理想，解释为什么？为 HasPtr 实现一个拷贝赋值运算符和一个移动赋值运算符，并比较你的新的移动赋值运算符中执行的操作和拷贝并交换版本中的执行的操作。

## 练习13.54

> 如果我们为 HasPtr 定义了移动赋值运算符，但未改变拷贝并交换运算符，会发生什么？编写代码验证你的答案。

```cpp
error: ambiguous overload for 'operator=' (operand types are 'HasPtr' and 'std::remove_reference<HasPtr&>::type { aka HasPtr }')
hp1 = std::move(*pH);
^
```

## 练习13.55

> 为你的 StrBlob 添加一个右值引用版本的 push_back。

```cpp
void push_back(string &&s) { data->push_back(std::move(s)); }
```

## 练习13.56

> 如果 sorted 定义如下，会发生什么？
```cpp
Foo Foo::sorted() const & {
	Foo ret(*this);
	return ret.sorted();
}
```

会产生递归并且最终溢出。

## 练习13.57

> 如果 sorted定义如下，会发生什么：
```cpp
Foo Foo::sorted() const & { return Foo(*this).sorted(); }
```

没问题。会调用移动版本。

## [练习13.58](exercise13_58.cpp)

> 编写新版本的 Foo 类，其 sorted 函数中有打印语句，测试这个类，来验证你对前两题的答案是否正确。
