#include "ConnectionPool.h"
#include "MysqlConn.h"
#include <chrono>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <json.h>
#include <memory>
#include <mutex>
#include <thread>
using namespace std;
using namespace Json;
ConnectionPool *ConnectionPool::getConnectionPool() {
  static ConnectionPool pool;
  return &pool;
}

bool ConnectionPool::parseJsonFile() {
  ifstream ifs("dbconf.json");
  Reader rd;
  Value root;
  rd.parse(ifs, root); // root是传出参数
  if (root.isObject()) {
    m_ip = root["ip"].asString();
    m_port = root["port"].asInt();
    m_user = root["username"].asString();
    m_passwd = root["passwd"].asString();
    m_dbName = root["dbName"].asString();
    m_minSize = root["minSize"].asInt();
    m_maxSize = root["maxSize"].asInt();
    m_maxIdleTime = root["maxIdleTime"].asInt();
    m_timeout = root["timeout"].asInt();
    cout << m_ip << ' ' << m_port << ' ' << m_user << ' ' << m_passwd << ' '
         << m_dbName << ' ' << endl;
    return true;
  }
  return false;
}
void ConnectionPool::addConnection() {

  MysqlConn *conn = new MysqlConn;
  conn->connect(m_user, m_passwd, m_dbName, m_ip, m_port);
  conn->refreshAliveTime();
  m_connectionQ.push(conn);
}
// 生产连接，连接池中连接过少时生产新的连接
void ConnectionPool::produceConnection() {
  while (true) {
    unique_lock<mutex> locker(m_mutexQ);
    while (m_connectionQ.size() >= m_minSize &&
           m_connectionQ.size() <= m_maxSize) { // 判断连接池里的连接是否够用
      m_cond.wait( // 正常情况下不需要生产，所以阻塞住
          locker); // 线程阻塞时会自动把互斥锁解锁，释放时会重新抢占互斥锁资源
    }
    addConnection();
    m_cond.notify_all();
  }
}
// 回收数据库连接，数据库连接池中连接太多时回收
void ConnectionPool::recycleConnection() {
  while (true) {
    this_thread::sleep_for(chrono::milliseconds(500));
    lock_guard<mutex> locker(m_mutexQ);
    while (m_connectionQ.size() > m_minSize) {
      // 为什么要取队头，队头的元素是先进的，空闲时间最长
      MysqlConn *conn = m_connectionQ.front();
      if (conn->getAliveTime() >= m_maxIdleTime) {
        m_connectionQ.pop();
        delete conn;
      } else {
        break; // 空闲时间最长的连接都没有超过最大空闲时长，直接break
      }
    }
  }
}

shared_ptr<MysqlConn> ConnectionPool::getConnection() {
  unique_lock<mutex> locker(m_mutexQ);
  while (m_connectionQ.empty()) {
    if (cv_status::timeout ==
        m_cond.wait_for(locker, chrono::milliseconds(m_timeout))) {
      if (m_connectionQ.empty()) {
        continue;
      }
    }
  }
  // 连接用完后放回连接池里
  // 地址回收，而不是把地址析构
  shared_ptr<MysqlConn> connptr(m_connectionQ.front(), [this](MysqlConn *conn) {
    lock_guard<mutex> locker(m_mutexQ);
    conn->refreshAliveTime(); // 连接用完，开始空闲，更新空闲的时间点
    m_connectionQ.push(
        conn); // 并不是要销毁内存，而是放到数据库连接池对应的队列里
  });
  m_connectionQ.pop();
  m_cond.notify_all();
  return connptr;
}

ConnectionPool::~ConnectionPool() {
  while (!m_connectionQ.empty()) {
    MysqlConn *conn = m_connectionQ.front();
    m_connectionQ.pop();
    delete conn;
  }
}

ConnectionPool::ConnectionPool() {
  // 加载配置文件
  if (!parseJsonFile()) {
    return;
  }
  for (int i = 0; i < m_minSize; i++) {
    addConnection();
  }
  thread producer(&ConnectionPool::produceConnection, this);
  thread recycler(&ConnectionPool::recycleConnection, this);
  producer.detach();
  recycler.detach();
}
