#include "MysqlConn.h"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <mysql/mysql.h>
using namespace std;

MysqlConn::MysqlConn() {
  m_conn = mysql_init(nullptr);
  mysql_set_character_set(m_conn, "utf8");
}

MysqlConn::~MysqlConn() {
  if (m_conn != nullptr) {
    mysql_close(m_conn);
  }
  freeResult();
}
bool MysqlConn::connect(string user, string passwd, string dbName, string ip,
                        unsigned short port) {
  // 第二个参数是char*类型，所以要将string类型转换一下(还可以使用ip.data())
  // 第7个参数是本地套接字
  MYSQL *ptr =
      mysql_real_connect(m_conn, ip.c_str(), user.c_str(), passwd.c_str(),
                         dbName.c_str(), port, nullptr, 0);
  return ptr != nullptr;
}
bool MysqlConn::update(string sql) {
  if (mysql_query(m_conn, sql.c_str())) {
    // 返回0说明执行成功了
    return false;
  }
  return true;
}
bool MysqlConn::query(string sql) {
  freeResult();
  if (mysql_query(m_conn, sql.c_str())) {
    // 返回0说明执行成功了
    return false;
  }
  // 将查询结果保存到客户端
  m_result = mysql_store_result(m_conn);
  return true;
}
bool MysqlConn::next() {
  if (m_result != nullptr) {
    m_row = mysql_fetch_row(m_result); // 返回一级指针，指向某一行
    if (m_row != nullptr)
      return true;
  }
  return false;
}
string MysqlConn::value(int index) {
  // 列数
  int rowCount = mysql_num_fields(m_result);
  if (index >= rowCount || index < 0) {
    return string();
  }
  char *val = m_row[index];
  unsigned long length = mysql_fetch_lengths(
      m_result)[index]; // 函数返回的是当前记录里所有字段对应的长度
  // 传入length的原因是因为如果string碰到/0会自动结束，就无法将整个字段取出
  return string(val, length);
}
bool MysqlConn::transaction() {
  return mysql_autocommit(m_conn, false); // 设置为手动提交
}
// 提交事务
bool MysqlConn::commit() { return mysql_commit(m_conn); }
// 事务回滚
bool MysqlConn::rollback() { return mysql_rollback(m_conn); }
// 刷新起始的空闲时间点
void MysqlConn::refreshAliveTime() { m_alivetime = steady_clock::now(); }
// 计算连接存活的总时长
long long MysqlConn::getAliveTime() {
  nanoseconds res = steady_clock::now() - m_alivetime; // 精确到纳秒
  milliseconds millsec = duration_cast<milliseconds>(res);
  return millsec.count();
}

void MysqlConn::freeResult() {
  if (m_result) {
    mysql_free_result(m_result);
    m_result = nullptr;
  }
}
