ftoi vs cvttss2si
========

In my IT266 Game Mod Development class the question was posed: "Is idSoftware's
idLib::Math::FtoiFast method still faster than present SIMD instructions?" My
initial reaction was correct. Intel's SIMD instructions present in the pre-7th
generation intel architectures are extremely complex. They require you to move
data into and out of the 32-bit xmm0 register. Access to these registers
(regardless of how much data you want to move) will require two full clock
cycles. After you get the data into the registers the SIMD instructions are
slow unless you can make use of all 128 bits of xmm0. Using cvttss2si for a 
single float is not faster than using the old-school casting techniques.


The following benchmarks were taken on my Thinkpad X220. You can see that the
idSoftware implementation took less time, less cycles, and has fewer stalled 
cycles. The idSoftware implementation is also making better use of the Intel
pipeline. The SIMD instruction are also wasting more time doing nothing. You
can see this in the front-end and back-end stalled cycles. On the front end
the SIMD instructions can't be packed into microcode optimizations. On the 
back end the instructions take forever to execute.  

```bash
$ sudo perf stat ./ftoi_id  

 Performance counter stats for './ftoi_id':

          0.390428      task-clock (msec)         #    0.548 CPUs utilized          
                 0      context-switches          #    0.000 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
                43      page-faults               #    0.110 M/sec                  
           822,266      cycles                    #    2.106 GHz                    
           606,616      stalled-cycles-frontend   #   73.77% frontend cycles idle   
           477,532      stalled-cycles-backend    #   58.08% backend cycles idle    
           478,269      instructions              #    0.58  insn per cycle         
                                                  #    1.27  stalled cycles per insn
            86,889      branches                  #  222.548 M/sec                  
             4,548      branch-misses             #    5.23% of all branches        

       0.000712552 seconds time elapsed

$ sudo perf stat ./ftoi_cast
./ftoi_cast: Segmentation fault

 Performance counter stats for './ftoi_cast':

          0.728353      task-clock (msec)         #    0.005 CPUs utilized          
                 2      context-switches          #    0.003 M/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
                43      page-faults               #    0.059 M/sec                  
         1,334,100      cycles                    #    1.832 GHz                    
         1,065,300      stalled-cycles-frontend   #   79.85% frontend cycles idle   
           857,001      stalled-cycles-backend    #   64.24% backend cycles idle    
           603,999      instructions              #    0.45  insn per cycle         
                                                  #    1.76  stalled cycles per insn
           108,054      branches                  #  148.354 M/sec                  
             6,773      branch-misses             #    6.27% of all branches        

       0.136181338 seconds time elapsed
```
