#define DEFAULT_ITERATIONS 1000

/* Initialization function that the user must call
 * before running any other library function.
 * The function may, for example, allocate memory or
 * create/open files.
 * Pay attention: this function may be empty for some desings. It's fine.
 * Returns 0 uppon success and -1 on failure
 */
int osm_init(){

}


/* finalizer function that the user must call
 * after running any other library function.
 * The function may, for example, free memory or
 * close/delete files.
 * Returns 0 uppon success and -1 on failure
 */
int osm_finalizer(){

}


/* Time measurement function for a simple arithmetic operation.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_operation_time(unsigned int iterations){
    iterations = (iterations == 0)? DEFAULT_ITERATIONS : iterations;

    timeval* startTime = new timeval();
    timeval* endTime = new timeval();
    gettimeofday(startTime, NULL);
    
    int i = 0, x = 0;
    for(; i < iterations; i++){
        x = 1 + 1;
    }
    
    gettimeofday(endTime, NULL);
    
    return (endTime.tv_sec - startTime.tv_sec) * 1000000000 + (endTime.tv_usec - startTime.tv_usec) * 1000;
}


/* Time measurement function for an empty function call.
   returns time in nano-seconds upon success, 
   and -1 upon failure.
   */
double osm_function_time(unsigned int iterations){

}


/* Time measurement function for an empty trap into the operating system.
   returns time in nano-seconds upon success, 
   and -1 upon failure.
   */
double osm_syscall_time(unsigned int iterations){
    iterations = (iterations == 0)? DEFAULT_ITERATIONS : iterations;
    
    
    timeval* startTime = new timeval();
    timeval* endTime = new timeval();
    gettimeofday(startTime, NULL);
    
    int i = 0;
    for(; i < iterations; i++){
        OSM_NULLSYSCALL();
    }
    
    gettimeofday(endTime, NULL);
    
    return (endTime.tv_sec - startTime.tv_sec) * 1000000000 + (endTime.tv_usec - startTime.tv_usec) * 1000;
}

/* Time measurement function for accessing the disk.
   returns time in nano-seconds upon success, 
   and -1 upon failure.
   */
double osm_disk_time(unsigned int iterations){
    iterations = (iterations == 0)? DEFAULT_ITERATIONS : iterations;
    
    timeval* startTime = new timeval();
    timeval* endTime = new timeval();
    gettimeofday(startTime, NULL);
    
    int i = 0;
    for(; i < iterations; i++){
        OSM_NULLSYSCALL();
    }
    
    gettimeofday(endTime, NULL);
    
    return (endTime.tv_sec - startTime.tv_sec) * 1000000000 + (endTime.tv_usec - startTime.tv_usec) * 1000;
}

timeMeasurmentStructure measureTimes (unsigned int operation_iterations,
									  unsigned int function_iterations,
									  unsigned int syscall_iterations,
									  unsigned int disk_iterations){
    timeMeasurmentStructure* times = new timeMeasurmentStructure();
    size_t* length;
    
    gethostname(times.machineName, length);
	times.instructionTimeNanoSecond = osm_operation_time(operation_iterations);
	times.functionTimeNanoSecond = osm_function_time(function_iterations);
	times.trapTimeNanoSecond = osm_syscall_time(syscall_iterations);
	times.diskTimeNanoSecond = osm_disk_time(disk_iterations);
	times.functionInstructionRatio = times.functionTimeNanoSecond / times.instructionTimeNanoSecond;
	times.trapInstructionRatio = times.trapTimeNanoSecond / times.instructionTimeNanoSecond;
	times.diskInstructionRatio = times.instructionTimeNanoSecond / times.instructionTimeNanoSecond;
	
	return times;
}
