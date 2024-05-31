# DataBase-HomeWork
数据库工程作业

数据库初始化见build.sql文件

点击Mixue.pro即可运行，构建时请选择MinGW 64-bit构建

Qt程序中通过ODBC连接至数据库，需提前在64位的ODBC中添加"用户DSN"，添加过程见如下连接：

https://blog.csdn.net/m0_38128647/article/details/89482413

注：1.添加DSN时，Data Source Name请写 "Mixue_64"。
2.还需在Qt 文件中所有含有conectsql()函数的部分，修改函数内部的连接参数，修改成你当前MySQL User名（默认为root），和其他连接的参数（如连接的TCP/IP，密码等）。