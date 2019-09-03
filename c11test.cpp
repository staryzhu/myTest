#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <stdio.h>

using namespace std;

struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    // 注意：此处非虚析构函数 OK
    ~Base() { std::cout << "  Base::~Base()\n"; }
};

struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};

void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p; // 线程安全，虽然自增共享的 use_count
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "local pointer in a thread:\n"
                  << "  lp.get() = " << lp.get()
                  << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}

static int init_destory_cnt = 0;
class cptr {
public:
  cptr() { aaa = 10; std::cout << "init cptr : " << init_destory_cnt ++ << std::endl;}
  cptr(const cptr& cr) {std::cout << "copy cptr : " << init_destory_cnt ++ << std::endl;};
  cptr(const cptr&& cr) {std::cout << "move copy cptr : " << init_destory_cnt ++ << std::endl;};
  ~cptr() { std::cout << "destory cptr : " << init_destory_cnt++ << endl;printf("aaa : %x\n", &aaa);}
private:
  int aaa;
};
#define D(...)                                                                 \
    do {                                                                       \
        printf("%s:%s:%d:\t", __FILE__, __FUNCTION__, __LINE__);               \
        printf(__VA_ARGS__);                                                   \
        printf("\n");                                                          \
    } while (0);

void testPTR() {
  shared_ptr<cptr> sptr = make_shared<cptr>();
  std::cout << "start testing ptr " << endl;
  cptr *pp = new cptr();
  std::shared_ptr<cptr> p(pp);
  cout << "pointer : " << p.use_count() << endl;
  shared_ptr<cptr> q(pp);
  cout << "pointer : " << p.use_count() << endl;
  shared_ptr<cptr> z = p;
  cout << "pointer : " << p.use_count() << endl;

  shared_ptr<cptr> x(p);
  cout << "pointer : " << p.use_count() << endl;
  //delete pp;
 // delete pp;
  D("who : %d", p.use_count());
}
#define TEST_

int main()
{
#ifdef TEST_
  testPTR();
  return 0;
#else
    std::shared_ptr<Base> p = std::make_shared<Derived>();

    std::cout << "Created a shared Derived (as a pointer to Base)\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    std::thread t1(thr, p), t2(thr, p), t3(thr, p);
    p.reset(); // 从 main 释放所有权
    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    t1.join(); t2.join(); t3.join();
    std::cout << "All threads completed, the last one deleted Derived\n";
#endif
}
