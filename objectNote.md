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
1.能方便的实现链式操作
2.是一个构造函数，new promise(fun(resolve, reject))，会执行这个构造函数，返回一个promise对象, reslove和reject，这两个函数的实现是promise内部的，至于是否执行，取决于promise是否实现了调用逻辑.传给resolve/reject的参数，最终传给then\catch. promise中不调用reslove，则then不会执行，catch一样。
3.promise中不是自动异步，需要有异步的实现，异步中可调用resolve或reject
4.promise.all([]),可传入一些异步，等所以异步完成后，才会执行then，then函数参数接收到的参数是一个数组。
5.Promise有三个状态，分别为pending、fulfilled和rejected，且只能从pending到fulfilled或者rejected.
9.then方法中会返回新的promise

#### async/await
1.async 一个封装好的 Promise 对象，调用时得到一个 Promise 对象
2.如果一个函数声明定义时加了async，调用时，如果需要async的函数执行完后。再执行下面的代码，则调用前要加await 
```
async function test () {
    console.info('in');
};
上式相当于将函数内的逻辑加到promise中
function test () {
    return new Promise() {
        console.info('in');
    }
}
```

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