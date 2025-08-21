#ifndef _STOPLIGHT_FRAMEWORK_H_
#define _STOPLIGHT_FRAMEWORK_H_

/**
 * Defines the API associated with the stoplight program.
 * 
 * The functions defined here do two things:
 * 1. Provide information about what each vehicle should be doing
 * 2. Provide well-defined functions for vehicles to perform the actions
 *    of moving through the intersection:
 * 
 *    - approach() to approach the intersection
 *    - enter() to enter one of the intersection sections (AB, BC, CA)
 *    - leave() to leave one of the intersection sections
 *    - transfer() to transfer between two sections (useful for left turning)
 * 
 * Note that these functions essentially boil down to printing a message to
 * the console.
 * 
 * The sequence of printed messages corresponds to the sequence of events,
 * and this sequence can be checked after-the-fact either manually or with
 * an automated program to see if there are any:
 * 
 *   - Crashes (Two vehicles entering e.g. AB at the same time)
 *   - Priority violations (A vehicle calling enter() when a higher-priority vehicle
 *     on the same route has already called approach())
 *   - Simple logical errors (calling enter(), leave(), transfer() with the wrong arguments)
 *   - Missed outputs (e.g. if your program deadlocks and doesn't print all the messages
 *     for a particular vehicle).
 */

/* ---------------------------------------------------------------------------
 *                          CONSTANT DEFINITIONS
 * ---------------------------------------------------------------------------
 *
 * These constants provide numerical values for e.g. Route A, Intersection AB,
 * Turning left, Turning right, and the vehicle types.
 * 
 * They are all defined as enums, but the get_vehicle_* functions each take
 * an integer for convenience (as then these values are more easily manipulated
 * arithmetically).
 * 
 * Feel free to directly use numerical values instead of these constants where
 * convenient. These values are the same values that the autograder will use. */

enum vehicle_type {
    VEHICLE_TRUCK = 0,
    VEHICLE_CAR   = 1,
};

enum turn_direction {
    TURN_RIGHT = 0,
    TURN_LEFT  = 1,
};

enum route {
    ROUTE_A = 0,
    ROUTE_B = 1,
    ROUTE_C = 2,
};

enum intersection {
    INTERSECTION_AB = 0,
    INTERSECTION_BC = 1,
    INTERSECTION_CA = 2,
};

/* ---------------------------------------------------------------------------
 *                          VEHICLE INFO FUNCTIONS 
 * ---------------------------------------------------------------------------
 *
 * These functions give you information about each vehicle in the problem.
 * (Note there are MULTIPLE test scenarios you can run!) */

/**
 * Provides the route number for a given vehicle.
 *
 * 0 = A
 * 1 = B
 * 2 = C
 * 
 * Note that these constants are intended to have certain
 * numerical relationships with the matching constants for
 * intersections.
 */
int get_vehicle_route(unsigned long vehicle);

/**
 * Provides the vehicle type for a given vehicle.
 * 
 * 0 = Truck
 * 1 = Car
 * 
 * Note that it is intended that higher-priority vehicles
 * have larger numerical values from this function.
 */
int get_vehicle_type(unsigned long vehicle);

/**
 * Provides the turn direction for a given vehicle.
 * 
 * Each vehicle is either turning right through a single intersection,
 * (e.g. A -> AB -> done) or turning left by traversing two intersections
 * (e.g. A -> AB -> BC -> done).
 * 
 * 0 = Right
 * 1 = Left
 * 
 * Note that using TURN_RIGHT or TURN_LEFT is likely your best bet for these,
 * as these numerical values do not have much intrinsic meaning.
 */
int get_vehicle_turn_direction(unsigned long vehicle);

/* ---------------------------------------------------------------------------
 *                          VEHICLE ACTION FUNCTIONS 
 * ---------------------------------------------------------------------------
 *
 * These functions actually perform the steps of approaching, entering, transferring,
 * and leaving. They each take a vehicle number as a parameter, plus values corresponding
 * to the INTERSECTION_ values in the case of enter(), leave(), and transfer(). */

/**
 * Call this method when your vehicle is "approaching" the intersection.
 * 
 * A vehicle approaches the intersection when it is considered a candidate
 * for enter()ing the intersection.
 * 
 * That is, a vehicle MUST call approach() before it calls enter(). However,
 * once a vehicle has called approach(), it must not enter() until all higher-priority
 * vehicles that are also on the same route that have called approach() have entered.
 * 
 * That is, the following is invalid:
 *     Car   5 from A turning right: approach()
 *     Truck 3 from A turning right: approach()
 *     Truck 3 from A turning right: enter(AB)
 * But the following is valid:
 *     Truck 3 from A turning right: approach()
 *     Truck 3 from A turning right: enter(AB)
 *     Car   5 from A turning right: approach()
 * Because Truck 5 has not approached yet.
 * 
 * HINT: For your implementation, you will want to perform any book-keeping needed
 * to track approached vehicles BEFORE actually calling approach(). This is necessary
 * to correctly implement the priority system.
 */
void approach(unsigned long vehicle);

/**
 * Call this method when your vehicle is entering an intersection.
 * 
 * You must provide the correct intersection number. Carefully observe the
 * relationship between e.g. route A, which is 0, and intersection AB, which is also 0,
 * in order to find a straightforward mapping from vehicle routes to the intersections
 * they should be enter()ing.
 * 
 * Your vehicle MUST NOT enter an intersection while there is still a vehicle in that
 * intersection, as two vehicles in the same intersection is a CRASH. (i.e. a car crash).
 * 
 * In particular, any sequence of commands such as:
 *     Car 3 from A turning right: enter(AB)
 * 
 *     ... Car 3 has not called leave() or transfer() yet
 * 
 *     Car 4 from A turning right: enter(AB)
 * is a crash.
 * 
 * This is because a vehicle remains in the same part of the intersection until it calls
 * either leave() or transfer().
 */
void
enter(unsigned long vehicle, int intersection);

/**
 * Call this method when a vehicle is transferring between two intersections.
 * 
 * This is mostly applicable to left-turning vehicles, which must e.g. transfer between
 * AB and BC at some point.
 * 
 * Note that transfer() is essentially leave()ing one intersection and enter()ing
 * another in one step. As such, the semantics of these two functions are both applicable
 * here.
 * 
 * In particular, the vehicle is still in the starting intersection right up until
 * the point where it calls transfer(). So vehicles can collide with it until the
 * call to transfer().
 * 
 * Similarly, the destination intersection for the transfer() must be clear for
 * transfer() to be safely called. If the vehicle transfer()s into a new intersection
 * where a car is already present, that causes a car crash, just the same as enter()ing
 * that intersection.
 */
void transfer(unsigned long vehicle, int from_intersection, int to_intersection);

/**
 * Call this method when your vehicle is leaving an intersection.
 * 
 * This method has the fewest requirements of the available methods. All you
 * have to do is provide the correct intersection number, and then call this
 * method when you want that vehicle to leave the intersection (it must have
 * either enter()ed or transfer()ed into that intersection first, of course).
 * 
 * HINT: Be careful about how you synchronize this. Is it safe to release
 * a controlling lock before calling leave()? If so, why? If not, why not?
 */
void leave(unsigned long vehicle, int intersection);

/**
 * Call this method after every vehicle has made its way through the intersection.
 * Calling finish correctly demonstrates that your solution is able to encapsulate
 * the stoplight problem into one solid task -- in particular, notice that until
 * you have correctly synchronized the call to finish(), you will additionally
 * see non-stoplight output such as "Operation succeeded" and the OS/161 menu popping
 * up. Once finish() is properly synchronized, these other outputs will not pop
 * up until the operation is actually done, which is what we want for a clean
 * multi-tasking program.
 */
void finish(void);

/**
 * Your driver function!
 * 
 * See stoplight.c for more info, and for the stub implementation.
 */
int stoplight_driver(int vehicle_count);

#endif /* _STOPLIGHT_FRAMEWORK_H_ */