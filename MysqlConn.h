#pragma once
#include <iostream>
#include <mysql/mysql.h>
using namespace std;
class MysqlConn {

public:
  // 初始化数据库连接
  MysqlConn();
  // 释放数据库连接
  ~MysqlConn();
  // 连接数据库
  bool connect(string user, string passwd, string dbName, string ip,
               unsigned short port = 3306);
  // 更新数据库
  bool update(string sql);
  // 查询数据库
  bool query(string sql);
  // 遍历得到结果集
  // 遍历是一行一行的
  bool next();
  // 得到结果集中的字段值
  string value(int index);
  // 事务操作
  bool transaction();
  // 提交事务
  bool commit();
  // 事务回滚
  bool rollback();

private:
  MYSQL *m_conn = nullptr;
  MYSQL_RES *m_result = nullptr;
  MYSQL_ROW m_row = nullptr;
};
