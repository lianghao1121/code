#include<memory>
#include<string>
class strvec
{
public:
	strvec():
		elements(nullptr),first_free(nullptr),cap(nullptr){}
	strvec(const strvec&);
	strvec& operator=(const strvec&) = (const strvec&);
	~strvec();
	void push_back(const std::string&);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements };
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }
private:
	static std::allocator<std::string>alloc;
	void chk_n_alloc()
	{if (size() == capacity()) reallocate();}
	std::pair<std::string*, std::string*> alloc_n_copy
	(const std::string*, const std::string*);
	void free();
	void reallocate();
	std::string* elements;
	std::string* first_free;
	std::string* cap;
};
void strvec::push_back(const std::string& s) {
	chk_n_alloc();  /*用check函数member去检查是否有空间去push_back元素*/
	alloc.construct(first_free++, s);  /*alloc的类型是是allocator，其类型来源于memory头文件的allotor函数，*/
}
std::pair<std::string*, std::string*>
strvec::alloc_n_copy(const std::string* b, const std::string* e) {
	auto data = alloc.allocate(e - b);  /*allocate是allocator类中的类型，data的类型其实是根据memory中的allocate返回值的
类型，一般来说如果引用的话有些申长，故用auto，此语句的功能就是来计算需要多少空间的*/
	return { data,uninitialized_copy(b,e,data) }; 
}
void strvec::free() { /*功能：去释放元素以及释放所申请的空间*/
	if (elements) {
		for (auto p = first_free; p != elements;/* empty */)  /*在这里，p类似于一个指针，他是指向vector的指向第一个元素的指针
这个for循环就是去释放该vector的指针，最后的结束条件是p==element时候的指针*/
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
	/*释放空间或者是释放元素的操作在不是模板的前提下是基于memory中的方法的函数操作，并不是真正意义上的自己去creat一个vector，但是相信
终有一天可以写出完全由自己的代码调控的vetcor*/
}
/* copy-control member */
strvec::strvec(const strvec& s) {  /*构造函数不需要写返回值*/
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
strvec::~strvec() { free();}
strvec& strvec::operator = (const strvec& rhs) {
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
void strvec::reallocate() {  /*模仿vector实现的核心，其目的是为了处理vector内部的指针问题，其中有三个指针，分别是：指向vector的
开头的指针，指向vector的最后元素的指针，指向该vector自动分配的内存的最大容量处的指针，其reallocate就是为了处理vector最大内存不够
用时候vector内部处理memory的模拟实现*/
	auto newcapacity = size() ? 2 * size() : 1;  /*newcapcaity是用来判断vector的size的变量，其中如果size存在，则会以目前最大
容量的二倍来扩增该容量*/
	auto newdata = alloc.allocate(newcapacity); /*newdata 借用memory头文件中的allocate函数来实现对于内存的实现，其申请的容量则
是newcapacity的容量*/
	auto dest = newdata;  
	auto elem = elements;
	for (size_t i = 0; i != size(); i++)
		alloc.construct(dest++, std::move(*elem++));  /*构造出来所需的对象*/
	free();  /*此时free是为了释放旧的vector，包括其中的指针和内存元素*/
	elements = newdata; 
	first_free = dest;
	cap = elements + newcapacity;
}
