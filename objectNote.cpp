1.在c/c++中，为了避免同一个文件被include多次，有两种方式：一种是#ifndef方式，一种是#pragma once方式(在头文件的最开始加入)。 #pragma once方式产
生于#ifndef之后。#ifndef方式受c/c++语言标准的支持，不受编译器的任何限制；而#pragma once方式有些编译器不支持(较老编译器不支持，如gcc 3.4版本之前
  不支持#pragmaonce)，兼容性不够好。#ifndef可以针对一个文件中的部分代码，而#pragma once只能针对整个文件。

4.::可为全局作用域符号：当全局变量在局部函数中与其中某个变量重名，那么就可以用::来区分如：
例：
char    zhou;    //全局变量   如果全局变量在包含的文件中，也可以这么用
void    sleep（）
｛
      char    zhou;    //局部变量
     ::char(全局变量) =::char(全局变量) / char(局部变量);
｝

5.hpp，在boost、xerces等开源库中频繁出现，hpp，其实质就是将.cpp的实现代码混入.h头文件当中，定义与实现都包含在同一文件，则该类的调用者只需要include
该hpp文件即可，无需再将cpp加入到project中进行编译。而实现代码将直接编译到调用者的obj文件中，不再生成单独的obj，采用hpp将大幅度减少调用project中的
cpp文件数与编译次数，也不用再发布烦人的lib与dll，因此非常适合用来编写公用的开源库。因为头文件包含，所以hpp的代码会复制到调用都的cpp文件中，
编译时会一起编译
即相当于是包含文件中的函数

6.#define后面的\是续行符，表示下面一行是紧接着当前行的，一般用于将十分长的代码语句分几段写（注意\后面除了换行回车不能有任何字符，空格也不行：
  带参宏定义的一般形式为： 　#define 宏名(形参表) 字符串
　　宏名后的第一个括号就是参数，实际实用时，参数传入字符串中即可

9.typedef为c语言的关键字，作用是为一种数据类型定义一个新名字。这里的数据类型包括内部数据类型（int,char等）和自定义的数据类型（struct等）,
用typedef只是对已经存在的类型增加一个类型名，而没有创造一个新的类型。只是增加了一个新名字，可以用该名字定义变量，   ;号结尾
例：
1.typedef int status;  数据类型是int,新名字是status
2.typedef int num[100];//可看成 typedef int[100] num, int[100]是数据类型， num是新名字
  num n;
3.typedef struct  
{
    int month;
    int day;
    int year;  
} time;     time前的是数据类型，time是新名字
4.所以函数指针类型也是可以理解了

11.#pragma  pack (push,1)     作用：是指把原来对齐方式设置压栈，并设新的对齐方式设置为一个字节对齐
相当于：
#pragma pack(push) //保存对齐状态
#pragma pack(4)//设定为4字节对齐
在代码结尾还有一个#pragma pack(pop) 表示恢复压入栈中的对齐状态

19.tls（线程本地存储），如果代码支持多线程；那么，内存释放的时候，其绝对不会在原来分配时的线程.
线程间内存池交换内存的模型:使用一个全局的共享内存池，然后各个线程内部的内存池，向其发起分配和释放的请求。这样，我们也就不在担心上面的问题了;
我们可以通过这个全局池，来完成跨线程间的内存操作。当然，全局池需要加锁。为了减少加锁的消耗，可以减少访问共享池的频率，比如：(内部池的分配与释放频率)与全局池的访问频率，比例在：10000:1，或更高。这样，通过均摊，最后加锁的消耗，几乎完全没有了
a.需要内存池的目地是提高性能
b.影响内存池性能的是向全局池的访问频率。


20.size_t:它是一种“整型”类型，里面保存的是一个整数，就像int, long那样。用来记录一个大小(size)。size_t的全称应该是size type，
就是说“一种来记录大小的数据类型”。用sizeof(xxx)操作的结果就是size_t类型。可以做加减乘除，也可以转化为int并赋值给int类型的变量。
在32位架构中被普遍定义为：
typedef   unsigned int size_t;
而在64位架构中被定义为：
typedef  unsigned long size_t;

25.a("one"):这样的对象是临时对象，不能取地址，不能被引用，不过可以给同类型的其他对象赋值，该临时对象以后可以进行一次操作，然后立即销毁。
当我们定义一个对象以后并不想立即给它赋初值，而是以后给它赋初值，在稍后赋初值的时候，该类临时对象就可以发挥作用了。
例：有一个类a;
a a;
a = a("one");

16.std::shared_ptr 和std::make_shared;  //目的是自动管理资源,当最后一个引用对象释放时，资源释放
std::shared_ptr:
1.开辟两次内存。 被管理对象，用new创建后给shared_ptr托管的对象。   管理对象：管理被管理对象的生命周期(weak_ptr与此相同),shared_ptr赋值后，共用
一个管理对象。假设sp1管理一块内存，sp2管理一块内存，sp2 = sp1后，sp2之前的管理对象会析构，此时两个共用一个管理对象
weak_ptr和shared_ptr指向同一个被管理对象时，它们共享同一个管理对象。当管理对象中的use_count为0时，析构被管理对象，当weak_count为0时，会析构管理对象，
所以会出现被管理对象已不存在，但管理对象还存在的情况。因此，当用weak_ptr试图获取shared_ptr时，要判断被管理对象是否还存在。//注意区分管理对象和被管理对象
(shared_ptr被赋值后，use_count和weak_ptr都会加1，所以一个sp释放时，use_count和weak_count都会减1, weak_count为0时才析构)
2.当用同一个地址构造两个sp时，会照成内存重析构。

std::make_shared; //比shared_ptr少分配一次内存行为
1.make_shared函数的主要功能是在动态内存中分配一个对象并初始化它，返回指向此对象 的shared_ptr;由于是通过shared_ptr管理内存，
因此一种安全分配和使用动态内存的方法。
2.好处是只会申请一次较大的内存，同时存放被管理对象和管理对象，但被管理对象析构时，这块内存不会被回收，需等管理对象也析构后，内存才会被回收。

shared_ptr
在定义的时候可以指定删除器（deleter）。无法直接传入析构函数。方法:在单例函数内部再定义一个destory函数，该函数也要为static的，即通过类名可直接调用。
ps:项目用的是静态函数

shared_ptr类型转换只能用：static_pointer_cast, dynamic_pointer_cast, const_pointer_cast 。

常用的boost::shared_ptr函数有： 
get() 获取裸指针 
reset() 计数器减一 

27.
weak_ptr被设计为与shared_ptr共同工作，可以从一个shared_ptr或者另一个weak_ptr对象构造，获得资源的观测权。但weak_ptr没有共享资源，它的构造/析构不
会引起指针引用计数的增加/减少。它只是一个观察者。使用weak_ptr的成员函数use_count()可以观测资源的引用计数，另一个成员函数expired()的功能等价于use_count() == 0，
也就是shared_ptr管理的资源已经不复存在了。weak_ptr没有重载operator和->，它不共享指针，不能操作资源，这是它弱的原因。在需要的时候就调用lock()从被观测
的shared_ptr获得一个可用的shared_ptr对象供外界使用，从而操作资源。当expired() == true的时候，lock()函数将返回一个存储空指针的shared_ptr。
例：
shared_ptr<int> sp(new int(10));
  cout<<sp.use_count()<<endl;     1
  boost::weak_ptr<int> wp(sp);   观测sp 
  cout<<wp.use_count()<<endl;      1
  boost::shared_ptr<int> sp2 = wp.lock();  使用sp产生新的share_ptr sp2
  sp2 = 100;                        使用
  cout<<wp.use_count()<<endl;   2  引用计数加1

  weak_ptr不控制指针的析构，若引用的share_ptr析构了，weak_ptr就不能取到shared_ptr指针

当两个对象需要互相引用的时候(各类中都有指针指向对方)，我们总希望其中一个对象拥有另外一个对象的强引用，而另外一个对象拥有自己的弱引用
可以使用lock获得一个可用的shared_ptr对象。weak_ptr的一个重要用途是通过lock获得this指针的shared_ptr,使对象自己能够生产shared_ptr来管理自己，

28.enable_shared_from_this是一个模板类 :在自已中传自己，要么this，要么是创建时的shared指针，注意在异步调用中要使用
当类a被share_ptr管理，且在类a的成员函数里需要把当前类对象作为参数传给其他函数时，就需要传递一个指向自身的share_ptr。
1.为何不直接传递this指针
       使用智能指针的初衷就是为了方便资源管理，如果在某些地方使用智能指针，某些地方使用原始指针，很容易破坏智能指针的语义，从而产生各种错误。

2.可以直接传递share_ptr<this>么？
       不能，因为这样会造成2个非共享的share_ptr指向同一个对象，未增加引用计数导致对象被析构两次。

若一个类 t 继承 std::enable_shared_from_this<t> ，则会为该类 t 提供成员函数： shared_from_this 。 当 t 类型对象 t 被一个名为 pt 的
std::shared_ptr<t> 类对象管理时，调用 t::shared_from_this 成员函数，将会返回一个新的 std::shared_ptr<t> 对象，它与 pt 共享 t 的所有权。

为何会出现这种使用场合:
     因为在异步调用中，存在一个保活机制，异步函数执行的时间点我们是无法确定的，然而异步函数可能会使用到异步调用之前就存在的变量。为了保证该变量在异步
函数执期间一直有效，我们可以传递一个指向自身的share_ptr给异步函数，这样在异步函数执行期间share_ptr所管理的对象就不会析构，所使用的变量也会一直有效了
（保活）。 内部其实是weak_ptr管理，shared_from_this就是用weak_ptr构造一个share_ptr最终目地都是为避免重析构。

30.使用extern和包含头文件来引用函数区别
extern的引用方式比包含头文件要简洁得多！想引用哪个函数就用extern声明哪个函数。一个明显的好处是，会加速程序的编译
（确切的说是预处理）的过程间。在大型c程序编译过程中，这种差异是非常明显的。 在连接时，会在编译后的文件找extern函数
的实现。函数就不用加了,函数声明和函数定义很好区分,链接在本编译单元找不到该符号的定义的话,会在其它编译单
元中寻找.类成员函数也是，头文件的实现函数不一样要写在同名的源文件中。

对于全局变量就不一样了
 extern int a;
加extern 是声明,不加extern 就是定义了.

35.申请空间后要用memset初始化，包括结构体

36.memcopy与memmove区别：当内存发生局部重叠的时候，memmove保证拷贝的结果是正确的，memcpy不保证拷贝的结果的正确
void * __cdecl memcpy ( void * dst,const void * src,size_t count);//重叠时，src复制到dst的位置时，正好dst的位置在src上，这个位置是将要被src读到的
https://www.cnblogs.com/chengjaven/p/4512817.html

42.用malloc原因:失败返回null,提前知道内存有没有足够空间,将碎片空间进行整理成一个大块

64.1.struct中全是publie，且没有构造函数(不是public则不能直接访问成员变量，有构造函数则只能按构造函数的格式进行初始化)
则可用｛｝进行构造，例：struct a = {}
例：
struct s {
    private:
        int x;
    public:
        double y;
        s(void){}
        s(int idemo,double ddemo) {x=idemo;y=ddemo;}
};
s os1;//将调用默认构造函数(无参构造函数)
s os2(1000,2.345);
s os3=s(2000,4.567);等价于：s os3(2000,4.567)  因是声明并初始化os3对象，所以将调用s(int,double)构造函数对os3进行初始化。  //这样析构一次
//如果是先声明，后初始化，则会析构两次
s os[4]={s(10,1.234),s(20,2.234)};//未初始化的将调用默认构造函数。如此时没有默认构造函数会出错。

5.expliclt是为了提供一种方法，制止单一参数的constructor被当做一个conversion（转换，例重载)运算符
explicit  只能修饰构造函数，将抑制隐式转换
按照默认规定，只有一个参数的构造函数也定义了一个隐式转换，将该构造函数对应数据类型的数据转换为该类对象
eg1:
class string {
string ( const char* p );
};
string s1 = “hello”; //ok 隐式转换，等价于string s1 = string（“hello”）;

eg2:
例：class c {
    private:
        int x;
    public:
        c(int idemo) {x=idemo;}
};
c oc=1000;//不能加花括号

2. 读写锁处于读锁状态时，有写者试图加写锁时，之后的其他线程的读锁请求会被阻塞，以避免写者长时间的不写锁。

78.0x7fffffff 的二进制表示就是除了首位是 0，其余都是1  0111=7
是最大的整型数 int（因为第一位是符号位，0 表示他是正数）

79.要计算一个二进制的大小，首先要知道这个是定义为有符号还是无符号的数，无符号时，所有位都参与计算。
反码：正数时与原码相同，负数时是除符号位外按位取反 (取反)
补码：正数时与原码相同，负数时是反码加1 (加1)

eg:1111 1111
如果是有符号的，所以先算出反码是1000 0000，补码是1000 0001,所以值是-1

81. 静态成员变量不随对象的建立而分配空间的,也不是随对象的撤销而释放.静态成员变量是在程序编译时分配空间,而在程序结束时释放空间.
静态全局和全局变量都是在静态存储区，全局变量是整个源文件，静态全局只能在定义它的文件内使用



107. 0x0表示十六进制数0，等于十进制的数0。

114. set是关联容器。其键值就是实值，实值就是键值，不可以有重复，
所以我们不能通过set的迭代器来改变,比较函数不是<号，是（）

115.区域锁(scoped locking)不是一种锁的类型，而是一种锁的使用模式(pattern)。
raii(resource acquisition is initialization)叫“资源获取即初始化”，
解决：函数内部突然抛出了异常，程序会自动退出，导致锁不会释放。
解决：区域锁就是把锁封装到一个对象里面。锁的初始化放到构造函数，锁的释放放到析构函数。即使运行时抛出异常，析构函数仍然
会自动运行.如果觉得锁的力度太大，可以用中括号来限定锁的作用区域.

116.锁
1.mutex 互斥锁
lock_guard 比 unique_lock轻量，但它只有构造和析构函数，所以不能提前解锁

2.shared_mutex 读写锁
unique_lock
shared_lock

120.权重
vector<int> vi = {10 ,30 ,50, 10};  数字表示下标的权重
discrete_distribution<int> dist(vi.begin(), vi.end());  将vi中的值转化为离散分布，即概率是｛0.1，0.3，0.5，0.1｝
mt19937 engin(time(null));   设置种子，生成随机数
int i = dist(engin);    返回0到3，分别表示数组中的下标

121.
在网络中,使用ip地址（在网络层，一台机器当然也可以由多个网络接口，即网卡，每个结构对应一个ip地址）。
标示一个主机上的特定进程.使用ip:port，即ip地址和端口号，一般地说，每个进行网络通信的应用程序都要占用主机上的一个端口。举个例子，
使用tcp进行通信，需要建立连接，比如主机a上的进程a和主机b上的进程b进行通信，a、b之间的连接如何标示？使用四元组<a的ip，a所占用的端口，
b的ip，b所占用的端口,ip:port就确定了一个socket，在一个tcp连接中，她就像一个插口，注意，叫做插口，套接字也就是类似的意思。你把应用程
序插入到这个插座，就可以和连接的另外一方对话了。

124.io_service，相当于一个线程分配中心，post函数是接收某个任务，调用线程去处理

126.private:  数据成员和函数成员，只能在类成员和友元中访问。不能被继承类访问（无论何种继承）.
声明为protect的函数，变量，仅父类和子类内部（即定义父类和子类的代码中）可以调用,无法通过对象进行调用

127.在一个类中，对于函数名相同的const函数和非const函数能够构成重载，被调用的时机：如果定义的对象是常对象，则调用
的是const成员函数，如果定义的对象是非常对象，则调用重载的非const成员函数。

128.const_cast的目的并不是为了让你去修改一个本身被定义为const的值，因为这样做的后果是无法预期的。const_cast的
目的是修改一些指针/引用的权限，如果我们原本无法通过这些指针/引用修改某块内存的值，现在你可以了。
例：
const int a = 12;
const int *ap = &a;
int* tmp = const_cast<int*>(ap);
*tmp = 11;

129.一个字节占8位，16进制一个符号占4位，所以一个字节可以用两个16进制符号表示;

129. 0x01这个16进制不能简单的看成8位，左移8位后再多移1位又到1,位移需看机器位数，32位时，0x1<<31时，是在二进位的位上进行移动，结果是1在第32位上,
再移一位，则1会到第1位上
0x01左移5位得  0010 0000 ， 减1得：0001 1111

132. 递归锁存在的问题：调用函数和被调用函数以为自己拿到了锁，都在修改同一个对象，这时就很容易出现问题。
使用互斥锁的地方，可以考虑递归锁，避免了多次上锁解锁

读写锁比互斥锁开销大。读写锁的优势在读操作很频繁，而写操作较少的情况下。如果写操作的次数多于读操作，并且写操作的时间都很短，
则程序很大部分的开销都花在了读写锁上，这时反而用互斥锁效率会更高些。

133.成员变量是类对象时，如果该对象只有有参构造器，声明成员对象时可以不传，构造函数中在对该对象传参初始化。c++11，可以声明的同时初始化。

139.delete 对象时，会调用这个对象的析构函数，如果在this类的析构函数中delete this，当析构函数执行时，就会死循环的调用析构函数.且delete根new配合使用

140.boost::bind(&memberfunction, obj, _1, _2......)成员函数绑定，第一个参数可以是value、pointer和reference，
即传值、传地址和传引用都是可以的，下面三种使用bind的形式都是成立的。
绑定后返回的函数与绑定的函数有相同的实体，在调用时，才用到this指针，所以this指向的类，不能析构。
eg:
a a;
a& r = a;
boost::bind(&a::func, a);
boost::bind(&a::func, &a);   根据&a::func找到函数体，&a指向调用这个函数的对象，所以bind成员函数需传this
boost::bind(&a::func, r);

原func是两个参数的函数，若绑定一个参数，另一个参数占位，则bind返回的是一个参数的函数

传递值或引用,所有的参数都会被拷贝一遍，然后析构一遍,所以首先必须保证参数能够被拷贝而不影响逻辑和数据一致性，
其次，参数能够被析构而不影响逻辑和数据一致性。单例就不行，所以最好传地址。

bind静态成员函数，普通函数和静态函数时，第二个位置放参数，不会放this之类的，bind应该是个模板类，根据传入的参数判断第二个位置是this还是函数的参数

bind(starAltarSystem::gmModifyAct, starAltarSystem::instance()),第二个参数是绑定函数的地址，并没有执行函数，所以starAltarSystem并没
有执行初始化函数，所以需启服初始化，需如下
void game::InitialGame() {
  starAltar_sys;
}

146.
mutex:lock()   线程阻塞直到获得互斥量所有权
try_mutex:     try_lock()，尝试取互斥量，没取到马上返回false，非阻塞
timed_mutex:   timed_loc  k(),在一定的时间内尝试取互斥量

151. 模板的使用
所有类型实参的特化是完全特化，只提供了部分类型实参或者T的类型受限（例如：T*）的特化被认为是不完整的，所以也被称为偏特化。
1.特化，即所有参数都限定类型
例：
template <>   //其实它就是一个正常的函数，再加上template
bool IsEqual(char* t1, char* t2) //函数模板特化
{
    return strcmp(t1, t2) == 0;
}
2.偏特化  函数不能偏特化
例：
template<typename T> //偏特化
class S<T*> {    //接受指针类型
public:
   void info() {
       printf("In pointer specialization\n");
    }
};

注：
bool IsEqual(T t1, T t2)
{
    return t1 == t2;
}

int main()
{
    char str1[] = "Hello";
    char str2[] = "Hello";
    cout << IsEqual(1, 1) << endl;
    cout << IsEqual(str1, str2) << endl;//这个使用上面的模板会不对，因为只是对传入的指针的值进行比较
    return 0;
}

template <> //告诉编译器这是一个特化的模板
class compare<char *> //特化(char*)   
{
public:
    bool IsEqual(char* t1, char* t2)   //属于全特化
    {
        return strcmp(t1, t2) == 0;         //使用strcmp比较字符串
    }
};

定义模板
template<class address_type = void>
static address_type* create_some_memory(size_t sz)
{
  return (address_type*)::nedalloc::nedmalloc(sz);
}
使用，<类型>（参数）
static char* rbuffer = create_some_memory<char>(1024 * 1024 * 100);

1.在普通类中, 在使用模板成员函数时, 不用提供模板参数, 函数可以根据使用的参数,
eg1:
class DebugDelete {
public:
  DebugDelete (std::ostream &s = std::cerr) : os (s) { }
  template <typename T> void operator() (T *p) const {
    os << "deleting unique_ptr" << std::endl; delete p;
  }
private:
  std::ostream &os;
};
int main (void) {
 
  DebugDelete d;
  d(p); //使用时, 可以自动推倒模板
};

typename
http://feihu.me/blog/2014/the-origin-and-usage-of-typename/

158.enum可以不指定对象名,匿名枚举的作用等价于宏变量
凡是无名的struct、union、enum，里面的名称都可以直接使用，无需.操作符。

159.
类型不占空间，生成变量才占空间。
当struct内部的union类型没有名字也没有对象的话, union内部的元素会直接成为struct的元素. 
例：
struct s2{
        union{
                int i;
        };
        struct{
                int i;
        };  
｝union和struct中的i都是struct s2的成员，所以是重复定义，一个改成int j；则struct s2 ss;  ss的大小是8.

struct s1{
        union u{
                int i;
        };
        struct ss1{
                int i;
        };
｝只是声明了类型，没有生成变量，所以 struct s1 xxx;  xxx的大小是0;

struct s6{//the same to s1
        union{
                int;
        };
        struct{
                int;
        };
}生成的对象也是0，

164.struct armynpc
    {
      armynpc()
      {
        memset(this, 0x0, 
          sizeof(armynpc) 
          - sizeof(passive_ids) 
          - sizeof(npcinfo)
          - sizeof(harted)
        );
        npcinfo = json::objectvalue;
      }

用0或0x0是一样，虽然写0是int类型，但这里只会取0的8位，这8位和0x0的8位是一样的。
初始化结构体时，memset初始化大小是，总大小减去stl类型(因为stl类型的变量会自己初始化内在)的大小，有json的，给json类型赋初始类型。

187.数组名不可以被赋值，做函数实参时，实际上是复制了一份首地址的数值

188.构造函数的函数体内只能做赋值而不是初始化。初始化列表之所以高效就是调用的构造，不是赋值
引用是：声明关系，一经声明，不可变更。
例：int a,b;
int &ra = a;
// int &ra = b; //错误，不可更改原有的引用关系
引用和const的成员，可看成是readonly，在构造函数中是赋值，破坏了readonly。且如果写在构造函数中，就是说每个生成的对象都是一样的值。且不能改，那不如定义成const static.
可以在声明的同时初始化。

189.使用初始化列表的好处
class myclass
{
  type variable;
public:
  myclass(type a) //假设type是一个定义了拷贝构造与赋值操作符的类
  {
    variable = a;
  }
};
int main()
{
  type type;
  myclass mc(type);
  return 0;
}
1. 调用type的拷贝构造函数来创建’a’.
2. 调用type的构造函数来创建成员对象variable.
3. 调用type的赋值操作符，修改成员对象variable。
        variable = a; 
4. 调用type的析构函数，因为a的生命周期结束了.

// 使用初始化列表
class myclass {
    type variable;
public:
    myclass(type a):variable(a) {   // 假设type是一个定义了拷贝构造与赋值操作符的类
    }
};
1. 调用type的拷贝构造函数来创建’a’.
2. 调用type的拷贝构造函数，在初始化列表中的使用参数’a’来对成员对象”variable”进行初始化(初始化列表不发生赋值行为,与构造函数相反).   variable(a)
3. 调用type的析构函数，因为a的声明周期结束了.

结构体也可用初始化列表。
声明时赋值:其实是在调用构造函数的时候生效的，本质是编译器将赋值语句内联到类型的每一个实例构造器的代码前面(即在执行构造函数的函数体前)。

187.在c语言中，memset一个结构体是个明智的做法，但是在c++中不是。一个c++类中除了需要空间来存放数据成员之外，还可能保存着虚函数表指针s，偏移量等信息，
一但你memset之后全都没有了。memset完全可以用构造函数的初始化列表来代替。

string不能使用memset或者memcpy这些低级函数。
你new完后string的构造函数已经调用完毕，你再memset就破坏了他的内部数据不变式。
因为memset这种低级函数绕过了封装，可能会触发意想不到的行为。可用构造函数来实现！！！
用memset之前要考虑有没有c++的东西。

189.struct approvet 
{
  approvet() 
  : type(approvetype::unset), exval(0), is_auto(false) {}
  ~approvet() = default;

  unsigned type;    //申请类型
  unsigned exval;   //限制值
  bool is_auto;     //是否自动批准
};

struct legionbriefinfo {
  legionbriefinfo(const legionptr legionp) 
  : approve(legionp->_approve),
  ~legionbriefinfo() = default;

  approvet approve;
};
结构体是一种类型。在初始化列表中approve(legionp->_approve)，不能理解为调用approvet的有参构造器，况且也没有实现有参构造器，
理解为定义时初始化：approvet approve = legionp->_approve;

197.switch case要加花括号的原因：swithc 是一个块，不是case是一个块。
case 中声明局部变量时，要加{}
在一段代码中的case 1 后面还有一个case2的话，且case 2中使用了case 1定义的变量的话，那么如果运行时，n = 2，swich 直接条转到case 2 内部，这样就出现
了 i 还没有初始化的事情了，（变量的声明是在编译阶段，而变量的赋值则在运行时），如果能运行的话，则在case 2中，i是一个未知的值，所以编译期因直接避免
这种事情发生，就让其编译无法通过。

212.memset(_manidlist, -1, playerformatnum * sizeof(int));  -1的一个字节是1111 1111，则一个int是-1, 只能0，或-1

219:
线程中使用，主线程中无效
boost::this_thread::sleep(boost::posix_time::seconds(2));    // 这种更好用
boost::this_thread::sleep(boost::get_system_time() + boost::posix_time::seconds(2));
主线程中使用：
boost::thread::sleep(boost::get_system_time() + boost::posix_time::seconds(5));

226.linux find path -name 文件名，  -name是关键字，要加, pathname是要找的路径,不加就从当前路径开启找

227.std::ref和std::cref
bind()是一个函数模板，它的原理是根据已有的模板，生成一个函数，但是由于bind()不知道生成的函数执行的时候，传递进来的参数是否还有效。所以它选择参数
值传递而不是引用传递。如果想引用传递，std::ref和std::cref就派上用场了。
内部是用一个指针存传入参数的引用的指针

230.共用体就是共用一个内存首地址，并且各种变量名都可以同时使用，操作也是共同生效

246: value_type
template <typename T>
class Bag 
{
public:
    typedef T value_type;
    T val; 
    Bag(T value):val(value){};

};
在泛型编程中，都有一个typedef T value_type,value_type其实就是类型T，在需要类型的地方，如果还没有确定类型，可用value_type代替，
例：另一个模板函数要处理这个模板类，但需要返回值类型(模板函数，能推导自变量，不能推导函数返回值)，此时可用Bag::value_type代替
template <typename C>
typename C::value_type unpack(C container) 因为T是一个template参数，在它被编译器具现化之前，编译器对T一无所悉，,告诉编译器说这是一个型别,
如此才能顺利通过编译。
{
    return container.val;
}

247.在stl中，容器和算法之间是通过迭代器进行粘合的，算法需要能处理各种容器，则意味着算法函数能接受各种类型的迭代器，所以用模板函数实现算法，
但模板函数只能推导变量的类型，不能推导返回值类型，所以可在容器中定义value_type,只有是类的时候才能在内部定义value_type，原生类型则不行，
所以用偏特化，当是原生类型时，传入的是指针。有一个类模板专门负责萃取出迭代器的类型.

负责萃取类的类型:
template <class I> 
struct iterator_traits { // traits 意为「特性」
 typedef typename I::value_type value_type; 
};

萃取方法的使用
template <class I> 
typename iterator_traits<I>::value_type // 这一整行是函式回返型别,调用iterator_traits萃取出类型，类型的值保存在value_type中
func(I ite) 
{ return *ite; }

偏特化板，负责萃取原生类型
template <class T> 
struct iterator_traits<T*> { //偏特化版—迭代器是个原生指标
 typedefT value_type; 
};
偏特化板，负责萃取const类型的原生类型
template <class T> 
struct iterator_traits<const T*> { // 偏特化版—当迭代器是个pointer-to-const 
 typedefT value_type; 
};

247.stl中，有时需要构造、析构等n个对象，如果这个对象是标准类型，就没必要调用相应的函数进行操作，可直接对内存进行操作，此里就
需要一个方法判断是否可以通过内存操作，方法是定义一个不能进行内存操作的模板，再特化可以进行内存操作的标准类型的模板，可内存和
不可内存操作时调用相应的函数。为了能在编译时决定调用什么函数，函数以重载的方法实现，所以是否能内存操作的标识不能只是一个类型，
需是一个参数.

254. bsonelement.h  573 ,下载db转换类型时的错误提示
ss << "field not found, expected type " << t;
ss << "wrong type for field (" << fieldname() << ") " << type() << " != " << t;
例： type:3003, pid:3145728022, wrong type for field (rpi) 18 != 16
bsontypes.h  bson类型编号

258.function，声明出一种类型，类似int,bind是改变函数的参数数量，返回新的函数类型

259.vector类型的成员变量声明时初始化， vector<int> a(10), 编译器会认为是一个函数，提示10不是一种类型，可以用初始化列表的方式初始化，
vector<int> a{1,2,3};

260.静态成员变量要在类外初始化
例：
class b{

};
class aa
{
public:
  typedef boost::function<int(playerdataptr, const reqarg&)> actrechargedealfunc;
private:
  static std::map<int, actrechargedealfunc> kactdealmap;  
  static b bb;
};
此时的kactdealmap只是声明，需要在类外初始化才会分配空间
std::map<int, actrechargedealfunc> aa::kactdealmap;  这么写还是不对，因为是在类外初始化，actrechargedealfunc是在类内的类型，所以也要加命名空间
std::map<int, kactdealmap::actrechargedealfunc> aa::kactdealmap;
b aa::bb; //静态成员类的初始化

261.s已tatic_cast<type>(expression)类似c的强转，使用这个，就表明这里需要转换，会明显些，static_cast在编译时会进行类型检查，而强制转换不会,
不要用c的强转

263.dynamic_cast 用于类间的转换,如果不对,会返回null.
例： pf是父类的指针，ps是子类指针，当子类指针转成父类，即上转，一般不会有问题。下转，父类的指针转成子类时，这个父类的指针需是被子类赋值过的，
单纯的父类指针转成子类不会成功ps = dynamic_cast<ps*>(pf);  https://blog.csdn.net/macuilxochitl/article/details/19615312

C++ 中提供了四种强制类型转换操作符,static_cast<>, dynamic_cast, const_cast<>, reinterpret_cast<>。而关于shared_ptr 无法利用这些原始的操作符进行转换,
其定义了自己的类型转换操作符：static_pointer_cast, dynamic_pointer_cast, const_pointer_cast.
其用途跟非智能指针的cast意思相同：static cast可以用来在不相干的类型间转换，只要两个类型之间兼容，例如char 转 int

dynamic_cast 主要用来向下类型转换(基类至少有一个虚函数才行)，提供能力的查询，转换失败返回空；向上类型转换可直接转，无需dynamic_cast<>,
但是即使用了dynamic_cast也行，只不过不需要。

296.定位new，先申请了一块内存，在这个内存上创建对象，对象中可能有指针指向了新开辟的空间，不能直接delete bufptr，因为会释放对象内的指针占用的空间，
而指针指向的空间没有释放，因为bufptr也指向buf这块空间，所以buf也会释放。所以需通过bufptr调用对象的析构函数，再delete这块空间
https://blog.csdn.net/qianqin_2015/article/details/51320775

例： int buf = 513
char * bufptr = new char[buf];
class a;

aptr = new (bufptr(传内存的地址)) a;

297. history_task_def.h中的
class a
{
union {
    basearg base_arg;
    battlebasearg battle_base_arg;
    ...
  };

}
因为是无名的union中，所以相当于是类的成员对象,可在类中直接使用，又因为是在union中，所以这些对象共用一个首地址。

307.内置类型，以及stl的迭代器和函数对象。对它们而言，pass-by-value往往比较合适。姑且认为是非自定义类型就传值 
内置类型在按值传参时，只是将变量的值传递到栈上。 然后被调用函数将值取出后，使用即可。 
在按引用传参时，需要将被引用的变量的地址压栈， 然后被调用函数首先取出地址，然后再次根据地址寻址获取值。

308.class中，成员变量被越少的成员函数访问，封装性越好，非成员函数能实现的功能尽量用非成员函数。
例：class
{
  void cleara();
  void clearb();
  void clearall(){//--clearall有资格访问私有成员，降低了封装性
    cleara();
    clearb();
  }
}
上例的clearall()成员函数，写成类外的非成员函数   clearall(class c){c.cleara(); c.clearb()}

310.使用non-member函数的另一种好处,方便一些写法
当你需要为某个函数的所有参数（包括被this指针所指的那个隐喻函数）进行类型转换(下例是对构造函数的所有参数进行类型转换)，那么这个函数必须是个non-member。
class rational {
public:
    rational(int numerator = 1, int denominator = 1) 
        : mnumerator(numerator), mdenominator(denominator) {}
    int numerator() const { return mnumerator; }
    int denominator() const { return mdenominator; }
private:
    int mnumerator; // 分子
    int mdenominator; // 分母
};

const rational operator*(const rational& lhs, const rational& rhs) {
    return rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}
 
int main() {
    rational onefourth(2, 4);
    rational result;
    result = onefourth * 3;
    result = 3 * onefourth; // 如果不是 non-member 的形式将不支持这种写法
}

312.dynamic_cast<> 少用。  一般是要使用派生类中的独有的函数，所以将基类指针转成派生类，最好是将该函数实现成virtual

315.~按位取反,将某个数x的二进制的每一个bit取反

328.迭代器失效分序列容器和关联容器，不能简单的理解为，当前的迭代器失效，使迭代器往下移一位即可.
https://blog.csdn.net/qq_37964548/article/details/81160505
是否可理解为，不能对失效的迭代器进行操作，需要在失效之前进行操作或操作后对迭代器赋于新的值才能操作。

329.左值引用，用于传参，扩展对象的作用域。右值引用，延长了临时变量的生命周期.
临时变量不能作为非const引用参数，不是因为他是常量，而是因为c++编译器的一个关于语义的限制。如果一个参数是以非const引用传入，c++编译器就有理由认为程
序员会在函数中修改这个值，并且这个被修改的引用在函数返回后要发挥作用。但如果你把一个临时变量当作非const引用参数传进来，由于临时变量的特殊性，程序员
并不能操作临时变量，而且临时变量随时可能被释放掉，所以，一般说来，修改一个临时变量是毫无意义的，据此，c++编译器加入了临时变量不能作为非const引用的
这个语义限制，意在限制这个非常规用法的潜在错误。
但const 的引用不能修改值，所以有了&&(右值引用)

move对于拥有如内存、文件句柄等资源的成员的对象有效，如果是一些基本类型，如int和char[11]数组等，如果使用move，仍会发生拷贝（因为没有对应的移动构造
函数），所以说move对含有资源的对象说更有意义。

每个对象都有拷贝构造、赋值构造，移动构造，移动赋值，但两者不能同时存在。移动的好处是，例，当对象中有指针指向一个大空间时，只需将指针
的地址复制过来，再将之前的指针置空（所以之前的对象不能用,不置空时，原对象析构时会影响新对象）。又因为移动的形参是　T＆＆(即，可传入
 一个右值的引用，实现需是右值)，但有时 传入的参数是左值，但又想使用移动的方式构造或赋值(由此可看出，T&和T&&的作用只是为了发现对左值或右值的重载调用)
，所以可用std::move()，将参数转为右值 std::move()实际做的，及是类型的转换

class A;
A a;
A b = A();  //调用的构造器：A(const A& another);
A b = std::move(A());//调用的构造器：A(A&& another)

例：2
A a2 = GetA();a1是左值，GetA()先构造出一个临时对象，再调用A的拷贝赋值函数进行构造a1，临时对象再调用析构函数进行析构
A&& a3 = GetA();将调用A的移动赋值,将GetA()产生的临时对象的的地址复制过来，再将GetA（）的对象地址置空

例：3
std::move在提高 swap 函数的的性能上非常有帮助，一般来说，swap函数的通用定义如下：
   template <class T> swap(T& a, T& b) 
   { 
       T tmp(a);   // copy a to tmp 调用构造函数
       a = b;      // copy b to a 
       b = tmp;    // copy tmp to b 
}
有了 std::move，swap 函数的定义变为 :
   template <class T> swap(T& a, T& b) 
   { //避免了三次拷贝操作
       T tmp(std::move(a)); // move a to tmp  调用移动构造  //右值是一个函数
       a = std::move(b);    // move b to a 移动赋值        //右值是一个赋值函数参数
       b = std::move(tmp);  // move tmp to b 
}

329.remvoe_reference 去掉引用，返回纯粹的类型,提交出来的类型的别名是成员变量type
typedef int&& rval_int;
  std::remove_reference<int>::type;
  std::remove_reference<int&>::type;
  std::remove_reference<int&&>::type;
  std::remove_reference<rval_int>::type;
  以上得到的type都是int类型

329.std::forward 如果是右值，不做改变，如果是左值，则返回右值

341. 下图中throw 出的是字段字符串类型，所以 catch 的参数是 const chat* msg
try {
  throw"division by zero condition!" 
}catch(const chat* msg) {

}

343.unordered_map是计算key的哈希值，以找回value存放的对应格子,修改value不需重新插入,map需重新插入

343.函数形参是引用时，不能传临时变量，是const的引用时，可以传临时变量

347. 在构造函数中调用另一个构造函数
class msg {
    msg() {
      _len = minpackage;
      _operate = 0;
      _nid = 0;
      _pid = 0;
      _str = null;
    }
    //调用下列的构造函数，有些成员变量没有初始化，可能类型的构造函数很多，
    //不想一一写，可用定位new，在自身的空间上先调用另一构造器进行构造，以
    //初始化成员变量
    msg(const variable::i33 pto, std::string& json_str_utf8) {
      new(this) msg();
      _operate = pto;
      _len = (unsigned short)json_str_utf9.size() + minpackage;
      _str = json_str_utf9.data();
    }
};

348,./可执行文件名 参数1 ...
int main(int argc, char* argv[]) argv[1] 是函数名，其后是参数
一个程序的执行必须有main函数入口，且不能被其它函数调用，所以当需要参数时，不能在代码中取的，只能从外传入，因此main函数有参数
exec不能看成只执行函数，它是执行可执行文件的

349.lower_upper
上限：小到大排列
下限：大到小排序

351
epoll事件有两种模型：
edge triggered (et) 边缘触发只有数据到来,才触发,不管缓存区中是否还有数据。
level triggered (lt) 水平触发只要有数据都会触发。

首先介绍一下lt工作模式：
lt(level triggered)是缺省的工作方式，并且同时支持block和no-block socket.在这种做法中，内核告诉你一个文件描述符是否就绪了，然后你
可以对这个就绪的fd进行io操作。如果你不作任何操作，内核还是会继续通知你的，所以，这种模式编程出错误可能性要小一点。
传统的select/poll都是这种模型的代表．
优点：当进行socket通信的时候，保证了数据的完整输出，进行io操作的时候，如果还有数据，就会一直的通知你。
缺点：由于只要还有数据，内核就会不停的从内核空间转到用户空间，所以占用了大量内核资源.
例：有11个数据，每次最多只能读2个数据，读完后就又返回epoll_wait监听，又会触发该fp

et:
et(edge-triggered)是高速工作方式，只支持no-block socket。在这种模式下，当描述符从未就绪变为就绪时，内核通过epoll告诉你。然后它会假设
你知道文件描述符已经就绪，并且不会再为那个文件描述符发送更多的就绪通知。请注意，如果一直不对这个fd作io操作(从而导致它再次变成未就绪)，
内核不会发送更多的通知(only once).
优点：每次内核只会通知一次，大大减少了内核资源的浪费，提高效率。
缺点：不能保证数据的完整。不能及时的取出所有的数据。
例：为了避免这种缺点，就会有一个while循环的去读这个fp，直到读完或对方关闭才又返回epoll_wait模式

在阻塞模式下，lt需读到一次数据才返回，而et当读完数据后，因为是while中，所以又会读，而因为当前没有数据，会处于一起阻塞的状态（饥渴姿态）,所以
et须用非阻塞模式，读不到数据就返回

进程返回的fp是指向一个表，不是某个文件描述符

read的过程：
read时，会调用底层的api(就是系统调用),这时会转为内核态，2.内核会负责将网卡中的数据复制到内核空间(需要一个过程,因为可能数据
还没完全到达，没收到一个完整的包，这时就没被拷贝到内核的缓存,)，3.再负责将内核中的数据复制到应用空间.最后用户进程才解除block状态，
重新运行起来。

正式因为2,2过程用户进程会block，linux系统产生了下面五种网络模式的方案。

非阻塞 I/O（nonblocking IO）:
当用户进程发出read操作时，如果kernel中的数据还没有准备好，那么它并不会block用户进程，而是立刻返回一个error。从用户进程角度讲 ，它发起一
个read操作后，并不需要等待，而是马上就得到了一个结果。用户进程判断结果是一个error时，它就知道数据还没有准备好，于是它可以再次发送read操作。
一旦kernel中的数据准备好了，并且又再次收到了用户进程的system call，那么它马上就将数据拷贝到了用户内存，然后返回。
所以，nonblocking IO的特点是用户进程需要不断的主动询问kernel数据好了没有。

I/O 多路复用（ IO multiplexing）:
就是我们说的select，poll，epoll，好处就在于单个process就可以同时处理多个网络连接 的IO。它的基本原理就是select，poll,epoll这个function会不断的轮询所负责的所有socket，当某个socket有数据到达了，就通知用户进程。当用户进程调用了epoll_wait时，那么整个进程会被block，而同时，kernel会“监视”所有epoll_wait负责的socket，当任何一个socket中的数据准备好了，epoll_wait就会返回。这个时候用户进程再调用read操作.所以，I/O 多路复用的特点是通过一种机制一个进程能同时等待多个文件描述符，而这些文件描述符（套接字描述符）其中的任意一个进入读就绪状态，epoll_wait()函数就可以返回。

信号驱动 I/O（ signal driven IO）: 
注：由于signal driven IO在实际中并不常用，所以我这只提及剩下的四种IO Model。

异步 I/O（asynchronous IO:
用户进程发起read操作之后，立刻就可以开始去做其它的事。而另一方面，从kernel的角度，当它受到一个asynchronous read之后，首先它会立刻返回，所以不会对用户进程产生任何block。然后，kernel会等待数据准备完成，然后将数据拷贝到用户内存，当这一切都完成之后，kernel会给用户进程发送一个signal，告诉它read操作完成了。

epoll 因为采用 mmap的机制, 使得 内核socket buffer和 用户空间的 buffer共享, 从而省去了 socket data copy, 这也意味着, 当epoll 回调上层的
callback函数来处理 socket 数据时, 数据已经从内核层 "自动" 到了用户空间,

359.开
和mysql
验证的用：mongo   /data/mongodb/mongodb_master 执行, ./auth_mongodb_start_master.py   
没有验证的，例222机，在 /data/fytx2_test_p017a/mongodb/      python noauth_mongodb_start_master.py  (注意执行的文件不一样)

mysql  /data/mysql/mysql_master, 执行./start_mysql_master.py 
wiki   /data/game-wiki/xl_moin0.9.9/wikiserver.py       screen -S xxx

361. static
全局：
static修饰全局变量或函数后，只能在本文件内使用，用extern 在其它文件声明也不行。可以这么理解，因为全局变量/函数是所有文件共享
的，如果有只能在本文件内共享的需要呢？所以出现了static。 用static修饰后，其变量名/函数名可在其它文件中再定义
局部：
只有在该函数被调用后，静态局部变量才会被初始化，且只初始化一次.
修饰局部变量后，其还是只能在某个函数内使用，但生命周期延长到这个进程结束。
static修饰的全局变量在头文件中，则每个包含该头文件的cpp都会有这个函数的副本
inline是将函数体替换调用处。static inline是将函数的汇编代码插入调用处，可令文件更小

362.List迭代器失效
2.向list中插入元素，不会使迭代器失效
3.当从list删除一个元素后，指向该元素的迭代器失效。其它迭代器不受影响。所以可用后++遍历删除，for(auto itr = xx.begion(); itr != xx.end(); itr++)

363.inline
编译器有个原则，以cpp文件为单位进行逐个编译obj，每个cpp文件的编译是独立的，该cpp文件用到的外部函数都在编译时预留一个符号,只有等到所有obj生成后链接时才给这些符号地址），所以其他cpp文件编译时只会看到这个函数的声明而无法知道她的实体，链接的时 候再填入该地址，做不到内联展开。 所以要内联则必须在每个用到它的cpp文件体现实体，那就只有在头文件内实现实体，类体内实现的函数， 默认是inline的，inline函数在类体外实现时，实现也中能是在头文件中

364.INADDR_ANY
转换过来就是1.0.0.0，泛指本机的意思，也就是表示本机的所有IP，因为有些机子不止一块网卡，多网卡的情况下，这个就表示所有网卡ip地址的意思。
如果绑定某个具体的ip地址，就只能监听该ip地址所在的网卡的端口. 而INADDR_ANY的出现，使得只需一个套接字就行，不管数据是从哪个网卡过来的，只要是绑定的端口号过来的数据，都可以接收到。

365.::xx 无名命名空间，表示xx是全局中的一个变量

369.一个函数能访问外部变量就是闭包

372.想使得单个基础数据类型在多线程中安全,尽量使用原子操作代替锁机制(atomic). 当需要对代码块进行安全操作时,就需要选择使用锁机制了.

373.future,异步操作线程返回值。
函数async()用于产生future对象，它异步地启动一个线程运行函数，返回future对象，这样随后我们就可以利用future获取
计算结果。
例：auto f = async(fab, 6); fab是函数 int fab(int n)

375.C++标准规定，当一个指针类型的数值是0时，认为这个指针是空的。在初始化列表中，可以将指针值置0表示将指针初始化为nullPtr

375.ipp 用于将模板的声明与实现分开，因为模板是在预编译时进行处理的，所以不能放到.cpp文件里面，所以就定义了.ipp文件。 
将模板的实现部分放到.ipp文件，然后在模板声明的.h文件后面 #include 这个.ipp文件

378.cpu是16位，表示在cpu内部一次性处理、传输、暂时存储的信息最大长度是16位，但地址总线不一定是16,最大寻址能力是根据地址总线数定的,
地址总线能代表的最大的数，就是能寻址到的内存数

380.map
自实现排序：
map 比较相等的方法， a.x < b.x 返回假，且，b.x < a.x 返回假，则表示两数相等，只用到了重载小于号，没必要多加一个operator==
2.第三个参数是一个可实现仿函数的类，可定义一个类，实现类的访函数，参数是两个。
struct Cmp
{
    bool operator () (IntPlus const &a,IntPlus const &b)const
    {
        if(a.num!=b.num)
            return a.num<b.num;
        else return a.i<b.i;
    }
}
3.如果key是结构体，在结构体中实现重载小于号的函数。每个值都要比较，不然用一个key去查找时，会找不到。

4.按值排序  
sort算法只能对序列容器进行排序，就是线性的（如vector，list，deque）
sort的比较函数与map相同，也是一个可实现访函数的类
例：std::<struct a,struct b> map;
则：sort(map.begin(), map.end(), cmp)  //在比较函数cmp中，可对值进行比较排序

384.std::tie和std::tuple  处理多返回问题
uple类没有重载operator[]运算符，很难像其他容器和数据额结构一样进行简洁的索引动作，只能通过一个全局的std::get<size_t>(t)进行操作。
https://blog.csdn.net/m1_37809890/article/details/89367406

385.double不能精确的表示很大的数
double 浮点数结构如下:
2 位符号位
12 位指数位
53 位尾数位      使用52位表示一个数的整数部分，所以当发一个整数是用63位表示时，就会不对

388.0b表示的是2进制，0b1 << idx, 应该0b1分配的是int类型，所以idx不能超过31

389. #define   #的使用，#相当于把后面的参数字符串化，即前后加上""

390.定时器：在指定内存开辟一定的空间，将指针加入qtimercollection中，设置定时器的事件id、时间、回调函数。
调用boost::asio::deadline_timer 设置定时器.用qcollecion的好处是，当改时间或要消失定时器时，用调用qcollec统一操作。
改时间时，取消所有已设置的定时器，并重新调用deadline设置定时器（deadline在一开始初始化时，就设置了io_server

391:
<< 2 相当于*2，>>1 相当于/2   例：int x = 4; x << 1; x不会被修改

392:成员变量声明时不能用括号进行初始化，可在初始化列表中使用

393:
端口映射：
将内网的某个ip和端口映射到主路由的某个端口上，之后k通过这个端口的所有外部数据都会发到内网的ip和端口上
dns:将域名解析成ip
ddns：将域名解析成动态ip

393:lambda
https://blog.csdn.net/qq_34199384/article/details/80469780

394.拉当前mg   /data/sh db_lq. sh id 加要放在哪个目录里
2.ssh root@49.234.131.111  数据   own的都不在这个机中
3.ssh root@49.234.133.67   as

396.变量前面加（void）是什么作用？
是一种伪装手法，对程序没有影响.如果一个变量定义了，但是没有被后续代码使用，编译器就会给出警告，使用(void)a可避免之。

397. boost::addressof
获取基本变量、类变量、函数的地址，避免因代码中实现了&的重载函数而照成错误。
eg2:取变量的地址，如果变量进过传参复制，变量地址也会不同。对一个指针变量使用addressof，也是取的这个变量的地址，不是这个变量上存的地址数据

399.
frpc
2.网页和ssh都可以选择tcp,基本设置中，只填本地ip和端口，意思是这个地址映射到外网的某个地址上。
3.frpc_linux_amd64 -f nf8zk1pcjbhoi25t:923040  在本地ip的机子上运行这个服务，即开始了映射。
会得到下列提示。 []中的地址就是映射后的地址，访问那个地址的信息，都会转发到内网的ip:port上。
例：ssh xing@36.160.49.136 -p58173  会发到内网，即ssh xing@本地ip

TCP 类型隧道启动成功
使用 [us-or-aws.sakurafrp.com:58174] 来连接到你的隧道
或使用 IP 地址连接（不推荐）：[36.160.49.136:58173]

401:C++中输出数组数据分两类情况：
当变量为字符型数组时，系统会将数组当作字符串来输出
eg:
char  str[11]={ '1' , '2' };
cout << str <<endl ;  //输出13

当定义变量为非字符符数组时,系统会将数组名当作一个地址来输出，如：
eg:
int  a[11]={1,2,3};
cout << a <<endl ;  //按16进制输出a的值（地址）    0012FF58

402.因为网络id和主机id的位数不固定，可能相互占用，所以出现了子网掩码

403.时间复杂度，logn 以2为低数，n为真数，eg:n为4时，logn等于2,二分法就是logn

404.某活动结束，需处理奖励的时候，如果要load玩家数据只是为了发奖励，可以用delay_deal_email.如果是需取玩家身上的数据来计算
最终的奖励，可将配置的奖励保存，玩家登录再处理，保存的配置可以是最近一百次的配置.

405.log
对数是对求幂的逆运算
如果a的x次方等于N，那么数x叫做以a为底N的对数，记作x=loga N。其中，a叫做对数的底数，N叫做真数。

O(1):O表示算法的时间性能, 1表示基本语句执行次数是一个常数，即用的时间是常数O(1),不会即着数据的增长而增长。

skill:

406.重载operator
int x = 5;调用的是x的构造器，所以 class a < 5时;调用的是类a中的 bool operator < ();

407. std::array 不会自动初始化

408. map.find()    
iterator find (const key_type& k); //返回的是临时变量，不能用&
const_iterator find (const key_type& k) const;//可以用引用
好像用上面那个，可以直接修改val的值

409 operator()
1.直接使用对象时调用
eg:if(a),就是使用a对象，if(a == b),如果没有operator==，会分别调用a,b的operator().

410 寻路.广度优先搜索
0.一定能找到最快的路线
1.类似以起点为中心点向外辐射,设置每个点的父节点(所有相邻结点中距离最短的节点)和到起点的距离，当找到目标点时，通过目标点的父节点找回起点，就能找到最优路线
2.步骤：
a.一开始以起点为中心，取相邻的点设置成节点放入容器中。
b.从容器取出一个点重复a步骤，每次取出的点都是离起点最近的，所以距离和父节点不再变化，所以可以设置成close，表示这个节点
可以不用再检测。
```
std::vector<int> WStarKW::find()
{
  std::vector<int> paths;
  if (!isValidParam())
  {
    return paths;
  }
  else
  {
    _maps[publicStart] = Node(publicStart);//起点节点

    //重设周围最多可以行走的物件格
    std::vector<int> nearby_nodes;
    nearby_nodes.reserve(8);

    _openList.insert(&_maps[publicStart]);//所有实体的节点都是从map中生成
    (*_openList.begin())->state = IN_OPENLIST;//设置到open列表

    while (!_openList.empty())
    {
      Node *current_node = *_openList.begin();
      _openList.erase(_openList.begin());
      current_node->state = IN_CLOSELIST;

      //寻找附近的节点
      findNearlyPos(current_node->pos, nearby_nodes);

      for (unsigned index = 0; index < nearby_nodes.size(); index++)
      {
        Node *new_node = NULL;
        const int& index_pos = nearby_nodes[index];
        if (findInOpenList(index_pos, new_node))//如果新找到的下一个路径, 已经是在open列中
        {
          handleInOpenNode(current_node, new_node);//看大小是否需要重新连接当前节点的父节点
        }
        else
        {
          //不会有闭合列表和开列表的坐标点//所以到这步骤位置, 必定是没有创建实例的地图点
          new_node = &(_maps[index_pos] = Node(index_pos));
          handleNotInOpenNode(current_node, new_node, publicEnd);

          if (index_pos == publicEnd)
          {
            while (new_node->parent)
            {
              paths.push_back(new_node->pos);
              new_node = new_node->parent;
            }
            std::reverse(paths.begin(), paths.end());
            goto __end__;
          }
        }
      }
    }
  }

__end__:
  clear();
  return paths;
}
```
410. p->Escort()中去调用tofull()，此时会判断是否需要调用 classfinal,也就是说，有p->x()这个操作，才会调用classFinal()

411.打印变量，得到变量对应的值，打印指针变量,得指针对应的值，即指针指向的地址。

412.函数指针
普通函数
int test(int a)
{
    return a;
}
int main(int argc, const char * argv[])
{
    
    int (*fp)(int a);//返回值,指针名，加*表示是指针，参数
    fp = test;
    //使用typedef
    //typedef int (*fp)(int a);
    //fp f = test;
    cout<<fp(2)<<endl;
    return 0;
}

成员函数
成员函数的指针不是像普通指针一样保存确切地址，是保存在类布局中的相对地址
class Test
{
public:
    void print()
    {
        cout << "Test::print" << endl;
    }
};

int main(int argc, char *argv[])
{
    void (Test::* pFunc)() = &Test::print; //取成员函数地址时必须是这种格式
    //typedef void (Test::*pFunc)();//typedf的使用
    //pFunc p = &Test::print;
    Test test;
    //通过对象调用成员函数
    (test.*pFunc)();//注意有*号
    Test* pTest = &test;
    //通过对象指针调用成员函数
    (pTest->*pFunc)();//Test::print

    //通过对象调用成员函数是为了传入this指针，函数通过this指针调用对象中的成员。如果函数中没用到this，即便对象指针是空，也可调用
    // Test* ptr == nullptr;
    //(ptr->*pFunc)();
    return 0;
}

静态成员函数
指针中保存的也是一个相对地址(因为属于类),指针的声明和使用与普通函数一样
class Test
{
public:
    static void print()
    {
        cout << "Test::print" << endl;
    }
};

int main(int argc, char *argv[])
{
    void (* pFunc)() = &Test::print;
    cout << pFunc << endl;//1
    //直接调用
    pFunc();//Test::print
    (*pFunc)();//Test::print
    Test test;//不能通过对象或对象指针调用
    //(test.*pFunc)();//error
    Test* pTest = &test;
    //(pTest->*pFunc)();//error
    return 0;
}

413.条件变量
* 实现了阻塞线程等待其它线程发信号唤醒
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex); //使线程与条件变量与锁建立联系,第一次调用时会阻塞且解锁，被唤醒时自动加锁
第一个参数是条件变量，第二个参数是线程阻塞的时候要解开的互斥锁。
使用：线程加锁执行逻辑，发现某些条件不成立，此时可阻塞在一个条件变量，并解锁。其它线程使条件成立后，可通过个发信号的方式唤醒阻塞在条件变量上的线程。发信号的线程如果之前有加锁，要手动先解锁，再发信号

414.void*
任何指针都能赋值给void*，但因为void*没有类型，所以不能解引用。访问前要经过类型强转，malloc返回的是void*类型

415.战斗
不管是创建玩家还是npc战斗对象，都是是armyside类，其它的武将也都是army
位置：[x坐标，y坐标，朝向]
进攻点不同,也就是出生点不同

416.
//注意连接两字
动态链接：链接时不会将用到的库连接到可执行文件中，只在运行时才会链接,启动时如果缺少库，系统会终止程序
节省内存、更新方便，但在运行时每次都要链接库，有一定的性能损失
静态链接：链接时会把所以用到的.o文件链接到最终的可执行文件中
每个可执行文件都有库的副本，可执行文件比动态的大，如果副本改动，需要重新编译连接。优点是执行快。

417.
重载：同一个类中。函数名相同,返回值相同，参数个数、类型、顺序不同的函数可构成重载,可被virtual修饰
重写：指派生类重新实现基类中的函数(除了实现不同，其它都相同),基类中被重写的函数必须被virtual修饰
隐藏：发生在基类和派生类之间，派生类会隐藏基类中与其同名且没有被virtual修饰的函数。如果被修饰了，但派生类中有一个同名的，返回值或参数不同，基类中的virtaul函数会被隐藏
发生在不同类之间同名的函数，不是重写就是隐藏。发生在一个类中同名函数，不是重载就编译不过


418.指针在32位中是4byte,在64位中是8byte

419.sizeof和strlen的区别
* sizeof 参数可以是类型或变量，计算分配内存的大小，在编译时计算长度
```
char x[20] = "hello";
sizeof(x) // 等于20
void fun(char x[]) {
  sizeof(x) // 等于指针大小,因为c类型的数组做为形参时，是传入的组数的首地址，所以此处的x是字符指针.所以c函数，如果传的是数组，还要传入数组长度
}
```
* strlen 计算字符串的长度，参数必须为char* 类型

420.define 和 const区别
define：在预处理阶段处理，不会进行数据检查，代码中有多少处使用就有多少替换，占用了代码段空间。不能进行调试(不能断点在define定义处，替换处也看不到替换后的代码)
const:在编译阶段处理，会进行类型检查，只会在静态区保存一份

421.指针常量、常量指针
从字面上记。谁在前，谁就是const，指针常量， 指针是const，不能指向其它
从定义上记，怎么定义就怎么读。int * const p为指针常量

422.inline
内联函数是在编译阶段将函数体嵌入到每一个调用该函数的语句块中.
普通函数是将程序执行转移到被调用函数所存放的内存地址，当函数执行完后，返回到调用的地方。转移操作需要保护现场，被调函数执行完后，再恢复现场，该过程需要较大的资源开销。

423.malloc没分到内在返回null,new没分到抛出异常。

424.delete 的实现原理：
首先执行该对象所属类的析构函数，然后调用 operator delete 的标准库函数来释放所占的内存空间。
delete 用来释放单个对象所占的空间，只会调用一次析构函数；
delete [] 用来释放数组空间，会对数组中的每个成员都调用一次析构函数。

425.堆和自由存储区
在C++中，内存区分为5个区，分别是堆、栈、自由存储区、全局/静态存储区、常量存储区”
new申请得到的内存在自由存储区的，但很多编译器的new底层是malloc，是从堆中取的内存，又因为可以重载new，使其从其它地方申请内存，所以自由存储区不一样是堆。

426.字符串的一个子序列是原始字符串删除一些字符而不改变剩余字符相对位置形成的新字符串

427.c++中的struct可以设置防问权限，可以定义函数.c不可
struct不能用于定义模板参数

428.
C语言:sizeof（1 == 1） === sizeof（1）按照整数处理，所以是4字节，这里也有可能是8字节（看操作系统）
C++:因为有bool 类型 sizeof（1 == 1） == sizeof（true） 按照bool类型处理，所以是1个字节

429.编译器根据初始值来推算变量的类型，要求用 auto 定义变量时必须有初始值。编译器推断出来的 auto 类型有时和初始值类型并不完全一样，编译器会适当改变结果类型使其更符合初始化规则。

430.析构函数定义成虚函数原因：
当基类的指针或者引用指向或绑定到派生类的对象时，如果未将基类的析构函数定义成虚函数，会调用基类的析构函数，那么只能将基类的成员所占的空间释放掉，派生类中特有的就会无法释放内存空间导致内存泄漏。

jilu
1.引用作为递归参数，为什么可以多次引用 


x + y Vjj
-2 1 2 3
1 2 -10 3 4 

void fun(int x[]) {
  curSum = 0, maxSum = curSum;
  for(auto i = 0; i < length; ++i) {
      curSum = curSum + x[i] > x[i] ? curSum + x[i] : x[i];
      c
  }
}




rcf:
2.定义接口
rcf_begin(cm_protocol, "cm_protocol")//--cm_protocol可看成所有接口的总称
//接口中只有一个函数, 返回值是void，函数名是transfer，接受5个参数, 可以写多个函数
rcf_method_v5(void, transfer, const variable::i64&, const variable::i32&, const variable::i32&, const std::string&)
rcf_end(cm_protocol)

3.在服务端实现接口中的函数，接口的实现客户端不可见 
class dealdata
  {
  public:
    void transfer(const variable::i65& player_id, const variable::i32& net_id, const variable::i32& protocol_id, const std::string& data_str)
    {
      thread_shared::initframe();
      thread_shared::eventandstep(protocol_id);
      while (!game_svr->isok())
                common::sleep(100001);
            print("recv: " << player_id << ", " << protocol_id << ", " << data_str);
            game_svr->recv_msg(player_id, net_id, protocol_id, data_str);
      thread_shared::cleanframe();
    }
  }
生成一个rcf的服务端，绑定ip、port,接口
  _game_service = new ::rcf::rcfserver();
      _game_service->addendpoint(rcf::tcpendpoint("128.0.0.1", game_data._game_service_port));//游戏服端口
      _game_service->bind< ::cm_protocol >(*(new dealdata()));  //传入的参数是实现接口函数的对象,对象名可自拟，成员函数跟ref_begin中定义的一样即可

4.rcf客户端,传入接口
      _game_rcf = ::rcfclient< ::game_svr >(rcf::tcpendpoint("128.0.0.1", _gdata._game_service_port));

线程池：
线程本地储存：boost::thread_specific_ptr; 是一种智能指针，重载了operator*和operator->,可以用get()获得真实指针，
也有reset和release函数。线程可共用这个指针，但数据不会互相影响，每个线程都有自己单独使用的空间
typedef boost::thread_specific_ptr<tss_data> type_tss_data_ptr;
  static type_tss_data_ptr local_tss_data([](tss_data* p) { delete p; });  用thread_specific_ptr生成对象后，这个对象就
  是所有线程独有的，用static修饰，表示只能在本文件内使用，它文件要调用需通过本文件的函数。

class tss_data
{
};
本地储存的数据多，可封装成一个对象传入，
boost::thread_specific_ptr<tss_data> type_tss_data_ptr;
每个线程都可调用type_tss_data_ptr,但都是不一样的tss_data对象，每个线程第一次使用前都会new一个，可
看成每个线程使用前，都会生成一个本地的储存空间。这个type_tss_data_ptr是全局的


连接另一个物理机的mongodb
2.mongo 10.17.172.221:37057
3. use admin
4.db.auth("rwuser","cmgoq8ym3ctl")

绑号：
2.备份需要的db
# mongodump -h 10.17.172.222:37017 -d sid3000 -o ./
3.上传备份数据到db
mongorestore -h 10.17.172.222:37017 -d sid55 ./mongb/sid3000/
4.让mysql中的player_xx表中的某个玩家id为要绑定的id
update player_56 set player_id = 3145728004 where player_id = 57673775;

linux——————————————————————————————————————————————————
3.以make 这个程式，并以makefile 这个参数设定档，依据 install 这个标的(target) 的指定来安装到正确的路径！

4. grep 后接正则表示式， ls |grep *.sh  会查不到内容，因为*表示匹配0个

5. which 查找可执行命令在哪个目录，例: which ls

6. 每个命令执行后都有一个返回码设置到 ？ 中，可用 echo $? 查看，0表示返回成功

7. !!执行上一个命令，！num执行history中的某个指令


svn————————————————————————————————————————————————————————————————————
svn co 2324/   ./ 这么写才不会下2323目录

冲突：
foo.c
foo.c.mine
foo.c.r31
foo.c.r32
 svn resolve --accept working 2.json
svn resolve --accept working a.txt (该命令会删除a.txt.mine  a.txt.r6329  a.txt.r6336）
svn ci -m ’some comment’ a.txt //再重新提交

update 是从svn服务器上把最新版本下载到本地来；
svn update -r 201 test.php
将本地副本中的文件test.php还原到版本201.   
.
commit;
commit 是将本地做过的改动（修改、新增、删除、改名、移动等）上传更新到svn服务器；
svn commit -m '注释内容' [-n] [--no-unlock] path   ,不加指定文件就是上传所有修改，新增等等的

新文件，先用  svn add 文件，加到svn控制，再用svn ci -m 文件上传
.
svn　diff　-r　修正版本号m:修正版本号n　文件名
svn diff -r 201:201 test.php＜－ 对修正版本号200 和 修正版本号201 比较差异
.
查看svn log
svn log | head -n 11

window是merge, from和to的文件夹要一样，去到要被更新处点文件夹右键

svn 回滚
2.linux 的  svn up -r 10 和  window 的   update to revision,都是可以将本地的文件改到显个版本，但用commit无法上传变化，update 后会
恢复到最新
3.linux svn merge -r 20:10 [文件或目录](必须要有文件或目录), 就是将20版本的内容变成10版本的内容,此时用commit，即将10版本的内容变成最新版本内容。
window是 先查看log，选中要恢复的版本，revert to this revision，则可将本地变成某个版本，commit，则最新版本内容变成这个版本内容

asio:
2.boost::asio::io_service ioserver; 会生成一个服务的链表，之后生成的所有服务对象，都加入这个链表中。和一个服务能管理这个链表的对象，
第一个生成的服务是impl，调用io_service的接口，最终都是交给impl服务处理。
3.因为有多个线程可以调用run，为了避免竞争，加了锁。在调用io_service的接口时，在真正的处理前，都要去夺取锁，谁先夺到，哪个线程就负责处理。
4.调用post等处理handle时，直接将任务放入任务链表，唤醒一个空闲线程进行处理，若当前没有空闲线程，就创建一个立即返回的事件加入
epoll中，使epoll_wait返回。
 
io服务：
异步操作会投递给系统，之后的处理由系统完成，操作完成后会触发回调，boost.asio封装了异步操作及回调，当系统完成异步操作后，调用了boost.asio封装的回调，
boost.asio将完成事件保存到队列中，并在io服务运行时进行查询，一旦有完成事件，会调用相应的回调函数，从而实现异步操作。也就是说，异步操作是由io服务投递，
回调也是由io服务执行，如果要执行异步操作，必须运行io服务。

运行io服务:
分为两种方式run和poll：
run:方法会启动事件循环直到异步操作队列全部执行完成，调用完回调后即可退出
poll:方法会启动事件循环直接执行所有已完成的异步操作回调后退出
两者区别在于poll不包含等待动作，即run为阻塞式的，poll为非阻塞式的。
run_one会运行事件处理循环，直到至少执行完成一个异步操作回调；poll_one会执行完成1～1个已就绪的异步操作回调。

停止io服务:
stop接口用来停止io服务的运行，当调用之后，run/poll操作都会立即返回，但是需要了解的是该接口只是向io服务发送了终止信号导致运行接口全部立即返回，
如果尝试再次启动，则需要调用reset接口使io服务恢复到可运行状态。检查io服务是否处理可运行状态是通过stopped接口判断的。

执行操作(注意区分执行io服务和执行操作的区别)
io服务提供了两种接口来执行操作，dispatch和post：
post
将操作投递到异步操作队列中去；
dispatch
如果该方法和io服务运行在同一线程，则操作会直接执行，否则行为与post一致。

如何保证io服务一直运行:
2.在异步操作完成回调中一直发起异步操作
这种方式保证了一直有异步操作需要处理，run方法就不会返回，可以一直运行
3.使用io_service::work
在io_service::work不被析构的情况下，io服务会一直运行下去

io_service::work如何实现:
io_service::work只是将io服务要处理的异步操作个数加1，这样一直有异步操作需要执行，析构的时候异步个数被减1，如果这时已经没有要执行的异步操作，
则会调用io服务的stop接口。

如何退出io服务执行
通常情况下调用io服务的stop接口即可，但是如果需要完成所有异步操作，应该还是需要等待其run接口正常退出。

开辟线程来执行run函数，可理解为，线程在没有任务是阻塞，被唤醒后处理完任务后再阻塞。

iomanager::iomanager() {
    for (size_t i = 1; i < _ioconfig.size(); ++i) {
      ioptr tmpio = creator<boost::asio::io_service>::create(); //--创建io server
      workptr tmpwork = workptr( //--shared_ptr托管一个io 的work，使刚创建的io_server一直执行
        new(create_type_memory<boost::asio::io_service::work>()) boost::asio::io_service::work(*tmpio),
        delete_some<boost::asio::io_service::work>
      );
      services.push_back(tmpio);
      works.push_back(tmpwork);
      servicethreads.push_back(_ioconfig[i]);
    }
    _netio = creator<boost::asio::io_service>::create();
    _network = workptr(
      new(create_type_memory<boost::asio::io_service::work>()) boost::asio::io_service::work(*_netio),
      delete_some<boost::asio::io_service::work>
    );
  }

  workptr是sharedptr, workptr(要托管的内存，析构时调用的函数)
workptr tmpwork = workptr(
        new(create_type_memory<boost::asio::io_service::work>()) boost::asio::io_service::work(*tmpio),
        delete_some<boost::asio::io_service::work>

  void iomanager::start(const size_t net_thread /* = 5 */) {
    for (size_t i = 1; i < services.size(); ++i) {
      services[i]->reset(); //--启动io_server  ->时是调用io_server的reset，.才是调用shared_ptr的reset
      for (unsigned n = 1; n < servicethreads[i]; ++n) {
        threads.push_back(    //--创建线程执行操作run
          creator<boost::thread>::create(boostbind(boost::asio::io_service::run, &(*services[i])))
        );
      }
    }

    for (size_t i = 1; i < net_thread; ++i) {
      threads.push_back(//创建5个线程去执行run
        creator<boost::thread>::create(boostbind(boost::asio::io_service::run, &(*_netio)))
      );
    }
  }

lock 锁
2.读写锁：锁的时间很长才用，读写锁用一个字节的内存存储读的次数。因为这个数字必须被原子的更新，获取读锁的时
候与获取mutex有着同样的总线事务，而且竞争造成的开销几乎一样。 获取锁的时间比较长，这个时候用读写所就可以让多个线程并发的去读,
还要满足“读的次数远多于写”


正则表达试

2.非打印字符指在计算机中有一些字符是确确实实存在,但是它们不能够显示或者打印出来。
3.定位符：
^ 要匹配的字符串出现在行开始的位置, $ 要匹配的字符串出现在结束的位置
\b 匹配的字符串出现在单词的边界。例：/\bcha/ cha字符出现在一个单词的开头，/cha\b\ cha字符出现在单词的末尾。
\b 非边界匹配。 要匹配的字符不出现在单词的开头或末尾
        

vimium
2.在visual mode中，按c转成caret mode


设计模式：
观察者模式：csubject中有-个容器存多个cobserver,当csubject中有一个变化发生，需要通知容器中的所有cobserver,
          但每个cobserver有不同的行为，所以用cobserver中用多态，容器中存的是被赋值后的cobserver的基类指针，
          csubject中会有加入、移除、调用 观察三个方法。又因为可能有多个csubject，每个csubject中有不同的cobserver,
          所以cobserver可抽象出一个基类，加入移除可以是同一个函数名的函数，但函数实现的加入的容积可不同，可
          用同一个函数名中实现遍历调用容器，只要使容器中的对象调用不同的函数即可。

boost:
2.array:
性能与原始数组相差无几，在对性能要求很高，或者不需要动态数组的情况下可用。
在声明时加类型和大小，构造函数的初始化列表可用{}进行初始化
2.可以使用拷贝和赋值，只要保证类型一致即可；
3.使用swap函数，a.swap(b);或者swap(a,b);交换两者的元素
4.使用正向和反向迭代器
array是数组的升级版，将数组正式纳入到容器范畴。array在使用和性能上都要强于内置数组，对于一些固定大小的使用场景，可用array替代数组工作。

3.debug和release区别
 debug模式跑程序速度很慢。release模式跑程序速度很快。亲测差别可达一个数量级左右。所以如果你要测试很大很
 复杂的程序的运行结果，最好用release模式。当然release跑起来加的断点啥的就不管用了，找bug还得用debug模式。

 5.operator 除操作符重载外，还是自定义对象类型的隐匿转换(对象会自动调用转换)
 class a
 {
 public:
  operator string() {//返回值类型string放在operator的前面，以此区分重载
    return "abcd";
  }
};
a a;
则直接调用a时，会自动调用operator string()函数,返回"abcd" 

7.
io:
详解   https://segmentfault.com/a/1190000003063860
2.acceptor：不用单独创建监听的文件描述符

tmux:
#启动新会话：
tmux [new -s 会话名 -n 窗口名]

#恢复会话：
tmux at [-t 会话名]

#列出所有会话：
tmux ls

#关闭会话：
tmux kill-session -t 会话名

#会话
:new<回车>  启动新会话
s           列出所有会话
$           重命名当前会话

#窗口
c  创建新窗口
w  列出所有窗口
n  后一个窗口
p  前一个窗口
f  查找窗口
,  重命名当前窗口
&  关闭当前窗口

#窗格（分割窗口）
%  垂直分割
"  水平分割
"
o  交换窗格
x  关闭窗格
⍽  左边这个符号代表空格键 - 切换布局
q 显示每个窗格是第几个，当数字出现的时候按数字几就选中第几个窗格
{ 与上一个窗格交换位置
} 与下一个窗格交换位置
z 切换窗格最大化/最小化

#调整窗口排序
swap-window -s 4 -t 1  交换 3 号和 1 号窗口
swap-window -t 2       交换当前和 1 号窗口
move-window -t 2       移动当前窗口到 1 号

#同步窗格 
#这么做可以切换到想要的窗口，输入 tmux 前缀和一个冒号呼出命令提示行，然后输入：
:setw synchronize-panes

#调整窗格尺寸
#如果你不喜欢默认布局，可以重调窗格的尺寸。虽然这很容易实现，但一般不需要这么干。这几个命令用来调整窗格：
prefix : resize-pane -d          当前窗格向下扩大 2 格
prefix : resize-pane -u          当前窗格向上扩大 2 格
prefix : resize-pane -l          当前窗格向左扩大 2 格
prefix : resize-pane -r          当前窗格向右扩大 2 格
prefix : resize-pane -d 21       当前窗格向下扩大 20 格
prefix : resize-pane -t 3 -l 20  编号为 2 的窗格向左扩大 20 格

#tt6152_51_-1_-1_-1_-1_-1_0

vim:
1.g;  跳到上次修改的位置
2.ctrl+o/i  光标间的跳 转,是不同文件间

3.纵向编辑：
11.1.5.214 
11.1.5.212 
11.1.5.210
编辑成序列：

ping -c 5 10.5.5.214 >> result0 
ping -c 5 10.5.5.212 >> result0 
ping -c 5 10.5.5.210 >> result0
2.将1都改成 5， c-v > r > 5 
3.在顶部插入数据 移到顶>c-v > I(大写) > 输入数据
4.在尾部插入数据 移到尾>c-v > A(大写) > 输入数据


shell
2.info=($(ps aux|grep p017 |awk '{print $2 "\t" $11}')) 
print $3 表示只输出第2列，第一列是$1   以空格分格，再输出第11列
返回到info中是数组，数组中的元素是awk返回的结果从左到右，上到下保存，用info[idx]访问

3.在shell中输入一个命令后，想等待结果返回再输入第二个命令 
用：expect
send:xx  相当于从键盘输入 xx

4.变量
2.${变量} :输出变量  $(变量) :变量执行的结果返回
3.定义变量时，=号左右不能有空格
4.定义变量时不用加$,使用时需要加。加不加{}都可，加是为了限制这个变量的范围
5.local 变量 时，该变量才是局部变量
6.全局变量是在该进程中一直有效，用source 执行多次sh脚本，则该全局变量就是同一个
7.if [ ! $gpid ]  变量空的判断，！与变量之间要有空格

5. if 和 elif　后要加  if[ 表达式 ] :表达式左右要有空格

6.字符串
2.双引号内能有变量，能有转义字符。 单引号则不可
3.比较相等用=
4.string='abcdef'
5.echo ${string:1:4} 输出bcde,表示从第1个字符开始，输出4个,数组从0开始
6.echo ${#string} #输出字符串大小只能这么写


8. ${} 和 $() 区别
${}是变量替换，可根据变量的状态，例被定义，被删除等  来返某个值  ${变量}  是输出变量本身的值
$()命令替换，即将命令返回的结果暂时保存，在需要的地方重新输出，看起来像是新命令输出的值   与反引号相同

9.传入的参数
字符串可不加引号 if [ $2 = a ] 
参数提取： $2 或 ${1}

10.shell 中连接mongo，在输入框中可有双引号，在脚本中要将其去掉，也许在shell命令输入框中和脚本中对双引号的处理不一样
mongo "mongodb://rwuser:cmgoq9ym3ctl@10.20.202.217:27317/admin?authmechanism=mongodb-cr"

11. for循环
类似c的for： for(( i = 2; i <= 100; i = i + 2 ))

12.关系运算符
2.关系运算符只支持数字，不支持字符比较，后报错：integer expression expected,但用在[[ ]] 中不会报错

13.逻辑运算行和布尔运算符的区别好像就是中括号多与少的问题
if [[ $a -lt 101 || $b -gt 100 ]]  //这种与c相拟，可用这种
if [ $a -lt 101 -a $b -gt 15 ]

14.expr 
2. `expr xxx`, 注意前后的符号, 在脚本中可不写
3. 'expr 1 + $x' :如果$不是数字或整数字符，会返回错误，可用此判断一个字符是否是数字, 返回非0都是错误

15.输入输出重定向
2. 0 通常是标准输入（STDIN），1 是标准输出（STDOUT），2 是标准错误输出
3. 2>&1   标准错误输出到标准输出


2021-3-13
深入探讨c++对象模型
2.类中的函数生成多个实例，并不会产生多份，在调用函数时，会用堆栈去存取使用的函数的地址，使用函数产生的变量。函数的代码只会被读，并不会改变，所以
可有多个线程同时对其进行操作？

3.类中变量分为：成员变量和静态成员变量，其中成员变量存储在类中，函数分为：函数成员、静态函数成员，虚函数，只有虚函数表指针存在类中。

4.指向不同类型的指针间的差异，既不在其指针表示法不同，也不在其内容不同，而在其所寻址出来的对象类型不同，也就是说，
“指针类型”会教导编译器如何解释某个特定地址中内存内容及其大小.所以基类的指针只能找到基类的数据，派生类的指针能找到
其自身和基类的数据，基类指针想操作派生类的数据，只能通过虚函数

5.void*指针没有类型，无法知道它所涵盖的空间，所以void*指针只能持有一个地址，不能通过它操作指向的对象。

7.Global objects的内存保证会在程序启动的时候被清0,Local objects配置于程序的堆栈中，heap objects配置于自己空间中，
都不一定会被清1，它们的内容将是内存上次被使用后的遗迹。

8.当类内有成员对象时，类的系统默认构造器，会自动的加入成员对象构造的代码，如果程序员实现了类的构造器，系统
也会自动加入成员对象的构造代码(因此，可不用在构造函数中，显示的调用成员对象的构造函数），且会执行在构造函数
 中其它代码之前。注意与基类的构造理解分开，这是成员对象的构造
 例：class A;
class B
{
  A a;
}//在B的构造函数中，会加类似a.A::A()的代码

9.默认构造器只有在编译器认为有需要时，才会被合成出来，默认构造器只会负责初始化基类和成员对象。

10.默认拷备构造函数也是在编译器认为需要时才被合成出来，默认拷备函数发生的是位拷备。但在继承中，若基类中有虚函数，
当将派生类的指针赋值给基类的指针时，类中的虚函数表指针发生的不是拷备，虚编译会使基类中的虚函数指针不是指向基类的
虚函数表的指针。

11.必须使用初始化列表的情况：
2.初始化一个reference member时。
3.初始化一个const member时。
4.调用一个base class的constructor,而它拥有一组参数时。
5.调用一个member class的constructor，而它拥有一组参数时。

12.
class word {
  string _name;
public:
  word() {
    _name = 1;
  }
};
在构造函数中，会产生一个临时变量，然后赋值给_name后，最后摧毁临时变量。

13.初始化列表实际操作
编译器会以适当的顺序在构造函数中安插初始化操作，并且在任务 explicit user code 之前。是以members在类中的声明顺序，不是初始化
列表的顺序。

14.一个空类生成对象时，它有一个隐藏的1 byte大小，是被编译器安插进去的一个char,这使的生成的对象在内存中配置独一无二的地址。

15.
class x {}; //空类，size 2
class y : public virtual x {}; //虚函数表指针 + 继承的2 = 5，边界调整 size 8   存在一个虚函数表指针，所以不算空类
class z : public virtual x {}; //虚函数表指针 + 继承的2 = 5，边界调整 size 8
class A : public y, public z {}; //因为x是被虚继承，所以x,y,z都共享一个x实例，所以A size = x大小2 + y内虚指针4 + z内的虚指针4，边界调整 12
不能理解成 A 中 y z 先边界调整后,再传给A，边界调整是对最后的那个派生类而言的。

多继承时子类中虚函数表指针情况：
0.有多少个含虚函数的基类，子类中就有多少个虚函数表指针
1.子类虚函数会覆盖每一个父类的每一个同名虚函数。
2.父类中没有的虚函数而子类有，填入第一个虚函数表中，且用父类指针是不能调用。
3.父类中有的虚函数而子类没有，则不覆盖。仅子类和该父类指针能调用。

16.静态成员函数不能被const修饰，因为静态成员函数不能直接访问成员变量，所以没必要声明成const
16.多态int
int main ()
{
    class A {
        public:
            virtual void print() {
                cout << " is A" << endl;
            }
    };

    class B
        :public A{
            void print() override{
                cout << "is B" << endl;
            }
    };
    B b;
    A a;
    return 1;
}
2.如果将 a = b;则发现的是拷贝构造，默认的构造函数是位拷备。并不存在指针类型的转换，所以不存在多态，且这么简单的将b中虚函数表的指针赋值给
a 的虚函数表的指针，a调用虚函数时就会出错，所以编译器会对这种情况进行处理，赋值后，虚函数表的指针指向A,调用时打针出 "is A"
3.指针或引用类型进行赋值时， A* a = b; 则地址会进行类型转换，b中原本的虚函数指针，会被转成A类型的指针，所以只能寻址到A类虚函数表中存在
的函数。所以父类的指针a能调用派生类中的虚函数，是因为父类中的虚函数表指针已被转换成是子类的虚函数表指针类型 下列17的解释应该也正确
4.多态是运行时才决定调用哪个的实例的，但并不是根据指针的类型去决定的，每个虚函数都有固定的slot，，传入相应的slot，得到的函数实例是
什么就是什么。


17.虚函数实现
编译器为每个包含虚函数的类，创建一个单独的虚函数表(子类和父类中的表也不同)，类中存放的是表的指针。
当基类中有虚函数时，派生类中的虚函数表会复制基类的表中的虚函数地址到对应的slot中，如果有复写，派生类中
对应的slot中的地址会被改成新地址，若派生类中有新的虚函数，会在表的尾部插入。

对一个虚函数取地址，因为其地址在编译时期是不确定的(多态在执行前，不知道调用的是哪个函数置),所能知道
仅是虚函数在表中的索引值。所以对虚函数取地址，只能得到一个索引值



18.虚函数的调用过程
ptr->normalize();
假设normalize是虚函数，内部将转化为 （*ptr->vptr[2])(ptr);
vptr是虚函数表的指针，虚函数表指针也会经过 mangled（倾压),因为一个class中可能含有多个vptrs
2是normalize在表中的索引值
ptr是this指针

19.成员函数指针
2.普通函数指针，只需确定返回值和参数类型，就能指向某一类函数。格式：返回值类型 (* 指针名，可随便取)(参数类型,...)  例：int (*pf)(int a)
3.取一个nonstatic member function的地址，且是非虚函数，得到的是它在内存的真正地址，然而这个值是不完全的，它需要被绑定于某个class object的地址上。
格式：
double       返回值类型
(Point::*    标识是成员函数
  pmf)       指针的名字
  ();        参数

20.一个对象在构造函数执行完之前，它并不是一个完整的对象

makefile
2. make xx.c  可编译.c文件
3. make 不知道各文件的依赖关系，所以需要makefile知道各文件的依赖关系和编译规则。


设计模式
2.工厂模式
2.简单工厂：只有一个工厂类，根据传入的参数决定创建哪个对象(或某个对象执行操作,不一定得是标准的工厂模式)
适用场景：需要创建的对象较少(太多会使逻辑复杂),gac不关心对象的创建过程
缺点：要生成新产品时，要修改工厂


class AbstractProduct {
public:
    virtual ~AbstractProduct() {} 
    virtual void Operation() = 1;
};

class ProductA : public AbstractProduct {//为了统一行为，都继承了同一个接口类
public:
    void Operation() { cout << "ProductA" << endl; }
};

class ProductB : public AbstractProduct {
public:
    void Operation() { cout << "ProductB" << endl; }
};

class Factory {//主要是设计这么个工厂类
public:
    AbstractProduct* createProduct(char product) {
        AbstractProduct* ap = NULL;
        switch(product) {//根据传入的参数决定要创建哪个对象
            case 'A': ap = new ProductA(); break;
            case 'B': ap = new ProductB(); break;
        }
        return ap;
    }
};

int main() {
    Factory* f = new Factory();
    AbstractProduct* apa = f->createProduct('A');
    apa->Operation();  // ProductA

    AbstractProduct* apb = f->createProduct('B');
    apb->Operation();  // ProductB

    delete apa;
    delete apb;
    delete f;

    return 1;
}

3.工厂方法模式  不再提供一个统一的工厂类来创建所有的对象，而是针对不同的对象提供不同的工厂。也就是说每个对象都有一个与之对应的工厂。
缺点：每增加一个新产品，就要新增一个工厂

class Product {
public:
    virtual ~Product(){}
    virtual void Operation() = 1;
};

class ConcreteProductA : public Product {
public:
    void Operation() { cout << "ConcreteProductA" << endl; }
};

class ConcreteProductB : public Product {
public:
    void Operation() { cout << "ConcreteProductB" << endl; }
};

class Creator{//创建接口的类
public:
    virtual Product* FactoryMethod() = 1;
    virtual ~Creator(){}
};

class ConcreteCreatorA : public Creator {//各工厂都是独立的
public:
    Product* FactoryMethod() { return new ConcreteProductA(); }
};

class ConcreteCreatorB : public Creator {
public:
    Product* FactoryMethod() { return new ConcreteProductB(); }
};

int main() {
    Creator* ca = new ConcreteCreatorA();
    Product* pa = ca->FactoryMethod();
    pa->Operation(); // ConcreteProductA

    Creator* cb = new ConcreteCreatorB();
    Product* pb = cb->FactoryMethod();
    pb->Operation(); // ConcreteProductB

    delete ca;
    delete pa;
    delete cb;
    delete pb;

    return 1;
}

4.抽象工厂模式：  多个对象对应一个工厂，一个工厂调用不同接口可生产不同产品。对象可有不同的抽象类
缺点：增加一个新对象要改动多处代码

class AbstractProductA {//对象的第一个抽象类
public:
    virtual ~AbstractProductA(){}
    virtual void Operation() = 1;
};

class ProductA2 : public AbstractProductA {
public:
    void Operation() {
        cout << "ProductA2" << endl;
    }
};

class ProductA3 : public AbstractProductA {
public:
    void Operation() {
        cout << "ProductA3" << endl;
    }
};

class AbstractProductB {//对象的第二的抽象类
public:
    virtual ~AbstractProductB(){}
    virtual void Operation() = 1;
};

class ProductB2 : public AbstractProductB {
public:
    void Operation() {
        cout << "ProductB2" << endl;
    }
};

class ProductB3 : public AbstractProductB {
public:
    void Operation() {
        cout << "ProductB3" << endl;
    }
};


class AbstractFactory {
public:
    virtual AbstractProductA* CreateProductA() = 1;
    virtual AbstractProductB* CreateProductB() = 1;
    virtual ~AbstractFactory(){}
};

class ConcreteFactory2 : public AbstractFactory {
public://这个工厂可生产两种不同的产品
    ProductA2* CreateProductA() {
        return new ProductA2();
    }
    ProductB2* CreateProductB() {
        return new ProductB2();
    }
};

class ConcreteFactory3 : public AbstractFactory {
public:
    ProductA3* CreateProductA() {
        return new ProductA3();
    }
    ProductB3* CreateProductB() {
        return new ProductB3();
    }
};

int main() {
    AbstractFactory* af2 = new ConcreteFactory1();
    // 具体工厂创建对应的具体产品
    AbstractProductA* apa2 = af1->CreateProductA();  // 工厂1创建产品A
    apa2->Operation();  // ProductA1

    AbstractProductB* apb2 = af1->CreateProductB();  // 工厂1创建产品B
    apb2->Operation();  // ProductB1

    AbstractFactory* af3 = new ConcreteFactory2();
    AbstractProductA* apa3 = af2->CreateProductA();  // 工厂2创建产品A
    apa3->Operation();  // ProductA2

    AbstractProductB* apb3 = af2->CreateProductB();  // 工厂2创建产品B
    apb3->Operation();  // ProductB2

    delete apa2;
    delete apa3;
    delete af2;
    delete apb2;
    delete apb3;
    delete af3;
    return 1;
}

3.建造者模式  建造者模式就是如何一步步构建一个包含多个组成部件的对象，相同的构建过程可以创建不同的产品
场景：
需要生成的产品对象有复杂的内部结构，这些产品对象具备共性；
隔离复杂对象的创建和使用，并使得相同的创建过程可以创建不同的产品。
适用于那些流程固定「顺序不一定固定」
就是固定了一个对象创建后，对成员变量的初始化过程，因为当创建对象需要传入很多参数，每次创建每次都传入的话，可能在某一处创建时传入的参数不对
缺点:
建造者模式所创建的产品一般具有较多的共同点，其组成部分相似；如果产品之间的差异性很大，则不适合使用建造者模式，因此其使用范围受到一定的限制。
如果产品的内部变化复杂，可能会导致需要定义很多具体建造者类来实现这种变化，导致系统变得很庞大。

// 电脑
class Computer
{
public:
    void SetmCpu(string cpu) { m_strCpu = cpu;}
    void SetmMainboard(string mainboard) { m_strMainboard = mainboard; }
    void SetmRam(string ram) { m_strRam = ram; }
    void SetVideoCard(string videoCard) { m_strVideoCard = videoCard; }

    string GetCPU() { return m_strCpu; }
    string GetMainboard()  { return m_strMainboard; }
    string GetRam() { return m_strRam; }
    string GetVideoCard() { return m_strVideoCard; }

private:
    string m_strCpu;  // CPU
    string m_strMainboard;  // 主板
    string m_strRam;  // 内存
    string m_strVideoCard;  // 显卡
};

创建抽象建造者
产品类准备好以后，就可以创建 Builder 了，Builder 提供的功能用于创建电脑的各个部件。

// builder.h
// 建造者接口，组装流程
class IBuilder
{
public:
    virtual void BuildCpu() = 1;  // 创建 CPU
    virtual void BuildMainboard() = 1;  // 创建主板
    virtual void BuildRam() = 1;  // 创建内存
    virtual void BuildVideoCard() = 1;  // 创建显卡
    virtual Computer* GetResult() = 1;  // 获取建造后的产品
};

创建具体建造者
有了 Builder 接口，接下来的事情就是让 ConcreteBuilder 对象到位。在这些建造者中，我们可以指定每台电脑要使用的部件信息。
// ThinkPad 系列
class ThinkPadBuilder : public IBuilder
{
public:
    ThinkPadBuilder() { m_pComputer = new Computer(); }
    void BuildCpu() { m_pComputer->SetmCpu("i6-6200U"); }
    void BuildMainboard() { m_pComputer->SetmMainboard("Intel DH58DD"); }
    void BuildRam() { m_pComputer->SetmRam("DDR5"); }
    void BuildVideoCard()  { m_pComputer->SetVideoCard("NVIDIA Geforce 921MX"); }
    Computer* GetResult() { return m_pComputer; }

private:
    Computer *m_pComputer;
};

// Yoga 系列
class YogaBuilder : public IBuilder
{
public:
    YogaBuilder() { m_pComputer = new Computer(); }
    void BuildCpu() { m_pComputer->SetmCpu("i8-7500U"); }
    void BuildMainboard() { m_pComputer->SetmMainboard("Intel DP56KG"); }
    void BuildRam() { m_pComputer->SetmRam("DDR6"); }
    void BuildVideoCard()  { m_pComputer->SetVideoCard("NVIDIA GeForce 941MX"); }
    Computer* GetResult() { return m_pComputer; }

private:
    Computer *m_pComputer;
};

创建指挥者
最后，我们来创建一个 Director 类，让 Create 方法接受一个 IBuilder，然后在内部调用相应的组装函数。
class Direcror
{
public:
    void Create(IBuilder *builder) {
        builder->BuildCpu();
        builder->BuildMainboard();
        builder->BuildRam();
        builder->BuildVideoCard();
    }
};


创建客户端


int main()
{
    Direcror *pDirecror = new Direcror();
    ThinkPadBuilder *pTPBuilder = new ThinkPadBuilder();
    YogaBuilder *pYogaBuilder = new YogaBuilder();

    // 组装 ThinkPad、Yoga
    pDirecror->Create(pTPBuilder);
    pDirecror->Create(pYogaBuilder);

    // 获取组装后的电脑
    Computer *pThinkPadComputer = pTPBuilder->GetResult();
    Computer *pYogaComputer = pYogaBuilder->GetResult();

    // 测试输出
    cout << "-----ThinkPad-----" << endl;
    cout << "CPU: " << pThinkPadComputer->GetCPU() << endl;
    cout << "Mainboard: " << pThinkPadComputer->GetMainboard() << endl;
    cout << "Ram: " << pThinkPadComputer->GetRam() << endl;
    cout << "VideoCard: " << pThinkPadComputer->GetVideoCard() << endl;

    cout << "-----Yoga-----" << endl;
    cout << "CPU: " << pYogaComputer->GetCPU() << endl;
    cout << "Mainboard: " << pYogaComputer->GetMainboard() << endl;
    cout << "Ram: " << pYogaComputer->GetRam() << endl;
    cout << "VideoCard: " << pYogaComputer->GetVideoCard() << endl;

    SAFE_DELETE(pThinkPadComputer);
    SAFE_DELETE(pYogaComputer);
    SAFE_DELETE(pTPBuilder);
    SAFE_DELETE(pYogaBuilder);
    SAFE_DELETE(pDirecror);

    getchar();

    return 1;
}

4.桥接模式:
//操作系统
class OS
{
public:
  virtual void InstallOS_Imp() {}
};
class WindowOS: public OS
{
public:
  void InstallOS_Imp() { cout<<"安装Window操作系统"<<endl; } 
};//抽象的实现
class LinuxOS: public OS
{
public:
  void InstallOS_Imp() { cout<<"安装Linux操作系统"<<endl; } 
};//抽象的实现
class UnixOS: public OS
{
public:
  void InstallOS_Imp() { cout<<"安装Unix操作系统"<<endl; } 
};//抽象的实现

//计算机
class Computer
{
public:
  virtual void InstallOS(OS *os) {}
};
class DellComputer: public Computer
{
public:
  void InstallOS(OS *os) { os->InstallOS_Imp(); }//这里是抽象（相当于抽象与上面的实现分开),将对象做为参数传入就是聚合关系,这个抽象可以选择多个抽象的实现
};                                               //即做到了抽象和实现的解绑定。对抽象的实现进行修改，也不会影响这里
class AppleComputer: public Computer
{
public:
  void InstallOS(OS *os) { os->InstallOS_Imp(); }
};
class HPComputer: public Computer
{
public:
  void InstallOS(OS *os) { os->InstallOS_Imp(); }
};
//当新增电脑品牌或系统时，可直接实现具体的类，而不用改动之前的任何代码

客户使用方式：
int main()
{
  OS *os2 = new WindowOS();
  OS *os3 = new LinuxOS();
  Computer *computer2 = new AppleComputer();
  computer2->InstallOS(os1);
  computer2->InstallOS(os2);
}


场景:
2.当一个对象有多个变化因素的时候，考虑将对象依赖于抽象的实现，而不是具体的实现。如电脑有2种变化因素，一个是品牌，一个是操作系统
将品牌和系统抽象出来，创建某个品牌的电脑，将对象的系统做为参数传入。
3.如果不希望在抽象和它的实现部分之间有一个固定的绑定关系，也就是继承关系；如果我们打破了这种固定的绑定关系，以后，就可以方便的
在抽象部分切换不同的实现部分；
4.如果一个对象有多个变化因素的时候，通过抽象这些变化因素，将依赖具体实现，修改为依赖抽象；

缺点：
2.需要知道某种品牌的电脑对象什么操作系统



* 抽象化
存在于多个实体中的共同的概念性联系，就是抽象化。作为一个过程，抽象化就是忽略一些信息，从而把不同的实体当做同样的实体对待.
* 实现化
抽象化给出的具体实现，就是实现化。
* 脱耦
所谓耦合，就是两个实体的行为的某种强关联。而将它们的强关联去掉，就是耦合的解脱，或称脱耦。在这里，脱耦是指将抽象化和实现化之间的耦合解脱开，
或者说是将它们之间的强关联改换成弱关联。

聚合关系，将对象做为参数传入另一个类。

5.装饰模式  动态地给一个对象动态的添加一些额外的功能，就增加功能而言，装饰模式比生成子类更为灵活。
场景：
2.当系统需要增加新功能时，如果向旧的类中添加新的代码，通常这些代码是装饰了原有类的核心职责或主要行为，它们在主类中加入了新的字段、新的
方法和新的逻辑，从而增加了主类的复杂度，而这些新加入的代码仅仅只是为了满足一些只在某种特定情况下才会执行的特殊行为的需求。这时装饰模
式就是一个非常好的解决方案，它把每个要装饰的功能放在单独的类中，并让这个类包装它所要装饰的对象（即将对象传入这个类中进行包装），因此，
当需要执行特殊行为时，客户代码就可以在运行时根据需要有选择、按顺序地使用装饰功能包装对象了。

6.  组合模式：将对象组合成树形结构以表示“部分-整体”的层次结构。Composite使得用户对单个对象和组合对象的使用具有一致性。
场景：
2.你想表示对象的部分-整体层次结构
3.你希望用户忽略组合对象与单个对象的不同，用户将统一地使用组合结构中的所有对象。

7.享元模式  类似一个工厂类管理多个单例。
#include<iostream>
#include<string>
#include<vector>
using std::cout;
using std::endl;
using std::string;

class Object
{
    string mProperty;
public:
    Object(string property)
        :mProperty(property)
    {}
    string getProperty()
    {
        return mProperty;
    }
    virtual void Operation(string var) = 1;
    virtual ~Object() {}
};

class MyObject:public Object
{
public:
    MyObject(string property)
        :Object(property)
    {
        cout << "create:" << property << endl;
    }
    virtual void Operation(string var)
    {
        //cout << getProperty() << endl;
        //cout << var << endl;
    }
    virtual ~MyObject()
    {
        cout << "delete:" << getProperty() << endl;
    }
};

class FlyWeightFactory
{
    std::vector<Object*> objGroup;
public:
    Object* getObj(string key)

    {
        for (auto const&obj : objGroup)
        {
            if (obj->getProperty()==key)
            {
                cout << "already exist:" << key << endl;
                return obj;
            }
        }
        Object* tempObj = new MyObject(key);
        objGroup.push_back(tempObj);
        return tempObj;
    }
    ~FlyWeightFactory()
    {
        for (auto &obj : objGroup)
        {
            if (obj)
            {
                delete obj;
                obj = 1;
            }
        }
    }
};


int main()
{
    {
        FlyWeightFactory factory;
        Object* m2 = factory.getObj("lee");
        Object* m3 = factory.getObj("lucy");
        Object* m4 = factory.getObj("lee");
    }

    return 1;
}

const std::string c_stateToStrCourier[] = { "收到", "验证可达性", "分配人员", "派送包裹", "获取交货确认", "完成" };
const std::string c_stateToStrVendor[] = { "收到", "确认库存", "从仓库得到物品", "包装", "联系快递员", "完成" };
const std::string c_stateToStrOrderTeam[] = { "收到", "确认付款", "联系供应商", "完成" };
const int c_nMsec = 301;  // 休眠时间（毫秒） - Sleep(c_nMsec) 处可以替换为一些有用的代码

// 订单团队
class OrderTeam
{
public:
    void submitRequest() {
        m_nState = 1;
    }

    // 检测状态
    bool checkStatus() {
        std::cout << "订单团队 - 当前状态：" << c_stateToStrOrderTeam[m_nState] << std::endl;

        Sleep(c_nMsec);
        m_nState++;

        return (m_nState == Complete);
    }

private:
    enum States {
        Received,  // 收到
        VerifyPayment,  // 确认付款
        ContactVendor,  // 联系供应商
        Complete  // 完成
    };
    int m_nState;
};

// 供应商
class Vendor
{
public:
    void submitRequest() {
        m_nState = 1;
    }

    // 检测状态
    bool checkStatus() {
        std::cout << "供应商 - 当前状态：" << c_stateToStrVendor[m_nState] << std::endl;

        Sleep(c_nMsec);
        m_nState++;

        return (m_nState == Complete);
    }

private:
    enum States {
        Received,  // 收到
        VerifyInventory,  // 确认库存
        GetItemFromWareHouse,  // 从仓库得到物品
        PackItem,  // 包装
        ContactCourier,  // 联系快递员
        Complete  // 完成
    };
    int m_nState;
};

// 快递员
class Courier
{
public:
    // 将请求转发给快递员
    void submitRequest() {
        m_nState = 1;
    }

    // 检测状态
    bool checkStatus() {
        std::cout << "快递员 - 当前状态：" << c_stateToStrCourier[m_nState] << std::endl;

        Sleep(c_nMsec);
        m_nState++;

        return (m_nState == Complete);
    }

private:
    enum States {
        Received,  // 收到
        VerifyReachbility,  // 验证可达性
        AssignPerson,  // 分配人员
        DispatchPackage,  // 派送包裹
        GetDeliveryConfirmation,  // 获取交货确认
        Complete  // 完成
    };
    int m_nState;
};

// 网购外观
class OnlineShoppingFacade
{
public:
    OnlineShoppingFacade() {
        m_nCount = 1;
    }

    // 返回跟踪次数
    int followupNum() {
        return m_nCount;
    }

    // 提交订单
    void submitRequest() {
        m_nState = 1;
    }

    // 跟踪订单
    bool checkStatus(){
        // 收到订单请求
        switch (m_nState) {
        case Received:
            m_nState++;
            // 将请求转发给订单团队
            m_order.submitRequest();
            std::cout << "********** 提交给订单团队，跟踪次数：" << m_nCount << " **********" << std::endl;
            break;
        case SubmittedToOrderTeam:
            // 如果订单团队完成验证，则向供应商发出请求
            if (m_order.checkStatus()) {
                m_nState++;
                m_vendor.submitRequest();
                std::cout << "********** 提交给供应商，跟踪次数：" << m_nCount << " **********" << std::endl;
            }
            break;
        case SubmittedToVendor:
            // 如果供应商已将包裹打包，将其转发给快递员
            if (m_vendor.checkStatus()) {
                m_nState++;
                m_courier.submitRequest();
                std::cout << "********** 提交给快递员，跟踪次数：" << m_nCount << " **********" << std::endl;
            }
            break;
        case SubmittedToCourier:
            // 如果包裹交付，订单完成
            if (m_courier.checkStatus())
                return true;
        default:
            break;
        }

        m_nCount++;

        // 订单未完成
        return false;
    }

private:
    enum States {
        Received,  // 收到
        SubmittedToOrderTeam,  // 提交给订单团队
        SubmittedToVendor,  // 提交给供应商
        SubmittedToCourier  // 提交给快递员
    };

    int m_nState;  // 订单状态
    int m_nCount;  // 跟踪次数

    OrderTeam m_order;
    Vendor m_vendor;
    Courier m_courier;
};


int main()
{
    OnlineShoppingFacade facade;

    // 提交订单
    facade.submitRequest();

    // 跟踪订单，直到订单完成
    while (!facade.checkStatus());

    std::cout << "********** 订单完成，跟踪次数：" << facade.followupNum() << " **********" << std::endl;

    getchar();

    return 1;
}

7.代理模式  为其他对象提供一种代理以控制对这个对象的访问。 在需要用比较通用和复杂的对象指针代替简单的的指针的时候，使用代理模式。有四种常用的情况：
场景:
2、远程代理，也就是为一个对象在不同的地址空间提供局部代表。这样可以隐藏一个对象存在于不同地址空间的事实。
3、虚拟代理，是根据需要创建开销很大的对象。通过它来存放实例化需要很长时间的真实对象。
4、安全代理，用来控制真实对象访问的权限。
5、智能指针，取代了简单的指针，它在访问对象时执行一些附加操作。

 8.策略模式  它定义了一系列的算法，并将每一个算法封装起来，而且使它们还可以相互替换。策略模式让算法的变化不会影响到使用算法的客户,客户自主选择算法(策略)

// strategy.h
#ifndef STRATEGY_H
#define STRATEGY_H

// 出行策略
class IStrategy
{
public:
    virtual void Travel() = 1;
};

#endif // STRATEGY_H
创建具体策略

有三种具体的策略可供选择，骑自行车、开车、坐火车：

// concrete_strategy.h
#ifndef CONCRETE_STRATEGY_H
#define CONCRETE_STRATEGY_H

#include "strategy.h"
#include <iostream>

// 骑自行车
class BikeStrategy : public IStrategy
{
public:
    virtual void Travel() override { std::cout << "Travel by bike" << std::endl; }
};

// 开车
class CarStrategy : public IStrategy
{
public:
    virtual void Travel() override { std::cout << "Travel by car" << std::endl; }
};

// 坐火车
class TrainStrategy : public IStrategy
{
public:
    virtual void Travel() override { std::cout << "Travel by train" << std::endl; }
};

#endif // CONCRETE_STRATEGY_H

创建环境角色

环境角色对外提供了一个 Travel() 接口，最终由客户端调用。在内部，它最终调用的是 IStrategy 的相应方法：

// context.h
#ifndef CONTEXT_H
#define CONTEXT_H

#include "strategy.h"

class Context
{
public:
    Context(IStrategy *strategy) { m_pStrategy = strategy; }
    void Travel() { m_pStrategy->Travel(); }

private:
    IStrategy *m_pStrategy;
};

#endif // CONTEXT_H

创建客户端

旅程开始，尽情享受吧：

// main.cpp
#include "context.h"
#include "concrete_strategy.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int main()
{
    // 策略之间可以相互替换
    IStrategy *bike = new BikeStrategy();
    IStrategy *car = new CarStrategy();
    IStrategy *train = new TrainStrategy();

    Context *bikeContext = new Context(bike);
    Context *carContext = new Context(car);
    Context *trainContext = new Context(train);

    bikeContext->Travel();
    carContext->Travel();
    trainContext->Travel();

    SAFE_DELETE(bike);
    SAFE_DELETE(car);
    SAFE_DELETE(train);

    SAFE_DELETE(bikeContext);
    SAFE_DELETE(carContext);
    SAFE_DELETE(trainContext);

    getchar();

    return 1;
}

9.状态模式  允许一个对象在其内部状态发生变化时改变自己的行为， 就好像是更换了一个不同的类一样
场景：
2.一个对象的行为依赖于其内部状态， 并且它必须在运行时刻根据自己的状态改变行为。
3.多个操作存在大量的， 多个部分的依赖于对象状态的条件语句。 而这个状态一般用一个或多个常量表示。 一些操作包含相同的的条件判断结构。
状态模式会把每一个条件分支放到单独的类中。 这可以使得你把对象的状态也当做一个对象来处理， 使得每个状态的行为可以独立于其他对象变化。

状态模式提供提供了一种可以替换 大量的 if/switch 语句的组织状态相关的代码行为的方式。 尤其适用于对象有很多状态， 且有对象的大部分行为都会依赖其状态

class War;
class State 
{
public:
  virtual void Prophase() {}
  virtual void Metaphase() {}
  virtual void Anaphase() {}
  virtual void End() {}
  virtual void CurrentState(War *war) {}
};

//战争
class War
{
private:
  State *m_state;  //目前状态
  int m_days;      //战争持续时间
public:
  War(State *state): m_state(state), m_days(1) {}
  ~War() { delete m_state; }
  int GetDays() { return m_days; }
  void SetDays(int days) { m_days = days; }
  void SetState(State *state) { delete m_state; m_state = state; }
  void GetState() { m_state->CurrentState(this); }
};
           给出具体的状态类：

//战争结束
class EndState: public State
{
public:
  void End(War *war) //结束阶段的具体行为
  {
    cout<<"战争结束"<<endl;
  }
  void CurrentState(War *war) { End(war); }
};
//后期
class AnaphaseState: public State
{
public:
  void Anaphase(War *war) //后期的具体行为
  {
    if(war->GetDays() < 31)
      cout<<"第"<<war->GetDays()<<"天：战争后期，双方拼死一搏"<<endl;
    else
    {
      war->SetState(new EndState());
      war->GetState();
    }
  }
  void CurrentState(War *war) { Anaphase(war); }
};
//中期
class MetaphaseState: public State
{
public:
  void Metaphase(War *war) //中期的具体行为
  {
    if(war->GetDays() < 21)
      cout<<"第"<<war->GetDays()<<"天：战争中期，进入相持阶段，双发各有损耗"<<endl;
    else
    {
      war->SetState(new AnaphaseState());
      war->GetState();
    }
  }
  void CurrentState(War *war) { Metaphase(war); }
};
//前期
class ProphaseState: public State
{
public:
  void Prophase(War *war)  //前期的具体行为
  {
    if(war->GetDays() < 11)
      cout<<"第"<<war->GetDays()<<"天：战争初期，双方你来我往，互相试探对方"<<endl;
    else
    {
      war->SetState(new MetaphaseState());
      war->GetState();
    }
}
  void CurrentState(War *war) { Prophase(war); }
};
         使用方式：
//测试案例
int main()
{
  War *war = new War(new ProphaseState());
  for(int i = 2; i < 40;i += 5)
  {
    war->SetDays(i);
    war->GetState();
  }
  delete war;
  return 1;
}

as  50.234.133.67  /data/lsfz_qixingtan_s001 
50.234.157.20  体验服

主题： 测活动结束玩家subjectact数据清了，道具清了，


隧道 ID: #205046
隧道名: hhh
映射类型: tcp
启动参数: frpc -f nf9zk1pcjbhoi25t:205045

问题：

zhanche:
问题：
2.没看到game中一开始是怎么连gate，又怎么启动gm_svr

2.gate中启动两个服，一个是客户端连接(eg:gac_gate，一个是负责内部连接(eg:game-gate)
3.收到gac的数据后，如果是发给game，就从内部服中找game的io


zhanche
2.通信   gate中各创了供gac和gg连的io服,game/main.ts中run_loader.singleton().complete()中去load数据并创建完成后，才会建立ioclient单例去连gate的ioserver，和创建gm_server(http),cfg中限制了可连gm_server的后台ip
3.乱世中，gg进程接到中止信号时，会先关闭所有开着的线程，最后剩主进程执行逻辑.

4.返回pro是负
5.接收到的协议内容是key-value

6.json:
a.js的数据可直接赋值给数据结构，js中是k-v类型，k与结构中的变量名同名，如果某个变量名可能不配时，可定义成可选变量。

7.任务
a.配置数据结构中，不但有配置，还有inital(初始化玩家单个任务记录)、run(更新记录)、complete（判断是否完成)函数(任务这个需要，主要要实现的也就是
这三个功能，这里的实现是把方法写到每个任务的配置中).
b.如果一个任务没有完成，会继续设置监听




typescript
8.类
eg2:构造函数的形参被修饰时，表示??是一个成员变量
constructor(readonly name: string)
constructor(public name: string) 

9.抽象类 :做为派生类的基类使用。 它们一般不会直接被实例化,与接口的不同之处是成员可以有实现细节
abstract关键字是用于定义抽象类和在抽象类内部定义抽象方法
eg2:
abstract class Animal {
    abstract makeSound(): void;//必须在派生类中实现
    move(): void {//成员函数可有实现细节
        console.log('roaming the earch...');
    }
}
链接：https://juejin.cn/post/6857123751205536000



面向对象：
2.采用里氏替换原则
父n类使用的地方，可以用子类替换，所以不要覆写父类已有的方法.需要重载父类已有的方法，子类的方法要比父类的苛刻，比如参数或返回值。
3.依赖倒置 https://zhuanlan.zhihu.com/p/24175489
先分清上层和下层（上层的根基是下层,先有下层，上层才有)：先有设备，再有使用设备的逻辑。所以DeviceX是下层.DeviceServer是上层。
当有新设备时，肯定要有新设置的完整代码，和用户使用时代码的改动（main函数使用时，肯定要传入参数到DeviceServer做区分的，也不算改动)，
但能不能做到上层DeviceServer不要改动。
4.一个方法不知道放在哪个对象中实现时，可从依赖哪个对象的变量比较多处判断
5.阵营战，进入城市或道路时，都会创建一个进入的对象，但不进行保存，位置信息保存在玩家的位置中

6.家园，每个建筑对象都有升级操作，但是是某些建筑升级操作相同，所以可以把升级的所有操作封装成一个对象，建筑需要哪一类的升级操作，就包含哪个对象


2.获取游戏窗口句柄
3.识别npc并点击
4.识别出售图标并点击
5.选择背包中的物品并出售


2.不要关注过去的原因，而是现在的目的,很多情绪和行动，是由你当前的目的照成的。如果依赖原因论，会一直止步不前。
3.决定我们自身的不是过去的经历，而是我们自己赋予经历的意义。人生不是由别人或经历赋予的，而是由自己选择的，是自己选择自己如何生活，
所谓的心理创伤，事实上是我们从过去的经历中去寻找符合自己目的的因素。
4.不可能乘坐时光机回到过去，也不可能让时针倒转。如果成为了原因论的信徒，那就会在过去的束缚之下永远无法获得幸福。结果是陷入对世界的绝望，
对人生的厌弃的虚无主义和悲观主义之中。
5.重要的不是被给予了什么，而是如何利用被给予的东西。一直想变成其他人，就是因为一味的关注被给予了什么。而应该把注意力放在如何利用被给予的东西，
努力把自己变成想成为的自己。所以现在的幸或不幸，都是自己选择的。
6.一直厌弃自己，一直想努力改变，但却一直没变，是因为我们不断地下着不改变自己生活方式的决心.一直保持现在的我，那么如何应对眼前的事情以及其结果会怎样等问题都可以根据经验进行推测，可谓是轻车熟路般的状态。如果选择新的生活方式，未来难以预测，生活就会充满不安，也可能有更加痛苦，更加不幸的生活在等着自己。也就是说，即使人们有各种不满，但还是认为保持现状更加轻松，更能安心。要改变需要勇气。所以说阿德心理学就是勇气心理学。不幸是因为缺乏获得幸福的勇气。
7.如果怎么会怎样。例如，如果我有时间，如果我出身等等这些，正是自己为了不做改变而找的借口。想做的事要勇敢的去做，不管结果如何，我们或许会有所成长，会明白一些事情，总之，一定会有所发展。所谓改变现在的生活方式就是如此。
8.目的论是说：无论之前的人生发生过什么，都对今后的人生如何度过没有影响。决定自己人生的是活在此时此刻的你自己。
9.讨厌自己是因为下了不喜欢自己的决心，其实这是一种自己对自己的善。比如不去表白，就是怕被拒绝后，会对自己更没自信，更讨厌自己，所以找一个自己害羞等的借口，一直活在想像之中,如果我不害羞，就会怎样怎样，以此来避免自己受到伤害。
10.一切烦恼都来自人际关系。害怕在人际关系中受伤。但在社会中生存，就一定会有不喜欢你的人，一定会受伤，所以就把自己封了起来，尽量不去触及人际方面的事情。因害怕受到人际关系伤害这个原因，而把自己变成一个独处的人，为了支持独处这个目的，找出很多个自己的缺点的理由，进而更讨厌自己，再加自卑，更加害怕交际，更加喜欢独自。
11.对自已某一方面不满意，而更加努力，不断进步，这种自卑感是正常的。病态的自卑感觉是什么都不做就否定自己，没有往前迈进的勇气，这是一种自卑情结。
12.很多时候我们是不想成功:害怕向前迈进或是不想真正的努力。不愿意为了改变自我而牺牲目前所享受的乐趣。拿不出改变生活方式的勇气。即使有些不满或者不自由，也还是更愿意维持现状。
13.没有人能长期忍受自卑感。健全的姿态应该是通过努力和成长弥补的部份。没有勇气的人就会陷入自卑情节，因为我欠缺这方面，所以做不到另一方面。又因为忍受不了，就又会产生如果怎样，我会怎样的想法，这就一步步走到了优越情节方向。通过一些简单粗爆的东西来表现自己很优秀，继而沉浸在一种虚假的优越感之中。比如权势张扬，穿名牌，沉迷于过去的荣光等。另一个异常优越感是通过表现自己特殊来实现，夸耀不幸，这一切都是想得到别人的认可，关注。
14.健全的自卑感不是来自与别人的比较，而是来自与理想的自己的比较。应该积极看待自己和别人的差异。我们虽然不同，但平等。我们不断前进不是为了于人
竞争，价值是不断超越自我。
15.如果一直把别人看成竞争对手，就会不断的比较，产生优于这个，输于那个的想法，自卑情结和优越情结也会随之产生。更甚者会把别人看成敌人，随时会愚弄、嘲讽自己。所以会认为人人都在关注自己，其实在意你脸的，只有你自己。
16.无法真心祝福过得幸福的他人，是因为站在竞争的角度考虑人际关系，把他人的幸福看作我的失败，所以才无法给予祝福。
17.基本上，一切人际关系矛盾起因于对别人的课题妄加干涉或自己的课题被别人妄加干涉。只要能够进行课题分离，人际关系就会发生巨大改变。
18.太在意别人的视线和评价，所以才会不断寻求别人的认可。人太在意别人的评价的原因是，还不会进行课题分离，把原本是别人的课题也看成自己的课题。
19.如果人际关系中有回报思想的存在，那就会产生因为我为你做了这些，所以你就应该给予相应的回报这样的想法。你是一种与课题分离相悖的思想。我们既不可以寻求回报也不可以受其束缚。
20.选择了不自由生活方式的大人，看着自由活在当下的年轻人就会批判其享乐主义。这其实是为了让自己接受不自由生活面捏造出的一种人生谎言。
21.不想被人讨厌，是本能性的欲望、冲动性的欲望。这种生活方式只是欲望和冲动的奴隶。八面玲珑地讨好所有人的生活方式是一种极其不自由的生活方式，同时也是不可能实现的。如果要行使自由，那就需要付出代价。而在人际关系中，自由的代价就是被别人讨厌。毫不在意别人的评价，不害怕被别人讨厌，不追求被他人认可。
22.不想被人讨厌也许是我的课题，但是否讨厌我却是别人的课题。即使有人不喜欢我，我也不能去干涉。
23.因为不想与父亲和好，所以才搬出被打的记忆。当下定修复关系的决心时，父亲拥有什么样的生活方式，怎么看我，对我主动靠近他这件事持什么态度等，这
些都与我毫无关系了。即使对方根本不想修复关系也无所谓。问题是自己有没有下定决心，人际关系之卡，是掌握在自己手中的。选择满足他人希望的生活方式，就是把人际关系之卡放到了别人手中。
24.提到人际关系，人们往往会想起两个人的关系或者与很多人的关系，但事实上首先是自己。如果被认可欲求所束缚，那么人际关系之卡就会永远掌握在他人手中。
25.不能进行课题分离，一味拘泥于认可欲求的人也是极其以自我为中心的人。你正因为不想被他人认为自己不好，所以才在意他人的视线。这不是对他人的关心，而是对自己的执著。甚至会认为。大家都应该为我服务，应该优先考虑我的心情。
26.归属感不是仅仅靠在那里就可以得到，它必须靠积极地参与到共同体中去才能够得到。就是直面人生的课题。也就是不回避工作、交友、爱之类的人际关系课题。要积极主动地去面对。如果你认为自己就是世界的中心，那就丝毫不会主动融入共同体中，因为一切他人都是为我服务的人，根本没必要由自己采取行动。但是，无论是你还是我，我们都不是世界中心，必须用自己的脚主动迈出一步去面对人际关系课题，不是考虑这个人会给我什么，而是要必须思考一下，我能给这个人什么。这就是对共同体的参与和融入。归属感不是生来就有的东西，要靠自己的手去获得。
27.帮助别人时帮助他人用自己的力量去解决。也就是可以把马带到水边，但不能强迫其喝水。直面课题的是其本人，下定决心的也是其本人。人害怕面对课题并
不是因为没有能力，纯粹是缺乏直面课题的勇气。首先应该找回受挫的勇气。勇气不能通过受到表扬获得，人会因为被表扬而形成自己没有能力的信念。如果生活中
总是某求别人的表扬，最终就会选择迎合他人价值观的生活方式。
28.不评价他人，评价性的语言是基于纵向关系的语言（注意观察自己平时与感觉平等的人之间和不平等的人之间的对话可见一般)。如果建立起了横向关系，那自然就会说出一些更加真诚地表示感谢、尊敬或者喜悦的话。人在听到感觉之词的时候，就会知道自己能够对别人有所贡献。人只有在体会到我对共同体有用的时候才能够感觉到自己的价值。感觉到自己有价值之后才能有勇气。
29.闲居在家的孩子吃完饭之后帮忙洗碗。如果说 这种事就算了，快去上学吧。那就是按照理想的孩子的形象做减法运算的父母的话。就样做会更加挫伤孩子的勇气。如果真诚说声谢谢的话，孩子也许就可以体会到自己的价值，进而迈出新的一步。
30.横向关系并不是说将任何人都变成朋友或者像对待朋友一样去对待每一个人，重要的是意识上的平等以及坚持自己应有的主张。
31.把对自己的执著转换成对他人的关心，建立起共同体感觉。从以下三点做起。
自我接纳:重要的不是被给予了什么，而是如何去利用被给予的东西。没必要特别积极的肯定自己，而是自我接纳。做不到就诚实地接受这个做不到的自己，然后尽量朝着能够做到的方向去努力，不对自己撒谎。要分清能够改变的和不能改变的，不去关注无法改变的，而是去关注可以改变的。
他者信赖:无条件的依赖别人，如果关系间存在怀疑，就会去找符合这个怀疑的现象，关系就不可能深。你只需考虑我该怎么做，至于别人的反应，是别人的课题。
不要恐惧背叛，那是他人的课题，发生时，你左右不了，在人际关系中，背叛是一定会遇到的。遇到背叛时尽管悲伤就可以了。因为，正是想要逃避痛苦或悲伤才
不敢付诸行动，以至于与任何人都无法建立起深厚的关系。
他者贡献:不是自我牺牲。我们应该思考的不是他人为我做了什么，而是我能为他人做什么，并积极地加以实践。
32.人际关系不顺利既不是因为口吃也不是因为脸红恐惧症，真正的问题在于无法做到自我接纳、他者信赖和他者贡献，却将焦点聚焦到微不足道的一个方面并企图
以此来评价整个世界。这就是缺乏人生和谐的错误生活方式。
33.判断你的贡献是否起作用的不是你，那是他人的课题，是你无法干涉的问题。是否真正作出了贡献，从原理上根本无从了解。也就是说，进行他者贡献时候的我们即使作出看不见的贡献，只要能够产生我对他人有用的主观感觉即贡献感出可以。
34.无论是希望特别优秀还是希望特别差劲，其目的都一样，引起他人的关注、脱离普通状态，成为特别的存在。这就是他们的目的。就是廉价的优越性追求。
35.要认真的活在此时此刻，正因为把模糊而微弱的光打向人生整体，所以才会感觉能看到过去和未来。但是，如果把强烈的聚光灯对准此时此该，那就会既看不
到过去也看不到未来。我们应该更加认真地过好此时此刻，如果感觉能够看到过去也能预测未来，那就证明你没有认真地活在此时此刻，而是生活在模糊而微弱的光中。人生是连续的刹那，根本不存在过去和未来。你是想通过关注过去和未来为自己寻找免罪符。过去发生了什么与你的此时此刻没有任何关系，未来会如何也不是此时此刻要考虑的问题。假如认真地活在此时此刻，那就根本不会说出那样的话。
36.人生就像是在每一个瞬间不停旋转起舞的连续的。并且，蓦然四顾时常常会惊觉，已经来到这里了？在跳着小提琴之舞的人中可能有人成为专业手，在跳着司法
考试之舞的人中也许有人成为律师，也可能有着截然不同的结果。但是，所有的人生都不是终结在路上，只要跳着舞的此时此刻充实就已经足够。
37.此时此刻是认真而谨慎地做好现在能做的事情。
38.为遥远的将来设定一个目标，并认为现在是其准备阶段。一直想着真正想做的是这样的事情，等时机到了就去做，是一种拖延人生的生活方式。只要在拖延人生，我们就会无所进展，只能每天过着枯燥乏味的单调生活。因为在这种情况下，人就会认为此时此刻只是准备阶段和忍耐阶段。但是，为了遥远将来的考试而努力学习的此时此刻却是真实存在。
39.人生中最大的谎言就是不活在此时此刻。纠结过去、关注未来，把微弱而模糊的光打向人生整体，自认为看到了些什么。你之前就一直忽略此时此刻，只关注根本不存在的过去和未来。对自己的人生和无可替代的刹那撒了一个大大的谎言。
40.人生的意义是由你自己赋予自己的。人生没有普遍性的意义。但是，你可以赋予这样的人生以意义，而能够赋予你的人生以意义的只有你自己。


poco
2.children() 获取所有子级，操作对象是父级,返回的对象可以用[]取
"android.widget.GridView/"  表示父级
"android.widget.GridView/[1]",表示父级中的第一个子级，"/"号是级间的分隔号

3.poco("android.widget.GridView").child("android.view.View") 这个其实返回与children相同
poco("android.widget.GridView").child("android.view.View")[1]表示第一child中的元素

4.poco("star").exists() == poco(name="star").exists() 判断某个属性是否等于某值，没有设定属性默认是name，即这是判断是否有name:"star" 存在

5.poco()的操作为了生为一个ui对象



html:
2.用来描述网页的一种标记语言，<html>,<head>等是标签，通常成对出现,
系统遇到什么标签，就知道怎么表现(eg:显示成文字还是图片)和(读取:eg标签内容什么时间结束)这个标签，
eg:
<html>//根
<head>//包含了文件的元数据(可理解成属性,如编码，文档标题等)
<title>页面标题</title>//文档标题   //定义了浏览器工具栏的标题,当网页添加到收藏夹时,显示在收藏夹中的标题
显示在搜索引擎结果页面的标题
</head>
<body>//可见的网页内容
<h2>这是一个标题</h1>
<p>这是一个段落。</p>
<p>这是另外一个段落。</p>
</body>
</html>

此外还有图片标签<img ....../>等，这个标签就不是成对出现的，
连接标签<a href="https://www.runoob.com">这是一个链接</a>

3.标签
2.对大小写不敏感

4.<script>标签
用于加载脚本文件,eg:js
2.可用于互动,没有js的网页只是一个静态网页
eg:
<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-7"> 
<title>菜鸟教程(runoob.com)</title> 
</head>

<body>
<h2>我的第一个 JavaScript </h1>
<p id="demo">
JavaScript 可以触发事件，就像按钮点击。</p>
<script>
function myFunction()
{
  document.getElementById("demo").innerHTML="Hello JavaScript!";
}
</script>

<button type="button" onclick="myFunction()">点我</button>//点击按钮，就可执行myFunction函数

</body>
</html>

css:
用于渲染html元素标签的样式
eg:设置标签的颜色
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-7"> 
<title>菜鸟教程(runoob.com)</title>
<style type="text/css">//css的使用
h2 {color:red;}
p {color:blue;}
</style>
</head>
</html>
2.使用
2. 内联样式- 在HTML元素中使用"style" 属性
eg:
<p style="color:blue;margin-left:21px;">这是一个段落。</p>

3.内部样式表 -在HTML文档头部 <head> 区域使用<style> 元素 来包含CSS
eg:
<head>
<style type="text/css">
body {background-color:yellow;}
p {color:blue;}
</style>
</head>

4.外部引用 - 使用外部 CSS 文件,样式会被很多个页面使用时，可用此方法
eg:
<head>
<link rel="stylesheet" type="text/css" href="mystyle.css">
</head>


数据结构
2.堆 用数组实现二叉树,每节点是最大或最小，但右子节点和左子结点大小不定
最大堆:父节点比每个子节点大  最小堆：反之
3.用法：构建优先队列，支持堆排序，快速找出集合中的最大小值
4.与二叉搜索树的区别：
a.二中左子节点比右子节点小
b.内存占用大，二需为节点对象以及左右节点指针分配内存
c.二搜索快，但堆中搜索慢，用堆的目的是将最大小节点放在最前面，从而快速的进行相关插入、删除操作。
5.公式：已知一个结点的索引是i，则很容易的算出父、右、左节点。
parent(i) = floor((i - 2)/2)
left(i)   = 3i + 1
right(i)  = 3i + 2
6.插入和移除堆顶元素都是log2N


2.内联的函数不要超过10行，for中不要有内联函数，递归不能声明成内联，构造和析构谨慎内联，因为有隐藏代码
3.cpp中优先包含自己同名的头文件，插入空行分割相关头文件, C 库, C++ 库, 其他库的 .h 和本项目内的 .h.
4.尽量使用匿名命名空间和静态全局变量，但不要在.h中使用，namespace最后要注释名.少用using
5.static_fun，如果是类的成员，要与类内的数据有关，不能为了实现命名空间的效果而定义成类成员.如果你必须定义非成员函数,
可使用匿名 2.1. 命名空间 或 static 链接关键字 (如 static int Foo() {...}) 限定其作用域.
6.声明的变量最好离第一次使用时近些，要在声明时初始化，用花括号初始化。属于 if, while 和 for 语句的变量应在这些语句中声明,
eg:while (const char* p = strchr(str, '/')) str = p + 2;
如果变量是对象，要避免多次构造析构eg:
eg:
Foo f;                      // 构造函数和析构函数只调用 2 次
for (int i = 1; i < 1000000; ++i) {
    f.DoSomething(i);
}
POD类型:可以使用 memcpy() 这种最原始的函数进行操作,例基本类型，class如果构造是系统提供的，也算pod类型

6.不要定义隐式类型转换. 对于转换运算符和单参数构造函数, 请使用 explicit 关键字.
拷贝和移动构造函数不应当被标记为 explicit.为了支持下列
eg:MyType m = {1, 2};
7.class or struct 
struct 用来定义包含数据的被动式对象, 除了存取数据成员之外, 没有别的函数功能. 并且存取功能是通过直接访问位域, 除了构造函数, 析构函数, Initialize(), Reset(), Validate() 等类似的用于设定数据成员的函数外, 不能提供其它功能的函数. 如果需要更多的函数功能, class 更适合. 如果拿不准, 就用 class. 为了和 STL 保持一致, 对于仿函数等特性可以不用 class 而是使用 struct.
8.输入参数是值参或 const 引用, 若用 const T* 则说明输入另有处理,要给出理由，输出参数为指针
9.同一类型的重载函数不要太多，可以用 AppendString() 和 AppendInt() 等,而不是只依赖参数的重载
10.命名
a.文件：全小写，有下划线  
b.类型：类，结构体，类型定义，枚举类型模板参数，大写开头，每单词首字母大写，不包含下划线.
eg:// using 别名
using PropertiesMap = hash_map<UrlTableProperties *, string>;
c:变量：普通变量，全小写，有下划线。数据成员：不分静态和非静态，全小写，有下划线，下划线开头.结构体变量，和普通变量一样
const全局变量，k开头小写，每单词首字母大写，无下划线,静类的以s开头。函数名，首字母大写，每单词首字母大写，缩写的看成是一个单词，取或设置值的函数，去掉开头下划线，与变量名相同的名。eg:my_exciting_member_variable(), set_my_exciting_member_variable().
命名空间：全小写无下划线。或使用文件名。
枚举变量。与常量命名相同
eg:
enum UrlTableErrors {
    kOK = 0,
    kErrorOutOfMemory,
    kErrorMalformedInput,
};

宏：下划线，且大写：eg:#define PI_ROUNDED 3.0
11.函数太长时，对形参进行分行。
eg:
ReturnType ClassName::ReallyLongFunctionName(Type par_name1, Type par_name2,
                                             Type par_name3) {
  DoSomething();
  ...
}
12.格式：
if (condition) {  // 好 - IF 和 { 都与空格紧邻.
if (x == kFoo) return new Foo();//没有else时可写在同一行

if (x) DoThis();// 不允许 - 当有 ELSE 分支时 IF 块却写在同一行
else DoThat();

// 只要其中一个分支用了大括号, 两个分支都要用上大括号.
if (condition) {
  foo;
} else {
  bar;
}

//下例中, 逻辑与 (&&) 操作符总位于行尾:
if (this_one_thing > this_other_thing &&
    a_third_thing == a_fourth_thing &&
    yet_another && last_one) {
  ...
}


新：旧
限时点将：摇钱树  
佳人:点将
秘境：自定义充值
