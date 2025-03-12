close all;
clear all;
fs = 100;
T = 1;
t = 0:1/fs:T;
x = zeros(61,length(t));
for f = 0:5:300
    iter = f/5+1
    disp(['Iteracja: ', num2str(iter), ', Częstotliwość: ', num2str(f), ' Hz']);
    x(iter,:) = sin(2*pi*f*t);
end
figure;
hold on;
plot(t, x(2, :), 'b-', 'LineWidth', 1.5);  % 5 Hz
plot(t, x(22, :), 'g-o', 'MarkerSize', 5); % 105 Hz
plot(t, x(42, :), 'r-o', 'MarkerSize', 5); % 205 Hz
hold off;
grid on;
xlabel('Czas [s]');
ylabel('Amplituda');
title('Porównanie sinusoid: 5 Hz, 105 Hz, 205 Hz');
legend('5 Hz', '105 Hz', '205 Hz');

figure;
hold on;
plot(t, x(20, :), 'b-', 'LineWidth', 1.5);  % 95 Hz
plot(t, x(40, :), 'g-o', 'MarkerSize', 5); % 195 Hz
plot(t, x(60, :), 'r-o', 'MarkerSize', 5); % 295 Hz
hold off;
grid on;
xlabel('Czas [s]');
ylabel('Amplituda');
title('Porównanie sinusoid: 95 Hz, 195 Hz, 295 Hz');
legend('95 Hz', '195 Hz', '295 Hz');

figure;
hold on;
plot(t, x(20, :), 'b-', 'LineWidth', 1.5);  % 95 Hz
plot(t, x(22, :), 'r-o', 'MarkerSize', 5); % 105 Hz
hold off;
grid on;
xlabel('Czas [s]');
ylabel('Amplituda');
title('Porównanie sinusoid: 95 Hz vs 105 Hz');
legend('95 Hz', '105 Hz');