clc
clear all

n = 10000;

sensores = serial('COM11');
dados = zeros(n,5);
fopen(sensores);


for i = 1:n
    
    a = strsplit(fscanf(sensores),',');
    for j = 1:5
    dados(i,j) = a(j);
    end
    
end

fclose(sensores);

