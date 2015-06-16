function CreateRandonMatrix(dimension,range)
% Creat two random integer only matrix and write them into a txt file
% The argument dimention represents the dimension of the n*n matrix you want to creat
% The argument range represents the range of random number in the matrix

% create two n*n random matrix
A=round(range*rand(dimension));
B=round(range*rand(dimension));

% create the txt file to store randon matrix 
fid = fopen('matrix.txt','wt');

% write matrix A into file
for i=1:dimension
    for j=1:dimension
       if j==dimension
         fprintf(fid,'%g \n',A(i,j));
       else
         fprintf(fid,'%g ',A(i,j)); 
       end   
    end
end

% separate two matrix in a single txt file
fprintf(fid,'\n');

% write matrix B into file
for i=1:dimension
    for j=1:dimension
       if j==dimension
         fprintf(fid,'%g \n',B(i,j));
       else
         fprintf(fid,'%g ',B(i,j)); 
       end   
    end
end
fclose(fid);