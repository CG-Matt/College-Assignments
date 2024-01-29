roomTemp = 25;
initialTemp = 100;

form1 = roomTemp + (initialTemp - roomTemp) * exp(-0.1 * t);
form2 = roomTemp + (initialTemp - roomTemp) * exp(-1 * t);
form3 = roomTemp + (initialTemp - roomTemp) * exp(-0.01 * t);
form4 = initialTemp * sin(t);

plot(TimeElapsed, LiquidTemperature, "c"); hold on;
plot(t, form1, "r");
plot(t, form2, "g");
plot(t, form3, "b");
plot(t, form4, "k");
xlabel("Time (m)");
ylabel("Temperature (°C)");
title("Temperature over time");
legend("Given", "k = 0.1", "k = 1", "k = 0.01", "T(t) = To sin(t)");