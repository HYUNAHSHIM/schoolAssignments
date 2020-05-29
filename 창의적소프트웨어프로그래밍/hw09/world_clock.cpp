#include "world_clock.h"


WorldClock::WorldClock() {

}

WorldClock::WorldClock(int hour, int minute, int second) {

}

void WorldClock::Tick(int seconds = 1) {

}

// 잘못된 값 입력시 false 리턴하고 원래 시간은 바뀌지 않음.
bool WorldClock::SetTime(int hour, int minute, int second) {

}

static bool WorldClock::LoadTimezoneFromFile(const string& file_path) {

}

static void WorldClock::SaveTimezoneToFile(const string& file_path) {

}

static void WorldClock::AddTimezoneInfo(const string& city, int diff) {

}

// 잘못된 값 입력시 false 리턴하고 원래 시간은 바뀌지 않음.
bool WorldClock::SetTimezone(const string& timezone) {

}

int WorldClock::hour() const {

}
int WorldClock::minute() const {

}
int WorldClock::second() const {

}
