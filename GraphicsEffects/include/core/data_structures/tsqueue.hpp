#pragma once
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif
#include <mutex>
#include <functional>
#include <deque>
#include <cassert>

#define SCOPED_LOCK std::scoped_lock lock(mQueueMutex)

template <typename T>
class TsQueue
{
public:
	// Default constructor
	TsQueue() = default;

	// Prevent copy construction because of the mutex
	TsQueue(const TsQueue<T>&) = delete;

	/// <summary>
	/// Gets a reference to the front item in the queue
	/// </summary>
	/// <returns>Item</returns>
	const T& Front()
	{
		SCOPED_LOCK;
		return mQueue.front();
	}

	/// <summary>
	/// Pushes a new item on the front of the queue
	/// </summary>
	/// <param name="item">Item</param>
	void Push(const T& item)
	{
		SCOPED_LOCK;
		mQueue.push(std::move(item));
	}

	/// <summary>
	/// Checks if the queue is empty
	/// </summary>
	/// <returns>Empty</returns>
	bool Empty()
	{
		SCOPED_LOCK;
		return mQueue.empty();
	}

	/// <summary>
	/// Get the number of items in the queue
	/// </summary>
	/// <returns>Count</returns>
	size_t Count()
	{
		SCOPED_LOCK;
		return mQueue.size();
	}

	/// <summary>
	/// Pops the item on the front of the queue
	/// </summary>
	/// <returns>Item</returns>
	T PopFront()
	{
		SCOPED_LOCK;
		T item = std::move(mQueue.front());
		mQueue.pop();
		return item;
	}

private:
	// Mutex guarding the queue
	std::mutex mQueueMutex;

	// Double ended queue
	std::queue<T> mQueue;
};

#undef SCOPED_LOCK
