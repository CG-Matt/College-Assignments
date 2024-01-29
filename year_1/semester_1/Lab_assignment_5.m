%% Q1
clc
clear
x = input("Enter a value for x: ");
y = input("Enter a value for y: ");
z = input("Enter a value for z: ");

if x > y && x > z
    p = 100;
elseif x < y || x == z
    p = 200;
elseif xor(x > y, x > z)
    p = 300;
elseif x == y && x < z
    p = 400;
elseif x == y && x >= z
    p = 500;
else
    p = 0;
end
p

%% Q2
clc
clear
loopcount = 0;
x = 1;
while x < 1000
    x = 2*x + 3;
    loopcount = loopcount + 1;
end
disp("Executed loop");disp(loopcount);disp("times.");

%% Q3
clc
clear
loopcount = 0;
x = 0;
while x <= 600
    x = x + loopcount + 1;
    loopcount = loopcount + 1;
end
loopcount

loopcount = 0;
x = 0;
okay = true;
while okay
    if(x + loopcount > 7028)
        break
    end
    x = x + loopcount + 1;
    loopcount = loopcount + 1;
end
loopcount

%% Q4
clc
clear
loopcount = 0;
x = 2;
while x < 755250
    x = x * (2 * (loopcount + 2));
    loopcount = loopcount + 1;
end

loopcount

%% Q5
clc
clear
x = linspace(0,1,100);
y1 = 0.5.*x.^5 - 0.6.*x.^4 - 0.6.*x.^3 + 0.3.*x.^2 + 0.25;
y2 = sin(x).*cos(x) + x.^2 - 1;
y3 = 5.*x.*exp(-5.*x)-0.2;

hold on
box on
set(gca, "XTick", linspace(0, 1, 6))
set(gca, "YTick", linspace(-1, 0.5, 16))
plot(x, y1, 'r:')
plot(x, y2, 'b')
plot(x, y3, 'k--')
lgd = legend("y1","y2","y3");
lgd.Location = "southeast";
title("Plot of y1, y2 and y3", "Fontweight", "normal")
xlabel("x")
ylabel("y")

%% Q6
clc
clear
[x, y] = meshgrid(-3:0.2:3);
z = 2.*x.*exp(-x.^2-y.^2);
surf(x, y, z);
colormap(jet);
set(gca, "XTick", -3:1:3);
set(gca, "YTick", -3:1:3);
set(gca, "ZTick", -1:0.2:1);
set(gca, "FontSize", 5);
xlim([-3,3]);
ylim([-3,3]);

%% Q7
clc
clear
P=1;
endVol = 5;
delta_U = 0;
delta_V = 0.1;
V = 1; % Starting volume
W = 0;
while V < endVol
    W = -P * delta_V;
    delta_U = delta_U - W;
    V = V + delta_V;
end
delta_Q = delta_U + W;

delta_Q
delta_U