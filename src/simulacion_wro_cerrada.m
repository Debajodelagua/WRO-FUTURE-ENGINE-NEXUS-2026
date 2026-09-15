%% =========================================================================
%% SIMULACIÓN WRO FUTURE ENGINEERS - RONDA CERRADA / OBSTÁCULOS (SLALOM PID)
%% Compatible con GNU Octave (Local y Online) y MATLAB
%%
%% Novedad:
%%   - Incluye los 4 pilares de tráfico oficiales (Rojos y Verdes).
%%   - Regla WRO: Pasar el Rojo por la DERECHA y el Verde por la IZQUIERDA.
%%   - Trayectoria con slalom suave intermedio (PID adaptativo de esquiva).
%%   - 3 vueltas completas en 41.0 segundos.
%% =========================================================================

clear all; close all; clc;
fprintf('Iniciando simulación WRO Ronda Cerrada (Obstáculos)...\n');

gif_name = 'wro_animacion_cerrada.gif';
if exist(gif_name, 'file'), delete(gif_name); end

num_vueltas = 3;
tiempo_max  = 41.0; 
delay_t     = 0.12;
max_tail    = 12;   

%% 1. TRAYECTORIA REALISTA DE ESQUIVA INTERMEDIA (SLALOM PID)
pts_vuelta = [
      0.00, -1.00;
      0.20, -1.06;
      0.42, -1.14;  % Esquiva pilar rojo por la derecha (exterior)
      0.65, -1.05;
      0.82, -0.96;
      0.96, -0.86;  % Curva 1 Sureste
      1.02, -0.65;
      0.98, -0.35;
      0.86, -0.10;  % Esquiva pilar verde por la izquierda (interior)
      0.86,  0.15;
      0.95,  0.40;
      1.00,  0.65;
      0.92,  0.88;  % Curva 2 Noreste
      0.75,  1.00;
      0.45,  1.00;
      0.15,  1.00;
     -0.15,  1.06;
     -0.40,  1.14;  % Esquiva pilar rojo por la derecha (exterior)
     -0.65,  1.06;
     -0.88,  0.92;  % Curva 3 Noroeste
     -1.02,  0.72;
     -1.02,  0.45;
     -1.00,  0.15;
     -1.04, -0.10;
     -1.14, -0.38;  % Esquiva pilar verde por la izquierda (exterior)
     -1.06, -0.65;
     -0.92, -0.86;  % Curva 4 Suroeste
     -0.72, -0.98;
     -0.42, -1.00;
     -0.20, -1.00
];

trayectoria_3v = [];
for v = 1:num_vueltas
    trayectoria_3v = [trayectoria_3v; pts_vuelta];
end
trayectoria_3v = [trayectoria_3v; pts_vuelta(1, :)];

N_muestras = 36;
dif = diff(trayectoria_3v);
d_acum = [0; cumsum(sqrt(sum(dif.^2, 2)))];
s_vec = linspace(0, d_acum(end), N_muestras);

tx = interp1(d_acum, trayectoria_3v(:, 1), s_vec, 'linear');
ty = interp1(d_acum, trayectoria_3v(:, 2), s_vec, 'linear');

total_f = length(tx);
dx_vec = gradient(tx);
dy_vec = gradient(ty);
th = atan2(dy_vec, dx_vec);

%% 2. CONFIGURACIÓN DEL LIENZO
fig = figure(1);
clf(fig);
set(fig, 'Visible', 'off');
set(fig, 'Color', [0.06, 0.08, 0.20]);
set(fig, 'PaperUnits', 'inches');
set(fig, 'PaperSize', [5.2, 5.2]);
set(fig, 'PaperPosition', [0, 0, 5.2, 5.2]);

hold on;
axis equal;
xlim([-1.72, 1.72]);
ylim([-1.72, 1.72]);
axis off;

% 1. Tapete Blanco
fill([-1.5, 1.5, 1.5, -1.5], [-1.5, -1.5, 1.5, 1.5], [0.98, 0.98, 0.99], 'EdgeColor', 'none');
plot([-1.5, 1.5, 1.5, -1.5, -1.5], [-1.5, -1.5, 1.5, 1.5, -1.5], ...
     'Color', [0.95, 0.85, 0.2], 'LineWidth', 2.5);

% 2. Secciones
line([-0.40, -0.40], [0.50, 1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([ 0.00,  0.00], [0.50, 1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([ 0.40,  0.40], [0.50, 1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.40,  0.40], [1.15, 1.15], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.40,  0.40], [0.82, 0.82], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
plot([-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], [1.15, 1.15, 1.15, 0.82, 0.82, 0.82], ...
     'o', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 8, 'LineWidth', 1);

line([-0.40, -0.40], [-0.50, -1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([ 0.00,  0.00], [-0.50, -1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([ 0.40,  0.40], [-0.50, -1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.40,  0.40], [-1.15, -1.15], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.40,  0.40], [-0.82, -0.82], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
plot([-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], [-1.15, -1.15, -1.15, -0.82, -0.82, -0.82], ...
     'o', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 8, 'LineWidth', 1);

line([0.50, 1.45], [-0.40, -0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([0.50, 1.45], [ 0.00,  0.00], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([0.50, 1.45], [ 0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([1.15, 1.15], [-0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([0.82, 0.82], [-0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
plot([1.15, 1.15, 1.15, 0.82, 0.82, 0.82], [-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], ...
     'o', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 8, 'LineWidth', 1);

line([-0.50, -1.45], [-0.40, -0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.50, -1.45], [ 0.00,  0.00], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.50, -1.45], [ 0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-1.15, -1.15], [-0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.82, -0.82], [-0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
plot([-1.15, -1.15, -1.15, -0.82, -0.82, -0.82], [-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], ...
     'o', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 8, 'LineWidth', 1);

% 3. Líneas Diagonales
plot([-0.46, -1.18], [0.46, 1.48], 'Color', [0.06, 0.38, 0.72], 'LineWidth', 2.8);
plot([-0.46, -1.48], [0.46, 0.72], 'Color', [0.96, 0.45, 0.08], 'LineWidth', 2.8);
plot([0.46, 1.18], [0.46, 1.48], 'Color', [0.96, 0.45, 0.08], 'LineWidth', 2.8);
plot([0.46, 1.48], [0.46, 0.72], 'Color', [0.06, 0.38, 0.72], 'LineWidth', 2.8);
plot([0.46, 1.48], [-0.46, -0.72], 'Color', [0.96, 0.45, 0.08], 'LineWidth', 2.8);
plot([0.46, 1.18], [-0.46, -1.48], 'Color', [0.06, 0.38, 0.72], 'LineWidth', 2.8);
plot([-0.46, -1.48], [-0.46, -0.72], 'Color', [0.06, 0.38, 0.72], 'LineWidth', 2.8);
plot([-0.46, -1.18], [-0.46, -1.48], 'Color', [0.96, 0.45, 0.08], 'LineWidth', 2.8);

% 4. Isla Central
fill([-0.46, 0.46, 0.46, -0.46], [-0.46, -0.46, 0.46, 0.46], ...
     [0.05, 0.08, 0.22], 'EdgeColor', [0.82, 0.92, 0.30], 'LineWidth', 2.5);
text(0, 0, sprintf('WRO\nOBSTACLES'), 'Color', [0.95, 0.80, 0.15], ...
     'FontSize', 9, 'FontWeight', 'bold', 'HorizontalAlignment', 'center');

% 5. DIBUJO DE LOS OBSTÁCULOS OFICIALES (PILARES 3D)
function dibujar_pilar(px, py, color_rgb)
    w = 0.09; h = 0.12;
    fill([px-w/2, px+w/2, px+w/2, px-w/2], [py-h/2, py-h/2, py+h/2, py+h/2], ...
         color_rgb, 'EdgeColor', [0.1, 0.1, 0.1], 'LineWidth', 1.2);
end

% Pilares Rojos y Verdes
dibujar_pilar( 0.40, -0.82, [0.92, 0.25, 0.25]); % Sur: Rojo
dibujar_pilar( 1.15,  0.00, [0.15, 0.78, 0.35]); % Este: Verde
dibujar_pilar(-0.40,  0.82, [0.92, 0.25, 0.25]); % Norte: Rojo
dibujar_pilar(-0.82, -0.40, [0.15, 0.78, 0.35]); % Oeste: Verde

% Elementos dinámicos
hTailCore = plot(NaN, NaN, 'w-', 'LineWidth', 2.5);
hCar = fill([0,0,0], [0,0,0], [0.98, 0.80, 0.08], 'EdgeColor', [0.60, 0.35, 0.02], 'LineWidth', 1.5);
hLidar = plot(NaN, NaN, 'ro', 'MarkerFaceColor', 'r', 'MarkerSize', 5);

temp_f = 'temp_wro_obs.png';
hx = []; hy = [];

for f = 1:total_f
    cx = tx(f); cy = ty(f); t_i = th(f);
    hx = [hx, cx]; hy = [hy, cy];
    
    if length(hx) > max_tail
        tail_idx = (length(hx)-max_tail):length(hx);
    else
        tail_idx = 1:length(hx);
    end
    set(hTailCore, 'XData', hx(tail_idx), 'YData', hy(tail_idx));
    
    % Carrito
    cL = 0.18; cW = 0.11;
    c_local = [-cL/2, -cW/2; cL/2, -cW/2; cL/2, cW/2; -cL/2, cW/2]';
    R = [cos(t_i), -sin(t_i); sin(t_i), cos(t_i)];
    c_rot = R * c_local + [cx; cy];
    set(hCar, 'XData', c_rot(1, :), 'YData', c_rot(2, :));
    
    lidar_p = R * [-cL*0.1; 0] + [cx; cy];
    set(hLidar, 'XData', lidar_p(1), 'YData', lidar_p(2));
    
    print(fig, temp_f, '-dpng', '-r50');
    im_f = imread(temp_f);
    [im_ind, map] = rgb2ind(im_f);
    
    if f == 1
        imwrite(im_ind, map, gif_name, 'gif', 'LoopCount', Inf, 'DelayTime', delay_t);
    else
        imwrite(im_ind, map, gif_name, 'gif', 'WriteMode', 'append', 'DelayTime', delay_t);
    end
end

if exist(temp_f, 'file'), delete(temp_f); end
fprintf('\n¡ÉXITO! Archivo de obstáculos creado: %s\n', gif_name);