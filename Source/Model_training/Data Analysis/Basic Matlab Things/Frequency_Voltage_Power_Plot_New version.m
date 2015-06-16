function Plot()
% Read data from txt file
data=importdata('power_model_log_1.60GHz.txt');

% Separate the data
Time=data(:,1);
Frequency=data(:,2);
A7_voltage=data(:,3);
A7_power=data(:,4);
A15_voltage=data(:,5);
A15_power=data(:,6);

% Plot 
subplot(1,3,1)
plot(Time,Frequency);
ylim([200,2000])
xlabel('Time')
ylabel('Frequency')
title('CPU Frequency')

subplot(1,3,2)
big=plotyy(Time,A15_voltage,Time,A15_power);
xlabel('Time')
set(get(big(1),'Ylabel'),'String','Voltage')
set(get(big(2),'Ylabel'),'String','Power')
title('Big CPU')

subplot(1,3,3)
small=plotyy(Time,A7_voltage,Time,A7_power);
xlabel('Time')
set(get(small(1),'Ylabel'),'String','Voltage')
set(get(small(2),'Ylabel'),'String','Power')
title('Little CPU')

% calculate the average power and voltage of Big CPU and Little CPU
A15_voltage_mean=mean(A15_voltage);
A15_power_mean=mean(A15_power);
A7_voltage_mean=mean(A7_voltage);
A7_power_mean=mean(A7_power);
average=[A15_voltage_mean A15_power_mean A7_voltage_mean A7_power_mean];

