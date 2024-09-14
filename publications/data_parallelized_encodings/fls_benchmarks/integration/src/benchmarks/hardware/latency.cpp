#include <atomic>
#include <iostream>
#include <algorithm>
#include <pthread.h>
#include <cstdint>

using namespace std;

uint64_t rdtsc() {
   uint32_t hi, lo;
   __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
   return static_cast<uint64_t>(lo)|(static_cast<uint64_t>(hi)<<32);
}
static void escape(void *p) {
  asm volatile("" : : "g"(p) : "memory");
}

#include <sys/time.h>

static inline double gettime(void) {
   struct timeval now_tv;
   gettimeofday (&now_tv, NULL);
   return ((double)now_tv.tv_sec) + ((double)now_tv.tv_usec)/1000000.0;
}

uint64_t n;
uint64_t* v;
atomic<bool> go(0);
uintptr_t rep;
unsigned ool;

static void* readThread(void *arg) {
   while (!go);
   uintptr_t threadNum = reinterpret_cast<uintptr_t>(arg);

#ifdef __linux__
   cpu_set_t cpuset;
   CPU_ZERO(&cpuset);
   CPU_SET(threadNum,&cpuset);
   pthread_t currentThread=pthread_self();
   if (pthread_setaffinity_np(currentThread,sizeof(cpu_set_t),&cpuset)!=0)
      throw;
#endif

   uint64_t start=rdtsc();

   uint64_t x[100];
   for (unsigned j=0; j<ool; j++)
      x[j]=j;
   for (uint64_t i=0; i<rep; i++) {
      for (unsigned j=0; j<ool; j++)
         x[j]=v[x[j]];
   }

   uint64_t sum=0;
   for (unsigned j=0; j<ool; j++)
      sum+=x[j];
   escape(&sum);

   // cout << threadNum << ": " << (rdtsc()-start)/(double)rep << " "<< sum << endl;

   return (void*) ((rdtsc()-start)/rep);
}

int main(int argc, char** argv) {
  if(argc != 5){
    cout << "Usage: " << argv[0] << " <threadCount> <Chain length> <Number of steps> <Number of outstanding loads>";
    return 0;
  }
   unsigned threadCount=atoi(argv[1]);
   n=atof(argv[2]);
   rep=atof(argv[3]);
   ool=atof(argv[4]);

#ifdef __linux__
   cpu_set_t cpuset;
   CPU_ZERO(&cpuset);
   CPU_SET(0,&cpuset);
   if (pthread_setaffinity_np(pthread_self(),sizeof(cpu_set_t),&cpuset)!=0)
      throw;
#endif

   uint64_t* v2=new uint64_t[n];
   for (uint64_t i=0; i<n;i++)
      v2[i]=i;
   random_shuffle(v2,v2+n);

   v=new uint64_t[n];
   for (uint64_t i=0; i<n;i++)
      v[v2[i]]=v2[(i+1)%n];

   //cout << "wait" << endl; std::string s; std::getline (std::cin,s);

   pthread_t threads[threadCount];
   for (unsigned i=0; i<threadCount; i++) {
      pthread_create(&threads[i], NULL, readThread, reinterpret_cast<void*>(i));
   }

   uint64_t times[threadCount];
   double start=gettime();
   go=1;
   for (unsigned i=0; i<threadCount; i++) {
      void *ret;
      pthread_join(threads[i], &ret);
      times[i]=(uint64_t)ret;
   }

   // cout << endl;
   cout << "final: " << ((ool*threadCount*64*rep)/(1024.0*1024.0*1024.0))/(gettime()-start) << "GB/s ";
   for (unsigned i=0; i<threadCount; i++) {
      cout << times[i] << " ";
   }
   cout << endl;
   return 0;
}
