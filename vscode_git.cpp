vscode中使用git
1.在本地创建git管理文件
a.创建文件夹，用vscode打开，点初始化git，此时本地就有了一个git管理的文件夹，只是还没有同步到远程。

2.提交到git保存，还没有推到远程。
a.暂存更改，b.输入提交log，c.点提交.d.不想要时可点撤销上次提交。

3.创建分支(git branch)
a.相当于复制了一份源代码，各分支的操作不会互相影响,创建后，当前的分支是新分支。
b.git checkout 可切换分支

4.
a.查看项目的分支们(包括本地和远程) git branch -a
b.删除本地分支 git branch -d <BranchName>
c.删除远程分支 git push origin --delete <BranchName>

5.在git文件列表中，单击一个未提交更改的文件，就会打开两个窗口来显示变更的内容。

6.将本地的文件连接到远程的某个仓库
a.git remote add origin https://github.com/xuanhun/vscode.git
