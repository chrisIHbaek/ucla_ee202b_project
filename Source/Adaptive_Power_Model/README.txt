Simply run make command to compile to code.

3 executables are generated.

1. print_parameter: It prints out adjusted parameters using the adaptive power model algorithm.
2. power_energy_measurement: It just displays the elapsed time, frequency, power, and energy.
3. energy_prediction: It first prints out values computed with rough power model and then values computed with the adaptive power model.
                      This runs dd command in the background.
                      This is program is used in the following way:
                      ./energy_prediction 1000000 100
                      The first input argument is the count input for dd command and 100 is the QoS in seconds.
                      
A sample output is:

Rough Power Model-based results: 
Execution time: 47.561000s	Power: 0.038918W		Energy: 1.850977 Watt-second for 250MHz
Execution time: 39.713700s	Power: 0.046688W		Energy: 1.854173 Watt-second for 300MHz
Execution time: 34.308000s	Power: 0.054459W		Energy: 1.868380 Watt-second for 350MHz
Execution time: 29.622400s	Power: 0.063083W		Energy: 1.868673 Watt-second for 400MHz
Execution time: 26.365000s	Power: 0.080134W		Energy: 2.112723 Watt-second for 450MHz
Execution time: 24.059600s	Power: 0.099843W		Energy: 2.402171 Watt-second for 500MHz
Execution time: 21.426200s	Power: 0.122396W		Energy: 2.622478 Watt-second for 550MHz
Execution time: 19.632000s	Power: 0.147980W		Energy: 2.905134 Watt-second for 600MHz
Execution time: 23.601000s	Power: 0.482338W		Energy: 11.383651 Watt-second for 800MHz
Execution time: 20.818000s	Power: 0.592184W		Energy: 12.328096 Watt-second for 900MHz
Execution time: 18.802000s	Power: 0.713217W		Energy: 13.409911 Watt-second for 1000MHz
Execution time: 17.058800s	Power: 0.845929W		Energy: 14.430534 Watt-second for 1100MHz
Execution time: 15.495900s	Power: 0.990813W		Energy: 15.353534 Watt-second for 1200MHz
Execution time: 14.536700s	Power: 1.148361W		Energy: 16.693383 Watt-second for 1300MHz
Execution time: 13.403300s	Power: 1.319068W		Energy: 17.679860 Watt-second for 1400MHz
Execution time: 12.595290s	Power: 1.503425W		Energy: 18.936073 Watt-second for 1500MHz
Execution time: 11.710330s	Power: 1.701926W		Energy: 19.930116 Watt-second for 1600MHz
250MHz will result in least energy consumption!


Adaptive Model-base Results: 
new aC (little): 0.000207
new aC (big): 0.000686
Execution time: 47.561000s	Power: 0.046832W		Energy: 2.227364 Watt-second for 250MHz
Execution time: 39.713700s	Power: 0.056185W		Energy: 2.231314 Watt-second for 300MHz
Execution time: 34.308000s	Power: 0.065538W		Energy: 2.248487 Watt-second for 350MHz
Execution time: 29.622400s	Power: 0.075919W		Energy: 2.248903 Watt-second for 400MHz
Execution time: 26.365000s	Power: 0.096442W		Energy: 2.542705 Watt-second for 450MHz
Execution time: 24.059600s	Power: 0.120166W		Energy: 2.891141 Watt-second for 500MHz
Execution time: 21.426200s	Power: 0.147313W		Energy: 3.156356 Watt-second for 550MHz
Execution time: 19.632000s	Power: 0.178108W		Energy: 3.496610 Watt-second for 600MHz
Execution time: 23.601000s	Power: 0.391054W		Energy: 9.229257 Watt-second for 800MHz
Execution time: 20.818000s	Power: 0.482166W		Energy: 10.037737 Watt-second for 900MHz
Execution time: 18.802000s	Power: 0.582557W		Energy: 10.953239 Watt-second for 1000MHz
Execution time: 17.058800s	Power: 0.692635W		Energy: 11.815523 Watt-second for 1100MHz
Execution time: 15.495900s	Power: 0.812809W		Energy: 12.595207 Watt-second for 1200MHz
Execution time: 14.536700s	Power: 0.943488W		Energy: 13.715200 Watt-second for 1300MHz
Execution time: 13.403300s	Power: 1.085081W		Energy: 14.543661 Watt-second for 1400MHz
Execution time: 12.595290s	Power: 1.237996W		Energy: 15.592919 Watt-second for 1500MHz
Execution time: 11.710330s	Power: 1.402643W		Energy: 16.425413 Watt-second for 1600MHz
250MHz will result in least energy consumption!
root@odroid:/home/odroid/Desktop/EE202B_codes/Source/Adaptive_Power_Model# 10000000+0 records in
10000000+0 records out
5120000000 bytes (5.1 GB) copied, 13.5235 s, 379 MB/s
!!! dd finished running !!!
