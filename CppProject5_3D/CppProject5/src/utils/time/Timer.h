#pragma once

#include <ctime>
#include <cstdlib>

/*
	A Timer class.
	Used for entity generation mainly.
	Initialized at construction, needs to be started to be active.

	eg:
		// 5000 ms
		Timer timer(5000);
		// waits 1000 ms
		unsigned long timeLeft = timer->getSecsTimeLeft();
		// prints 4
		std::cout << timeLleft;
*/
class Timer {
private:
	// the start time
	unsigned long startTime;
	// the curren time
	unsigned long currentTime;
	// the initial delay
	unsigned long delay;
	// the left time in ms
	unsigned long leftTime;
	// the passed time in ms
	unsigned long spentTime;
	// is the timer still alive
	bool alive;

	// updates the times
	void update();
	// check the timer state
	void checkState();
	// get the current time
	unsigned long time() const;

public:
	Timer(unsigned long delay);
	~Timer();

	// Starts the timer
	void start();
	// Resets the timer
	void reset();
	// Is the timer stopped
	bool isStopped();

	// Time getters
	unsigned long getSecsTimeElapsed();
	unsigned long getMillisTimeElapsed();
	unsigned long getSecsTimeLeft();
	unsigned long getMillisTimeLeft();

};

