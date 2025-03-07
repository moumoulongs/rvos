#ifndef __PROC__
#define __PROC__

#include "types.h"
#include "param.h"
#include "spinlock.h"

// Saved registers for kernel context switches.
struct context {
	reg_t ra;
	reg_t sp;
  
	// callee-saved
	reg_t s0;
	reg_t s1;
	reg_t s2;
	reg_t s3;
	reg_t s4;
	reg_t s5;
	reg_t s6;
	reg_t s7;
	reg_t s8;
	reg_t s9;
	reg_t s10;
	reg_t s11;
  };

 // CPU 状态
struct cpu {
	struct proc *proc;		  // 当前进程运行在这个CPU上
	struct context context;	// 进程切换时保存的上下文
	int noff;				  // 中断嵌套深度
	int intena;				  // 是否允许中断
};

extern struct cpu cpus[NCPU];

struct trapframe {
	/*   0 */ reg_t kernel_satp;   // kernel page table
	/*   8 */ reg_t kernel_sp;     // top of process's kernel stack
	/*  16 */ reg_t kernel_trap;   // usertrap()
	/*  24 */ reg_t epc;           // saved user program counter
	/*  32 */ reg_t kernel_hartid; // saved kernel tp
	/*  40 */ reg_t ra;
	/*  48 */ reg_t sp;
	/*  56 */ reg_t gp;
	/*  64 */ reg_t tp;
	/*  72 */ reg_t t0;
	/*  80 */ reg_t t1;
	/*  88 */ reg_t t2;
	/*  96 */ reg_t s0;
	/* 104 */ reg_t s1;
	/* 112 */ reg_t a0;
	/* 120 */ reg_t a1;
	/* 128 */ reg_t a2;
	/* 136 */ reg_t a3;
	/* 144 */ reg_t a4;
	/* 152 */ reg_t a5;
	/* 160 */ reg_t a6;
	/* 168 */ reg_t a7;
	/* 176 */ reg_t s2;
	/* 184 */ reg_t s3;
	/* 192 */ reg_t s4; 
	/* 200 */ reg_t s5;
	/* 208 */ reg_t s6;
	/* 216 */ reg_t s7;
	/* 224 */ reg_t s8;
	/* 232 */ reg_t s9;
	/* 240 */ reg_t s10;
	/* 248 */ reg_t s11;
	/* 256 */ reg_t t3;
	/* 264 */ reg_t t4;
	/* 272 */ reg_t t5;
	/* 280 */ reg_t t6;
  };

enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// 进程状态
struct proc {
	struct spinlock lock;

	// p->lock must be held when using these:
	enum procstate state; // 进程状态
	void *chan;			  // 如果非空，进程正在等待chan
	int killed;			  // 如果非0，进程应该被杀死
	int xstate;			  // 返回给父进程waite函数的退出状态
	int pid;			  // 进程ID

	// wait_lock must be held when using these:
	struct proc *parent; // 父进程

	//进程私有，无需持锁
	uint64_t stack; // 进程内核栈
	uint64_t sz;	 // 进程内存大小
	struct trapframe *trapframe; // data page for trampoline.S
	struct context context; // 进程上下文
	// 文件系统没有实装
	// struct file *ofile[NOFILE];  // 打开的文件
  	// struct inode *cwd;           // 当前目录
	char name[16]; // 进程名字
};


#endif