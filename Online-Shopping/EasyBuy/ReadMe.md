# 在线电商购物网站

EasyBuy 易买网

------------------------------

生产实习样例项目。Java 构建。

老师配置：

- JDK 1.8
- MySQL 5.5

自用配置：

- open-jdk 9
- MariaDB 10

---------------------

## package

biz.impl：业务层内容存放的位置 

dao.impl：数据库访问层内容存放位置 

test：临时测试 

util：所有工具 

web：servlet控制内容 

entity：对应表信息的实体类

## database.properties

127.0.0.1: 机的回环地址 

url: 连接数据库的地址 

3306：数据库端口号 

url = jdbc:mysql://127.0.0.1:3306/easybuy 连接数据库的驱动 

driver = com.mysql.jdbc.Driver 

username = root 

password = root (默默吐槽老师推荐配置。。。)

## 项目搭建步骤

1. 分析项目需求 

2. 数据库设计并创建（三大范式） 

3. 数据库关系设计（类型设计） 

4. 项目版本选择控制（环境搭建） 

5. 准备项目需要的包或库 

6. 项目准备（Web项目） 

7. 数据库连接测试（创建database.properties和DataSourceUtil） 

8. 表映射的实体类设计（entity包下的实体类） 

9. 数据库操作层设计（BaseDaoImpl和相应的 实体类DAO层操作创建---需要验证非空的工具类和分页数据的工具类）



#### 什么是DAO

1. Data Access Object（数据存取对象） 
2. 位于业务逻辑和持久化数据之间 3.实现对持久化数据的访问

## JDBC操作步骤

1. 加载驱动（加载驱动包，mysql-connector-java） DataSourceUtil --> Class.forName 
2. 通过驱动管理员，建立 Java 和 MySQL 之间的连接（获取连接对象） DataSourceUtil  --> DriverManager.getConnection 
3. 通过链接获得预编译对象 PrePareStatement（翻译 SQL 语句给 MySQL 数据库） BaseDaoImpl --> connection.prepareStateMent(sql) 
4. 通过 PrePareStatement 对象，将 SQL 语句中的 '?' 占位符进行填充（保证 SQL 语句翻译的正确性和完整性） 
5. mysql数据库执行翻译后的sql语句，并得到相应结果 （增删改的结果为int类型，结果要大于0；查询的结果为ResultSet，需要将rs转化为相应的user对象） UserDao.impl --> count=this.executeUpdate(sql,params) rs=this.executeQuery(sql,params)
6. 处理结果信息（增删改的大于0，查询的 ResultSet） 
7. 关闭资源