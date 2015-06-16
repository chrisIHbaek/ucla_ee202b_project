% Read the data file
Data=csvread('Execution Time Raw Data_Big CPU_For matlab.csv');

% Separate the data
Frequency=Data(:,2);
Time=Data(:,3);

% Plot
figure(1)
hold on;
plot(Frequency,Time,'o');
xlim([700,1700])
ylim([-1,50])
x=800:1600;
c=ones(1,length(x));
y1=34077.8*c./x+2.62;
plot(x,y1,'Color',[227/255,23/255,13/255])
y2=27922.62*c./x+1.56;
plot(x,y2,'Color',[255/255,99/255,71/255])
y3=23397.82*c./x+0.67;
plot(x,y3,'Color',[255/255,97/255,3/255])
y4=17900*c./x+0.237;
plot(x,y4,'Color',[237/255,145/255,33/255])
y5=14392.956*c./x-0.162;
plot(x,y5,'Color',[227/255,207/255,87/255])
y6=11572.905*c./x-0.262;
plot(x,y6,'Color',[255/255,215/255,0/255])
y7=8045.821*c./x-0.109;
plot(x,y7,'Color',[127/255,255/255,0/255])
y8=6242.785*c./x-0.198;
plot(x,y8,'Color',[189/255,252/255,202/255])
y9=4552.1649*c./x-0.0669;
plot(x,y9,'Color',[127/255,255/255,212/255])
y10=3100*c./x-0.0106;
plot(x,y10,'Color',[0/255,255/255,255/255])
y11=2300*c./x-0.0246;
plot(x,y11,'Color',[135/255,206/255,235/255])
y12=1310*c./x-0.0654;
plot(x,y12,'Color',[65/255,105/255,225/255])
y13=736.9077*c./x-0.0692;
plot(x,y13,'Color',[0/255,0/255,255/255])
y14=429.7185*c./x-0.0205;
plot(x,y14,'Color',[218/255,112/255,214/255])
y15=219.7185*c./x-0.0136;
plot(x,y15,'Color',[160/255,32/255,240/255])
y16=61.6677*c./x-0.0416;
plot(x,y16,'Color',[25/255,25/255,112/255])

xlabel('Frequency (MHz)')
ylabel('Execution Time (seconds)')
title('Matrix Multiplication Execution Time Model (Big CPU)')
legend('Raw Data','Matrix Dimension = 850','Matrix Dimension = 800','Matrix Dimension = 750','Matrix Dimension = 700','Matrix Dimension = 650','Matrix Dimension = 600','Matrix Dimension = 550','Matrix Dimension = 500','Matrix Dimension = 450','Matrix Dimension = 400','Matrix Dimension = 350','Matrix Dimension = 300','Matrix Dimension = 250','Matrix Dimension = 200','Matrix Dimension = 150','Matrix Dimension = 100','Location','Eastoutside')
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
grid on;
hold off;

