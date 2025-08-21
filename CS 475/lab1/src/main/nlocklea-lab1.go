package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

// Vehicle types
const (
	Car   = 100
	Truck = 300
)

// Vehicle directions
const (
	Northbound = 1
	Southbound = -1
)

// Bridge constraints
const (
	MaxWeight    = 750
	MaxConsec    = 6
	CrossTimeSec = 2
)

type Bridge struct {
	mutex         sync.Mutex
	cond          *sync.Cond
	currentWeight int
	currentDir    int // 0: no traffic, 1: northbound, -1: southbound
	numVehicles   int
	dirCount      int // Consecutive vehicles in current direction
	waitingNorth  int
	waitingSouth  int
}

func NewBridge() *Bridge {
	b := &Bridge{}
	b.cond = sync.NewCond(&b.mutex)
	return b
}

func (b *Bridge) Arrive(id, vType, direction int) {
	b.mutex.Lock()
	defer b.mutex.Unlock()

	if direction == Northbound {
		b.waitingNorth++
	} else {
		b.waitingSouth++
	}

	// Wait until it is safe to cross
	for !b.canCross(vType, direction) {
		b.cond.Wait()
	}

	// Vehicle is now crossing, update state
	if direction == Northbound {
		b.waitingNorth--
	} else {
		b.waitingSouth--
	}
	b.currentWeight += vType
	b.numVehicles++
	b.currentDir = direction
	b.dirCount++

	fmt.Printf("Vehicle %d (%s) is crossing %s. [Weight: %d, Vehicles on bridge: %d]\n", 
		id, typeStr(vType), dirStr(direction), b.currentWeight, b.numVehicles)
}

func (b *Bridge) Cross() {
	time.Sleep(CrossTimeSec * time.Second)
}

func (b *Bridge) Leave(id, vType, direction int) {
	b.mutex.Lock()
	defer b.mutex.Unlock()

	b.currentWeight -= vType
	b.numVehicles--

	fmt.Printf("Vehicle %d (%s) left the bridge. [Current Weight: %d]\n", id, typeStr(vType), b.currentWeight)

	// If no vehicles are left on the bridge, check if direction needs to be switched
	if b.numVehicles == 0 {
		b.dirCount = 0 // Reset consecutive vehicle count
		if (b.waitingNorth > 0 && b.currentDir == Southbound) || (b.waitingSouth > 0 && b.currentDir == Northbound) {
			b.currentDir = -b.currentDir // Switch direction only when needed
		}
	}

	b.cond.Signal() // Wake up waiting vehicles
}

// fairness enforcement
func (b *Bridge) canCross(vType, direction int) bool {
	if b.currentWeight+vType > MaxWeight {
		return false
	}
	if b.numVehicles == 0 {
		return true
	}
	if direction == b.currentDir && b.dirCount < MaxConsec {
		return true
	}
	if direction != b.currentDir && b.dirCount >= MaxConsec && b.numVehicles ==0{
		return true
	}
	return false
}

func OneVehicle(id, vType, direction int, bridge *Bridge) {
	fmt.Printf("Vehicle %d (Type: %s, Direction: %s) arrived at the bridge.\n", id, typeStr(vType), dirStr(direction))
	bridge.Arrive(id, vType, direction)
	bridge.Cross()
	bridge.Leave(id, vType, direction)
}

func main() {
	rand.Seed(1)
	bridge := NewBridge()
	var wg sync.WaitGroup
	var seed int64 = 1
	//var group1Vehicles, group2Vehicles int
	//var delay float64
	//var probCar, probTruck float64

	for {
		fmt.Println("\nSelect an option:")
		fmt.Printf("1) Set seed for random generator (Current: %d)\n", seed)
		fmt.Println("2) Enter custom test")
		fmt.Println("3) Run pre-established test")
		fmt.Println("4) Quit")

		var choice int
		fmt.Scanln(&choice)

		switch choice {
		case 1:
			fmt.Print("Enter seed: ")
			fmt.Scanln(&seed)
			rand.Seed(seed)

		case 2: //you should be able to manually imput any case you'd like, assuming that it has 2 or fewer groups.//update: reread the instructions. Now should accomodate all sizes.
			fmt.Print("Enter number of groups in the schedule: ")
			var numGroups int
			fmt.Scanln(&numGroups)
		
			var groups []struct {
				groupVehicles      int
				delay             float64
				probCar, probTruck float64
				probNorth, probSouth float64
			}
		
			for i := 0; i < numGroups; i++ {
				fmt.Printf("\nGroup %d:\n", i+1)
		
				fmt.Print("Enter number of vehicles in this group: ")
				var groupVehicles int
				fmt.Scanln(&groupVehicles)
		
				fmt.Print("Enter delay (seconds) before the next group: ")
				var delay float64
				fmt.Scanln(&delay)
		
				fmt.Print("Enter Car/Truck probability (e.g., 0.7 0.3): ")
				var probCar, probTruck float64
				fmt.Scanln(&probCar, &probTruck)
		
				fmt.Print("Enter Northbound/Southbound probability (e.g., 0.6 0.4): ")
				var probNorth, probSouth float64
				fmt.Scanln(&probNorth, &probSouth)
		
				// Store the group information
				groups = append(groups, struct {
					groupVehicles      int
					delay             float64
					probCar, probTruck float64
					probNorth, probSouth float64
				}{
					groupVehicles, delay, probCar, probTruck, probNorth, probSouth,
				})
			}
			// Run all the groups in sequence
			for _, group := range groups {
				fmt.Printf("\nRunning group with %d vehicles...\n", group.groupVehicles)
				fmt.Println("Starting test...")

				runTest(group.groupVehicles, group.probCar, group.probTruck, bridge, &wg, group.probNorth)
				// Sleep between groups
				time.Sleep(time.Duration(group.delay) * time.Second)
			}

		case 3:
			preestablishedTests := []struct {
				group1Vehicles, group2Vehicles int
				delay                          float64
				probCar, probTruck             float64
			}{
				{20, 10, 10.0, 1.0, 0.0},
				{30, 15, 5.0, 0.6, 0.4},
				{10, 25, 8.0, 0.3, 0.7},
				{15, 10, 3.0, 0.5, 0.5},
				{25, 5, 2.0, 0.9, 0.1},
				
				
			}

			fmt.Println("Running pre-established tests...")
			for i, test := range preestablishedTests {
				fmt.Printf("Test %d: Group: %d vehicles, delay %.1f sec, Car/Truck probability [%.1f, %.1f]\n",
					i+1, test.group1Vehicles, test.delay, test.probCar, test.probTruck)
				fmt.Println("Starting test...")
				runTest(test.group1Vehicles,  test.probCar, test.probTruck, bridge, &wg, 0.5)
				time.Sleep(time.Duration(test.delay) * time.Second)
				runTest(test.group2Vehicles, test.probCar, test.probTruck, bridge, &wg, 0.5)
			}

		case 4:
			fmt.Println("Exiting.")
			return

		default:
			fmt.Println("Invalid choice, try again.")
		}
	}
}

//this basically just exists as a dedicated runner for the given tests.
func runTest(group1Vehicles int, probCar, probTruck float64, bridge *Bridge, wg *sync.WaitGroup, northboundProb float64) {
	var id int = 0
	//say hi to southbound probability!!
	// Group 1
	for v := 0; v < group1Vehicles; v++ {
		wg.Add(1)
		vType := getRandomVehicleType(probCar)
		direction := getRandomDirection(northboundProb)
		id++
		go func(id, vType, dir int) {
			defer wg.Done()
			OneVehicle(id, vType, dir, bridge)
		}(id, vType, direction)
	}
	wg.Wait()
	fmt.Println("Test completed.\n")
}

func getRandomVehicleType(probCar float64) int {
	if rand.Float64() < probCar {
		return Car
	}
	return Truck
}

func getRandomDirection(probNorth float64) int {
	if rand.Float64() < probNorth {
		return 1
	}
	return -1
}


func typeStr(vType int) string {
	if vType == Car {
		return "Car"
	}
	return "Truck"
}

func dirStr(direction int) string {
	if direction == Northbound {
		return "Northbound"
	}
	return "Southbound"
}