%% =========================================================================
%% SIMULACIÓN CARRITO WRO FUTURE ENGINEERS - RONDA ABIERTA (EDICIÓN OFICIAL)
%% Distribución exacta por orientación (como la foto de acercamiento):
%%   - Cada orientación (Norte, Sur, Este, Oeste) tiene 6 posiciones oficiales
%%   - Dispuestas en 2 filas de 3 casillas (fila exterior e interior)
%%   - 3 líneas punteadas verticales y 2 líneas punteadas horizontales por lado
%%   - Casillas con círculo exterior y cuadrado interior
%%   - Movimiento realista con desvíos y correcciones PID de carril
%%   - 3 vueltas en 41 segundos máximos
%%   - Estela con desvanecimiento gradual que persigue al robot
%% =========================================================================

clear all; close all; clc;
fprintf('Iniciando simulación WRO (6 Secciones por Orientación)...\n');

gif_name = 'wro_animacion.gif';
if exist(gif_name, 'file'), delete(gif_name); end

num_vueltas = 3;
tiempo_max  = 41.0; 
delay_t     = 0.12;
max_tail    = 12;   

%% 1. TRAYECTORIA REALISTA CON CONTROL PID CALIBRADO (3 VUELTAS)
% Carril centrado en 1.0 m. Única perturbación sutil en la recta Este (+4 cm a la derecha)
% con rápida y suave corrección crítica PID.
pts_vuelta = [
     0.00, -1.00;   % Recta Sur (Meta)
     0.25, -1.00;
     0.50, -1.00;
     0.75, -1.00;
     0.92, -0.92;   % Curva 1 Sureste
     1.00, -0.75;
     1.00, -0.50;
     1.00, -0.25;   % Recta Este: ÚNICA SECCIÓN con micro-desvío
     1.04, -0.05;   % Micro-desvío sutil (+4 cm a la derecha)
     1.01,  0.15;   % Corrección PID suave (Kd amortiguado)
     1.00,  0.35;   % Retorno perfecto al centro
     1.00,  0.55;
     0.92,  0.92;   % Curva 2 Noreste
     0.75,  1.00;
     0.50,  1.00;
     0.25,  1.00;   % Recta Norte
     0.00,  1.00;
    -0.25,  1.00;
    -0.50,  1.00;
    -0.92,  0.92;   % Curva 3 Noroeste
    -1.00,  0.75;
    -1.00,  0.50;
    -1.00,  0.25;   % Recta Oeste
    -1.00,  0.00;
    -1.00, -0.25;
    -1.00, -0.50;
    -0.92, -0.92;   % Curva 4 Suroeste
    -0.75, -1.00;
    -0.50, -1.00;
    -0.25, -1.00
];

trayectoria_3v = [];
for v = 1:num_vueltas
    trayectoria_3v = [trayectoria_3v; pts_vuelta];
end
trayectoria_3v = [trayectoria_3v; [0.00, -1.00]];

N_muestras = 36;
dif = diff(trayectoria_3v);
d_acum = [0; cumsum(sqrt(sum(dif.^2, 2)))];
s_vec = linspace(0, d_acum(end), N_muestras);

tx = interp1(d_acum, trayectoria_3v(:, 1), s_vec, 'linear');
ty = interp1(d_acum, trayectoria_3v(:, 2), s_vec, 'linear');

total_f = length(tx);
dx = gradient(tx);
dy = gradient(ty);
th = atan2(dy, dx);

%% 2. CONFIGURACIÓN DEL LIENZO Y DIBUJO DE LAS 6 SECCIONES (2 FILAS DE 3)
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

% 1. Tapete Blanco con Borde Dorado
fill([-1.5, 1.5, 1.5, -1.5], [-1.5, -1.5, 1.5, 1.5], [0.98, 0.98, 0.99], 'EdgeColor', 'none');
plot([-1.5, 1.5, 1.5, -1.5, -1.5], [-1.5, -1.5, 1.5, 1.5, -1.5], ...
     'Color', [0.95, 0.85, 0.2], 'LineWidth', 2.5);

% 2. DIBUJO EXACTO DE LAS 6 SECCIONES POR ORIENTACIÓN (2 FILAS DE 3)
% --- NORTE ---
line([-0.40, -0.40], [0.50, 1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([ 0.00,  0.00], [0.50, 1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([ 0.40,  0.40], [0.50, 1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.40,  0.40], [1.15, 1.15], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.40,  0.40], [0.82, 0.82], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);

plot([-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], [1.15, 1.15, 1.15, 0.82, 0.82, 0.82], ...
     'o', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 8, 'LineWidth', 1);
plot([-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], [1.15, 1.15, 1.15, 0.82, 0.82, 0.82], ...
     's', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 5.5, 'LineWidth', 1);

% --- SUR ---
line([-0.40, -0.40], [-0.50, -1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([ 0.00,  0.00], [-0.50, -1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([ 0.40,  0.40], [-0.50, -1.45], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.40,  0.40], [-1.15, -1.15], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.40,  0.40], [-0.82, -0.82], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);

plot([-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], [-1.15, -1.15, -1.15, -0.82, -0.82, -0.82], ...
     'o', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 8, 'LineWidth', 1);
plot([-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], [-1.15, -1.15, -1.15, -0.82, -0.82, -0.82], ...
     's', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 5.5, 'LineWidth', 1);

% --- ESTE ---
line([0.50, 1.45], [-0.40, -0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([0.50, 1.45], [ 0.00,  0.00], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([0.50, 1.45], [ 0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([1.15, 1.15], [-0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([0.82, 0.82], [-0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);

plot([1.15, 1.15, 1.15, 0.82, 0.82, 0.82], [-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], ...
     'o', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 8, 'LineWidth', 1);
plot([1.15, 1.15, 1.15, 0.82, 0.82, 0.82], [-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], ...
     's', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 5.5, 'LineWidth', 1);

% --- OESTE ---
line([-0.50, -1.45], [-0.40, -0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.50, -1.45], [ 0.00,  0.00], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.50, -1.45], [ 0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-1.15, -1.15], [-0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);
line([-0.82, -0.82], [-0.40,  0.40], 'Color', [0.80, 0.84, 0.90], 'LineStyle', ':', 'LineWidth', 1);

plot([-1.15, -1.15, -1.15, -0.82, -0.82, -0.82], [-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], ...
     'o', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 8, 'LineWidth', 1);
plot([-1.15, -1.15, -1.15, -0.82, -0.82, -0.82], [-0.40, 0.00, 0.40, -0.40, 0.00, 0.40], ...
     's', 'Color', [0.65, 0.70, 0.80], 'MarkerSize', 5.5, 'LineWidth', 1);

% 3. Líneas diagonales reglamentarias idénticas al PDF oficial:
line([-0.46, -1.18], [0.46, 1.48],  'Color', [0.06, 0.38, 0.72], 'LineWidth', 2.8);
line([-0.46, -1.48], [0.46, 0.72],  'Color', [0.96, 0.45, 0.08], 'LineWidth', 2.8);
line([0.46, 1.18],   [0.46, 1.48],  'Color', [0.96, 0.45, 0.08], 'LineWidth', 2.8);
line([0.46, 1.48],   [0.46, 0.72],  'Color', [0.06, 0.38, 0.72], 'LineWidth', 2.8);
line([0.46, 1.48],   [-0.46, -0.72],'Color', [0.96, 0.45, 0.08], 'LineWidth', 2.8);
line([0.46, 1.18],   [-0.46, -1.48],'Color', [0.06, 0.38, 0.72], 'LineWidth', 2.8);
line([-0.46, -1.48], [-0.46, -0.72],'Color', [0.06, 0.38, 0.72], 'LineWidth', 2.8);
line([-0.46, -1.18], [-0.46, -1.48],'Color', [0.96, 0.45, 0.08], 'LineWidth', 2.8);

% 4. Isla Central Oficial con marco verde lima
fill([-0.46, 0.46, 0.46, -0.46], [-0.46, -0.46, 0.46, 0.46], [0.03, 0.05, 0.18], 'EdgeColor', 'none');
plot([-0.46, 0.46, 0.46, -0.46, -0.46], [-0.46, -0.46, 0.46, 0.46, -0.46], ...
     'Color', [0.82, 0.92, 0.30], 'LineWidth', 3);

text(0, 0.12, 'WRO', 'HorizontalAlignment', 'center', ...
     'FontSize', 12, 'FontWeight', 'bold', 'Color', [1.0, 0.85, 0.1]);
text(0, -0.04, 'FUTURE', 'HorizontalAlignment', 'center', ...
     'FontSize', 8, 'FontWeight', 'bold', 'Color', [1, 1, 1]);
text(0, -0.16, 'ENGINEERS', 'HorizontalAlignment', 'center', ...
     'FontSize', 8, 'FontWeight', 'bold', 'Color', [0.2, 0.75, 1.0]);

% Línea de Meta
line([0, 0], [-1.48, -0.46], 'Color', [1.0, 0.5, 0.0], 'LineWidth', 3.5);

% Estela dinámica
hTrailGlow = plot(NaN, NaN, '-', 'Color', [0.3, 0.8, 1.0], 'LineWidth', 5);
hTrail     = plot(NaN, NaN, '-', 'Color', [0.0, 0.4, 0.95], 'LineWidth', 2.5);

%% 3. CARRITO AMARILLO
hx = 0.17; hy = 0.11;
ch_loc = [-hx, -hy; hx*0.6, -hy; hx, -hy*0.5; hx, hy*0.5; hx*0.6, hy; -hx, hy; -hx, -hy]';
ws_loc = [-hx*0.2, -hy*0.65; hx*0.35, -hy*0.55; hx*0.35, hy*0.55; -hx*0.2, hy*0.65]';
rw_x = 0.05; rw_y = 0.025;
w_shape = [-rw_x, -rw_y; rw_x, -rw_y; rw_x, rw_y; -rw_x, rw_y]';
w_pos = [hx*0.55, hy*1.08; hx*0.55, -hy*1.08; -hx*0.60, hy*1.08; -hx*0.60, -hy*1.08];

%% 4. BUCLE CON ESTELA QUE DESAPARECE
hx_hist = []; hy_hist = [];
temp_png = 'tmp_wro_exact_sections.png';
hCarParts = [];

for i = 1:total_f
    cx = tx(i); cy = ty(i); t_i = th(i);
    hx_hist(end+1) = cx; hy_hist(end+1) = cy;
    
    if length(hx_hist) > max_tail
        idx_ini = length(hx_hist) - max_tail;
        hx_disp = hx_hist(idx_ini:end);
        hy_disp = hy_hist(idx_ini:end);
    else
        hx_disp = hx_hist;
        hy_disp = hy_hist;
    end
    
    set(hTrail, 'XData', hx_disp, 'YData', hy_disp);
    set(hTrailGlow, 'XData', hx_disp, 'YData', hy_disp);
    
    if ~isempty(hCarParts)
        delete(hCarParts);
        hCarParts = [];
    end
    
    R = [cos(t_i), -sin(t_i); sin(t_i), cos(t_i)];
    
    for w = 1:4
        wh_c = R * w_pos(w, :)' + [cx; cy];
        wh_r = R * w_shape + wh_c;
        hW = fill(wh_r(1, :), wh_r(2, :), [0.1, 0.1, 0.1], 'EdgeColor', 'none');
        hCarParts(end+1) = hW;
    end
    
    ch_w = R * ch_loc + [cx; cy];
    hC = fill(ch_w(1, :), ch_w(2, :), [0.98, 0.82, 0.08], 'EdgeColor', [0.4, 0.3, 0], 'LineWidth', 1.8);
    hCarParts(end+1) = hC;
    
    ws_w = R * ws_loc + [cx; cy];
    hG = fill(ws_w(1, :), ws_w(2, :), [0.10, 0.15, 0.25], 'EdgeColor', 'none');
    hCarParts(end+1) = hG;
    
    lidar_p = R * [-hx*0.05; 0] + [cx; cy];
    hL = plot(lidar_p(1), lidar_p(2), 's', 'MarkerFaceColor', [0.1, 0.1, 0.1], ...
              'MarkerEdgeColor', [0.1, 0.6, 1.0], 'MarkerSize', 7);
    hCarParts(end+1) = hL;
    
    f_izq = R * [hx*0.9;  hy*0.48] + [cx; cy];
    f_der = R * [hx*0.9; -hy*0.48] + [cx; cy];
    hF = plot([f_izq(1), f_der(1)], [f_izq(2), f_der(2)], 'o', ...
              'MarkerFaceColor', [1, 1, 0.6], 'MarkerEdgeColor', [0.8, 0.7, 0], 'MarkerSize', 5);
    hCarParts(end+1) = hF;
    
    print(fig, temp_png, '-dpng', '-r60');
    im_f = imread(temp_png);
    [im_ind, map] = rgb2ind(im_f);
    
    if i == 1
        imwrite(im_ind, map, gif_name, 'gif', 'LoopCount', Inf, 'DelayTime', delay_t);
    else
        imwrite(im_ind, map, gif_name, 'gif', 'WriteMode', 'append', 'DelayTime', delay_t);
    end
    
    t_act = (i / total_f) * tiempo_max;
    v_act = min(3, floor((i-1)*3 / total_f) + 1);
    fprintf('Cuadro %d/%d | Vuelta %d/3 | Tiempo: %4.1fs / 41s\n', i, total_f, v_act, t_act);
end

if exist(temp_png, 'file'), delete(temp_png); end

fprintf('\n¡ÉXITO TOTAL! Archivo generado: %s\n', gif_name);
