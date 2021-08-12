### 通信
#### gate
1. 分别生成监听gac的服务器csvr和内部通信服svr
2. 登录时与后台的验证，是gate负责
#### game
1.生成gm服(http,主要是修改游戏数据), user服(主动去连接gate的svr)


### 战车
7. 邮件:tag.keep 判断是否是要保留着的邮件。out:判断是否是大于邮件容量，要清的邮件，delete是主动删除标记
8. cfg:之前前端是用一个返回码，去找对应的信息，现在是gas把要显示的信息先找到，再给gac
```
//带参数处理方法
module.exports = {
    "资源不足": "{0}不足",  //用{number}进行参数占位，多个参数时number往上加
};
{Common.StringFormat(CodeMessage.Message("资源不足"), ItemConfigureMgr.singleton().name(2)) }//打包时将对应的参数加上即可
```

### ts
1.v8的Array.sort(),<=10用插入排序，其它用快速排序(不稳定排序，适合排序无序，最差时的效率是排序有序数列)
3. any
1.可以被赋值为任意类型，即使之前被赋值过.也可以赋值给任何值。可能是编译器看成any类型就不检查类型
2.声明变量，但没有初始和类型.是any类型.
3.可以访问any变量的任意属性和方法。即对它的任何操作和返回的内容的类型都是任意值

4. let 块作用局，相当于声明局部变量. 初始化，但不加类型，相当于auto
5. 联合类型 type Index = 'a' | 'b' | 'c'; type是重命名

6. 类型断言,告诉编译器是什么类型,更像强转，不像断言(c++的断言是判断是什么类型，不是就报错),它没有运行时的影响，只是在编译阶段起作用.
```
1. 尖括号 语法
let someValue: any = "this is a string";
let strLength: number = (<string>someValue).length;

2. as 语法
let someValue: any = "this is a string";
let strLength: number = (someValue as string).length;
```
7. buffer
0. JavaScript 语言自身只有字符串数据类型，没有二进制数据类型。但在处理像TCP流或文件流时，必须使用到二进制数据。
1. 因此在 Node.js中，定义了一个 Buffer 类，该类用来创建一个专门存放二进制数据的缓存区。每当需要在 Node.js 中处理I/O操作中移动的数据时，就有可能使用 Buffer 库。原始数据存储在 Buffer 类的实例中。一个 Buffer 类似于一个整数数组，但它对应于 V8 堆内存之外的一块原始内存。

8. 类class
1. 类中的静态函数可以传this指针使用静态成员

10. bignumber 进行数学运算的库
11. 索引签名，限制对象存的内容
```
声明一个索引签名
const foo: {
  [index: string]: { message: string };
} = {};  下标是string，值是对象，有一个message属性.值的属性不能多也不能少

foo['a'] = { mesages: 'some message' }; error!
```
12. nodejs是只有主线程在执行程序代码，定时器时间到时，会将回调函数放入事件循环，主线程只有在处理完当前的事件后，才会去处理另一个事件.主线程要尽量避免处理有阻塞的操作，比如大量的计算
```
eg:定时器是1毫秒打印，但主线程会先处理完循环后，才会去处理定时器的回调打印事件。
setTimeout(() => {
    console.log("time");
}, 1);

for(let i = 0; i < 9000000000; ++i);
console.log(process.pid)
```
12. 如果 person 是一个对象，下面的语句不会创建 person 的副本
```
var x = person;  //x是person的引用 x 和 person 是同一个对象。对 x 的任何改变都将改变 person，因为 x 和 person 是相同的对象。
```
13. 元组可存不同类型
14. === 运算符需要类型和值同时相等,!== 值不相等或类型不相同
15. 要返回undefine时，用void num，一般void 0, 不能直接返回undefine,因为undefine可以是变量，可被改写
16. 已声明未初始化的值要直接访问的话，类型需要定义为undefined.
17. < T extend x> 约束T的类型为x类型或继承至x类型
19. npm install会先检查node_modules目录中是否存在指定模块，如果存在就不安装，即便远程有新版本。如果.npm中有压缩包，但没有安装到node_modules中，也会重新下载。压缩包又不能用，当然要重新下载.下载时npm 向registry服务查询模块压缩包的网址,下载压缩包，将存放在~/.npm目录解压压缩包到当前项目的node_modules目录
20. tsconfig.json  该文件存在的地方就是根目录.可通过include和files指定编译的文件。如果rootDir打开了，则files指定的文件要在rootDir指定的目录中，exclude要打开，不打开会默认忽略./
21. npm install --production(生产模块)  不安装devdependencies中的模块,安装模块时，--dev表示添加到devdependencies中，即这个模块是开发时需要的，生产时不需要.全局安装的模块或是不加参数的npm install的模块，在 npm install初始化项目时，不会下载模块.
22. 因为js中的函数可以有属性和方法,所以即是函数也是对象。ts中的类，最终会解析成函数。箭头函数没有this，不适合定义对象方法。
```
eg:ts类解析成js
class Greeter {
    greeting: string;
    constructor(message: string) {
        this.greeting = message;
    }
    greet() {
        return "Hello, " + this.greeting;
    }
}
执行一个匿名函数来执行创建对象的逻辑
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
23. promise
1.能方便的实现链式操作,传入的promise是第一个函数，之后的then传入的函数可理解为回调执行，promise的模式保证了顺序的执行。即第一个then是在传入promise的函数执行后再执行，之后的then都是上一个then传入的回调函数执行完后再执行
2.是一个构造函数，new promise(fun(resolve, reject)),new之后，会立即执行传入的函数.
3.resolve,和reject的执行时机是我们传入的函数实现中决定的.resolve和reject主要是改变promise的状态,状态不可逆，且只会改变一次，函数返回的value会给then使用。
4.then可传入onFulfillment和onRejection函数，分别处理上一个promise的Fulfilled和rejected状态之后的事情. then方法会创建一个新的promise,并返回，并根据上一个promise的状态，决定是将then传入的回调方法(回调方法会用到上一个promise返回的value)存入立即执行队列还是订阅队队列(当是pending状态时)。立即执行队列并不是立即执行，而是之后没有接着then才会去执行。不论是异步和同步，都保证了then是顺序执行的。
5.promise中传入的函数如果没有异步，直接调用了resolve函数，则状态会马上改变，不然会是pending状态，到第二个then时，不管是将then的函数参数传入哪个队列，都不会立即执行，而是再执行下一个then，这时的then会判断上一个then的状态是pending，所以会将函数传入订阅队列
6.resolve静态方法内部是帮我们创建了一个状态为Fulfilled的promise对象并返回，如果resolve参数是promise，则直接返回该promise
6.参考<https://juejin.cn/post/6844904144382197774/>

24. async/wait
1.async 一个封装好的 Promise 对象，调用时得到一个 Promise 对象,遇到await时，会执行await修饰的代码，然后让出所有权，如果await中都是同步代码，那加await并没有提高什么效率。
2.await中有异步调用去获取某数据，await接下来的逻辑需要这个数据。此时的await才有意思，await会触发异步调用后，此时另一个线程在取数据，我让出所有权，不走await之后的代码，等异步取到数据后，再回到await处，执行后面的代码
3.一定会返回promise,如果返回值看起来不是promise，会被稳式的包装在promise中.
```
async function foo() {
   return 1
}
等价于:
function foo() {
   return Promise.resolve(1)
}
```

4.async中不含await，是同步运行，有await，就一样会异步执行
```
async function foo() {
   await 1
}
等价于:
function foo() {
   return Promise.resolve(1).then(() => undefined)
}
```
4.promose解决了回调地狱，async与promise一样，只是写起来更好理解,async依然是promise
5.await是不管异步过程的reject(error)消息的，async函数返回的这个Promise对象的catch函数就负责统一抓取内部所有异步过程的错误,或用try_catch
6.加了async关键字表示里面可能有异步代码，里面可以加await，如果都是同步代码，async显的多余
7.async修饰的函数返回值可以不写
8.如果一个数据是内嵌多个函数的最后一个函数才异步去取的，则不因只是在最后异步取数据时加await，从第一个取数据入口处起，调用的每个函数都要加await

25. ||,&& 用于对象(对象的真假可通过存在或不存在判断,好比数字的真假通过0非0判断)
1.【a || b】：a存在返回a，a不存在返回b  
2.【a && b】：a存在返回b，a不存在返回a

26. Getter 和 Setter
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

27. try finally
1.try是否捕捉到错误，finally后的代码都会执行

28. map,set 
1. 一个 Object 的键只能是字符串或者 Symbols，Map 的键可以是任意值。
3. set 可存不同类型


28. 任务
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
29. 字面量
在计算机科学中，字面量是用于表达源代码中一个固定值的表示法.(暂理解成临时变量)
```
std::string x = "hello"; "hello"就是字符串字面量
let x = {color: "blue", len: 2}; 右边的{...}就是对象字面量
```

30. 奖励池
random: {imit(限制, 需要才配置)
        way:"all",//随机类型 all:所有奖池都抽，抽的次数取决于其中的pick. random:先要抽取奖池，抽的次数是opt中的times.
        opt:{times:1, putback:true},//选项, all类型配置opt:{}或者没有这个字段都可, random类型opt:{times:次数需要>0, putback:可以不写,默认false, 不放回}
        pool:[
            {
                choose:10000,//选择该奖池的权重//way的值等于all的时候, 这个值写不写无所谓
                pick:1,//抽取次数 >0  declare这个奖池中的奖励的抽取个数
                declare:[
                    {
                        name: "item",
                        types: 1,
                        num: 500,//以上几个字段都是奖励描述//请对应英雄或者道具的奖励说明对应配置即可
                        weight: 1000,//抽取该奖励的权重
                        putback:true,//抽取完之后是否放回, 可以不写, 不写默认false(不放回)
                        limit: function(player) {//限制//可以不配置
                            return player.war().process > 100;
                        }
                    },
                    ...
                    ...
                ]
            },
            ...
            ...
        ]
    };
1. 先判断way的类型，如果是random，先抽取出奖池
2. 抽取出的奖池，都会有机会抽里面的奖励
3. 权重相加，在0到总权重中随机一个数。大于这个数的权重就是抽到的奖励，如果是不放回，要把奖励踢出，总权重也要相应的减去。
```
for (let i = 0; i < opt.times; ++i) {
                let rv = Common.RandomHalfOpenBetween(0, total);
                let cal: number = 0;
                for (let item of s) {
                    cal += item.weight;
                    if (rv < cal) {
                        arr.push(item);
                        if (!item.putback) {
                            s.delete(item);
                            total -= item.weight;
                        }
                        break;
                    }
                }
            }
```

31. 
```
let x = {
	x:1,
	y:2,
};

interface tx {
	x:number;
}
let xx: tx = x;//xx打印是{ x: 1, y: 2 },但tx只有x，所以只能访问x，防问y时也可得到y的值，但会报错
console.log(xx.y);

```
32. enum
1. 加const后，编译后直接替换，不加时.编译过后生成key和value互相对应的key/value,不管用key和value都能取到对应的值，但用的内在较多。
```
eg:
 const enum responseStatus {
  error = 400,
  success = 200,
}
console.log(responseStatus[400])// 加const 后，会报错
console.log(responseStatus.error)// 编译成js后，是// console.log(400)
```
zcjilu

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
  [index: number]: string;
}

let myArray: StringArray;//可以是数组或对象
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
//类实现接口要用implements , 子类必须实现接口里面声明的所有属性和方法
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
接口可互相继承(注意：不是类与接口间的继承),一个接口可以继承多个接口，创建出多个接口的合成接口。
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

let square = <Square>{};//(使用时有个<>,可能就是断言的作用)
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

### 索引
1. 索引不是独立于表的另外的元素，属于表中的元素.将某个数做为索引，可按递增递减排序
2. 可提高查找效率。
3. 索引可设置成唯一或非唯一。
4. 多重索引，eg:以第一个索引做递增减排序，当索引相同时，再以第二个索引进行比较排序

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
### C
#### 只能在堆或栈上建立对象
* 栈上的对象是直接调用构造函数，同时会检查析构函数是否可用
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

#### 算法
### 位运算
* 将最右边的1去掉。n&(n-1),
* 取最右边的1。n&(-n),因为-n为n取反加1.取反后，n最右边的零变为1，最右边的1变为0，所以加1后，进位使原最右边的1又由0变成1

1. 找出数组中缺失的那个数 (一个数与同一个数^运算两次，还是原来的数
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
2. 找出数组中不重复的两个元素
* 两个不相等的元素在位级表示上必定至少一位存在不同。找出其中一位的不同，所有元素与其&操作。结果一定为0或非0
```
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
1 10 11 100 101 110 111 1000
```
3. 统计从 0 ~ n 每个数的二进制表示中 1 的个数
```
x的二进制去掉最右边的1，一定得到小于x的数，0，1的1个数已知。用动态规划
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

```
#### 链表
### 找出两条单向链表的交点
```
设A: a1 a2 c1 c2 c3
设B: b1 b2 b3 c1 c2 c3
则 A+B==B+A

a1 a2 c1 c2 c3 b1 b2 b3 c1 c2 c3
b1 b2 b3 c1 c2 c3 a1 a2 c1 c2 c3
                        交点
```
### 判断是否有交点
* 最后一个结点是否相同

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
1 2 3
* 用递归打断所有结点，当到最后一个时，2接到3后，1接到2后，都是接到本身结点的下一个结点
* newHead始终是最后一个结点3
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
1 2 2
2 3 4
* 递归功能：每次比较头结点，下次比较是取大的与小的的next时行比较,返回的结果接在小后
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
#### 从有序链表中删除重复节点
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
好比全部打断，从尾开始比较大小重新连接
public ListNode deleteDuplicates(ListNode head) {
    if (head == null || head.next == null) return head;
    head.next = deleteDuplicates(head.next);自己的下一个是上一次比较的返回结果
    return head.val == head.next.val ? head.next : head;
}

#### 判断链表回文
1. 找到中点，注意倚偶的中点,倚时分割的链表大小不一也可以判断回文
2. 分割成两个链表
3. 反转其中一个链表
4. 比较每个元素

#### 分割链表，分成k段，长度尽可能相同，排在前面的要大于等于后面的长度
* 余数往前加，每个加1才能长度相当
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
1->2->3->4->5

public ListNode oddEvenList(ListNode head) {
    if (head == null) {
        return head;
    }
    ListNode odd = head, even = head->next(//分别创建奇偶的头), evenHead = even(保存偶的头，最后要连);
    while (even != null && even.next != null) {
        odd->next = odd->next->next;
        odd = odd->next;
        even->next = even->next->next;
        even = even->next;
    }
    odd.next = evenHead;
    return head;
}
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
* 若curMax + x[i] <= x[i], curMax只能使收益减少或不亏，还不如用x[i]当头
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

### 二分查找
* 明确左右边界的设置条件,退出循环的条件可试最后的几次就知道
* 试乎左右无所谓谁先设置
* 死循环问题
```
int m = l + (h - l) / 2;
上式可能出现 l == m
在接下的设边界中，不要出现l = m,如果出现，改成int m = r - (h - l) / 2;
```
#### 在有重复数中找左边界
* left:<,m+1 right: >=, m
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
#### 大于给定元素的最小元素
* left:<=, m+1  right:>, m
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
#### 一个有序数组只有一个数不出现两次，找出这个数
0 0 1 2 2
* 所在区间，[偶] != [偶+1], 使min == 偶，判断[mid] == [mid+1] ? ,left:==, mid+2, right:!=, h = m
* mid本来要处理奇偶，把mid变成偶，就只需处理一种情况
```
public int singleNonDuplicate(int[] nums) {
    int l = 0, h = nums.length - 1;
    while (l < h) {
        int m = l + (h - l) / 2;
        if (m % 2 == 1) {
            m--;
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
* 用背包方法还快点

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
1. 队列：用来存储每一轮遍历得到的节点；下一轮可走的所有结点
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
For example, given s = "aab",
[
  ["aa","b"],
  ["a","a","b"]
]
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
* 利用历史记录，来避免我们的重复计算。而这些历史记录，我们得需要一些变量来保存，一般是用一维数组或者二维数组来保存。
* 分析问题是否符合动态规则，有以下两个性质，再写出状态转移方程(利用当状态，计算下一状态)。
eg:找钱:f(n) = min[f(n-1), f(n-5), f(n-11)] + 1;
* 1.重叠子问题，可将一个大问题分成小问题，分别求解小问题的解就能推出大问题的解。2.最优子结构:大问题的最优解可由小问题的最优解得到

### 爬楼梯(可爬1或2阶)
* 每梯的方法是定的，并不会随梯数的增加，n时，可能会爬1，就需算f(n-1)的方法，也可能爬2，需算f(n-2)的方法，所以总方法为f(n-1) + f(n-2)
### 强盗在环形街区抢劫
* 看成是两个街道，分别求最优，再比较两个的最优
### 信封错放
```
1 0
2 1
3 3  f(3) = 3
eg:有4个信和信封
1 2 3 4(信)     
//--------
2 1 4 3     
2 3 4 1
2 4 1 3
如果2信放到1封时，剩的信息如下
1   3 4//信
  2 3 4//信封    f(n-2) + f(n-1)
分情况分析:
当1放2位时，次数取决于3,4，相当于f(n-2);
当1不能放到2位时，发现此时的情况与3个信封时相同。f(n-1)
所以当n时:
(n-1)*(f(n-2) + f(n-1));
```
### 母牛生产
* f(n)=上一年数+增加数, 增加数是上一年成年的，上一年的成年牛只能来自前三年的小牛，或是前三年就已存在的成年牛,所以f(n) = f(n-1) + f(n-3)
```
A
A a
A a a
A A a a
A A A a a a
A A A A a a a a a 

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
* 到某个点只能是从上或从左过来的，只需比较从哪过来的和比较小，就选哪条路,且某个点的上或左，一定比这个点先算。
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
### 数组中等差递增子区间的个数
* 如果一个数列至少有三个元素，并且任意两个相邻元素之差相同，则称该数列为等差数列
* 注意是子区间(相邻)，不是子序列
```
 //A[i] - A[i-1] == A[i-1] - A[i-2]，那么 [A[i-2], A[i-1], A[i]] 构成一个等差递增子区间。而且在以 A[i-1] 为结尾的递增子区间的后面再加上一个 A[i]，一样可以构成新的递增子区间。且dp[i] = dp[i-1] + 1;//dp[i]表示以A[i]结尾的等差递增子区间个数
 void numberOfArithmeticSlices() {
    std::vector<int> A = {0, 1, 2, 3, 4};
    int n = A.size();
    std::vector<int> dp;
    dp.assign(n, 0);
    for (int i = 2; i < n; i++) {
        if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
            dp[i] = dp[i - 1] + 1;/1是当前以i结尾的，最短的等差子区间
        }
    }
    int total = 0;
    for (int cnt : dp) {
        total += cnt;
    }
    cout << total << endl;
}
```
### 按平方数来分割整数(求最少平方数)
* vec[i],i能被平方数分割的最小数量。每个i能选的平方数区间是一样的。i可能成背包，平方数可看到物品，求用最少数量的物品填满背包
* 1属于平方数
```
void square() {
    const auto n = 4;
    std::vector<int> sqVec;
    auto i = 1;
    auto i_sq = 1;
    while(i_sq < n) {
        sqVec.push_back(i_sq);
        ++i;
        i_sq = i * i;
    }
    std::vector<int> vec;
    vec.assign(n+1, 0);
    for(auto j = 1; j <= n; ++j) {
        auto min = 10000;
        for(auto it : sqVec){
            if(it > j)break;
            min = std::min(vec[j - it] + 1, min);
        }
        vec[j] = min;
    }
    cout << vec[n] << endl;
}
```
#### 分割整数构成字母字符串(解码成字母)，求可解码个数
* eg:"12"，可解码成两种，"AB","L";
* 后面的解码个数与前面的个数有关
* 每个数的解码有两种可能：1.自己构成解码数f(n) += f(n-1)，2.与前一个数构成解码数f(n) += f(n-2),前一个数为0，则不能与其构成解码数
* 第一个字符为0，则不能解码，否则解码数为1

#### 最长递增子序列
* 是子序列(可不相邻)
* 定义f(n),以某数结尾的最长递增子序列
```
[10,9,2,5,3,7,101,18]
5:25
3:23
7:27 257 57 237 37
101:25 101, 23 101, 27 101, 257 101.
//观察可知，如果7 > 5,最长为5的最长+1

void maxLength() {
    std::vector<int> vec = {0,0};
    std::vector<int> lVec;
    lVec.assign(vec.size(), 0);
    auto max = 1;
    for(unsigned i = 0; i < vec.size(); ++i) {
        for(auto j = 0; j < i; ++j) {
            if(vec[i] > vec[j]) {
                max = std::max(max, lVec[j] + 1);
            }
        }
        lVec[i] = max;
    }
}
```
#### 找出摆动序列的最长子序列
* 如果连续数字之间的差在正数和负数之间交替，则数字序列称为摆动序列。仅有一个元素或者含两个不等元素的序列也视作摆动序列。
* 某个序列被称为「上升摆动序列」，当且仅当该序列是摆动序列，且最后一个元素呈上升趋势。如序列 [1,3,2,4][1,3,2,4] 即为「上升摆动序列」。
* 状态转移 nums[i] > nums[i-1],up = down + 1. nums[i] < nums[i - 1]. down = up + 1;
```
public int wiggleMaxLength(int[] nums) {
    if (nums == null || nums.length == 0) {
        return 0;
    }
    int up = 1, down = 1;//up表示，前i个元素中，最长的上升摆动序列长度
    for (int i = 1; i < nums.length; i++) {
        if (nums[i] > nums[i - 1]) {
            up = down + 1;//观察可知，在一个上升趋势中，上升摆序列长度=下降摆动序列长度+1
        } else if (nums[i] < nums[i - 1]) {
            down = up + 1;//同理
        }
    }
    return Math.max(up, down);
}
```
#### 最长公共子序列
* 给定两个字符串text1和text2，返回这两个字符串的最长公共子序列的长度。
* 定义dp[i][j],当选到str1的第i个字符和str2的第j个字符时，最长公共子序列为dp[i][j]
* 两个数比较有两种情况：1.相同.dp[i][j] = dp[i-1][j-1] + 1. 2.不同dp[i][j] = max(dp[i-1][j], dp[i][j-1]).不能理解为dp[i][j] = dp[i-1][j-1],因为dp[i-1][j-1],只表示当i从0到i-1,j从0到j-1中的最长子序列，还没有包括当到i到i和j到j的情况
```
void maxDp() {
    std::string str1 = "abc", str2 = "def";
    std::vector<int> dp;//只用到i 或i+1位，且之前会先求得，所以可不定义成二维
    dp.assign(str1.length() + 1, 0);//不加一的话，求当前位要求i-1，当i=0时会越界
    for(auto i = 0; i < str1.length(); ++i) {
        for(auto j = 0; j < str2.length(); ++j){
            if(str1[i] == str2[j])
                dp[i+1] = dp[i] + 1;
            else
                dp[i+1] = std::max(dp[i+1], dp[i]);
        }
    }
    cout << dp.back();
}
```
#### 背包0-1
* 找钱时，是每一个剩余没找的钱，可选择的对象(面额)是一样的,所以当前的状态可用之前已算出的状态.背包剩余的空间可选择的物品，与当前选择的物品有关。所以可反过来，让物品去选择空间，每个物品可选择的空间都是1到w;
* 状态转移:dp[i][j],当选到第i个物品，空间为j时的价值.第一种情况，不可选第i个物品，dp[i][j] = dp[i-1][j](j不应再减去任务数，[i-1][j]是之前求出的状态,要结合实际).可选时，要
比较是选还是不选价值高。dp[i][j] = max(dp[i-1][j], dp[i-1][j-当前物品空间] + 当前物品价值);
* 解题时，要分析题型是否属于背包问题,是01背包，完全背包，还是多重背包
* 当二维状态改成一维时，要注意覆盖问题,eg:i-1=[2,3,4],，如果从前往后算，当计算i的3位时，需要i-1，2位的结果，但计算i的2位时已经覆盖了。
```
N = 3 //地主家有三样东西
wt = [2,1,3] //每样东西的重量
val = [4,2,3] //每样东西的价值
W = 4 //背包可装载重量

void xbdpf() {
    std::vector<int> v = {4,2,3};
    std::vector<int> w = {2,1,3};
    const auto wt = 4;
    std::vector<int> tmp;
    tmp.assign(v.size() + 1, 0);
    std::vector<std::vector<int>> vec;
    vec.assign(wt + 1, tmp);
    for(auto i = 1; i <= wt; ++i) {
        for(auto j = 1; j <= w.size(); ++j) {
            if(w[j-1] > i)
                vec[i][j] = vec[i-1][j];
            else
                vec[i][j] = std::max(vec[i-1][j], vec[i - 1][j-w[i]] + v[i];
        }
    }
    return;
}

```
#### 划分数组为和相等的两部分
* 想求和为v，取出一个<=v的数i，想知道i+x==v？就需判断能组成的数中，有没有x. x=v-i;
v的取值为[i,v]
* 当成
```
void maxNum() {
    const auto v = 11;
    const std::vector<int> vec = {1,5,11,5};
    std::vector<bool> res_vec;//j从i开始，会使得结果全为true
    res_vec.assign(v + 1, false);
    res_vec[0] = true;
    for(auto i = 0; i < vec.size(); ++i) {
        for(auto j = v; j >= vec[i]; --j) {//j从i开始，会使得结果全为true
            if(res_vec[j])continue;

            if (vec[i] == j)
                res_vec[j] = true;
            else
                res_vec[j] = res_vec[j - vec[i]];
 
        }
    }
    return;
}
当成0-1背包，求物品的重量能不能刚好为sum/2
void maxNum() {
    const auto v = 11;
    const std::vector<int> vec = {1,5,11,5};
    std::vector<int> res_vec;//j从i开始，会使得结果全为true
    res_vec.assign(v + 1, 0);
    for(auto i = 0; i < vec.size(); ++i) {
        for(auto j = v; j >= 1; --j) {
            if(j < vec[i])
                res_vec[j] = res_vec[j];
            else
                res_vec[j] = res_vec[j - vec[i]] + vec[i] <= v ? res_vec[j-vec[i]] + vec[i] : res_vec[j];
            if(res_vec[j] == v)break; 
        }
    }
    return;
}
```
#### 改变一组数的正负号使得它们的和为一给定数
* [i][j]//前i个数中，合为j的个数，从vec中取出一个不大于v的数i，v-i=j,则能组成合为v的个数为dp[v](能组成本身的个数)+dp[j]的个数
```
(正)sum(P) - (负)sum(N) = target
sum(P) + sum(N) = sum
所以:sum(P) = (target + sum) / 2，
求sum(p)是否存在

public int findTargetSumWays(int[] nums, int S) {
    int sum = computeArraySum(nums);
    if (sum < S || (sum + S) % 2 == 1) {
        return 0;
    }
    int W = (sum + S) / 2;
    int[] dp = new int[W + 1];
    dp[0] = 1;
    for (int num : nums) {//想知道num+x=i?，判断x是否存在，存在几个，就能组成几个num+x==i
        for (int i = W; i >= num; i--) {
            dp[i] = dp[i] + dp[i - num];
        }
    }
    return dp[W];
}

private int computeArraySum(int[] nums) {
    int sum = 0;
    for (int num : nums) {
        sum += num;
    }
    return sum;
}
```
#### 多重背包
* [i][j][z],选第i个时，当背包1为j，背包2为z时，最多可装入的数量
* 可直接用bp[j][z],因为只会用到i可i-1，且i-1的[j][z]结果，不会被改变
```
strs = ["10", "0001", "111001", "1", "0"], m = 5, n = 3
输出：4
解释：最多有 5 个 0 和 3 个 1 的最大子集是 {"10","0001","1","0"} ，因此答案是 4 。

void towBb()
{
    std::vector<string> str_vec = {"10", "0001", "111001", "1", "0"};
    const auto m0 = 5;
    const auto n1 = 3;
    int vec[m0+1][n1+1];
    memset(vec, 0, sizeof(vec));
    for (const auto str : str_vec)
    {
        auto len0 = 0, len1 = 0;
        for (const auto it : str)
            if (it == '0')
                ++len0;
        len1 = str.length() - len0;
        for(auto j = m0; j >= len0; --j) {
            for(auto z = n1; z >= len1; --z) {//不用--会覆盖之前的状态,除非用三维，vec[i][j][z],因为i用到的状态是i-1的
                vec[j][z] = std::max(vec[j][z], vec[j-len0][z-len1] + 1);//装下这个字符时，背包1，2都会变化，所以要找上一个字符两背包剩下的值
            }
        }
    }
    return;
}
```
#### 找零钱组合数，无限多个金币
```
j-vec[i] = x;
如果x存在，j就存在，
之后的j如果能取到vec[i] + j,则j(命名为jj)也存在，因为下一个判断是jj - vec[i]结果是否存在,jj相当于vec[i] + j; 记住，第二个循环是for(j = m; j >= vec[i]; --j),就相当于vec中的数是存在一个，for(j = vec[i]; j <= m; ++j) 相当于vec中的数可以无限的

eg:组成3
当选1
希望先选出以下组合,能组成111是因为之前组成了11,是同级，且用了上一个改变之后的状态，所以第二个循环是++
1
11
111
void zq() {
    std::vector<int> vec = {1, 2, 5};
    const auto m = 5;
    std::vector<int> res_vec;
    res_vec.assign(m + 1, 0);
    res_vec[0] = 1;

    for(auto i = 0; i < vec.size(); ++i){
        for(auto j = vec[i]; j <= m; ++j) {
            res_vec[j] = res_vec[j] + res_vec[j-vec[i]];
        }
    }
    return;
}
```
#### 单词拆分
* 给定一个非空字符串 s 和一个包含非空单词的列表 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。wordDict可无限使用
* s相当于背包容量，wordDict相当于物品，判断背包能否被刚好填满。物品要能放入，不仅长度够，字符串还要相同
* dp[i] 选到第i个s字符时，能否放满

#### noncopyable
```
构造函数中申请了空间，赋值构造函数若用默认的，会直接复制数据成员的地址，就有两个指针指向同一块空间
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
#### 设计模式
### 负责链
```
 const httpErrorHandler = (error) => {
   const errorStatus = error.response.status;
   if (errorStatus === 400) {
     console.log('你是不是提交了什么奇怪的东西？');
   }
   
   if (errorStatus === 401) {
     console.log('需要先登陆！');
   }
   
   if (errorStatus === 403) {
     console.log('是不是想偷摸干坏事？');
   }
   
   if (errorStatus === 404) {
     console.log('这里什么也没有...');
   }
};
```
1. 单一职责：就是只做一件事，上式把对所有错误的处理写在一个函数中，当需要增加或修改代码时，就需要阅读所有代码。
2. 开放封闭原则：对已写好的核心逻辑就不要去改动。但能因需要的增加而扩充原本功能。上式当增加需求时，会修改原来正常的逻辑，容易导致原本正常的代码出错.

封装后
```
class Chain {
  constructor(handler) {
    this.handler = handler;
    this.successor = null;
  }

  setSuccessor(successor) {
    this.successor = successor;
    return this;
  }

  passRequest(...args) {
    const result = this.handler(...args);
    if (result === 'next') {
      return this.successor && this.successor.passRequest(...args);
    }
    return result;
  }
}

好好感受下列代码，当功能扩展时，只要在原有代码的基础上加两行，几乎不可能造成原有逻辑的错误,因为根本没有动原来逻辑
连if(result === 'next')这个逻辑都没有暴露出来

const httpErrorHandler = (error) => {
  const chainRequest400 = new Chain(response400);
  const chainRequest401 = new Chain(response401);
  const chainRequest403 = new Chain(response403);
  const chainRequest404 = new Chain(response404);

  chainRequest400.setSuccessor(chainRequest401);
  chainRequest401.setSuccessor(chainRequest403);
  chainRequest403.setSuccessor(chainRequest404);

  chainRequest400.passRequest(error);
};

```
### 装饰器
1. 解决频繁修改的需要，即一个东西需要时常的进行打扮装饰。给原本的功能改增删。理解装饰这个词
```
const publishArticle = () => {
  console.log('发布文章');
};//本身只有身发文章的功能，以下两个装饰器增加了发现到微博和空间的功能

const publishWeibo = (publish) => (...args) => {
  publish(args);
  console.log('发 微博 动态');
};
const publishQzone = (publish) => (...args) => {
  publish(args);
  console.log('发 QQ空间 动态');
};

const publishArticleAndWeiboAndQzone = publishWeibo(publishQzone(publishArticle));
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
class ID
  : private noncopyable
{
public:
  /// Constructor.
  ID() {}
}

class A
    : public id{
        static ID id;
    }
std::list<ID*> keys;
keys.find(&A:id) != keys.end() //true时，说明A生成对象过
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

win
1.使用创建基本任务。

wt:

布阵：
1.其它阵上没有同车，同配件，同甲板
2.车存在，配件存在，数量《=孔位，甲板存在，布阵的位置对

key: 
pid


1.插入新元素排序,  
  1.key为新元素，排序完退出,使用传入的比较函数.

2.修改原有元素.
 1.不知道修改的元素，插入排序,排序有一次修改就退出

3.查找元素。
二分查找



插入新元素
修改元素
1.只接修改值，只需要sort
2.替换

构造：
1.空
2.obj数据   

1.当前积分段位
2.当前段位取新段位
3.段位的积分
[当前段位，]

dan:[
    [ 积分下限(必须从高到低配), { dan:当前段位, newDan:新赛季对应的段位}],
    [],
    ...
]
1-100
100 -200
200 - 300

1 100 200


1.game: playercollect.LegionActCbzf 全清
2.game: legion_act_cbzf  保留母服


调用gate.svr.send_to_game


创建一个svr，一个c_svr去连svr，  c_svr可取标准输入

1.定时查看配置md5，不一样就判断标记要不要执行
2.没有文件就清除定时器
{
    pid:
    proto:
    debug_done:
}

1.inital 读取配置，如果文件不存在，退出，
2.存在   创建定时器
3.如果为false  发现且 设为true,