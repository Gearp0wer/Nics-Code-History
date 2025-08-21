package mapreduce

import (
	"sync"
)
var persistentWorkersMu sync.Mutex
var persistentWorkers []string

func (mr *Master) schedule(phase jobPhase) {
	var ntasks int
	var nios int
  
	switch phase {
	case mapPhase:
		ntasks = len(mr.files)
		nios = mr.nReduce
	case reducePhase:
		ntasks = mr.nReduce
		nios = len(mr.files)
	}
	//debug("Schedule: %v %v tasks (%d I/Os)\n", ntasks, phase, nios)

	var wg sync.WaitGroup
	workerChan := make(chan string, 100)
	//debug("Worker channel initialized (buffered)\n")

	// pre-load any persistent (idle) workers from previous phases.
	//I'm not sure if there was a better way to do this, but this works!
	if phase == reducePhase {
		persistentWorkersMu.Lock()
		if len(persistentWorkers) > 0 {
			//debug("Pre-loading persistent workers into reduce worker pool\n")
			for _, w := range persistentWorkers {
				//debug("Pre-loading worker %v into pool\n", w)
				workerChan <- w
			}
		} 
        //else {
			//debug("No persistent workers found for reduce phase\n")
		//}
		persistentWorkersMu.Unlock()
	}

	go func() {
		for worker := range mr.registerChannel {
			//debug("Worker registered via registerChannel: %v\n", worker)
			workerChan <- worker
		}
		//debug("mr.registerChannel closed, worker listener goroutine ending\n")
	}()

	for taskNum := 0; taskNum < ntasks; taskNum++ {
		wg.Add(1)
		go func(taskNum int) {
			defer wg.Done()

			args := DoTaskArgs{
				JobName:       mr.jobName,
				File:          "",
				Phase:         phase,
				TaskNumber:    taskNum,
				NumOtherPhase: nios,
			}
			if phase == mapPhase {
				args.File = mr.files[taskNum]
			}

			attempts := 0
			success := false
			for !success {
				attempts++
				//debug("Task %v (attempt %d) waiting for worker...\n", taskNum, attempts)
				worker := <-workerChan
				//debug("Task %v (attempt %d) assigned to worker %v\n", taskNum, attempts, worker)

				//debug("Task %v: making RPC call on worker %v\n", taskNum, worker)
				ok := call(worker, "Worker.DoTask", args, nil)
				//debug("Task %v: RPC call returned %v for worker %v\n", taskNum, ok, worker)

				if ok {
					//debug("Task %v succeeded on worker %v\n", taskNum, worker)
					// yeah its an O(n) duplicatre checker, but it works!
					persistentWorkersMu.Lock()
					alreadyPresent := false
					for _, w := range persistentWorkers {
						if w == worker {
							alreadyPresent = true
							break
						}
					}
					if !alreadyPresent {
						//debug("Adding worker %v to persistent pool\n", worker)
						persistentWorkers = append(persistentWorkers, worker)
					} 
					//else {
						//debug("Worker %v already in persistent pool, not adding duplicate\n", worker)
					//}
					persistentWorkersMu.Unlock()

					//debug("Returning worker %v to pool\n", worker)
					workerChan <- worker
					success = true
				} else {
					//debug("Worker %v failed on task %v (attempt %d). Re-assigning task...\n", worker, taskNum, attempts)
				}
			}
		}(taskNum)
	}

	wg.Wait()
	//debug("Schedule: %v phase done\n", phase)
}
