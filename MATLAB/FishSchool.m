clear all;
close all;

FishAmount = 200;
InitialSpeed = 0.1;     % 0 - 1
C1 = 0.9;     % Globalbest coefficient
C2 = 0.005; % Neighbour avoid coefficient
C3 = 0.2;   % Neighbour attraction coefficient
dt = 0.05;   % Time step

RepulsionRadius = 0.07; % Zone of repulsion

%% Initialization 
empty_fish.Pos = [];
empty_fish.Vel = [];
empty_fish.Cost = [];

fish = repmat(empty_fish, FishAmount, 1);
Px = zeros(FishAmount, 3);

for i = 1:FishAmount
   
    % Random Starting Positions
    fish(i).Pos = rand(1,3);
    Px(i,:) = fish(i).Pos;
    % Initialize Velocity
    fish(i).Vel = zeros(1,3);
    
end

BestPos = [0 0 0];
BestCost = inf;
%%

for it = 0:dt:30
    
    NeighbourIdx = knnsearch(Px,Px(:,:),'K',5); % Nearest neighbours
    BestCost = inf;
    
    for i = 1:FishAmount
        
        % Get mouse coordinates
        set(gcf, 'WindowButtonMotionFcn', @mouseMove);
        mousePos = get(gca, 'CurrentPoint');
        mouseVec = [mousePos(1,1) mousePos(1,2) 0];
        %mouseVec = [0 0 0];
        fish(i).Cost = CostFunc(fish(i).Pos, mouseVec);
        
        if (sqrt(sum(fish(i).Pos - fish(NeighbourIdx(i,2)).Pos).^2)) < RepulsionRadius
            Repulsion = 1/sqrt(sum(fish(i).Pos - fish(NeighbourIdx(i,2)).Pos).^2);
            Slowdown = 0.2;
        else
            Repulsion = 0;
            Slowdown = 1;
        end
        % Calculate velocity (Pv) of each fish and position (Px)
        fish(i).Vel = fish(i).Vel + rand()*C1*(BestPos - fish(i).Pos) ...
            + rand()*C2*Repulsion*(fish(i).Pos - fish(NeighbourIdx(i,2)).Pos) ...
            - Slowdown*(rand()*C3*(fish(i).Pos - fish(NeighbourIdx(i,2)).Pos) ...
            - 0.7*rand()*C3*(fish(i).Pos - fish(NeighbourIdx(i,3)).Pos) ...
            - 0.5*rand()*C3*(fish(i).Pos - fish(NeighbourIdx(i,4)).Pos));

        % Cap speed of fish

        if fish(i).Cost < BestCost
            BestCost = fish(i).Cost;
            BestPos = fish(i).Pos;
        end
        
        if sqrt(sum((fish(i).Vel).^2)) > 1.5
             fish(i).Vel = fish(i).Vel / sqrt(sum(fish(i).Vel.^2));
        end
            
        fish(i).Pos = fish(i).Pos + fish(i).Vel*dt;    
        Px(i,:) = fish(i).Pos;
        Vx(i,:) = fish(i).Vel;

    end
        
        % Plot fishes
        %scatter3(Px(:,1), Px(:,2), Px(:,3)); 
        %scatter(Px(:,1), Px(:,2)); 
        %quiver(Px(:,1), Px(:,2),Vx(:,1), Vx(:,2));
        quiver3(Px(:,1), Px(:,2),Px(:,3),Vx(:,1), Vx(:,2), Vx(:,3));
        % Axis follows fish target
        % axis([Pg(1)-1.5 Pg(1)+1.5 Pg(2)-1.5 Pg(2)+1.5 Pg(3)-1.5 Pg(3)+1.5]);
        %axis([-2 2 -2 2])
        axis([-2 2 -2 2 -2 2])
        pause(dt);
end