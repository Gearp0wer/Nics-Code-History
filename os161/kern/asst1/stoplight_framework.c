/**
 * This file contains the implementation of all the helper functions provided
 * to you for implementing stoplight.c.
 * 
 * Note that when testing your code, we will be using a fresh copy of this file.
 * You should ONLY change stoplight.c and synch.c in order to solve the synchronization
 * problem assignment.
 * 
 * That said, definitely go ahead and add custom tests to stoplight_custom function
 * at the bottom of this file. We will not use your custom tests during grading,
 * but checking your code more thoroughly can only ever be a good idea!
 * 
 * Feel free to read through the code in this file; it mostly consists of printing
 * the approach()/enter()/leave()/transfer() messages with a well-defined format,
 * plus the definition for each of the provided test cases.
 */

#include "stoplight_framework.h"

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>

#include <synch.h>

/**
 * The vehicle information tracked by the framework for each test case.
 * 
 * Used to provide get_vehicle_route(), get_vehicle_type(), and
 * get_vehicle_turn_direction() for each vehicle.
 */
struct vehicle {
	int route;
	int type;
	int turn_direction;
};

/**
 * A static array of all vehicles for a test case.
 * 
 * As such, each test case may only have up to 256 vehicles.
 */
static struct vehicle all_vehicles[256];

/* Vehicle info functions -- very straightforward, just returns
 * info from the vehicle info array. */

int
get_vehicle_route(unsigned long vehicle) {
	return all_vehicles[vehicle].route;
}

int
get_vehicle_type(unsigned long vehicle) {
	return all_vehicles[vehicle].type;
}

int
get_vehicle_turn_direction(unsigned long vehicle) {
	return all_vehicles[vehicle].turn_direction;
}

/**
 * Returns a character representing the route name for
 * a given route. E.g. route 0 is A.
 */
static char
route_name_char(int direction) {
	return 'A' + direction;
}

/**
 * Returns a string representing the intersection name for
 * a given intersection. E.g. intersection 0 is AB.
 */
static const char*
intersection_name_string(int intersection) {
	switch(intersection) {
		case 0: return "AB";
		case 1: return "BC";
		case 2: return "CA";
		default: return "unknown";
	}
}

/**
 * Returns a string representing the vehicle type for a given
 * vehicle. Note that you pass in the vehicle number, not the
 * type.
 */
static const char*
vehicle_string(unsigned long vehicle) {
	switch(get_vehicle_type(vehicle)) {
		case 0: return "Truck ";
		case 1: return "Car   ";
		default: return NULL;
	}
}

/**
 * Returns a string representing e.g. a value from get_vehicle_turn_direction().
 */
static const char*
turn_name_string(int turn) {
	switch(turn) {
		case 1: return "left ";
		case 0: return "right";
		default: return "unknown";
	}
}

#define VEHICLE (&all_vehicles[vehicle])

#define COMMON_MESSAGE "%s %3lu from %c turning %s"
#define COMMON_KPRINTF_ARGS vehicle_string(vehicle), vehicle, route_name_char(VEHICLE->route), turn_name_string(VEHICLE->turn_direction)

/** Prints the enter() message for a vehicle entering an intersection. */
static void
print_enter(unsigned long vehicle, int intersection) {
	kprintf(COMMON_MESSAGE ": enter(%s)\n", COMMON_KPRINTF_ARGS, intersection_name_string(intersection));
}

/** Prints the leave() message for a vehicle leaving an intersection. */
static void
print_leave(unsigned long vehicle, int intersection) {
	kprintf(COMMON_MESSAGE ": leave(%s)\n", COMMON_KPRINTF_ARGS, intersection_name_string(intersection));
}

/** Prints the approach() message for a vehicle approaching its route. */
static void
print_approach(unsigned long vehicle) {
	kprintf(COMMON_MESSAGE ": approach()\n", COMMON_KPRINTF_ARGS);
}

/** Prints the transfer() message for a vehicle transferring between two intersections. */
static void
print_transfer(unsigned long vehicle, int from, int to) {
	kprintf(COMMON_MESSAGE ": transfer(%s, %s)\n", COMMON_KPRINTF_ARGS, intersection_name_string(from), intersection_name_string(to));
}

/* Stoplight action functions -- these just consist of printing a message.
 * They could in theory do other logic, but for now, they do not. */

void
approach(unsigned long vehicle) {
	print_approach(vehicle);
}

void
enter(unsigned long vehicle, int intersection) {
	print_enter(vehicle, intersection);
}

void
transfer(unsigned long vehicle, int from_intersection, int to_intersection) {
	print_transfer(vehicle, from_intersection, to_intersection);
}

void
leave(unsigned long vehicle, int intersection) {
	print_leave(vehicle, intersection);
}

void
finish(void) {
	/* Very straightforward. */
	kprintf("finish()\n");
}

/**
 * Sets up a stoplight program with the given number of vehicles.
 */
static void
setup(int count) {
	assert(count <= 255);

	int i;
	for(i = 0; i < count; ++i) {
		all_vehicles[i].route = 0;
		all_vehicles[i].type = 0;
		all_vehicles[i].turn_direction = 0;
	}

	/* Indicate the start to the autograder. */
	kprintf("\nstart(%d)\n", count);
}

/**
 * Stoplight test sl_simple.
 * 
 * Consists of 30 cars turning right, all from A.
 */
int
stoplight_simple(int nargs, char** args) {
	(void)nargs;
	(void)args;

	setup(30);

	/* After the call to setup(), the only thing that needs to be
	 * changed is the vehicle type to CAR. All the other values
	 * can be left at their default 0 (so route 0, turn direction 0). */
	int i;
	for(i = 0; i < 30; ++i) {
		all_vehicles[i].type = VEHICLE_CAR;
	}

	stoplight_driver(30);

	return 0;
}

/**
 * Stoplight test sl_random.
 * 
 * Consists of 100 vehicles with totally random setup.
 * - Each vehicle is assigned a random route (A, B, or C).
 * - Each vehicle is assigned a random turn direction (left or right).
 * - Each vehicle is assigned a random type (car or truck).
 */
int
stoplight_random(int nargs, char **args) {
	(void)nargs;
	(void)args;

	setup(100);

	/* After setup(), randomize all info. Use modulo to get values
	 * in-range.
	 *
	 * This way of getting random numbers is slightly biased, but
	 * that's OK, as the main point of this test is to have cars
	 * in *all possible combinations*, which it does. */
	int i;
	for(i = 0; i < 100; ++i) {
		all_vehicles[i].route = random() % 3;
		all_vehicles[i].turn_direction = random() % 2;
		all_vehicles[i].type = random() % 2;
	}

	stoplight_driver(100);
	
	return 0;
}

/**
 * Stoplight test sl_prio.
 * 
 * This test is specifically for testing the priority system, and
 * can help you flush out subtle bugs.
 * 
 * It consists of 30 vehicles. The first 15 are low-priority, i.e. trucks,
 * while the last 15 are high-priority, i.e. cars.
 * 
 * All vehicles are on route A and turning right.
 * 
 * Once the cars start approach()ing, the trucks should defer
 * to them for as long as there is any car left that has approach()ed
 * and has not yet enter()ed.
 * 
 * (Check your output with the auto-checker for more info).
 */
int
stoplight_prio(int nargs, char **args) {
	(void)nargs;
	(void)args;

	setup(30);
	int i;
	for(i = 0; i < 30; ++i) {
		/* Important: All vehicles on same route, so we can test priority. */
		all_vehicles[i].route = ROUTE_A;
		all_vehicles[i].turn_direction = TURN_RIGHT;

		/* First 15 low priority, next 15 high priority. */
		all_vehicles[i].type = (i >= 15 ? VEHICLE_CAR : VEHICLE_TRUCK);
	}

	stoplight_driver(30);
	
	return 0;
}


/**
 * Stoplight test sl_custom.
 * 
 * This can be invoked from the OS/161 menu with "sl_custom <number>".
 * 
 * Any number of additional tests can be easily added here. When adding
 * a test, follow the pattern:
 * 
 *     setup(NUMBER);
 * 
 *     ... your vehicle setup code ...
 * 
 *     stoplight_driver(NUMBER);
 * 
 * Make sure NUMBER is the same in both places.
 * 
 * For some ideas for custom tests, you could consider:
 * - A test with right turners from route A and route B
 * - A test with left turners from all three intersections
 * - A three-level priority test
 * - Anything else you can dream of!
 */
int
stoplight_custom(int nargs, char **args) {
	if(nargs >= 2) {
	}
	else {
		kprintf("Must provide a numerical argument to sl_custom\n");
		return 0;
	}

	int num = atoi(args[1]);

	switch(num) {
		/* Feel free to add your own custom stoplight tests here! */

		case 0:
			setup(30);

			/* Add vehicle setup here */

			stoplight_driver(30);
			break;

		case 1:
			setup(30);

			/* Add vehicle setup here */

			stoplight_driver(30);
			break;

		/* Add more tests if you want here */

		default:
			kprintf("Unknown sl_custom test %d\n", num);
			break;
	}

	return 0;
}