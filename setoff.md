**Вопросы к экзамену**

**Intrusive container**

Intrusive container does not store copies of passed objects, but it stores the objects themselves. The additional data needed to insert the object in the container must be provided by the object itself.  

-   None of them allocate memory, and correspondingly, more of them are  adorned with noexcept (except for the unordered containers, for which the allocator might throw, and for the associative containers, where the comparison object might throw).
-   Serveral functions take parameters by reference, instead of by const reference.
-   Functions taking InputIterator parameters modify the objects made available by those parameters.

http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0406r1.html

**Heterogeneous lookup**
http://cpptrivia.blogspot.com/2017/10/c14-heterogeneous-lookup-in-associative.html

**shared_ptr**  
**weak_ptr**

**(N)RVO**  
**Rvalue references**  
**Move semantics, _std::move_, reference collapsing**  
**Perfect forwarding, _std::forward_**

**Auto**  
**Lambdas**  
**_std::function_**  
**Type erasure**

**Variadic templates**  
**_std::bind_**

**_Signals_**  
**Reentrancy**

**Decltype(expr)**  
**Decltype(variable)**  
**Prvalue, xvalue, lvalue**

**_Nullptr_t_**

**void_t**

**Pointer-to-member**

**std::optional, differences with std::unique_ptr**  
**Pimpl**

**std::variant, usage**

**Types of parallelism**  
**Std::thread, join and detach**  
**Race condition**  
**Mutex**  
**_Spinlock_**  
**Futex(maybe optional)**  
**std::lock_guard**  
**Deadlock**  
**Atomic types**  
**std::condition_variable**  
**Spurious wakeups (fake wakeups)**  
**std::unique_lock**  
**Amdahl’s law**

**std::future + std::promise**  
**std::async**  
  
**Thread pool**  
**Thread_local**  
**Transactional memory (software and hardware)**  
**map, reduce, filter**  
**Asynchronous io (maybe Boost.Asio?)**  
**Sharing**  
**False sharing**  
**Message loop**  
**Fiber**(stackful coroutine? answer -> (it can be regarded as implementation of co’s concept, but in general this implementation use some ideas of stackfullness))

**std::transform**

**Push and pull strategies**

**coroutines(stackful and stackless)**

**C++11 new features:**  
**Rvalue references for *this**  
**On-declaration initialization of non-static members**  
**Enum classes**

**Uniform initialization**  
**std::initializer_list**

**Generalized attributes**

**Unicode**  
**Code point**  
**Code unit**  
**Utf-[8|16|32]**

**С++11 flaws:**  
**std::cbegin, std::cend**  
**Lambdas and move semantics**  
**Std::initializer_list and move semantics**

**Filesystems**  
**FAT**  
**Inode**  
**File descriptors**  
**File locks**  
**Creating inode without creating file in fs**

**PLT/GOT**
<!--stackedit_data:
eyJoaXN0b3J5IjpbLTE5OTEwNTUxNjQsMTI3OTE1NDI1NywtNj
MzNjkzNjE3LDIwMzQ1Mzk3NTMsLTIwODg3NDY2MTJdfQ==
-->