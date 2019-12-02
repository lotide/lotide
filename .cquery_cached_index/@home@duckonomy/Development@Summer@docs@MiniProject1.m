% *********************************************************************
% 
% ME123 Winter 2013-2014
% Mini Project 1

% This script analyzes pressure data from a tornado simulator experiment.
% It plots raw pressures, it integrates and plots forces in x, y, z
% directions. It computes 3-sec moving averages of the forces and plots
% them. And finally, it estimates the full-scale x, y, z forces from the 
% maximum magnitudes of the 3-sec moving average vectors. 
% 

% Fred L. Haan, Jr.
% Dec 27, 2013


clear
clc


% ========================================================================
%
% Day 1 - Download the data and plot raw pressures
%


% Initialize parameters
%
dt = 1/430; % sec -- this is the sampling interval 


% 
% Load the data file
%
load pressuredata
p = SCAN0; % Pa -- use a more convenient variable for pressure

[Nrows,Ncols] = size(p);


 
% Create a time vector for plotting
% 
t = 0;
for i = 1:Nrows
    time_vec(i,1) = t;
    t = t + dt;
end




% Extract the specific signals for plotting
%
p5 = p(:,5);
p66 = p(:,66);
p14 = p(:,14);



% Plot the pressure signals:
%
figure(1)
clf

plot(time_vec,p5,time_vec,p14,time_vec,p66)
legend('Center of Side Wall','Center of Rear Wall','Center of Roof Peak')
xlabel('Time (sec)')
ylabel('Pressure (Pa)')

% ========================================================================









% ========================================================================
%
% Day 2 - Integrate pressures over the building to get forces
%


 
% Load the projected areas file
%
load projectedareas



% Generated Fx, Fy, Fz vectors using the pressures and the projected areas:
%
for row = 1:Nrows
    
    Fx = 0;
    Fy = 0;
    Fz = 0;
    
    for col = 1:Ncols
        Fx = Fx - p(row,col) * Area(1,col);
        Fy = Fy - p(row,col) * Area(2,col);
        Fz = Fz - p(row,col) * Area(3,col);
    end
    
    Fx_vec(row,1) = Fx;
    Fy_vec(row,1) = Fy;
    Fz_vec(row,1) = Fz;
    
end




% Plot the force signals:
%
figure(2)
clf

plot(time_vec,Fx_vec,time_vec,Fy_vec,time_vec,Fz_vec)
legend('Fx','Fy','Fz')
xlabel('Time (sec)')
ylabel('Force (N)')


% ========================================================================

% ========================================================================
%
% Day 3 - Compute a moving average of the force signals
%



% Set # of points to be included in the moving average
Navg = 31; % We will average +31 and -31 from the point i


% These are the starting and ending points of the new moving average
% vector--we will just ignore the first Navg and the last Navg points of the
% original vector
istart = Navg + 1;
iend = Nrows - Navg;

index = 1;
for i = istart:iend
    t_avg(index) = time_vec(i);
    
    Fx_avg = 0;
    Fy_avg = 0;
    Fz_avg = 0;
    for row = (i-Navg):(i+Navg)
        Fx_avg = Fx_avg + Fx_vec(row);
        Fy_avg = Fy_avg + Fy_vec(row);
        Fz_avg = Fz_avg + Fz_vec(row);
    end
    
    Fx_avg_vec(index) = Fx_avg / (2*Navg+1);
    Fy_avg_vec(index) = Fy_avg / (2*Navg+1);
    Fz_avg_vec(index) = Fz_avg / (2*Navg+1);
    
    index = index + 1;
    
end

figure(3)
clf


plot(t_avg,Fx_avg_vec,t_avg,Fy_avg_vec,t_avg,Fz_avg_vec)
legend('Fx','Fy','Fz')
xlabel('Time (sec)')
ylabel('3-sec Moving Average Force (N)')


% ========================================================================
%
% Day 4 - Find maximum forces
%
Fx_max = max(abs(Fx_avg_vec));
Fy_max = max(abs(Fy_avg_vec));
Fz_max = max(abs(Fz_avg_vec));

% Find full-scale values for each component of the force:
Lscale = 1/100; % length scale
Vscale = 1/5;   % velocity scale
Fx_max_FS = Fx_max / Vscale^2 / Lscale^2;
Fy_max_FS = Fy_max / Vscale^2 / Lscale^2;
Fz_max_FS = Fz_max / Vscale^2 / Lscale^2;

fprintf('The maximum x-direction force is %7.1f N \n',Fx_max_FS)
fprintf('The maximum y-direction force is %7.1f N \n',Fy_max_FS)
fprintf('The maximum z-direction force is %7.1f N \n',Fz_max_FS)
