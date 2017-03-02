function z = Food(x,q)
        
        u = zeros(1,2);

        u(1,1) = x(1,1) - q(1,1);
        u(1,2) = x(1,2) - q(1,2);     
        
        z = sum(u.^2);

end

