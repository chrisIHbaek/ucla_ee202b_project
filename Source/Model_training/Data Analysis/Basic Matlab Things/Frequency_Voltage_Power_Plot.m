function Plot()
% Read data from txt file
data=importdata('power_model_log_600MHz.txt');

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


