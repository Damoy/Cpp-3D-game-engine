#include "Timer.h"


Timer::Timer(unsigned long delayy)
	:	delay(delayy), alive(false), 
		startTime(0L), currentTime(0L), leftTime(0L), spentTime(0L){
}

Timer::~Timer(){
}

void Timer::update() {
	if (!alive) return;
	currentTime = clock();
	spentTime = currentTime - startTime;
	leftTime = delay - spentTime;
	checkState();
}

void Timer::checkState() {
	if (leftTime <= 0L || leftTime > delay)
		alive = false;
}

unsigned long Timer::time() const {
	return static_cast<unsigned long>(clock());
}

void Timer::start() {
	startTime = time();
	alive = true;
}

unsigned long Timer::getSecsTimeElapsed() {
	return static_cast<unsigned long>(getMillisTimeElapsed() / 1000.0f);
}

unsigned long Timer::getMillisTimeElapsed() {
	update();
	return spentTime;
}

unsigned long Timer::getSecsTimeLeft() {
	return static_cast<unsigned long>(getMillisTimeLeft() / 1000.0f);
}

unsigned long Timer::getMillisTimeLeft() {
	update();
	return leftTime;
}

void Timer::reset() {
	currentTime = 0L;
	startTime = 0L;
	leftTime = 0L;
	spentTime = 0L;
	alive = true;
}

bool Timer::isStopped() {
	update();
	return !alive;
}




