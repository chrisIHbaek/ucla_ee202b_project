% Read the data file
Data=csvread('Execution Time Raw Data_Little CPU_For matlab.csv');

% Separate the data
Frequency=Data(:,2);
Time=Data(:,3);

% Plot
figure(1)
hold on;
plot(Frequency,Time,'o');
xlim([200,650])
x=250:600;
c=ones(1,length(x));
y1=45003.06*c./x+3.37;
plot(x,y1,'Color',[227/255,23/255,13/255])
y2=36953.23*c./x+3.89;
plot(x,y2,'Color',[255/255,99/255,71/255])
y3=30355.36*c./x+2.48;
plot(x,y3,'Color',[255/255,97/255,3/255])
y4=24653*c./x+1.91;
plot(x,y4,'Color',[237/255,145/255,33/255])
y5=19603.25*c./x+1.35;
plot(x,y5,'Color',[227/255,207/255,87/255])
y6=15535*c./x+1.25;
plot(x,y6,'Color',[255/255,215/255,0/255])
y7=11600*c./x+0.701;
plot(x,y7,'Color',[127/255,255/255,0/255])
y8=8601.635*c./x+0.622;
plot(x,y8,'Color',[189/255,252/255,202/255])
y9=6282.88*c./x+0.42;
plot(x,y9,'Color',[127/255,255/255,212/255])
y10=4457.979*c./x+0.115;
plot(x,y10,'Color',[0/255,255/255,255/255])
y11=3131.2484*c./x-0.0401;
plot(x,y11,'Color',[135/255,206/255,235/255])
y12=1988.0032*c./x-0.0708;
plot(x,y12,'Color',[65/255,105/255,225/255])
y13=1160*c./x-0.0471;
plot(x,y13,'Color',[0/255,0/255,255/255])
y14=621.1476*c./x+0.0269;
plot(x,y14,'Color',[218/255,112/255,214/255])
y15=280.995*c./x+0.102;
plot(x,y15,'Color',[160/255,32/255,240/255])
y16=108.5343*c./x+0.0344;
plot(x,y16,'Color',[25/255,25/255,112/255])

xlabel('Frequency (MHz)')
ylabel('Execution Time (seconds)')
%title('Matrix Multiplication Execution Time Model (Little CPU)')
legend('Raw Data','Matrix Dimension = 850','Matrix Dimension = 800','Matrix Dimension = 750','Matrix Dimension = 700','Matrix Dimension = 650','Matrix Dimension = 600','Matrix Dimension = 550','Matrix Dimension = 500','Matrix Dimension = 450','Matrix Dimension = 400','Matrix Dimension = 350','Matrix Dimension = 300','Matrix Dimension = 250','Matrix Dimension = 200','Matrix Dimension = 150','Matrix Dimension = 100','Location','Eastoutside')
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;

