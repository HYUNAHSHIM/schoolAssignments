#include "world_clock.h"


WorldClock::WorldClock() {

}

WorldClock::WorldClock(int hour, int minute, int second) {

}

void WorldClock::Tick(int seconds = 1) {

}

// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
bool WorldClock::SetTime(int hour, int minute, int second) {

}

static bool WorldClock::LoadTimezoneFromFile(const string& file_path) {

}

static void WorldClock::SaveTimezoneToFile(const string& file_path) {

}

static void WorldClock::AddTimezoneInfo(const string& city, int diff) {

}

// �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
bool WorldClock::SetTimezone(const string& timezone) {

}

int WorldClock::hour() const {

}
int WorldClock::minute() const {

}
int WorldClock::second() const {

}
