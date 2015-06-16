% Read the data file
bigCPUdata=csvread('Power Model Raw Data_Big CPU.csv');
littleCPUdata=csvread('Power Model Raw Data_Little CPU.csv');

% Separate data
big_Frequency=bigCPUdata(:,1);
big_Voltage=bigCPUdata(:,2);
big_Power=bigCPUdata(:,3);
little_Frequency=littleCPUdata(:,1);
little_Voltage=littleCPUdata(:,2);
little_Power=littleCPUdata(:,3);

figure(1)
hold on;
plot(big_Voltage.*big_Voltage.*big_Frequency,big_Power,'bo')
x=600:2200;
y=0.000827*x-0.0529;
plot(x,y,'Color',[1,0.5,0])
ylim([0.4,1.8])
xlabel('Voltage^2¡ÁFrequency')
ylabel('Power (W)')
%title('Power Model (Big CPU)')
legend('Raw Data','Fitting Model','Location','NorthWest')
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;

figure(2)
hold on;
plot(big_Frequency,big_Voltage,'bo')
x=800:1600;
y=0.0003152*x+0.6472870;
plot(x,y,'Color',[1,0.5,0])
ylim([0.9,1.2001])
xlabel('Frequency (MHz)')
ylabel('Voltage (V)')
%title('Correlation between Frequency and Voltage (Big CPU)')
legend('Raw Data','Fitting Model','Location','NorthWest')
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;

figure(3)
hold on;
plot(little_Voltage.*little_Voltage.*little_Frequency,little_Power,'bo')
x=200:900;
y=0.0001722*x+0.00006534;
plot(x,y,'Color',[1,0.5,0])
ylim([0.03,0.16])
xlabel('Voltage^2¡ÁFrequency')
ylabel('Power (W)')
%title('Power Model (Little CPU)')
legend('Raw Data','Fitting Model','Location','NorthWest')
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;

figure(4)
hold on;
plot(little_Frequency,little_Voltage,'bo')
x1=250:400;
y1=0.95;
plot(x1,y1,'Color',[1,0.5,0])
x2=400:600;
y2=0.0012*x2+0.4765;
plot(x2,y2,'Color',[1,0.5,0])
ylim([0.9,1.25])
xlabel('Frequency (MHz)')
ylabel('Voltage (V)')
%title('Correlation between Frequency and Voltage (Little CPU)')
legend('Raw Data','Fitting Model','Location','NorthWest')
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;