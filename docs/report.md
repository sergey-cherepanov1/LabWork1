# Performance Comparison Experiment Report

## Experiment Objective
Comparison of sequential and parallel image processing efficiency using rotation and blur operations.

## Testing Methodology
- **Sequential processing**:  
  Execution of rotate90 + gaussian_filter and rotate270 + gaussian_filter operations consecutively in a single thread
- **Parallel processing**:  
  Simultaneous execution of both operations in separate threads
- **Test conditions**:  
  10 runs with identical input data (kernel_size = 5, sigma = 5)

## Run Results

- **Run 1**  
  Sequential: 0.19832 sec  
  Parallel: 0.108866 sec  
  Speedup: 45%

- **Run 2**  
  Sequential: 0.197066 sec  
  Parallel: 0.109205 sec  
  Speedup: 44%

- **Run 3**  
  Sequential: 0.196613 sec  
  Parallel: 0.107708 sec  
  Speedup: 45%

- **Run 4**  
  Sequential: 0.196267 sec  
  Parallel: 0.10868 sec  
  Speedup: 44%

- **Run 5**  
  Sequential: 0.197447 sec  
  Parallel: 0.108809 sec  
  Speedup: 44%

- **Run 6**  
  Sequential: 0.198786 sec  
  Parallel: 0.109472 sec  
  Speedup: 44%

- **Run 7**  
  Sequential: 0.197217 sec  
  Parallel: 0.109662 sec  
  Speedup: 44%

- **Run 8**  
  Sequential: 0.198247 sec  
  Parallel: 0.109535 sec  
  Speedup: 44%

- **Run 9**  
  Sequential: 0.19748 sec  
  Parallel: 0.110029 sec  
  Speedup: 44%

- **Run 10**  
  Sequential: 0.198317 sec  
  Parallel: 0.109245 sec  
  Speedup: 44%

## Key Observations
- All 10 runs demonstrate consistent speedup of **44-45%**
- Parallel execution time fluctuates in a narrow range of **0.107-0.110 sec**
- Sequential processing consistently takes **~0.197-0.198 sec**

## Conclusion
The parallel implementation provides consistent speedup of approximately **44.5%**
