# Operating System Simulator  

This program simulates an operating system processing a random batch of programs.  

For this project, I chose to implement the operating system in C++ as it was a brand new language I wanted to learn more about.  

##### Execution Process
  1. A batch of randomized programs are created based on the template and number of programs specified in the run.sh script.  
  2. The OS creates a Process and PCB object for each randomized program template.  
  3. Programs are loaded into different queues based on available memory(waiting queue, ready queue, etc).  
  4. In a Round Robin manner, programs are loaded onto the CPU and executed until they end or their time slice expires.  
  5. Once all programs have finished, the simulator exits.  
<br /><br /><br />

##### Features:  
  - Programs created with randomized instruction sizes  
  - Scheduler to organize processes in queues  
  - Dispatcher to move processes between queues and the CPU  
  - Critical Sections within each program with a semaphore lock to ensure only one program is in a critical section at any time  
  - Multi-level child process creation based on FORK instructions  
  - Cascading termination for child processes when parent exits  
  - I/O instructions for 3 different hardware peripherals executed concurrently with CPU instructions  
  - Separate queues implemented for each hardware peripheral  
  - Memory management to control number of processes that are loaded into ready queue  
