% Read the data file
Data=csvread('Execution Time dd.csv');
Data_1=csvread('Execution Time dd_Little CPU.csv');
Data_2=csvread('Execution Time dd_Big CPU.csv');

% Separate the data
Dimension=Data(:,1);
Time=Data(:,3);
Dimension_1=Data_1(:,1);
Time_1=Data_1(:,3);
Dimension_2=Data_2(:,1);
Time_2=Data_2(:,3);

% Plot
figure(1)
hold on;
plot(Dimension,Time,'o');
x=10:100;
y1=0.472*x+0.361;    % 250MHz
plot(x,y1,'Color',[227/255,23/255,13/255])
y2=0.3965*x+0.0637;  % 300MHz
plot(x,y2,'Color',[255/255,99/255,71/255])
y3=0.342*x+0.108;    % 350MHz
plot(x,y3,'Color',[255/255,97/255,3/255])
y4=0.2958*x+0.0424;  % 400MHz
plot(x,y4,'Color',[237/255,145/255,33/255])
y5=0.262*x+0.165;    % 450MHz
plot(x,y5,'Color',[227/255,207/255,87/255])
y6=0.2413*x-0.0704;  % 500MHz
plot(x,y6,'Color',[255/255,215/255,0/255])
y7=0.2134*x+0.0862;  % 550MHz
plot(x,y7,'Color',[127/255,255/255,0/255])
y8=0.195*x+0.132;    % 600MHz
plot(x,y8,'Color',[189/255,252/255,202/255])
y9=0.235*x+0.101;    % 800MHz
plot(x,y9,'Color',[127/255,255/255,212/255])
y10=0.207*x+0.118;   % 900MHz
plot(x,y10,'Color',[0/255,255/255,255/255])
y11=0.187*x+0.102;   % 1000MHz
plot(x,y11,'Color',[135/255,206/255,235/255])
y12=0.1703*x+0.0288; % 1100MHz
plot(x,y12,'Color',[65/255,105/255,225/255])
y13=0.1542*x+0.0759; % 1200MHz
plot(x,y13,'Color',[0/255,0/255,255/255])
y14=0.1447*x+0.0667; % 1300MHz
plot(x,y14,'Color',[218/255,112/255,214/255])
y15=0.1333*x+0.0733; % 1400MHz
plot(x,y15,'Color',[160/255,32/255,240/255])
y16=0.12586*x+0.00929; % 1500MHz
plot(x,y16,'Color',[25/255,25/255,112/255])
y17=0.11718*x-0.00767; % 1600MHz
plot(x,y17,'Color',[160/255,82/255,45/255])
xlabel('dd Command Input (10^5)')
ylabel('Execution Time (seconds)')
title('dd command Execution Time Model')
legend('Raw Data','Fitting Model (250MHz)','Fitting Model (300MHz)','Fitting Model (350MHz)','Fitting Model (400MHz)','Fitting Model (450MHz)','Fitting Model (500MHz)','Fitting Model (550MHz)','Fitting Model (600MHz)','Fitting Model (800MHz)','Fitting Model (900MHz)','Fitting Model (1000MHz)','Fitting Model (1100MHz)','Fitting Model (1200MHz)','Fitting Model (1300MHz)','Fitting Model (1400MHz)','Fitting Model (1500MHz)','Fitting Model (1600MHz)','Location','BestOutside')
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;

% In order to display figure better, separately plot
figure(2)
hold on;
plot(Dimension_1,Time_1,'o');
plot(x,y1,'Color',[227/255,23/255,13/255])
plot(x,y2,'Color',[255/255,99/255,71/255])
plot(x,y3,'Color',[255/255,97/255,3/255])
plot(x,y4,'Color',[237/255,145/255,33/255])
plot(x,y5,'Color',[227/255,207/255,87/255])
plot(x,y6,'Color',[255/255,215/255,0/255])
plot(x,y7,'Color',[127/255,255/255,0/255])
plot(x,y8,'Color',[189/255,252/255,202/255])
xlabel('dd Command Input (10^5)')
ylabel('Execution Time (seconds)')
title('Matrix Multiplication Execution Time Model')
legend('Raw Data','Fitting Model (250MHz)','Fitting Model (300MHz)','Fitting Model (350MHz)','Fitting Model (400MHz)','Fitting Model (450MHz)','Fitting Model (500MHz)','Fitting Model (550MHz)','Fitting Model (600MHz)','Location','Northwest')
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;

figure(3)
hold on;
plot(Dimension_2,Time_2,'o');
plot(x,y9,'Color',[127/255,255/255,212/255])
plot(x,y10,'Color',[0/255,255/255,255/255])
plot(x,y11,'Color',[135/255,206/255,235/255])
plot(x,y12,'Color',[65/255,105/255,225/255])
plot(x,y13,'Color',[0/255,0/255,255/255])
plot(x,y14,'Color',[218/255,112/255,214/255])
plot(x,y15,'Color',[160/255,32/255,240/255])
plot(x,y16,'Color',[25/255,25/255,112/255])
plot(x,y17,'Color',[160/255,82/255,45/255])
xlabel('dd Command Input (10^5)')
ylabel('Execution Time (seconds)')
title('Matrix Multiplication Execution Time Model')
legend('Raw Data','Fitting Model (800MHz)','Fitting Model (900MHz)','Fitting Model (1000MHz)','Fitting Model (1100MHz)','Fitting Model (1200MHz)','Fitting Model (1300MHz)','Fitting Model (1400MHz)','Fitting Model (1500MHz)','Fitting Model (1600MHz)','Location','Northwest')
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;

