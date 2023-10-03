# cpproutine

Coroutines system is very usefull in games. Is the way to control the flow of the program with asynchronous functions. I have provided this library with the main functionality of coroutines (with the same methodology as Unity).

# Requirements
* **C++20**
* **Compiler that supports C++20 features**

# Compilation Command
``` cpp
 g++ -std=c++20 -fcoroutines your_program_name.cpp -o your_output_name
```
You need to specify the **-fcoroutines** flag.

Note : On **Visual Studio 2019+** you just need to specify the project language to C++20 and you are done.

Include : You have to include only the **Coroutine.h** on your program (Note: **Coroutine.h** is depended from the other files on the **include\cpproutine**) and you are done.

* **Coroutine Functionality**
  * StartCoroutine(IEnumerator)
  * StopCoroutine(Coroutine)
  * Update()
* **Coroutine Types**
  * IEnumerator
* **Return Types**
  * WaitForSeconds
  * WaitUntil

This coroutine system is very capable of asynchronus multitasking. With the ability to **yield return** multiple times on each function.

# Example with WaitForSecond

``` cpp
  cpproutine::IEnumerator ExampleWaitForSecondsCoroutine()
  {
    std::cout << "Start Coroutine" << std::endl;
  
    yield_return cpproutine::NewReturnType<cpproutine::WaitForSeconds>(/*seconds*/);
  
    std::cout << "End Coroutine";
  }
```
# Example with WaitUntil

``` cpp
  cpproutine::IEnumerator ExampleWaitUntilCoroutine()
  {
    std::cout << "Start Coroutine" << std::endl;

    /* You can capture this if it needed */
    yield_return cpproutine::NewReturnType<cpproutine::WaitUntil>([&]() -> bool { return  /*condition*/; });
  
    std::cout << "End Coroutine";
  }
```

Use the **yield_return** keyword as you see.

# Example Starting / Stopping a coroutine

``` cpp
  cpproutine::Coroutine corutine;
  if(/*condition*/)
  {
    coroutine = cpproutine::CoroutineManager::StartCoroutine(ExampleWaitUntilCoroutine());
  }

  if(/*condition*/)
  {
    cpproutine::CoroutineManager::StopCoroutine(coroutine);
  }
```

# Example Updating coroutines

``` cpp
  /* Game Loop */
  while(true)
  {
    cpproutine::CoroutineManager::Update();
  }
```

You just have to manage coroutines witt **StartCoroutine()/StopCoroutine()** and **Update()** will do the job for you.
