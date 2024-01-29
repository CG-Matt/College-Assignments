%% Q1
clc
clear
for i = 1 : 4
    x = 9*i + 4;
    disp("The new value of x is");disp(x);
end

%% Q2
clc
clear
loopcount = 0;
for p = 39 : -3 : -60
    disp("The new value of p is");disp(p);
    y = p^3 + 6;
    disp("The new value of y is");disp(y);
    loopcount = loopcount + 1;
    disp("We have now gone through the loop");disp(loopcount);disp("times");
end

disp("We have now exited the for loop");
disp("The loop was completed");disp(loopcount);disp("times");

%% Q3
clc
clear
for i = 1 : 100
    x(i) = i/100;
    y(i) = i^2 + 2*i + 3;
end

plot(x, y);
xlabel("X");
ylabel("Y");
title("Student_Name Student_Number");

%% Q4
clc
clear
idx = 1;
theta_vec = zeros(100, 1);
y = zeros(100, 1);
for theta = linspace(-2*pi,2*pi,100)
    theta_vec(idx) = theta;
    y(idx) = sin(theta)*cos(theta) - 4*sin(theta);
    idx = idx + 1;
end

plot(theta_vec, y);
xlabel("Theta");
ylabel("Y");
title("Student_Name Student_Number"); 

%% Q5
clc
clear
A = zeros(4,3);
for i = 1 : 4
    for j = 1 : 3
        A(i,j) = 1/(i+2*j);
    end
end

B = zeros(4,3);
for i = 1 : 4
    for j = 1 : 3
        B(i,j) = 4*i - 3*j;
    end
end

C = zeros(4,3);
for i = 1 : 4
    for j = 1 : 3
        C(i,j) = A(i,j) * B(i,j) + 2*A(i,j);
    end
end

A
B
C

%% Q6
clc
clear
A = [1 3 5; 7 9 11; 13 15 17];
B = [2 4 6; 8 10 12; 14 16 18];
C = A.*B;
D = zeros(3);
for i = 1 : 3
    for j = 1 : 3
        D(i,j) = A(i,j) * B(i,j);
        if C(i,j) ~= D(i,j)
            disp("WARNING: Product in D is not the dot product");
        end
    end
end

A
B
D

%% Q7
clc
clear
A = [1 3 5; 7 9 11; 13 15 17];
B = [2 4 6; 8 10 12; 14 16 18];
C = zeros(3);
D = A*B;
for i = 1 : 3
    for j = 1 : 3
        for k = 1 : 3
            C(i,j) = C(i,j) + A(i,k) * B(k,j);
        end
        if C(i,j) ~= D(i,j)
            disp("WARNING: Product in C is not the matrix product");
        end
    end
end

A
B
C
D
%% Q8
clc % Clearing the console
clear % Clearing the workspace
T = zeros(1, 201); % Pre=allocating T to save time
T(1) = 50; % Assigning the starting temperature of the drink to the first entry of T
K = 0.045; % Assigning the conduction coefficient to K
F = 5; % Assigning the ambient temperature of the room to F
% For loop to calculate the value of T(i) using the given formula
for i = 1 : 200
    T(i+1) = T(i) + K * (F - T(i));
end
time = 0:200; % Defining the time domain
% Plotting the graph, labeling the axes and titling the graph
plot(time, T);
xlabel("time (minutes)");
ylabel("Temperature(deg C)");
title("Student_Name Student_Number");