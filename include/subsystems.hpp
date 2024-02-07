#ifndef _SUBSYSTEMS_HPP_
#define _SUBSYSTEMS_HPP_

#define LAUNCHER_FREE_ZONE 28

extern int launcher_speed;
void moveLauncher(int power);
void breakLauncher();
void windUpLauncher();
void releaseLauncher();

void movePlough(int power);
void openPlough();
void closePlough();

void subSystemDebug();

#endif // SUBSYSTEMS_HPP_