% Read the data file
Data=csvread('Execution Time Raw Data.csv');
Data_1=csvread('Execution Time Raw Data_1.csv');
Data_2=csvread('Execution Time Raw Data_2.csv');

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
x=100:900;
y1=0.000000326*x.*x.*x-0.0000252*x.*x+0.928;
plot(x,y1,'Color',[227/255,23/255,13/255])
y2=0.000000267*x.*x.*x-0.0000162*x.*x+0.517;
plot(x,y2,'Color',[255/255,99/255,71/255])
y3=0.000000237*x.*x.*x-0.0000206*x.*x+0.802;
plot(x,y3,'Color',[255/255,97/255,3/255])
y4=0.000000202*x.*x.*x-0.0000117*x.*x+0.386;
plot(x,y4,'Color',[237/255,145/255,33/255])
y5=0.000000189*x.*x.*x-0.0000180*x.*x+0.636;
plot(x,y5,'Color',[227/255,207/255,87/255])
y6=0.000000169*x.*x.*x-0.0000138*x.*x+0.432;
plot(x,y6,'Color',[255/255,215/255,0/255])
y7=0.000000153*x.*x.*x-0.0000128*x.*x+0.423;
plot(x,y7,'Color',[127/255,255/255,0/255])
y8=0.000000138*x.*x.*x-0.0000091*x.*x+0.283;
plot(x,y8,'Color',[189/255,252/255,202/255])
y9=0.0000000967*x.*x.*x-0.0000212*x.*x+0.739;
plot(x,y9,'Color',[127/255,255/255,212/255])
y10=0.0000000888*x.*x.*x-0.0000209*x.*x+0.717;
plot(x,y10,'Color',[0/255,255/255,255/255])
y11=0.0000000795*x.*x.*x-0.0000184*x.*x+0.661;
plot(x,y11,'Color',[135/255,206/255,235/255])
y12=0.0000000746*x.*x.*x-0.0000186*x.*x+0.667;
plot(x,y12,'Color',[65/255,105/255,225/255])
y13=0.0000000687*x.*x.*x-0.0000169*x.*x+0.594;
plot(x,y13,'Color',[0/255,0/255,255/255])
y14=0.0000000639*x.*x.*x-0.000016*x.*x+0.574;
plot(x,y14,'Color',[218/255,112/255,214/255])
y15=0.0000000622*x.*x.*x-0.0000171*x.*x+0.607;
plot(x,y15,'Color',[160/255,32/255,240/255])
y16=0.0000000607*x.*x.*x-0.0000175*x.*x+0.637;
plot(x,y16,'Color',[25/255,25/255,112/255])
y17=0.0000000557*x.*x.*x-0.0000158*x.*x+0.578;
plot(x,y17,'Color',[160/255,82/255,45/255])
xlabel('Dimension of Input Matrices')
ylabel('Execution Time (seconds)')
title('Matrix Multiplication Execution Time Model')
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
xlabel('Dimension of Input Matrices')
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
xlabel('Dimension of Input Matrices')
ylabel('Execution Time (seconds)')
title('Matrix Multiplication Execution Time Model')
legend('Raw Data','Fitting Model (800MHz)','Fitting Model (900MHz)','Fitting Model (1000MHz)','Fitting Model (1100MHz)','Fitting Model (1200MHz)','Fitting Model (1300MHz)','Fitting Model (1400MHz)','Fitting Model (1500MHz)','Fitting Model (1600MHz)','Location','Northwest')
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;
