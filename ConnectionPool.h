#pragma once
#include <MysqlConn.h>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
using namespace std;
/*
 *因为数据库连接池对象只有一个，所以创建单例模式
 *
 */
class ConnectionPool {
public:
  ConnectionPool(const ConnectionPool &pool) = delete;
  ConnectionPool &operator=(const ConnectionPool &pool) = delete;
  static ConnectionPool *getConnectionPool();
  shared_ptr<MysqlConn> getConnection();
  ~ConnectionPool();

private:
  ConnectionPool();
  bool parseJsonFile();
  void produceConnection(); // 生产数据库连接
  void recycleConnection(); // 销毁数据库连接
  void addConnection();     // 建立新的连接

  string m_ip;
  string m_user;
  string m_passwd;
  string m_dbName;
  unsigned short m_port;
  int m_minSize;
  int m_maxSize;
  int m_timeout;
  int m_maxIdleTime;
  // 存储的是若干个连接
  queue<MysqlConn *> m_connectionQ;
  mutex m_mutexQ;
  condition_variable m_cond;
};
