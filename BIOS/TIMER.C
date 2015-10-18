#include "FIX.H"
#include <math.h>
#include <Windows.h>

LARGE_INTEGER start, frequency;

void timer_init() {
	QueryPerformanceCounter(&start);
	QueryPerformanceFrequency(&frequency);
}

void timer_close() {

}

void timer_set_rate(int count_val) {

}

void timer_set_function(void * function) {

}

fix timer_get_fixed_seconds() {
	LARGE_INTEGER end_time, elapsed_time;
	float seconds;

	QueryPerformanceCounter(&end_time);
	elapsed_time.QuadPart = end_time.QuadPart - start.QuadPart;
	seconds = (float)elapsed_time.QuadPart / (float)frequency.QuadPart;
	return fl2f(seconds);
}

fix timer_get_fixed_secondsX() {
	return timer_get_fixed_seconds();
}

fix timer_get_approx_seconds() {
	return timer_get_fixed_seconds();
}

long timer_get_millis() {
	LARGE_INTEGER end_time, elapsed_time;
	float milis;

	QueryPerformanceCounter(&end_time);
	elapsed_time.QuadPart = end_time.QuadPart - start.QuadPart;
	milis = (float)elapsed_time.QuadPart * 1000.0f / (float)frequency.QuadPart;
	return (long)roundf(milis);
}

void timer_set_joyhandler(void(*joy_handler)()) {

}
