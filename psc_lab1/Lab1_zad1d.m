clear all;
close all;
T = 1;
fpr = 10000;
fn = 50;
fm = 1;
df = 5;
t = 0:1/fpr:T;
m_t = sin(2*pi*fm*t);
y_t = sin(2*pi*fn*t+2*pi*df*cumsum(m_t)/fpr);
% Wykres sygna�u modulowanego i moduluj�cego
figure;
subplot(2,1,1);
plot(t, m_t, 'r'); hold on;
plot(t, y_t, 'b');
legend('Sygna� moduluj�cy', 'Sygna� FM');
title('Sygna� moduluj�cy i zmodulowany');
xlabel('Czas [s]'); ylabel('Amplituda'); grid on;

fs2 = 25;
t2 = 0:1/fs2:T;
y_t2 = sin(2*pi*fn*t2+2*pi*df*cumsum(sin(2*pi*fm*t2)/fs2));
% Wykres por�wnania sygna�u analogowego i pr�bkowanego
subplot(2,1,2);
plot(t, y_t, 'b'); hold on;
stem(t2, y_t2, 'r');
legend('Sygna� analogowy', 'Sygna� pr�bkowany');
title('Por�wnanie sygna�u analogowego i pr�bkowanego');
xlabel('Czas [s]'); ylabel('Amplituda'); grid on;
% Obliczenie b��d�w pr�bkowania
errors = interp1(t2, y_t2, t, 'nearest', 'extrap') - y_t;

% Wykres b��d�w pr�bkowania
figure;
plot(t, errors, 'k');
title('B��dy spowodowane pr�bkowaniem');
xlabel('Czas [s]'); ylabel('B��d'); grid on;
% Widma g�sto�ci mocy przed i po pr�bkowaniu
figure;
subplot(2,1,1);
pspectrum(y_t, fpr);
title('Widmo g�sto�ci mocy sygna�u przed pr�bkowaniem');

subplot(2,1,2);
pspectrum(y_t2, fs2);
title('Widmo g�sto�ci mocy sygna�u po pr�bkowaniu');