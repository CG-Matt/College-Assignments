Stress = ForceN/100;
Strain = Displacementmm/10;

AverageX = sum(Strain)/length(Strain);
AverageY = sum(Stress)/length(Stress);

Modulus = polyfit(Strain, Stress, 1);

plot(Strain, Stress, 'b');
xlabel("Strain");
ylabel("Stress (N/mm2)");
title("Stress vs. Strain Graph");
