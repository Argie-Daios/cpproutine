#include "Coroutine.h"

class ExampleClass
{
public:
	ExampleClass() = default;
	ExampleClass(int value) { m_ExampleValue = value; }

	cpproutine::IEnumerator ExampleWaitForSecondsCoroutine()
	{
		std::cout << "Start Coroutine" << std::endl;

		yield_return cpproutine::NewReturnType<cpproutine::WaitForSeconds>(7.0f);

		std::cout << "End Coroutine";
	}

	cpproutine::IEnumerator ExampleWaitUntilCoroutine()
	{
		std::cout << "Start Coroutine" << std::endl;

		yield_return cpproutine::NewReturnType<cpproutine::WaitUntil>([this]() -> bool { return m_ExampleValue > 10; });

		std::cout << "Continue" << std::endl;

		yield_return cpproutine::NewReturnType<cpproutine::WaitUntil>([this]() -> bool { return m_ExampleValue > 20; });

		std::cout << "End Coroutine";
	}

	int& GetValue() { return m_ExampleValue; }

private:
	int m_ExampleValue = 0;
};

int main()
{
	ExampleClass example(5);

	cpproutine::CoroutineManager::StartCoroutine(example.ExampleWaitUntilCoroutine());

	while (true)
	{
		cpproutine::CoroutineManager::Update();
	}

	return 0;
}