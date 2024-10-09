#include "ConnectionPool.h"
#include "MysqlConn.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
using namespace std;
// 1.单线程：使用/不使用连接池
// 2.多线程：使用/不使用连接池
void opt1(int begin, int end) {
  for (int i = begin; i < end; ++i) {
    MysqlConn conn;
    conn.connect("root", "123456", "testdb", "127.0.0.1");
    char sql[1024] = {0};
    sprintf(
        sql,
        "insert into person(id,name,age,sex) values(%d, 'tom', 18, 'woman')",
        i);
    bool flag = conn.update(sql);
  }
}
void opt2(ConnectionPool *pool, int begin, int end) {
  for (int i = begin; i < end; ++i) {
    shared_ptr<MysqlConn> conn = pool->getConnection();
    char sql[1024] = {0};
    sprintf(
        sql,
        "insert into person(id,name,age,sex) values(%d, 'tom', 18, 'woman')",
        i);
    conn->update(sql);
  }
}
void test1() {
#if 0
  steady_clock::time_point begin = steady_clock::now();
  opt1(0, 5000);
  steady_clock::time_point end = steady_clock::now();
  auto length = end - begin;
//  非连接池，单线程，用时：80779889942纳秒,80779毫秒
  cout << "非连接池，单线程，用时：" << length.count() << "纳秒,"
       << length.count() / 1000000 << "毫秒" << endl;
#else
  ConnectionPool *pool = ConnectionPool::getConnectionPool();
  steady_clock::time_point begin = steady_clock::now();
  opt2(pool, 0, 5000);
  steady_clock::time_point end = steady_clock::now();
  auto length = end - begin;
  //  连接池，单线程，用时：66648935238纳秒,66648毫秒
  cout << "连接池，单线程，用时：" << length.count() << "纳秒,"
       << length.count() / 1000000 << "毫秒" << endl;

#endif
}

void test2() {
#if 1
  steady_clock::time_point begin = steady_clock::now();
  thread t1(opt1, 0, 1000);
  thread t2(opt1, 1000, 2000);
  thread t3(opt1, 2000, 3000);
  thread t4(opt1, 3000, 4000);
  thread t5(opt1, 4000, 5000);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  steady_clock::time_point end = steady_clock::now();
  auto length = end - begin;
  // 非连接池，多线程，用时：22496310814纳秒,22496毫秒
  cout << "非连接池，多线程，用时：" << length.count() << "纳秒,"
       << length.count() / 1000000 << "毫秒" << endl;

#else
  ConnectionPool *pool = ConnectionPool::getConnectionPool();
  steady_clock::time_point begin = steady_clock::now();
  thread t1(opt2, pool, 0, 1000);
  thread t2(opt2, pool, 1000, 2000);
  thread t3(opt2, pool, 2000, 3000);
  thread t4(opt2, pool, 3000, 4000);
  thread t5(opt2, pool, 4000, 5000);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  steady_clock::time_point end = steady_clock::now();
  auto length = end - begin;
  //  连接池，多线程，用时：20870625456纳秒,20870毫秒
  cout << "连接池，多线程，用时：" << length.count() << "纳秒,"
       << length.count() / 1000000 << "毫秒" << endl;

#endif
}

int query() {
  MysqlConn conn;
  conn.connect("root", "123456", "testdb", "127.0.0.1");
  string sql = "insert person(id,name,age,sex) values(4,'test',23,'man')";
  bool flag = conn.update(sql);
  cout << "flag value: " << flag << endl;

  sql = "select * from person";
  conn.query(sql);
  while (conn.next()) {
    for (int i = 0; i < 4; i++) {
      cout << conn.value(i) << ", ";
    }
    cout << endl;
  }

  return 0;
}
int main(int argc, char *argv[]) {
  test1();
  return 0;
}
