// @copyright 2017-2018 zzu_softboy <zzu_softboy@163.com>
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Created by softboy on 2017/01/25.

#include "pdk/kernel/internal/CoreApplicationPrivate.h"
#include "pdk/kernel/EventdispatcherUnix.h"
#include "pdk/base/os/thread/internal/ThreadPrivate.h"
#include "pdk/global/PlatformDefs.h"

#include <sched.h>
#include <errno.h>

#ifdef PDK_OS_BSD4
#include <sys/sysctl.h>
#endif
#ifdef PDK_OS_VXWORKS
#  if (_WRS_VXWORKS_MAJOR > 6) || ((_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR >= 6))
#    include <vxCpuLib.h>
#    include <cpuset.h>
#    define PDK_VXWORKS_HAS_CPUSET
#  endif
#endif // PDK_OS_VXWORKS

#ifdef PDK_OS_HPUX
#include <sys/pstat.h>
#endif // PDK_OS_HPUX

#if defined(PDK_OS_LINUX) && !defined(PDK_LINUXBASE)
#include <sys/prctl.h>
#endif

#if defined(PDK_OS_LINUX) && !defined(SCHED_IDLE)
// from linux/sched.h
# define SCHED_IDLE    5
#endif

#if defined(PDK_OS_DARWIN) || !defined(PDK_OS_OPENBSD) && defined(_POSIX_THREAD_PRIORITY_SCHEDULING) && (_POSIX_THREAD_PRIORITY_SCHEDULING-0 >= 0)
#define PDK_HAS_THREAD_PRIORITY_SCHEDULING
#endif

namespace pdk {
namespace os {
namespace thread {

PDK_STATIC_ASSERT(sizeof(pthread_t) <= sizeof(pdk::HANDLE));
const int THREAD_PRIORITY_RESET_FLAG = 0x80000000;
#if defined(PDK_OS_LINUX) && defined(__GLIBC__) && (defined(PDK_CC_GNU) || defined(PDK_CC_INTEL)) && !defined(PDK_LINUXBASE)
/* LSB doesn't have __thread, https://lsbbugs.linuxfoundation.org/show_bug.cgi?id=993 */
#define HAVE_TLS
#endif

static thread_local internal::ThreadData *sg_currentThreadData = nullptr;
static pthread_once_t sg_currentThreadDataOnce = PTHREAD_ONCE_INIT;
static pthread_key_t sg_currentThreadDataKey;

namespace {

void destroy_current_thread_data(void *p)
{
}

void create_current_thread_data_key()
{
}

void destroy_current_thread_data_key()
{
}

PDK_DESTRUCTOR_FUNCTION(destroy_current_thread_data_key)

static internal::ThreadData *get_thread_data()
{
}

static void set_thread_data(internal::ThreadData *data)
{
}

static void clear_thread_data()
{
}

template <typename T>
static typename std::enable_if<std::is_integral<T>::value, pdk::HANDLE>::type
toPdkHandleType(T id)
{
}

template <typename T>
static typename std::enable_if<std::is_integral<T>::value, T>::Type
fromPdkHandle(pdk::HANDLE id)
{
}

template <typename T>
static typename std::enable_if<std::is_pointer<T>::value>::type
toPdkHandle(T id)
{
}

template <typename T>
static typename std::enable_if<std::is_pointer<T>::value, T>::Type
fromPdkHandle(pdk::HANDLE id)
{
}

#if (defined(PDK_OS_LINUX) || defined(PDK_OS_MAC) || defined(PDK_OS_QNX))
void set_current_thread_name(pthread_t threadId, const char *name)
{
}
#endif

timespec make_timespec(time_t secs, long nsecs)
{
}

#ifdef PDK_HAS_THREAD_PRIORITY_SCHEDULING
// Does some magic and calculate the Unix scheduler priorities
// sched_policy is IN/OUT: it must be set to a valid policy before calling this function
// sched_priority is OUT only
static bool calculate_unix_priority(int priority, int *schedPolicy, int *schedPriority)
{
}
#endif

}

namespace internal {

void ThreadData::clearCurrentThreadData()
{
}

ThreadData *ThreadData::current(bool createIfNecessary)
{
}

void AdoptedThread::init()
{
}

extern "C" {
using PdkThreadCallback = void* (*)(void*);
}

void ThreadPrivate::createEventDispatcher(ThreadData *data)
{
}

void *ThreadPrivate::start(void *arg)
{
}

void ThreadPrivate::finish(void *arg)
{
}

} // internal

pdk::HANDLE Thread::getCurrentThreadId() noexcept
{
}

#if defined(PDK_LINUXBASE) && !defined(_SC_NPROCESSORS_ONLN)
// LSB doesn't define _SC_NPROCESSORS_ONLN.
#  define _SC_NPROCESSORS_ONLN 84
#endif

int Thread::getIdealThreadCount() noexcept
{
}

void Thread::yieldCurrentThread()
{
}

void Thread::sleep(unsigned long secs)
{
}

void Thread::msleep(unsigned long msecs)
{

}

void Thread::usleep(unsigned long usecs)
{

}

void Thread::start(Priority priority)
{
}

void Thread::terminate()
{
}

bool Thread::wait(unsigned long time)
{
}

void Thread::setTerminationEnabled(bool enabled)
{
}


// Caller must lock the mutex
void ThreadPrivate::setPriority(Thread::Priority threadPriority)
{
}

} // thread
} // os
} // pdk
