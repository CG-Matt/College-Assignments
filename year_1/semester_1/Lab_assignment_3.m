clear 
clc

% Q1
colon_vec = 0:250/19:250;
linspace_vec = linspace(0,250,20);

% Q2
v = [3 4 5 6]
v_t = v'

% Q3
x=[1 2 3 4 5];

%x1 = x.*x
%x2 = x'*x
%x3 = x*x'
%x4 = x*x

% Q4
dot_product = x*x';

% Q5
clear
clc
x = linspace(-10,10,10);
y = x.^2;
plot(x, y, 'k');
xlabel("x");
ylabel("y");
title("Student_Name Student_Number");

% Q6
clear
clc
theta = linspace(0, 2, 4);
y = sin(theta);
plot(theta, y, 'r');
xlabel("θ");
ylabel("Sin(θ)");
title("Student_Name Student_Number");

% Q7
clear
clc
theta = linspace(0, 2, 100);
y = sin(theta);
plot(theta, y, 'r');
xlabel("θ");
ylabel("Sin(θ)");
title("Student_Name Student_Number");

% Q8
% There are not enough data points in Q6 to produce an accurate sin wave

% Q9
clear
clc
theta = linspace(0, 2, 100);
y = theta.*cos(theta);
plot(theta, y, 'r');
xlabel("θ");
ylabel("θ * Cos(θ)");
title("Student_Name Student_Number");

% Q10
A = [1 3 5;2 4 6];
% B = A+A'; % Does not work, A would need to be a n*n vector for this command

% Q11
C = A.*A;
% This is not the matrix product this is the dot product

% Q12
clear
clc
X = [1 2 3;4 5 6];
Y = [2 4 6;5 7 9;1 2 3];

% X.*Y No - Incompatible size
XY = X*Y % Yes
% Y*X No - Incorrect dimensions for matrix multiplication
% Y'*X % No - Incompatible size
% X'*Y' % No - Incompatible size
% Y*X' % No - Incompatible size
%G b is the matrix product
len_X = length(X);
len_Y = length(Y);
% XY has a size of 2 x 3 - Check again

% Q13
clear
clc
A = [4 6 9;1 3 4;6 2 4];
B = [1 2 3;5 6 7;6 8 10];

C = A.*B
C(2, 3)
% Asking how the element was calculated form the original A and B vectors
A.*B % is the dot product of the vectors
D = A*B % Not the same as matrix C
D(2, 3)
% Asking how the element was calculated form the original A and B vectors
% A*B is the matrix product of the vectors

% Q14
A = [4 6 9;1 3 4; 6 2 4];
x = [1 4 9];
A.*x % Yes we can calculate it
% A*x No we cannot calculate it - The dimensions are incorrect for matrix
% multiplication
A*x' % Yes

% Q15
A = [4 6 9;1 3 4;6 2 4];
y = [2;4;8];
A*y % Yes a column vector with [104;46;52]
% y*A No - The dimensions are incorrect for matrix multiplication