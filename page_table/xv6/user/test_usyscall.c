#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/riscv.h"   
#include "kernel/memlayout.h"

#define PASS(name) printf("  [PASS] %s\n", name)
#define FAIL(name) do { printf("  [FAIL] %s\n", name); exit(1); } while(0)

void test_basic() {
  printf("\n--- Basic test: comparing syscall and usyscall ---\n");
  int a = getpid();
  int b = ugetpid();

  printf("syscall getpid() = %d\n", a);
  printf("usyscall ugetpid() = %d\n", b);

  if (a != b)
    FAIL("basic pid mismatch");

  PASS("basic");
}

void test_repeat() {
  printf("\n--- Repeat test: calling ugetpid() 100,000 times ---\n");
  int pid = ugetpid();
  int i;

  for (i = 0; i < 100000; i++) {
    if (ugetpid() != pid)
      FAIL("repeat inconsistent");
  }

  printf("Checked %d iterations. PID stably remains: %d\n", i, pid);

  PASS("repeat");
}

void test_fork() {
  printf("\n--- Fork test: checking usyscall in child process ---\n");
  int parent = ugetpid();
  printf("Parent PID before fork: %d\n", parent);

  int pid = fork();

  if (pid < 0)
    FAIL("fork failed");

  if (pid == 0) {
    int child = ugetpid();
    printf("Child process executing. My PID: %d, Parent PID was: %d\n", child, parent);

    if (child == parent)
      FAIL("fork child pid same as parent");

    PASS("fork child");
    exit(0);
  }
  else {
    wait(0);
    printf("Parent process resumed after child exit.\n");
    PASS("fork parent");
  }
}

void test_exec() {
  printf("\n--- Exec test: checking process image replacement ---\n");
  printf("Forking to test exec...\n");
  int pid = fork();

  if (pid == 0) {
    char* argv[] = { "echo", "exec successful and outputting this string!", 0 };
    exec("echo", argv);

    FAIL("exec failed");
  }
  else {
    wait(0);
    PASS("exec");
  }
}

void test_null() {
  printf("\n--- Null/Address test: verifying USYSCALL mapped page ---\n");
  struct usyscall* u = (struct usyscall*)USYSCALL;

  if (u == 0)
    FAIL("null pointer");

  printf("USYSCALL mapped at address: %p\n", u);
  printf("Value of u->pid inside mapped page: %d\n", u->pid);

  if (u->pid <= 0)
    FAIL("invalid pid value");

  PASS("null check");
}

void test_stress() {
  int num_forks = 5;
  printf("\n--- Stress test: testing with %d concurrent forks ---\n", num_forks);

  for (int i = 0; i < num_forks; i++) {
    int pid = fork();

    if (pid == 0) {
      int cpid = ugetpid();
      if (cpid <= 0)
        FAIL("stress invalid pid");
      printf("Stress child %d created with PID: %d\n", i + 1, cpid);
      exit(0);
    }
  }

  for (int i = 0; i < num_forks; i++)
    wait(0);

  printf("All %d children executed and reaped cleanly.\n", num_forks);
  PASS("stress");
}

void test_write_protect() {
  printf("\n--- Write protect test (EXPECTING KERNEL TRAP / CRASH) ---\n");
  struct usyscall* u = (struct usyscall*)USYSCALL;

  printf("Attempting to write value 1234 to read-only address %p...\n", &u->pid);

  u->pid = 1234;

  FAIL("write protection failed (Did not crash!)");
}

void test_out_of_bound() {
  printf("\n--- Out-of-bound test (EXPECTING KERNEL TRAP / CRASH) ---\n");

  volatile char* p = (volatile char*)USYSCALL;

  char x = p[0];      
  (void)x;          

  printf("Read byte at offset 0 successfully.\n");

  printf("Attempting to read byte at offset 4096 (address %p)...\n", p + 4096);
  printf("If you see this value, it's a BUG: %d\n", p[4096]);

  FAIL("out-of-bound failed (Did not crash!)");
}
int main() {
  printf("==== USYSCALL TEST START ====\n");

  test_basic();
  test_repeat();
  test_null();
  test_fork();
  test_exec();
  test_stress();

  printf("\n==== ALL SAFE TESTS PASSED ====\n");

  printf("\nNOTE:\n");
  printf("- Run separately to verify protection mechanisms:\n");
  printf("  test_write_protect();\n");
  printf("  test_out_of_bound();\n");

  // Không chạy mặc định vì sẽ crash kernel/user process
  //test_write_protect();
  //test_out_of_bound();

  printf("\n==== DONE ====\n");

  exit(0);
}
