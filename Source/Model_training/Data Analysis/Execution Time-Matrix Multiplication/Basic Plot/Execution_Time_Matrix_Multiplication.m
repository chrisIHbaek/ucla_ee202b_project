% Read the data file
Data=csvread('Execution Time Raw Data matrix.csv');

% Separate the data
Matrix_Dimension=100:50:850;
Frequency=[250 300 350 400 450 500 550 600 800 900 1000 1100 1200 1300 1400 1500 1600];
RawTime=Data(:,3);

% Create a two dimensional matrix which is used for mesh funciton to record
% the execution time
Time=zeros(length(Matrix_Dimension),length(Frequency));
count=1;
for i=1:length(Matrix_Dimension)
    for j=1:length(Frequency)
        Time(i,j)=RawTime(count);
        count=count+1;
    end
end

% Plot the execution time as the function of the frequency and the matrix
% dimentions
mesh(Frequency,Matrix_Dimension,Time)
xlabel('CPU Frequency (MHz)')
ylabel('Dimension of Input Matrices')
zlabel('Execution Time (seconds)')
set(gca,'FontSize',12);
set(get(gca,'XLabel'),'FontSize',12);
set(get(gca,'YLabel'),'FontSize',12);
set(get(gca,'ZLabel'),'FontSize',12);