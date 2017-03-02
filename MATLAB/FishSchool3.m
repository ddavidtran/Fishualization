clc;
clear;
close all;

%% Problem Definition

CostFunction = @(x,q) Food(x,q); % Cost Function

nVar = 3;   % Number of unknown (decision) variables
            % x is a vector in the nVar-space (3D-space)

VarSize = [1 nVar];   % Matrix size of Decision variables

VarMin = -10; % Lower Bound of Decision variables (arena space)
VarMax = 10;  % Upper Bound of Decision variables (arena space)

%% Parameters of PSO

MaxIt = 12;
SchoolSize = 50;
w = 1;    % Inertia Coefficient 
d = 0.98; % Damping Ratio of Inertia Weight
c1 = 0.5;
c2 = 0.5;

%% Initialization

empty_fish.Pos = [];
empty_fish.Vel = [];
empty_fish.Cost = [];
empty_fish.Best.Pos = [];
empty_fish.Best.Cost = [];

%q = zeros(2,3);
q = get(gca, 'CurrentPoint'); 

% Create school
fish = repmat(empty_fish, SchoolSize, 1);

% Initialize Global Best
GlobalBest.Cost = inf; 

for i = 1:SchoolSize
   
    % Random Starting Positions
    fish(i).Pos = unifrnd(VarMin, VarMax, VarSize);
    
    % Initialize Velocity
    fish(i).Vel = zeros(VarSize);
    
    % Evaluation
    fish(i).Cost = CostFunction(fish(i).Pos, q);
    
    % Update Personal Best
    fish(i).Best.Pos = fish(i).Pos;
    fish(i).Best.Cost = fish(i).Cost;
    
    % Update Global Best
    if fish(i).Best.Cost < GlobalBest.Cost
       GlobalBest = fish(i).Best;
    end
    
end

% Array to hold best cost value on each iteration
BestCosts = zeros(MaxIt, 1);

%% Main loop
dt = 0.1;

Mat = zeros(SchoolSize, 3);


for it=0:0.1:MaxIt
     
    GlobalBest.Cost = inf;
    
    
    for i=1:SchoolSize
        
        fish(i).Best.Cost = inf;
        
        fish(i).Vel = w*d*fish(i).Vel ...
            + c1*rand(VarSize).*(fish(i).Best.Pos - fish(i).Pos) ...
            + c2*rand(VarSize).*(GlobalBest.Pos - fish(i).Pos);
        
        if sum((fish(i).Vel).^2) > 3
            fish(i).Vel = fish(i).Vel/sum((fish(i).Vel).^2);
        end
        
        fish(i).Pos = fish(i).Pos + fish(i).Vel;
        
        fish(i).Cost = CostFunction(fish(i).Pos, q);
        
        if fish(i).Cost < fish(i).Best.Cost
            
            fish(i).Best.Pos = fish(i).Pos;
            fish(i).Best.Cost = fish(i).Cost;
            
             % Update Global Best  
                if fish(i).Best.Cost < GlobalBest.Cost
                GlobalBest = fish(i).Best;
                end
                
        end
        
        Mat(i,:) = fish(i).Pos; 
        
    end
      set (gcf, 'WindowButtonMotionFcn', @mouseMove);
   
  % scatter3(Mat(:,1), Mat(:,2), Mat(:,3));
          q = get(gca, 'CurrentPoint');
      %  q = [a(1), a(2)]
        
        plot(Mat(:,1), Mat(:,2), '*');
  
         %   axis([-10 10 -10 10 -10 10]);
          axis([-10 10 -10 10]);
          pause(dt);

end





