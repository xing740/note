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

### step 进入函数
没有进函数的原因是gdb不会在不具有调用信息的代码内停止
```
printf()
```
#### finish
恢复gdb运行，直到恰好在函数返回之后为止.

### until
1. 执行完循环直到跳出循环的第一行代码处暂停。
2. 如果执行until导致回跳到循环顶部，再执行until就可离开当前循环。
3. 执行到某行或某函数入口.
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

### print
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