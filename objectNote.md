## js
#### npm
1. npm install会先检查node_modules目录中是否存在指定模块，如果存在就不安装，即便远程有新版本。如果.npm中有压缩包，但没有安装到node_modules中，也会
重新下载
2. 发出npm install命令,npm 向registry服务查询模块压缩包的网址,下载压缩包，存放在~/.npm目录解压压缩包到当前项目的node_modules目录
3. tsconfig.json  该文件存在的地方就是根目录
可通过include和files指定编译的文件。如果rootDir打开了，则files指定的文件要在rootDir指定的目录中，exclude要打开，不打开会
默认忽略./
4. npm install --production(生产模块)  不安装devdependencies中的模块,安装模块时，--dev表示添加到devdependencies中，即这个模块是开发时需要的，生产时不需要.全局安装的模块或是不加参数的npm install的模块，在 npm install初始化项目时，不会下载模块.

#### 函数
1.因为js中的函数可以有属性和方法,所以即是函数也是对象。ts中的类，最终会解析成函数。箭头函数没有this，不适合定义对象方法。
ts类解析成js
```
class Greeter {
    greeting: string;
    constructor(message: string) {
        this.greeting = message;
    }
    greet() {
        return "Hello, " + this.greeting;
    }
}

var Greeter = (function () {//执行一个匿名函数
    function Greeter(message) {//定义与ts类同名的函数，相当于构造函数
        this.greeting = message;
    }
    //成员函数，即上式函数中加入变量，变量初始化成函数
    Greeter.prototype.greet = function () {
        return "Hello, " + this.greeting;
    };
    return Greeter;//返回与类同名的函数
}());
```

#### promise
1.能方便的实现链式操作,传入的promise是第一个函数，之后的then传入的函数可理解为回调执行，promise的模式保证了顺序的执行。即第一个then是在传入promise的函数执行后再执行，之后的then都是上一个then传入的回调函数执行完后再执行
2.是一个构造函数，new promise(fun(resolve, reject)),new之后，会立即执行传入的函数，resolve,和reject的执行时机是我们传入的函数决定的。
3.resolve和reject主要是改变promise的状态函数返回的value会组then使用。
4.then方法会创建一个新的promise,并返回，并根据上一个promise的状态，决定是将then传入的回调方法(回调方法会用到上一个promise返回的value)存入立即执行队列还是订阅队队列。立即执行队列并不是立即执行，而是之后没有接着then才会去执行。不论是异步和同步，都保证了then是顺序执行的。
5.参考<https://juejin.cn/post/6844904144382197774/>

#### async/await
1.async 一个封装好的 Promise 对象，调用时得到一个 Promise 对象,遇到await时，会阻塞
2.如果一个函数声明定义时加了async，调用时，如果需要async的函数执行完后。再执行下面的代码，则调用前要加await 

#### || && 用于对象
1.【a || b】：a存在返回a，a不存在返回b  
2.【a && b】：a存在返回b，a不存在返回a

#### Getter 和 Setter
1.允许属性和方法的语法相同
```
var person = {
  curTime: 1,
  get time(){
    return this.curTime;
  }
  set time(tm){
    this.curTime = tm;
  }
}
var tm = person.time;  person.time = 1;
```

#### try finally
1.try是否捕捉到错误，finally后的代码都会执行

#### any
1.js是结构性语言，又因为会增加字段，所以结构确定不了，所以函数参数用any??
any[],数组中的数据是any?

#### map set 
1. 一个 Object 的键只能是字符串或者 Symbols，但一个 Map 的键可以是任意值。
2. Map的键值对个数可以从 size 属性获取，而 Object 的键值对个数只能手动计算.
3. set 可存不同类型

#### 任务
##### zhanche
1. 配置上放了init update complect函数，调用时传入玩家ptr和参数
2. 每创建一个新任务就调用init初始化任务记录。
   eg:某任务条件是3次，r初始是1，完成次数是 3 * r,第二次完成时，条件是3 * (r + 1)
3. 初始和更新是不同的函数(且不同的任务，实现都不同)，只设置奖励是否已领标记，三个函数都设置到配置中

##### luanshi
1. 任务配置：只是checkptr函数是取一样的，其它的配置信息不一样，所以封装成一个类.
```
struct TaskCfg {
        TaskCfg(const Json::Value& js)
            :_id(0), _openLv(0), _blv(0), _star(0),
            _findCost(0), _history(0),
            _reward(Json::arrayValue), _checkPtr(nullptr) {
            _id = js["id"].asInt();
            _star = js["star"].asUInt();
            _findCost = js["findCost"].asUInt();
            _openLv = js["limitLv"].asInt();
            _reward = js["reward"];
            _history = js["history"].asUInt();
            _checkPtr = gg::Task::Checker::create(js["condition"]);
        }
```
5.记录：取checkptr的逻辑不一样，其它都一样，所以是继承class record后，自实现自己的record,又因为record都不一样，所以record_mgr是模板，又因为方法很多，又封闭成一个类.
```
class StrongTaskRec
    : public Task::Record {
public:
    StrongTaskRec(const mongo::BSONElement& obj)
        :Task::Record(obj) {}

    StrongTaskRec(int id, const Task::CheckPtr& ptr, playerDataPtr p)
        :Task::Record(id, ptr, p) {}
private:
    bool getCheckPtr() const override {
        if (!_check_ptr) {
            auto ptr = strong::TaskCfgMgr::shared().getTaskPtr(_id);
            if (!ptr)return false;
            ptr->checkPtr(_check_ptr);
            if (!_check_ptr)return false;
        }
        return true;
    }
};
```
#### 字面量
在计算机科学中，字面量是用于表达源代码中一个固定值的表示法.(暂理解成临时变量)
```
std::string x = "hello"; "hello"就是字符串字面量
let x = {color: "blue", len: 2}; 右边的{...}就是对象字面量
```

#### 接口(implements是实现，extends是继承)
1. 对参数进行约束
```
interface LabelledValue {
  label: string;
}
function printLabel(labelledObj: LabelledValue) {
  console.log(labelledObj.label);
}

let myObj = {size: 10, label: "Size 10 Object"};
printLabel(myObj);//如果传入的是对象字面量，需要属性不能多也不能少
```
2. 对函数类型约束
```

interface SearchFunc {
  (source: string, subString: string): boolean;
}

let mySearch: SearchFunc;
mySearch = function(source: string, subString: string) {
  let result = source.search(subString);
  return result > -1;
}
=右边的函数参数名不需要与接口的一样
```
3. 对可索引类型进行约束
```
interface StringArray {
  [index: number]: string;//索引签名
}

let myArray: StringArray;
myArray = ["Bob", "Fred"];
或
myArray = { 1:"Bob", 2:"Fred" }

interface NumberDictionary {
  [index: string]: number;
  length: number;    // 可以，length是number类型
}//表示这个接口中有索引签名，且有一个属性length,值是number类型

只读索引签名
interface ReadonlyStringArray {
    readonly [index: number]: string;
}
let myArray: ReadonlyStringArray = ["Alice", "Bob"];
myArray[2] = "Mallory"; // error!
```
4. 类 类型接口（对类的属性和方法进行约束)
类实现接口，并不是类继承接口
```
interface Anmal {
    //对类里面的属性和方法进行约束
    name : string
    eat (food:string) : void
}
//类实现接口要用implements , 子类必须实现接口里面声明的属性和方法
class Laoshu implements Anmal{
    name : string
    constructor (name : string) {
        this.name = name
    }
    eat(food:string):void {
        console.log(`${this.name}吃${food}`)
    }
```
5. 接口继承
接口可互相继承(注意：不是类与接口间的继承)
一个接口可以继承多个接口，创建出多个接口的合成接口。
```
interface Shape {
    color: string;
}
interface PenStroke {
    penWidth: number;
}
interface Square extends Shape, PenStroke {
    sideLength: number;
}

let square = <Square>{};//(使用时有个<>)
square.color = "blue";
square.sideLength = 10;
square.penWidth = 5.0;
```

6. 混合类型
```
interface Counter {
    (start: number): string;
    interval: number;
    reset(): void;
}

function getCounter(): Counter {
    let counter = <Counter>function (start: number) { };//使用时有个<>，函数直接赋值给接口变量,因为接口中并没有函数对象的属性名
    counter.interval = 123;
    counter.reset = function () { };
    return counter;
}

let c = getCounter();
c(10);
c.reset();
c.interval = 5.0;
```

#### Math
1. Math.ceil()向上舍入为最接近的整数；
2. Math.floor()向下舍入为最接近的整数；
3. Math.round()四舍五入为最接近的整数;

#### 类型断言(它没有运行时的影响，只是在编译阶段起作用)
1. 尖括号 语法
```
let someValue: any = "this is a string";
let strLength: number = (<string>someValue).length;
```
2. as 语法
```
let someValue: any = "this is a string";
let strLength: number = (someValue as string).length;
```

#### node.js
1. Node.js 就是运行在服务端的 JavaScript。
2. node *.js，执行js文件，tsc *.ts  将ts编译成js文件
3. tsconfig.json文件中指定了用来编译这个项目的根文件(本身在的目录就是根目录)和编译选项。
4. package.json.安装包时的记录
5. inspect 以调试模式启动项目，inspect会监听一个端口，去连接这个端口，就可看到项目的环境 
6. process 对象是一个 global （全局变量），提供有关信息，控制当前 Node.js 进程。作为一个对象，
它对于 Node.js 应用程序始终是可用的，故无需使用 require()。

#### 杂(zha)
1. 
```
private add_memory<T extends item>(ni: T): void {//--约束T的类型为item类型或继承至item的类型

```
2. 
如果 person 是一个对象，下面的语句不会创建 person 的副本：
var x = person;  //x是person的引用
x 和 person 是同一个对象。
对 x 的任何改变都将改变 person，因为 x 和 person 是相同的对象。
3. 元组可存不同类型
4. === 运算符需要类型和值同时相等
!== 值不相等或类型不相同
在TS中，因为有了类型声明，不同类型间比较时会有报错：
This condition will always return 'false' since the types '5' and '"5"' have no overlap.
所以比较时,可用===，在编译时就判断了类型是否相同
4. 要返回undefine时，用void num，一般void 0, 不能直接返回undefine,因为undefine可以是变量，可被改写
5. 已声明未初始化的值要直接访问的话，类型需要定义为undefined.
6. < T extend x> 约束T的类型为x类型或继承至x类型

#### any
1. any:没有声明其类型，也没有初始化.
```
变量的值会动态变动。
let x: any = 2;    // 数字类型
x = 'I am who I am';    // 字符串类型
x = false;    // 布尔类型

定义存储各种类型的数组。
let arrayList: any[] = [2, false, 'fine'];
arrayList[2] = 100;
```

## EventEmitter (事件触发和事件监听功能封装)
1. Node.js 所有的异步 I/O 操作在完成时都会发送一个事件到事件队列。异步操作逻辑后，都有event.emit('some_event'); ?

#### ts与c++
1. 要传结构体式的数据时，ts是传对象的结构(eg:{x:xx, y:yy})
2. x: Map<string, Function> = new Map();
以c的角度是 Map<string, Function> x = new Map();

##### websocket(一种网络通信协议)
连接允许客户端和服务器之间进行全双工通信，以便任一方都可以通过建立的连接将数据推送到另一端。WebSocket 只需要建立一次连接，就可以一直保持连接状态。比轮询方式的不停建立连接效率更高.

### zhanche
#### io
1. gate启动时，在main中创建gate_server,设置监听标识connect，有gac连接后，会得到一个io，也设置这个io的监听标识
3. 奖励
```
ResourceAlloc.reslove(pid, rw, iorw);
找处理函数，目前就bag,man,car
```

## vscode
#### task.json
类似于写好一个脚本，需要的时候就调用执行
#### launch.json
启动调试时，vs从里面找要执行文件的信息，写好launch后，不论选中什么文件，都按照launch的规则执行
launch是启动程序并进行调试；
attach是调试某个已启动的线程；

#### python
### 变量
1. 变量是没有类型的，类型属于对象,变量是对类型的引用(引用即是对指针的封装，给一个指针于类型，就能寻址到变量的正确范围),所以python中变量可能是不同类型的引用。
```
eg1:
a = [2, 2, 3]
a = "Rank"
[2,2,3]和"Runoob" 是对象，[1,2,3] 是 List 类型，"Runoob" 是 String 类型，变量 a 是没有类型，她仅仅是一个对象的引用

eg2:
a = b = c = 20;三个变量都是对20的引用，所以分配到同一块内在空间
```
2. strings, tuples（元组）, 和 numbers 是不可更改的对象，而 list,dict 等则是可以修改的对象。在传参时，不可变类型是传值，可变类型是传引用
```
eg:
a = "abc"
def modify(a)：
    a = "cc"
print(a)
modify(a)
print(a)
//以上结果都为"abc"
b = [1, 2]
def modify(b):
    b[0] = 0
print(b)
modify(b)
print(b)
//结果为：[1, 2] 和 [0, 2]
```
3. 字典的键必须是不可变的，所以可用数字，字符串，元组充当，列表不行。

### pass
是空语句，为了保持程序结构的完整性。如果定义一个空函数程序会报错，当你没有想好函数的内容是可以用 pass 填充

### lambda
1. 函数实现是一个表达试，不是语句块,只有一行 
```
lambda arg1, arg2, ...：expression
sum = lambda arg2, arg2: arg1 + arg2;
print "相加后的值为 : ", sum( 11, 20 )
```
2. 绑定函数时，如果类型不符合，可绑定一个lambda，lambda内部调用目标函数

### 导入导出
1. export 导出，import 引入
2. import 导入整个文件。
3. 只引用部分 from...import..
4. import .. as.. 导入后重命名

### python zha
1. os.listdir()返回值不能保存

#### GDB
1. -g,主编译器将符号表（对应程序的变量和代码行的内存地址列表)保存在生成的可执行文件中，这样才能在调试过程中引用源代码中的变量名和行号,-o必须写在后面.
2. gdb实际上是使用机器语言指针工作。不能简单的理解为是一行一行的执行代码。例：声明i确实会生成机器码，但是gdb发现这种代码对调用目的来
说没有用处，所以在这行设置断点不会停。被优化后的代码也会出来断点的位置不是我们想要的的结果.

### jump(j)
* 跳到某行，中间的不执行，可用于跳过判断，如果之后的代码用到的变量是之前跳过的，会报错

### step 进入函数
没有进函数的原因是gdb不会在不具有调用信息的代码内停止
```
printf()
```
### finish
恢复gdb运行，直到恰好在函数返回之后为止.

### until
1. 执行完循环直到跳出循环的第一行代码处暂停。
2. 如果执行until导致回跳到循环顶部，再执行until就可离开当前循环。
3. 执行到某行或某函数入口.
4. 想设临时断点时可用
```
until 13, until bed.c:12, until swap, until bed.c:swap
```

### 程序运行参数。
set args=x 可指定运行时参数。
show args 命令可以查看设置好的运行参数。

### break
1. tbreak 临时断点
2. 条件断点
```
condition 2 num_y==2  //断点已存在时设置条件，不加if
break 20 if num_y==2  新创建的断点
condition 2 //删除断点条件
break test.c:myfunc if !check_sanity(i) //条件中调用函数
```
3. commands
```
//简单模式
commands 2  给断点1设命令列表
silent  加这个是为了打印简洁
printf "main was pass %d.\n", n    printf 就相当于平时用的，只是去掉了括号
continut   加这个相当于按了c键
end   每个命令需以end的结束

//if 的使用
  commands 2 //if的使用同c，printf只是去掉括号，可用gdb的print
  p tmp->val
  if(tmp->left != 1)
  p tmp->ledf->val
  else
  printf "%s\n" "none"
  end
  if(tmp->right != 1)
  p tmp->right->val
  else
  printf "%s\n", "none"
  end
 end

 //调用其它函数
 commands 1
 printf "xxxxx"
 call printftree(root) 
 end

 //取消 commands
 commands 2  .... end
```
4. delete 3 3 4(删除2，3，4位置的断点)
delete：删除断点、监视点和捕获点
禁用断点：disable 数字列表
启用断点：enable 数字列表

5. 在函数入口处设置断点
若有函数 void main(); 设置断点 break main
存在重载函数或同名静态函数：break bed.c:main

### watch
1. 监视点：即是断点，也可打印变量值，用于监视某个变量什么时候发生变化，在哪变化。watch z , watch (z > 29). 对全局变量和函数之间连续传递的局部变量来说特别有用。
2. 使用watch时步骤如下：
1. 使用break在要观察的变量所在处设置断点：
2. 使用run执行，直到断点；
3. 使用watch设置观察点；
4. 使用continue观察设置的观察点是否有变化。

### 调用脚本调试
```
//gdb attach 124 -x 脚本(脚本后缀无所谓)
//下列为文件内容
b escort_system.cpp.h:112  if m._pid == 57671899
commands 2
p m._pid  //p 可以直接打印变量，prinf是像c一样使用 eg:printf "%s\n" "none"
c
end
c
```
### 栈帧
1. frame 当前栈帧，up, down切换，backtrace显示当前存在的所有帧集合bt=backtrace
2. info locals:当前栈帧中的所有局部变量的值列表
3. info args:显示当前函数的传入参数

### continue
```
continue 3 //忽略接下来的3个断点
```

### print/display
```
//打印结构体
p *tmp

//打印数组
int a[26];
p *a@25  

//打印给定类型的指针
p (int[25])*a 
p *((playerItem*)0x7fad322ccab0)

//有作用域
p *node::root //和.cpp函数的实现一样，类型开头，作用域符::
```

* display x时，每次停下就会打印x的值

### ptype
1. 查看类型

### set
```
//设置变量的值
set x = 13  
//设置数组的值
若有int arr[6],则可set arr={1,1,2,2}
//设置新变量接收值
set $q = p 必须加$,$q称为方便变量）
//遍历数组
set $i=1, p w[$i++]
//不限制打印字符串的长度 
set print element 0   
```
### log
```
set logging file <filename> //设定logging output 的文件
set logging on //打开记录功能
set logging off //关闭记录功能
没有指明文件，会自动生成gdb.txt
```
#### gdb zha
1. 很多调用动作需先执行到断点位置才能设置，因为在进行这个位置的函数之前，函数内的变量还不存在
2. new thread xxx (lwp xxx) ：gdb提示有线程创建
3. ni 和si 是执行机器语句，一个函数可能解析成多个机器语句。
4. disas看反汇编， i r 看寄存器
5. g++ -e xx.cpp -o xx.i   预处理
6. 打印所有线程堆栈:thread apply all bt,用f编号跳入指定的堆栈 
7. return 不执行断点以下的代码，并返回
8. call function() 如果该函数返回值为void，则调用后不会有内容

#### mongo
* mongo::BSONObj，BSON对象的表示  
* mongo::BSONElement，BSON对象中元素的表示方法   
* mongo::BSONObjBuilder,构建BSON对象的类  //封装了很多处理bsonobj的方法
* mongo::BSONObjIterator，BSON对象迭代器  
* #define BSON_ARRAY(x) ((::mongo::BSONArrayBuilder() << x).arr())
* #define BSON(x) ((::mongo::BSONObjBuilder(64) << x).obj())
* addFields 操作对象是空的bsonObj

### insert
```
eg:命令操作
>db.col.insert({title: 'mongodb 教程', 
    description: 'mongodb 是一个 nosql 数据库',
    by: '菜鸟教程',
    url: 'http://www.runoob.com',
    tags: ['mongodb', 'database', 'nosql'],
    likes: 101
})

eg:代码实现
objCollection insert_objs;
insert_objs.push_back(BSON("pi" << player_it.first << "id" << card_it.first << "star" << 0 << "poke" << 0));
thread_shared::GetLocalMongo().InsertMongo(
    DBN::dbPlayerCard, insert_objs);
```
### find
```
eg:
db.tk.player_collection.find({pi:57671698},{"babelfm":1}).pretty()

eg: and 
db.col.find({key2:value1, key2:value2}).pretty() // 多个key以逗号隔开

eg: or 
db.col.find({$or:[{key2:value1}, {key2:value2}]}).pretty() //多个key用[]括起

eg:and or 联用
db.col.find({"likes": {$gt:51}, $or: [{"by": "菜鸟教程"},{"title": "mongodb 教程"}]}).pretty()

eg:模糊查询
db.col.find({title:/教/}) // 查询 title 包含"教"字的文档：
db.col.find({title:/^教/}) // 查询 title 字段以"教"字开头的文档：
db.col.find({title:/教$/}) // 查询 titl e字段以"教"字结尾的文档：

eg:以类型进行查询
db.col.find({"title" : {$type : 'string'}})

eg:limit/skip
>db.collection_name.find().limit(number)    // 只显示前number条记录
>db.collection_name.find().limit(y).skip(x)  //先跳过x条记录，再显示前y条记录

eg:sort 2升序排列，-1降序排列。
>db.collection_name.find().sort({key:2})

执行顺序: sort > skip > limit
```
### 比较符
{<key>:<value>} 模式
```
db.col.find({"by":"菜鸟教程"}).pretty()   
db.col.find({"likes":{$lt:51}}).pretty()
db.col.find({"likes":{$lte:51}}).pretty()  //小于或等于
db.col.find({"likes":{$gt:51}}).pretty()
db.col.find({"likes":{$gte:51}}).pretty() 
db.col.find({"likes":{$ne:51}}).pretty() //不等于
```

### update
* 不存在会插入新数据，加mulit表示更新全部
* 数字时要加类型限制
```
eg:
db.tk.player_collection.update({"reset2.mct":{$exists:true}},{$set:{"reset1.mct":NumberInt(0)}},{multi:true})

eg: $unset,删除表中某字段
update({"userid":10},{"$unset":{"allyreq":true}})
```

### query
```
* 返回的是数组
eg:
mongo::query find_query(bson("biz.sm" << bson("$gt" << 1)));
find_query.sort(bson("biz.sm" << 0 << "biz.smct" << 1 << strplayerid << 1));
mongo::bsonobj find_val = bson(strplayerid << 1);
objcollection objs = thread_shared::getlocalmongo().query(
    dbn::dbplayercollection, 
    find_query, 
    101,
    &find_val
    );
```
### 对数组进行操作
1. $addToSet 添加元素到数组中,数组已存在该值，将不会加入
```
eg: 添加值
调用save, { $addToSet: { tags: "camera"  } } //向tags数组只加"camera"

eg: 添加多个值
{ $addToSet: { tags: { $each: [ "camera", "electronics", "accessories" ] } } }

//eg: 判断数组非空
auto key = BSON("Array.opens.0" << BSON("$exists" << true))

eg:代码
thread_shared::GetLocalMongo().SaveMongo(DBN::dbPlayerEmail,
    BSON(strPlayerID << player_it.first),
    BSON("$set" << BSON("oid" << oid) << "$addToSet" <<
    BSON("pkg" << BSON("k" << 1 << "v" << email_ptr->toJson().toIndentString()))) //往数组pkg中加对象
```

#### 算法
### 位运算
* n&(n-1)可实现去除n中最右边的1(因为一定会用到n最右边的1，且其它位的1一定用不到)
* n&(-n)得n最右边的1.(-n为n取反加1)

1. 找出数组中缺失的那个数 (将数组模拟成里面都是两两相同的元素)
```
Input: [3,0,1]
Output: 2

public int missingNumber(int[] nums) {
    int ret = 0;
    for (int i = 0; i < nums.length; i++) {
        ret = ret ^ i ^ nums[i];//好比是一个数组中有一个数不重复，只需将所有数进行异或运算.
    }
    return ret ^ nums.length;//不可能是最后一个数，所以还要与数组长度进行异或
} 
```
2. 数组中不重复的两个元素(试图分成两个数组，不同的数分别在不同的数组，数组其它数都是两两相同)
两个不相等的元素在位级表示上必定会有一位存在不同。
设x = (diff &= -diff) 得到出 diff 最右侧不为 0 的位，也就是不存在重复的两个元素在位级表示上最右侧不同的那一位. 两个不同的元素与x进行&操作，一定有一个结果全为0，一个这位为1

public int[] singleNumber(int[] nums) {
    int diff = 0;
    for (int num : nums) diff ^= num;
    diff &= -diff;  // 得到最右一位
    int[] ret = new int[2];
    for (int num : nums) {
        if ((num & diff) == 0) ret[0] ^= num;//好比是第一个数组
        else ret[1] ^= num;//第二个数组
    }
    return ret;
}

3. 统计从 0 ~ n 每个数的二进制表示中 1 的个数
```
i&(i-1)会把i中最右边的1去掉，所以i去掉1后，肯定是一个小于i的数，而所有小于i的数的1个数，之前已算出结果，所以可找到之前算出的结果加1。可看成是动态规则
void oneNum(int num) {
    std::vector<int> n;
    n.assign(num + 1, 0);
    for(auto i = 1; i <= num; ++i) {
        n[i] = n[i&(i-1)] + 1;
    }
    cout << n.back() << endl;
}
```
### 位运算表示状态
* 利用一个bit位表示一个状态，如果是int类型，就有32个bit，所以可以表示32个状态
```
enum EPLAYER_STATE
{
    EPST_NONE    = 0x00000000,     // 没有状态
    EPST_ADDHP  = 0x00000001 ,    // 加血
    EPST_ADDMP  = 0x00000002,     // 加蓝
};
unsigned state = EPST_NONE;
state |= EPST_ADDHP // 设成加血态，其它位不变，只是那一位变成1
state |= (EPST_ADDHP | EPST_ADDMP)

if(state & EPST_ADDHP) // 判断某位是否为1，将其它位置成0，同时判断那一位是否为1,结果非0，表示一定有一个bit是1

state &= ~(EPST_ADDHP | EPST_ADDMP) //清除状态，将某位置0，其它位不变

//2021-5-31
```
#### 链表
### 找出交点
* 同时遍历两条链表，遍历到尾后，再交换从头遍历
```
A:a1 → a2
            ↘
                c1 → c2 → c3
            ↗
B:b1 → b2
```
只是单向链表，只能从头开始遍历
因为：
a2 a2 c1 c2 c3 b1 b2 b3 c1 c2 c3
b1 b2 b3 c1 c2 c3 a1 a2 c1 c2 c3
所以：按照以上顺序开始同时遍历，就能找到
### 判断是否有交点
由上可知:只需比较最后一个结点是否相同

### 链表反转
头插法：取旧链表的头,剩下的是下个旧链表，取出的头插入新链表第二位，
```
public ListNode reverseList(ListNode head) {
    ListNode newHead = new ListNode(-1);
    while (head != null) {
        ListNode next = head.next;//新头取出。临时保存下个旧链表的索引(头)
        head.next = newHead.next;//插入新链表第二位
        newHead.next = head;
        head = next;//
    }
    return newHead.next;//新链表的头是第二位
}
```
递归法:
```
1 2 2 
3 4 5 
从后往前，每次取出一个接在后，1要怎么接2后，先保存2，2和3交换完后，再将1接在2 后
public ListNode reverseList(ListNode head) {
    if (head == null || head.next == null) {
        return head;
    }
    ListNode next = head.next;//经过reverseList后，head.next变了，所以要先保存next
    ListNode newHead = reverseList(next);
    next.next = head;
    head.next = null;
    return newHead;
}
```
### 归并两个递增链表
每次取头进行比较，如果大小,较少者的next就是接下个比较的小的，每次比较都是取较小的next与另一个链表进行比较
```
public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
    if (l1 == null) return l2; //递归终点
    if (l2 == null) return l1;
    if (l1.val < l2.val) {
        l1.next = mergeTwoLists(l1.next, l2); //小的就取下个next进行比较，小的的next等于下个小的
        return l1;
    } else {
        l2.next = mergeTwoLists(l1, l2.next);
        return l2;
    }
}
```
### 从有序链表中删除重复节点
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
好比全部打断，从尾开始比较大小重新连接
public ListNode deleteDuplicates(ListNode head) {
    if (head == null || head.next == null) return head;
    head.next = deleteDuplicates(head.next);自己的下一个是上一次比较的返回结果
    return head.val == head.next.val ? head.next : head;
}

### 判断链表回文
1. 找到中点，注意倚偶的中点,倚时分割的链表大小不一也可以判断回文
2. 分割成两个链表
3. 反转其中一个链表
4. 比较每个元素

#### 分割链表，分成k段，排在前面的要大于等于后面的长度
* 设置每次的分割长度。分割时找到每段的尾，实尾与后面的断开。
```
public ListNode[] splitListToParts(ListNode root, int k) {
    int N = 0;
    ListNode cur = root;
    while (cur != null) {
        N++;
        cur = cur.next;
    }
    int mod = N % k;
    int size = N / k;
    ListNode[] ret = new ListNode[k];
    cur = root;
    for (int i = 0; cur != null && i < k; i++) {
        ret[i] = cur; //数据中只需保存链表头
        int curSize = size + (mod-- > 0 ? 1 : 0);
        for (int j = 0; j < curSize - 1; j++) {
            cur = cur.next;//找到这一组的最后一个
        }
        ListNode next = cur.next;//将最后一个与组分割
        cur.next = null;
        cur = next;
    }
    return ret;
}
```
### 链表元素按奇偶聚集
* 创建头，因为偶之后要链在奇末尾，所以要先保存偶头。
* 先操作奇，所以要先判断偶的头和next是否存在
```

public ListNode oddEvenList(ListNode head) {
    if (head == null) {
        return head;
    }
    ListNode odd = head, even = head.next(//分别创建奇偶的头), evenHead = even(保存偶的头，最后要连);
    while (even != null && even.next != null) {//同时操作while中的逻辑时，偶会先遇到null
        odd.next = odd.next.next;
        odd = odd.next;
        even.next = even.next.next;
        even = even.next;
    }
    odd.next = evenHead;
    return head;
}
```


### 堆或栈上建立对象
* 栈上的对象是直接调用构造函数，同时会检查析构函数是否可用，禁用时可private析构函数
```
class A
{
protected: //不能直接调用构造和析构，所以不能在栈上创建
    A(){}
    ~A(){}
public:
    static A* create()//要在堆上建需要调用这两个函数
    {
        return new A();
    }
    void destory()
    {
        delete this;
    }
};
```
* 堆上的对象是先new，再调用构造函数，禁用可私有重载new和delete
```
class A
{
private:
    void* operator new(size_t t){}     // 注意函数的第一个参数和返回值都是固定的
    void operator delete(void* ptr){} // 重载了new就需要重载delete
public:
    A(){}
    ~A(){}
```
#### 贪心思想
* 贪心算法总是作出在当前看来最好的选择，也就是说贪心算法并不从整体最优考虑，作出的选择只是在某种意义上的局部最优选择。
* 是否能理解成先算好算的？
* eg1:找钱，先找最大，剩下的就好找。eg2:找一组数中的最大值，每次保存当前找过的数的最大值。eg3:子数组最大和，每次组成一个数组求和与当前最大进行比较
## 需要移除最少多少组构成不重叠
总-不重叠数=移除数(不好理解可看成重叠是一种类型，有多少种类型就表示可组成不重叠的最多多少组,要移除的越少，表示类型越多，先找到的类型占的区间越少,后边的才有更多位置,更有可能组成不同类型，所以右边界递增排序，用较小的区间做比较物)

```
eg1:
Input: [ [1,2], [1,2], [1,2] ]
Output: 2
eg2:
Input: [ [1,2], [2,3] ]
Output: 0

public int eraseOverlapIntervals(int[][] intervals) {
    if (intervals.length == 0) {
        return 0;
    }
    Arrays.sort(intervals, Comparator.comparingInt(o -> o[1])); //以右边界递增排序
    int cnt = 1;
    int end = intervals[0][1];
    for (int i = 1; i < intervals.length; i++) {
        if (intervals[i][0] < end) {//由eg2可知相等时不算重叠
            continue;
        }
        end = intervals[i][1];
        cnt++;
    }
    return intervals.length - cnt;
}
```
###  一次买卖股票最大的收益
* 观察图表，找解题方法
* 找出落差最大的区间，观察一波趋势可知，趋势中的每个上升小区间的低点是最先出现的点，且一定比后面的点小
```
2 4 6
输入: [7,1,5,3,6,4]
输出: 5
遍历全部，遇到小时设置最少，偶到大时算差
public int maxProfit(int[] prices) {
    int n = prices.length;
    if (n == 0) return 0;
    int soFarMin = prices[0];
    int max = 0;
    for (int i = 1; i < n; i++) {
        if (soFarMin > prices[i])
            soFarMin = prices[i];
        else
            max = Math.max(max, prices[i] - soFarMin);
    }
    return max;
}
```
### 买卖股票的最大收益II
* 在一波趋势中交易每一个上升区间，会个上升区间又可分成n个区间，这些区间都是前一点小于后一点
* 对于 [a, b, c, d]，如果有 a <= b <= c <= d ，那么最大收益为 d - a。而 d - a = (d - c) + (c - b) + (b - a) 
```
public int maxProfit(int[] prices) {
    int profit = 0;
    for (int i = 1; i < prices.length; i++) {
        if (prices[i] > prices[i - 1]) {
            profit += (prices[i] - prices[i - 1]);
        }
    }
    return profit;
}
```
### 子数组最大的和
* 主要是区分取一个数，是加入上个数组中，还是成为新的数组头。
* 若curMax + x[i] <= x[i], 再加下一位，curMax + x[i+1]不可能超过x[i] + x[i+1],还不如从x[i]当新头开始算
```
[-2,1,-3,4,-1,2,1,-5,4],
out:[4,-1,2,1]

public int maxSubArray(int[] nums) {
    if (nums == null || nums.length == 0) {
        return 0;
    }
    int preSum = nums[0];
    int maxSum = preSum;
    for (int i = 1; i < nums.length; i++) {
        preSum = preSum + nums[i] > nums[i] ? preSum + nums[i] : nums[i];
        maxSum = Math.max(maxSum, preSum);
    }
    return maxSum;
}
```
### 递归
1. 明确函数要做什么
2. 寻找递归结束条件(递归函数中什么时候不再调用递归函数)
3. 找出函数的等价关系,不断的缩小参数范围
4. 递归函数中什么时候调用递归函数

#### 二分查找
* 比较目标数存在的区域，找到方法不断的缩小区间的范围
* 死循环问题
```
int m = l + (h - l) / 2;
上式可能出现 l == m
在接下的设边界中，不要出现l = m,如果出现，改成int m = r - (h - l) / 2;
```
### 在有重复数中找左边界
* 右边界与目标相等时要不断移，左边只有小于目标时才移。求右边界反之
* 找到后不要退出，继续找，可假设极端的例子进行设想，比如全是0，找最左边的0，所以右边要不断的移，(主要是要根据找的是右边还是左边来判断先设哪个边界),最后是h=l,试验循环的最后两次，就知道如果while(l <= h)时会无法退出(可最后在判断是什么条件结束循环)，
```
public int binarySearch(int[] nums, int key) {
    int l = 0, h = nums.length;
    while (l < h) {
        int m = l + (h - l) / 2;
        if (nums[m] >= key) {
            h = m;
        } else {
            l = m + 1;
        }
    }
}
```
### 大于给定元素的最小元素
* 如果是要比较全部的找一个数据，就一直找到指向同一个。然后比较结果
* 左边移动的条件是<=，右边移动的条件是大于，且需要先判断右边
```
int find(int x[], int y, int length) {
    auto l = 0, r = length - 1;
    while(l < r) {
        auto mid = l + (r - l) / 2;
        if(x[mid] > y)
            r = mid;
        else
            l = mid + 1;
    }
    return x[l] > y ? l : -1;
}
```
### 一个有序数组只有一个数不出现两次，找出这个数
* mid本来要处理奇偶，把mid变成偶，就只需处理一种情况，剩下的区间内只要包括目标数，最后就一定能找的到
* 左边移条件:偶奇位相同，右边移条件:偶奇位不同
```
public int singleNonDuplicate(int[] nums) {
    int l = 0, h = nums.length - 1;
    while (l < h) {
        int m = l + (h - l) / 2;
        if (m % 2 == 1) {
            m--;   // 保证 l/h/m 都在偶数位，使得查找区间大小一直都是奇数
        }
        if (nums[m] == nums[m + 1]) {
            l = m + 2;
        } else {
            h = m;
        }
    }
    return nums[l];
}
```
#### 广度优先搜索
* 同步搜索所有可能，看哪种可能性最先达到目的
* 是一层一层地进行遍历，每层遍历都是以上一层遍历的结果作为起点，遍历一个距离能访问到的所有节点。需要注意的是，遍历过的节点不能再次被遍历。
* 相当于，每遇到分叉时，分身出多个人同时走遇到的叉路。也就相当于很多人，同时走所有可以走的路线。看谁先到终点。

### 组成整数的平方数的最少数量
* 整数不断的减去一个平方数，直到为0，所有可能性同时找，

#### 深度优先搜索
* 深度优先搜索在得到一个新节点时立即对新节点进行遍历,同一时间只会判断一种可能性
* 递归的判断某一可能性

### 即能流到太平洋，又能流到大西洋的点
* 通过已知在太平洋的点，反向搜索源头，经过的点都是可流到太平洋的.大西洋也一样，最后比较重叠点
```
  Pacific ~   ~   ~   ~   ~
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic
```
#### 搜索
### 计算在网格中从原点到特定点的最短路径长度
* 在程序实现 BFS 时需要考虑以下问题：
1. 队列：用来存储每一轮遍历得到的节点；
2. 标记：对于遍历过的节点，应该将它标记，防止重复遍历。
```
搜索左上到右下的最短长度
1能走。相邻点间距离为1，每次搜索一层，搜多少次就是多少长度
[[1,1,0,1],
 [1,0,1,0],
 [1,1,1,1],
 [1,0,1,1]]
```

#### 回溯
* 一种选优搜索法，按选优条件向前搜索，以达到目标。但当探索到某一步时，发现原先选择并不优或达不到目标，就退回一步重新选择.
* 可以理解为通过选择不同的岔路口寻找目的地，一个岔路口一个岔路口的去尝试找到目的地。如果走错了路，继续返回来找到岔路口的另一条路，直到找到目的地。
* 当发现一条路走不通时，是返回最近的一个分叉选择另一条路走。之所以能回到分叉处走另一条路，是因为分叉处选择的第一条路好比是第一次调用递归，递归函数返回时，就好比回到了分叉处。第二次调用递归，就好比走第二条路
* 递归找到后停止递归：即是回到分叉口后不再调用递归函数。递归第一次返回，是在终点，在终点处可返回Bool判断这条路对不对。每个分叉通过递归返回值判断要不要再次调用递归
* 适合解决类似树的运行顺序的问题，即从一个分叉开始，走到底后返回最近的分叉重新走，离终点最近的分叉走完后，再返回第二近的分叉选择路走。

### 排列
```
[1,2,3]
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

//含有相同元素求排列
[1,1,2]
[[1,1,2], [1,2,1], [2,1,1]]
//分叉处不要使用该处已使用过的相同数字
```
###
* 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。 数字可以无限制重复被选取。解集不能包含重复的组合。 
```
解集中出现重复的组合，是因为用了一个数字之后，可能在之后的任意一次选取中，又使用了这个数字。
保证每次选取一个数时，下次又尝试取同一个数,如果尝试的这次不行，之后都不会再取到这个数
(解题时想出出现问题的条件，避免这些条件出现，问题则不会出现)

std::vector<int> p = {3, 5, 2};
int target = 8;
void heDfs(int i, int sum, std::vector<int> res)
{
    sum += p[i];
    res.push_back(p[i]);
    if (sum == target)
    {
        cout << endl;
        for (const auto &it : res)
            cout << it << " ";
        return;
    }
    for(auto j = i; j < p.size(); ++j)
    {
        if (sum + p[j] > target)
            continue;
        heDfs(j, sum, res);
    }
}
int main()
{
    for(auto i = 0; i < p.size(); ++i)
        heDfs(i, 0, {});
}
```
### 子集
* 给你一个整数数组,数组中的元素互不相同.返回该数组所有可能的子集.解集不能包含重复的子集.你可以按任意顺序返回解集。
```
eg:
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
//观察结果，可总结出规律，本分叉使用的idx，下一个分叉只能idx从+1开始使用。
从上面的结果不容易发现规律，因为不是走完一个完整的递归函数返回的结果。
1 
1 2
1 2 3  //上三行是一个递归返回的结果，可看出下一递归使用的idx从+1开始
1 3
2
2 3
3

std::vector<int> p = {1, 2, 3};
void zjDfs(int start, std::vector<int> res) {
    if(start >= p.size())return;
    for(auto i = start; i < p.size();++i) {
        //if(i > start && p[i] == p[i - 1]) //每个分叉不使用使用过的元素，就可避免p中有重复元素问题
            //continue;
        res.push_back(p[i]);
        cout << endl;
        for(const auto& it : res) {
            cout << it << " ";
        }
        zjDfs(i + 1, res);
        res.pop_back();
    }
}
```
### 分割字符串使得每个部分都是回文数
```
//模拟出一个完整的递归是怎么走的。回到叉路口又怎么走
bool isHW(const string& str) {
    if(str.empty())return false;
    auto l = str.length() - 1;
    auto s = 0;
    while(s < l) {
        if(str[s++] == str[l--])continue;
        return false;
    }
    return true;
}
void hwDfs(std::vector<string> res, const string& str) {
    if(str.empty()) {
        cout << endl;
        for(const auto& it : res)cout << it << " ";
    }
    for(auto i = 1; i <= str.length(); ++i) {
        const auto tmpStr = str.substr(0, i);
        if(!isHW(tmpStr))continue;
        res.push_back(tmpStr);
        hwDfs(res, str.substr(i));
        res.pop_back();
    }
}
```

#### 回溯和深度优先异同
* 相同
1. 一步步的往前探索
* 不同
1. 深度目的是“遍历”，本质是无序的,访问次序不重要，重要的是都被访问过了。要标记是否被访问过。
2. 回溯目的是“求解过程”，本质是有序的.同样的内容不同的序访问就会造成不同的结果，而不是仅仅“是否被访问过”这么简单。也就是对于每个点记录已经访问过的邻居方向，回溯之后从新的未访问过的方向去访问邻居。至于这点之前有没有被访问过并不重要，重要的是没有以当前的序进行访问。
3. 深度优先遍历：已经访问过的节点不再访问，所有点仅访问一次。
4. 回溯法：已经访问过的点可能再次访问，也可能存在没有被访问过的点。

#### 动态规划
* 一定范围内的最优解，并不会随范围的变大而变化
* 增加范围后的最优解与原范围有关系。原范围的最优解与增加的范围没有关系
* 枚举多个，观察推导出n时的公式
* 新步骤的解需通过已算出的步骤的解求值
### 抓楼梯(可抓1或2阶)
* 从n-1到n和从n-2到n(都是只跳一次)，一定是不同的方法(n-1最后一步是1阶，n-2最后一步是2阶).且从0到n-1的方法等于0到n-1再到n的方法(n-2也一样).所以到n = 0到n-1方法 + 0到n-2方法
### 强盗在环形街区抢劫
* 看成是两个街道，分别求最优，再比较两个的最优
### 信封错放
```
eg:有4个信和信封
1 2 3 4(信)     
//--------
2 1 4 3     
2 3 4 1
2 4 1 3
如果2信放到1封时，剩的信息如下
1   3 4//信
  2 3 4//信封
因为1可以放到234位，所以与3个信和信封的情况不同(1只能放2个位).
分情况分析:
当1放2位时，发现此时只是两封信交叉放，剩下的(2种)有多少种才是起决定性的。
当1不能放到2位时，发现此时的情况与3种相同。
所以2信放到1封时，有f(4-2) + f(4-1)
当其它信也放到1封时，有(4-1)*f(4-2) + (4-1)*f(4-1);
所以当n时:
(n-1)*(f(n-2) + f(n-1));
ps:感觉要这种题要枚举出来找规律
```
### 母牛生产
* 没有从大小处考虑，而是枚举出多个，再找规律
```
f(n) = f(n - 1) + f(n - 3);
因为规律是从n > 3后开始，所以一开始要自行算出n为1~3的数

int cowNums(int n){
    int []dp=new int [n+1];
    if(n==0)
        return 0;
    if(n==1)
        return 1;
    if(n==2)
        return 2;
    if(n==3)
        return 3;
    dp[0]=0;
    dp[1]=1;
    dp[2]=2;
    dp[3]=3;
    for(int i=4;i<=n;i++){
        dp[i]=dp[i-1]+dp[i-3];
    }
    return dp[n];
```
### 矩阵路径
* 只能往下或往右走，找从左上到右下的最小路径和
```
* 到某个点只能是从上或从左过来的，只需比较从哪过来的和比较小，就选哪条路。
[[1,3,1],
 [1,5,1],
 [4,2,1]]

 void dtSum() {
    std::vector<std::vector<int>> vec = {
        {1,3,1},
        {1,5,1},
        {4,2,1}
        };
    std::vector<int> sum_vec;sum_vec.assign(vec[0].size(), 0);
    for(auto i = 0; i < vec.size(); ++i) {
        for(auto j = 0; j < vec[i].size(); ++j) {
            if(j == 0)
                sum_vec[j] = sum_vec[j];
            else if(i == 0) {
               sum_vec[j] = sum_vec[j - 1];
            }
            else
                sum_vec[j] = std::min(sum_vec[j], sum_vec[j - 1]);
            sum_vec[j] += vec[i][j];
        }
    }
    cout << sum_vec.back() << endl;
}
```

#### noncopyable
```
class Matrix {
public:
   _T* data;
   Matrix(){
      data = new  _T[w*h];
   }
   // 析构函数
   ~Matrix() {
       delete [] data;
   }
}
Matrix a
Matrix b = a; //此时就有两个指针指向同一块空间，除非自实现拷备构造函数。
或者禁用类的拷备构造和赋值构造，继承boost::noncopyable
基类的构造函数，不论派生类中是否自实现调用,什么继承方式，最终都会调用
```
#### skill
### 根据不同类型，执行不同的逻辑，我可能会在一个函数中实现，逻辑会很多很长，以下是构建类时，就确定了要执行的方法
```
class ActivityCCRank {
public:
    ActivityCCRank(const int type) : Type(type) {
        SGM = SINGLETONMUTEXPTRCREATE();
        if (type == ActivityRankEnum::activity_battle_rank) {
            _clean_function = boost::bind(&ActivityCCRank::_impl_clean_rank_list_sp1, this);
        }
        else {
            _clean_function = boost::bind(&ActivityCCRank::_impl_clean_rank_list, this);
        }
    }
private:
    boost::function<void> _clean_function;
};
```
### 利用一个数组保存对象和标记位对应的外部函数
_subscribers[length] = child;
_subscribers[length + FULFILLED] = onFulfillment;
_subscribers[length + REJECTED] = onRejection

### 根据类型进行某种操作时，可将类型以模板的形式传入
```
eg:
template <typename Service>
asio::io_service::service* service_registry::create(
    asio::io_service& owner)
{
  return new Service(owner);
}
```
### 判断一个类是否生成对象过，类中声明一个静态成员变量(可是一个空类)，把静态变量的地址做为key
```
class io_service::id
  : private noncopyable
{
public:
  /// Constructor.
  id() {}
}
```
### 如果锁需要在函数中进行操作，可将锁当参数传入
```
mutex::scoped_lock lock(mutex_);
  op_queue_.push(op);//放入任务队列，并唤醒一个线程进行处理
  wake_one_thread_and_unlock(lock);
```
### 保证某逻辑一定执行的方法
```
struct task_io_service::work_finished_on_block_exit
{
  ~work_finished_on_block_exit()
  {
    task_io_service_->work_finished();
  }
  task_io_service* task_io_service_;
};
void func()
{
  work_finished_on_block_exit on_exit = { this };
  (void)on_exit;//因为on_exit没用使用，加void避免警告
  o->complete(*this);//想这里执行完成，一定调用work_finished函数，但某些错误可能会导致执行不到，
  //work_finished_on_block_exit的方法保证了，只要不挂，就一样能执行到.要挂了，执不执行都无所谓了
}
```
      