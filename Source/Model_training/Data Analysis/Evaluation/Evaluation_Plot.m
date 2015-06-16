% Read the data file
littleCPUdata=csvread('Evalution_little CPU power model.csv');
bigCPUdata=csvread('Evalution_big CPU power model.csv');

% Separate data
little_obeserved=littleCPUdata(:,1);
little_predicted=littleCPUdata(:,2);
little_error=littleCPUdata(:,3);
big_obeserved=bigCPUdata(:,1);
big_predicted=bigCPUdata(:,2);
big_error=bigCPUdata(:,3);

figure(1)
hold on;
plot(little_predicted,little_obeserved,'o')
x=0.04:0.001:0.16;
y=x;
plot(x,y,'r:')
xlabel('Predicted little CPU power')
xlim([0.04,0.16])
ylabel('Observed little CPU power')
ylim([0.04,0.16])
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;

figure(2)
hold on;
plot(big_predicted,big_obeserved,'o')
x1=0.4:0.01:1.8;
y1=x1;
plot(x1,y1,'r:')
xlabel('Predicted big CPU power')
xlim([0.4,1.81])
ylabel('Observed big CPU power')
ylim([0.4,1.81])
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;
